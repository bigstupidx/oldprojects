package com.cooee.wallpaper.common;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.view.MotionEvent;

import com.cooee.wallpaper.framework.GLWallpaperRenderer;
import com.cooee.wallpaper.framework.Logger;

public class CommonRenderer implements IRenderer, GLWallpaperRenderer {
	private final static String TAG = "CommonRenderer";

	protected IRenderer iRenderer;

	/**
	 * Derived should set the iRenderer.
	 * @param context
	 */
	public CommonRenderer(Context context) {
		Logger.log(TAG, "new CommonRenderer");
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
