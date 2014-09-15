package com.kivvi.theline.android.channel.munion360;

import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.RelativeLayout;

import com.badlogic.gdx.Gdx;
import com.kivvi.theline.android.channel.IAds;
import com.pubukeji.diandeows.adviews.DiandeBanner;
import com.pubukeji.diandeows.adviews.DiandeResultCallback;

public class Munion360Ads implements IAds {
	private Activity activity;
	private String banner_AD_ID = "bb92999153bbc9861de3399be84c3a14";
	private DiandeBanner banner;

	public void init(Activity activity) {
		this.activity = activity;

		createAdView();
	}

	private void createAdView() {
		banner = new DiandeBanner(activity, banner_AD_ID);

		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
				RelativeLayout.LayoutParams.MATCH_PARENT,
				RelativeLayout.LayoutParams.WRAP_CONTENT);
		params.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM, RelativeLayout.TRUE);
		params.addRule(RelativeLayout.CENTER_HORIZONTAL, RelativeLayout.TRUE);

		banner.setLayoutParams(params);
		banner.setBackgroundColor(Color.TRANSPARENT);
	}

	@Override
	public View getView() {
		return banner;
	}

	@Override
	public void show() {
		banner.show();
		banner.setRequestCallBack(new DiandeResultCallback() {
			@Override
			public void onSuccess(boolean result, String message) {
				Gdx.app.log("Munion360Ads", message);
			}

			@Override
			public void onFailed(String errorMessage) {
				Gdx.app.log("Munion360Ads", errorMessage);
			}

			@Override
			public void onAdShowSuccess(int code, String message) {
				Gdx.app.log("Munion360Ads", code + "  " + message);
			}
		});
	}

	@Override
	public void close() {
		banner.close();
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
