package com.kivvi.theline.android.channel.anzhi;

import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.RelativeLayout;

import com.fw.bn.AdBanner;
import com.kivvi.theline.android.channel.IAds;

public class AnzhiAds implements IAds {
	private Activity activity;
	private String appKey = "28e7nmw45sRhLSapW8ROxPTP";
	private AdBanner myAdView;

	public void init(Activity activity) {
		this.activity = activity;

		createAdView();
	}

	private void createAdView() {
        myAdView = new AdBanner(activity);
		myAdView.setAppKey(appKey);

		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
				RelativeLayout.LayoutParams.MATCH_PARENT,
				RelativeLayout.LayoutParams.WRAP_CONTENT);
		params.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM, RelativeLayout.TRUE);
		params.addRule(RelativeLayout.CENTER_HORIZONTAL, RelativeLayout.TRUE);

		myAdView.setLayoutParams(params);
		myAdView.setBackgroundColor(Color.TRANSPARENT);
		
//		RecevieAdListener adListener = new RecevieAdListener() {
//			@Override
//			public void onSucessedRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.VISIBLE);
//			}
//			@Override
//			public void onFailedToRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.GONE);
//			}
//		};
//		myAdView.setRecevieAdListener(adListener);
	}

	@Override
	public View getView() {
		return myAdView;
	}

	@Override
	public void show() {
	}

	@Override
	public void close() {
	}

	@Override
	public void resume() {
	}

	@Override
	public void pause() {
	}

	@Override
	public void destroy() {
	}
}
