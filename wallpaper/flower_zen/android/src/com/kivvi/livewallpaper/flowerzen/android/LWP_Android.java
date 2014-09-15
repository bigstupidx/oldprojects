package com.kivvi.livewallpaper.flowerzen.android;


import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;
import com.badlogic.gdx.backends.android.AndroidWallpaperListener;
import com.kivvi.livewallpaper.flowerzen.LWPGame;
import com.kivvi.livewallpaper.flowerzen.Resolver;
import com.umeng.analytics.MobclickAgent;

public class LWP_Android extends AndroidLiveWallpaperService {
	public static float pixelOffset = 0;

	@Override
	public void onCreateApplication () {
		super.onCreateApplication();

		final AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useCompass = false;
		config.useWakelock = false;
		config.useAccelerometer = false;
		config.getTouchEventsForLiveWallpaper = true;

		final ApplicationListener listener = new WallpaperListener();
		LWPGame.setStatisticsService(new AndroidAnalyticsService(this));
		initialize(listener, config);
	}

	@Override
	public void onCreate() {
		MobclickAgent.updateOnlineConfig(this);
		super.onCreate();
	}
	

	public static class WallpaperListener extends LWPGame implements AndroidWallpaperListener {
		@Override
		public void create() {
			super.resolver = new Resolver() {
				@Override
				public float getxPixelOffset() {
					return pixelOffset;
				}
			};
			super.create();
		};

		/*
		 * never use xOffset/yOffset and xOffsetStep/yOffsetStep, because custom launchers will fuck your 
		 * brain and this problem can't be fixed! Use only xPixelOffset/yPixelOffset (who used yPixelOffset???)))
		 */

		@Override
		public void offsetChange (float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {
			pixelOffset = xPixelOffset;
		}

		@Override
		public void previewStateChange (boolean isPreview) {
			
		}
	}
}
