package com.kivvi.livewallpaper.flowerzen.android;

import android.content.Context;

import com.kivvi.livewallpaper.flowerzen.utils.IAnalyticsService;
import com.umeng.analytics.MobclickAgent;

public class AndroidAnalyticsService implements IAnalyticsService {

	Context context;

	public AndroidAnalyticsService(Context context) {
		this.context = context;
	}

	@Override
	public void onResume() {
		MobclickAgent.onResume(context);
	}

	@Override
	public void onPause() {
		MobclickAgent.onPause(context);
	}
}
