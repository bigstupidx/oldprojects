package com.cooee.wallpaper.mushroom;

import com.cooee.wallpaper.framework.ConfigMode;
import com.cooee.wallpaper.framework.GLWallpaperRenderer;
import com.cooee.wallpaper.framework.OpenGLES2WallpaperService;
import com.cooee.wallpaper.framework.Logger;

public class WallpaperService extends OpenGLES2WallpaperService {

	public static final boolean useGLES2 = false;
	private boolean enableLog = false;
	private boolean textureCompression = false; // not implement

	@Override
	public GLWallpaperRenderer getNewRenderer() {
		return new Renderer(this);
	}

	@Override
	public Engine onCreateEngine() {
		// catch all exception here
		Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {
			public void uncaughtException(Thread thread, Throwable ex) {
				Logger.log(ex.getMessage(), Logger.WARNING);
			}
		});
		
		// set log level
		if (!enableLog) {
			Logger.setLogLevel(Logger.LL_ONLY_ERRORS);
			Logger.setOnError(Logger.ON_ERROR_RESUME_NEXT);
			com.threed.jpct.Logger.setLogLevel(Logger.LL_ONLY_ERRORS);
			com.threed.jpct.Logger.setOnError(Logger.ON_ERROR_RESUME_NEXT);
		}
		
		// set texture compression
		ConfigMode.setTextureCompression(textureCompression);
		
		// create engine
		if (useGLES2) {
			return super.onCreateEngine();
		} else {
			return super.createOpenGLES1Engine();
		}
	}
}
