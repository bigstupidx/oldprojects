package com.cooee.wallpaper.garden;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.view.MotionEvent;

import com.cooee.wallpaper.framework.GLWallpaperRenderer;
import com.cooee.wallpaper.framework.Logger;

public class Renderer implements GLWallpaperRenderer {
	private final static String TAG = "Renderer";

	private IRenderer iRenderer;

	public Renderer(Context context) {
		// new garden
		iRenderer = new Garden(context);

		Logger.log(TAG, "new Renderer");
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		iRenderer.onDrawFrame(gl);
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int w, int h) {
		iRenderer.onSurfaceChanged(gl, w, h);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		iRenderer.onSurfaceCreated(gl, config);
	}

	@Override
	public void onOffsetsChanged(float xOffset, float yOffset,
			float xOffsetStep, float yOffsetStep, int xPixelOffset,
			int yPixelOffset) {
	}

	@Override
	public void onTouchEvent(MotionEvent event) {
		iRenderer.onTouchEvent(event);
	}
}
