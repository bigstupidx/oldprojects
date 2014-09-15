package com.cooee.wallpaper.framework;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;

public class AAConfigChooser implements GLSurfaceView.EGLConfigChooser {
	private int eglVersion = 1;
	private boolean withAlpha = true;
	private int bufferSize = 32;
	private final int depth = 16;
	private final int samples = 2; // 多重采样

	public AAConfigChooser(int eglVersion) {
		this(eglVersion, true);
	}

	public AAConfigChooser(int eglVersion, boolean withAlpha) {
		this(eglVersion, withAlpha, 32);
	}

	private AAConfigChooser(int eglVersion, boolean withAlpha,
			int bufferSize) {
		this.eglVersion = eglVersion;
		this.withAlpha = withAlpha;
		this.bufferSize = bufferSize;
	}

	public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
		/**
		 * RGBA: 5550 5651 8880 8888
		 */
		int greenSize = this.withAlpha ? 5 : 6;
		int alphaSize = this.withAlpha ? 1 : 0;
		int redSize = 5;
		int blueSize = 5;

		if (this.bufferSize == 32) {
			redSize = 8;
			blueSize = 8;
			greenSize = 8;
			alphaSize = this.withAlpha ? 8 : 0;
		}

		int[] val = new int[1];

		int[] configSpec = { EGL10.EGL_RED_SIZE, redSize, // red size
				EGL10.EGL_GREEN_SIZE, greenSize, // green size
				EGL10.EGL_BLUE_SIZE, blueSize, // blue size
				EGL10.EGL_ALPHA_SIZE, alphaSize, // alpha size
				EGL10.EGL_DEPTH_SIZE, this.depth, // z depth
				EGL10.EGL_SAMPLE_BUFFERS, 1, // sample buffers
				EGL10.EGL_SAMPLES, this.samples, // sample
				EGL10.EGL_RENDERABLE_TYPE, 4,
				EGL10.EGL_NONE };
		this.fixConfigSpec(configSpec);
		
		if (!egl.eglChooseConfig(display, configSpec, null, 0, val)) {
			error();
		}
		int numConfigs = val[0];
		Logger.log("numConfigs = " + numConfigs);

		if (numConfigs <= 0) {
			int EGL_COVERAGE_BUFFERS_NV = 12512;
			int EGL_COVERAGE_SAMPLES_NV = 12513;
			int EGL_DEPTH_ENCODING_NV = 12514;
			int EGL_DEPTH_ENCODING_NONLINEAR_NV = 12515;

			configSpec = new int[] { EGL10.EGL_RED_SIZE,
					redSize, // red size
					EGL10.EGL_GREEN_SIZE,
					greenSize, // green size
					EGL10.EGL_BLUE_SIZE,
					blueSize, // blue size
					EGL10.EGL_ALPHA_SIZE,
					alphaSize, // alpha size
					EGL10.EGL_DEPTH_SIZE,
					depth, // z depth
					EGL_DEPTH_ENCODING_NV, EGL_DEPTH_ENCODING_NONLINEAR_NV,
					EGL_COVERAGE_BUFFERS_NV, 1, // buffers
					EGL_COVERAGE_SAMPLES_NV, 2, // samples
					EGL10.EGL_RENDERABLE_TYPE, 4, // egl2.0
					EGL10.EGL_NONE };
			this.fixConfigSpec(configSpec);
			
			if (!egl.eglChooseConfig(display, configSpec, null, 0, val)) {
				error();
			}
			numConfigs = val[0];

			if (numConfigs <= 0) {
				Logger.log("No AA config found...defaulting to non-AA modes!");
				configSpec = new int[] { 12324, redSize, 12323, greenSize,
						12322, blueSize, 12321, alphaSize, 12325, depth, 12352,
						4, 12344 };
				this.fixConfigSpec(configSpec);
				
				if (!egl.eglChooseConfig(display, configSpec, null, 0, val)) {
					error();
				}
				numConfigs = val[0];

				if (numConfigs <= 0) {
					error();
				}
				ConfigMode.setAAMode(0);
				Logger.log("No AA enabled!");
			} else {
				ConfigMode.setAAMode(2);
				Logger.log("CSAA enabled!");
			}
		} else {
			ConfigMode.setAAMode(1);
			Logger.log("MSAA enabled with " + samples + " samples!");
		}

		// get all EGLConfigs
		EGLConfig[] configs = new EGLConfig[numConfigs];
		if (!egl.eglChooseConfig(display, configSpec, configs, numConfigs, val)) {
			error();
		}

		// set EGLConfig[0]
		int index = 0;
		EGLConfig config = configs.length > 0 ? configs[index] : null;
		if (config == null) {
			error();
		}
		return config;
	}

	private void error() {
		ConfigMode.setAAMode(0);
		Logger.log("Failed to choose config!", Logger.ERROR);
	}
	
	private void fixConfigSpec(int spec[]) {
		for (int i = 0; i < spec.length; i++) {
			if (spec[i] == EGL10.EGL_RENDERABLE_TYPE) {
				if (this.eglVersion == 1) {
					spec[i] = EGL10.EGL_NONE;
				}
				break;
			}
		}
	}
}