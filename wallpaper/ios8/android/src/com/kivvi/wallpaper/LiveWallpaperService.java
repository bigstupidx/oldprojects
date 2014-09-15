package com.kivvi.wallpaper;

import android.view.SurfaceHolder;

import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;
import com.kivvi.ios8.IOS8;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperService extends AndroidLiveWallpaperService {
	private IOS8 ios8 = null;

	@Override
	public void onCreate() {
		MobclickAgent.updateOnlineConfig(this);
		MobclickAgent.openActivityDurationTrack(false);
		super.onCreate();
	}

	@Override
	public void onCreateApplication() {
		super.onCreateApplication();
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useWakelock = true;
		config.numSamples = 4;
		config.useAccelerometer = true;
		ios8 = new IOS8();
		initialize(ios8, config);
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

		@Override
		public void onVisibilityChanged(boolean visible) {
			if (isPreview()) {
				if (visible) {
					MobclickAgent.onPageStart("preview");
				} else {
					MobclickAgent.onPageEnd("preview");
				}
			} else {
				if (visible) {
					MobclickAgent.onPageStart("wallpaper");
					MobclickAgent.onResume(LiveWallpaperService.this);
				} else {
					MobclickAgent.onPageEnd("wallpaper");
					MobclickAgent.onPause(LiveWallpaperService.this);
				}
			}
			super.onVisibilityChanged(visible);
		}
	}

}
