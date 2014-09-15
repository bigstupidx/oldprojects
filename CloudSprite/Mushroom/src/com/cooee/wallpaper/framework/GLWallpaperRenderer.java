package com.cooee.wallpaper.framework;

import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public interface GLWallpaperRenderer extends GLSurfaceView.Renderer {
	public void onOffsetsChanged(final float xOffset, final float yOffset,
			final float xOffsetStep, final float yOffsetStep,
			final int xPixelOffset, final int yPixelOffset);

	public void onTouchEvent(MotionEvent event);
}
