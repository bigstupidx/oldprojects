package com.cooee.wallpaper.common;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.view.MotionEvent;

public interface IRenderer {
	public void onDrawFrame(GL10 gl);

	public void onSurfaceChanged(GL10 gl, int w, int h);

	public void onSurfaceCreated(GL10 gl, EGLConfig config);

	public void onTouchEvent(MotionEvent event);
}
