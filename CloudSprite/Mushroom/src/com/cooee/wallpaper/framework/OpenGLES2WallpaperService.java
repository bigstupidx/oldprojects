package com.cooee.wallpaper.framework;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

public abstract class OpenGLES2WallpaperService extends GLWallpaperService {
	private final static String TAG = "OpenGLES2WallpaperService";

	@Override
	/**
	 * Create OpenGLES2Engine for default.
	 */
	public Engine onCreateEngine() {
		return new OpenGLES2Engine();
	}

	/**
	 * create OpenGLES1Engine.
	 * 
	 * @return Engine.
	 */
	public Engine createOpenGLES1Engine() {
		return new OpenGLES1Engine();
	}

	class OpenGLESEngine extends GLWallpaperService.GLEngine {

		protected GLWallpaperRenderer renderer;

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			super.onCreate(surfaceHolder);

			Logger.log(TAG, "onCreate");
			
			// Get renderer
			renderer = getNewRenderer();
		}

		@Override
		public void onOffsetsChanged(final float xOffset, final float yOffset,
				final float xOffsetStep, final float yOffsetStep,
				final int xPixelOffset, final int yPixelOffset) {
			super.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep,
					xPixelOffset, yPixelOffset);

			// Log.v(TAG, "yOffset = " + xOffset);
			// Log.v(TAG, "yOffsetStep = " + xOffsetStep);
			// Log.v(TAG, "yPixelOffset = " + xPixelOffset);

			if (!isPreview()) {
				renderer.onOffsetsChanged(xOffset, yOffset, xOffsetStep,
						yOffsetStep, xPixelOffset, yPixelOffset);
			}
		}

		@Override
		public void onTouchEvent(MotionEvent event) {
			super.onTouchEvent(event);

			// if (!isPreview()) {
			renderer.onTouchEvent(event);
			// }
		}
	}

	class OpenGLES1Engine extends OpenGLESEngine {

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			super.onCreate(surfaceHolder);

			// Request an OpenGL ES 1.0 compatible context.
			setEGLContextClientVersion(1);

			// On Honeycomb+ devices, this improves the performance when
			// leaving and resuming the live wallpaper.
			setPreserveEGLContextOnPause(true);
			
			// Set the renderer to our user-defined renderer.
			setRenderer(renderer);
		}
	}

	class OpenGLES2Engine extends OpenGLESEngine {

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			super.onCreate(surfaceHolder);

			// Check if the system supports OpenGL ES 2.0.
			final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
			final ConfigurationInfo configurationInfo = activityManager
					.getDeviceConfigurationInfo();
			final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;

			if (supportsEs2) {
				// Request an OpenGL ES 2.0 compatible context.
				setEGLContextClientVersion(2);

				// On Honeycomb+ devices, this improves the performance when
				// leaving and resuming the live wallpaper.
				setPreserveEGLContextOnPause(true);

				// Set the renderer to our user-defined renderer.
				setRenderer(renderer);
			} else {
				// This is where you could create an OpenGL ES 1.x compatible
				// renderer if you wanted to support both ES 1 and ES 2.
				return;
			}
		}
	}

	public abstract GLWallpaperRenderer getNewRenderer();
}