package com.kivvi.crystalswan.android;

import com.badlogic.gdx.backends.android.AndroidLiveWallpaper;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;

public class LiveWallpaper extends AndroidLiveWallpaper {

	public LiveWallpaper(AndroidLiveWallpaperService service) {
		super(service);
	}

	@Override
	public void onResume() {
		super.onResume();
	}

}
