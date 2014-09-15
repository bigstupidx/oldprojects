package com.kivvi.galaxy3d.android;

import android.view.SurfaceHolder;

import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;
import com.kivvi.galaxy3d.Galaxy3D;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperService extends AndroidLiveWallpaperService {
	private Galaxy3D galaxy = null;

	@Override
	public void onCreate() {
		MobclickAgent.updateOnlineConfig(this);
		MobclickAgent.openActivityDurationTrack(false);
		super.onCreate();
	}

	@Override
	public void onCreateApplication() {
		super.onCreateApplication();
		com.badlogic.gdx.Configs.setAssetEncrypt(false);
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useWakelock = true;
		config.numSamples = 4;
		galaxy = new Galaxy3D();
		initialize(galaxy, config);
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
