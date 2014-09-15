package com.kivvi.sunflower.android;

import android.view.SurfaceHolder;

import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;
import com.kivvi.sunflower.Sunflower;

public class LiveWallpaperService extends AndroidLiveWallpaperService {
	private Sunflower sunFlower = null;

	@Override
	public void onCreate() {
		super.onCreate();
	}

	@Override
	public void onCreateApplication() {
		super.onCreateApplication();
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useWakelock = true;
		config.numSamples = 4;
		sunFlower = new Sunflower();
		initialize(sunFlower, config);
	}

	@Override
	public Engine onCreateEngine() {
		return new LiveWallpaperServiceEngine();
	}

	class LiveWallpaperServiceEngine extends
			AndroidLiveWallpaperService.AndroidWallpaperEngine {

		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			super.onCreate(surfaceHolder);
		}

		@Override
		public void onResume() {
			super.onResume();
		}

	}

}
