package com.kivvi.theline.android.channel;


import android.app.Activity;

public interface IChannel {
	public void init(Activity activity);

	public IAds getAds();

	public String getShareString();
}
