package com.kivvi.livewallpaper.flowerzen.android;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidDaydream;
import com.badlogic.gdx.backends.android.AndroidWallpaperListener;
import com.kivvi.livewallpaper.flowerzen.LWPGame;

public class LWP_Android_Daydream extends AndroidDaydream {
	@Override
	public void onAttachedToWindow() {
		super.onAttachedToWindow();

		final AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useCompass = false;
		config.useWakelock = false;
		config.useAccelerometer = false;
		config.getTouchEventsForLiveWallpaper = false; // No need it in daydream

		final ApplicationListener listener = new WallpaperListener();
		initialize(listener, config);
	}

	public static class WallpaperListener extends LWPGame implements AndroidWallpaperListener {
		@Override
		public void offsetChange (float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {
		}

		@Override
		public void previewStateChange (boolean isPreview) {
		}
	}
}
