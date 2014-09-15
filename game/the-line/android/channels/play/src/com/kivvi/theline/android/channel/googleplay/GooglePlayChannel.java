package com.kivvi.theline.android.channel.googleplay;

import android.app.Activity;

import com.badlogic.gdx.Gdx;
import com.kivvi.theline.android.channel.IAds;
import com.kivvi.theline.android.channel.IChannel;
import com.kivvi.theline.resource.Data;

public class GooglePlayChannel implements IChannel {

	private IAds ads;
	private Activity activity;

	public GooglePlayChannel() {
		ads = new GoogleAds();
	}

	@Override
	public void init(Activity activity) {
		this.activity = activity;

		ads.init(activity);
	}

	@Override
	public IAds getAds() {
		return ads;
	}

	@Override
	public String getShareString() {
		String share = "";
		
		// attach promotion.
		int bestScore = Gdx.app.getPreferences(Data.prefName)
				.getInteger("best");
		String prefix = " OMG! I scored ";
		String suffix = " points in The Line!";
		share += prefix + bestScore + suffix;
		
		// attach url
		String url = " https://play.google.com/store/apps/details?id="
				+ activity.getApplicationContext().getPackageName();
		share += url;
		
		return share;
	}
}
