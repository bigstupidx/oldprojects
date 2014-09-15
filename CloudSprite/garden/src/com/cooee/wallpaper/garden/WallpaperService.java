package com.cooee.wallpaper.garden;

import com.cooee.wallpaper.framework.GLWallpaperRenderer;
import com.cooee.wallpaper.framework.OpenGLES2WallpaperService;

public class WallpaperService extends OpenGLES2WallpaperService {

	public static final boolean useGLES2 = false;

	@Override
	public GLWallpaperRenderer getNewRenderer() {
		return new Renderer(this);
	}

	@Override
	public Engine onCreateEngine() {
		if (useGLES2) {
			return super.onCreateEngine();
		} else {
			return super.createOpenGLES1Engine();
		}
	}
}
