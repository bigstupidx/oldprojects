package com.kivvi.theline.android.channel.munion360admob;

import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.RelativeLayout;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.kivvi.theline.android.channel.IAds;

public class GoogleAds implements IAds {
	private static final String AD_UNIT_ID = "ca-app-pub-4005700910133098/5002774366";
	private static final String GOOGLE_PLAY_URL = "https://play.google.com/store/apps/developer?id=TheInvader360";
	private AdView adView;
	private Activity activity;

	public void init(Activity activity) {
		this.activity = activity;

		createAdView();
	}

	private AdView createAdView() {
		adView = new AdView(activity);
		adView.setAdSize(AdSize.SMART_BANNER);
		adView.setAdUnitId(AD_UNIT_ID);
		adView.setId(12345); // this is an arbitrary id, allows for relative
								// positioning in createGameView()
		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
				RelativeLayout.LayoutParams.MATCH_PARENT,
				RelativeLayout.LayoutParams.WRAP_CONTENT);
		params.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM, RelativeLayout.TRUE);
		params.addRule(RelativeLayout.CENTER_HORIZONTAL, RelativeLayout.TRUE);
		adView.setLayoutParams(params);
		adView.setBackgroundColor(Color.TRANSPARENT);
		return adView;
	}

	@Override
	public View getView() {
		return adView;
	}

	@Override
	public void show() {
		AdRequest adRequest = new AdRequest.Builder().build();
		adView.loadAd(adRequest);
	}

	@Override
	public void close() {
	}

	@Override
	public void resume() {
		adView.resume();
	}

	@Override
	public void pause() {
		adView.pause();
	}

	@Override
	public void destroy() {
		adView.destroy();
	}
}
