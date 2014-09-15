package com.kivvi.channel;

import android.app.Activity;

import com.kivvi.ads.IAds;

public interface IChannel {
	public void init(Activity activity);

	public IAds getAds();

	public String getShareString();
}
