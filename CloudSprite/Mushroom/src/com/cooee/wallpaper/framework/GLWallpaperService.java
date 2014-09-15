package com.cooee.wallpaper.framework;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.os.Build;
import android.service.wallpaper.WallpaperService;
import android.view.SurfaceHolder;

public abstract class GLWallpaperService extends WallpaperService {

	public class GLEngine extends Engine {
		private static final String TAG = "GLEngine";

		private WallpaperGLSurfaceView glSurfaceView;
		private boolean rendererHasBeenSet;

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			super.onCreate(surfaceHolder);

			glSurfaceView = new WallpaperGLSurfaceView(GLWallpaperService.this);
		}

		@Override
		public void onVisibilityChanged(boolean visible) {
			super.onVisibilityChanged(visible);

			if (rendererHasBeenSet) {
				if (visible) {
					Logger.log(TAG, "onResume");
					glSurfaceView.onResume();
				} else {
					Logger.log(TAG, "onPause");
					glSurfaceView.onPause();
				}
			}
		}

		@Override
		public void onDestroy() {
			Logger.log(TAG, "onDestroy");
			super.onDestroy();
			glSurfaceView.onDestroy();
		}

		protected void setRenderer(Renderer renderer) {
			glSurfaceView.setRenderer(renderer);
			rendererHasBeenSet = true;
		}

		protected void setEGLContextClientVersion(int version) {
			Logger.log(TAG, "setEGLContextClientVersion(" + version + ")");
			glSurfaceView.setEGLContextClientVersion(version);
			glSurfaceView
					.setEGLConfigChooser(new AAConfigChooser(version, true));
		}

		protected void setPreserveEGLContextOnPause(boolean preserve) {
			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
				Logger.log(TAG, "Build.VERSION.SDK_INT = " + Build.VERSION.SDK_INT);
				Logger.log(TAG, "setPreserveEGLContextOnPause(" + preserve + ")");
				glSurfaceView.setPreserveEGLContextOnPause(preserve);
			}
		}

		class WallpaperGLSurfaceView extends GLSurfaceView {
			private static final String TAG = "WallpaperGLSurfaceView";

			WallpaperGLSurfaceView(Context context) {
				super(context);
			}

			@Override
			public SurfaceHolder getHolder() {
				return getSurfaceHolder();
			}

			public void onDestroy() {
				super.onDetachedFromWindow();
			}
		}
	}

}
