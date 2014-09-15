package com.kivvi.livewallpaper.flowerzen.desktop;

import com.badlogic.gdx.Gdx;
import com.kivvi.livewallpaper.flowerzen.utils.IAnalyticsService;

public class DesktopAnalyticsService implements IAnalyticsService {
	private static final String TAG = DesktopAnalyticsService.class.getName();
	
	@Override
	public void onResume() {
		Gdx.app.debug(TAG, "onResume");
	}

	@Override
	public void onPause() {
		Gdx.app.debug(TAG, "onPause");
	}

}
