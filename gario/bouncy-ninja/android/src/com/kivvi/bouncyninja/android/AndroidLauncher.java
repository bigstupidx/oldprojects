package com.kivvi.bouncyninja.android;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.channel.IChannel;
import com.umeng.analytics.MobclickAgent;

public class AndroidLauncher extends AndroidApplication {
	protected View adView;
	protected View gameView;
	protected IChannel channel;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// Channel
		channel = new Channel();
		channel.init(this);
		
		// umeng
		MobclickAgent.updateOnlineConfig(this);
		MobclickAgent.openActivityDurationTrack(false);

		// Do the stuff that initialize() would do for you
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().clearFlags(
				WindowManager.LayoutParams.FLAG_FORCE_NOT_FULLSCREEN);

		RelativeLayout layout = new RelativeLayout(this);
		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
				RelativeLayout.LayoutParams.MATCH_PARENT,
				RelativeLayout.LayoutParams.MATCH_PARENT);
		layout.setLayoutParams(params);

		// Game view.
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		View gameView = createGameView(config);
		layout.addView(gameView);

		// Adview
		if (channel.getAds().getView() != null) {
			layout.addView(channel.getAds().getView());
		}

		setContentView(layout);

		// Start advertising
		channel.getAds().show();
	}

	private View createGameView(AndroidApplicationConfiguration cfg) {
		gameView = initializeForView(new BouncyNinjaGame() {

			@Override
			public void rate() {
				final Uri uri = Uri.parse("market://details?id="
						+ getApplicationContext().getPackageName());
				final Intent rateAppIntent = new Intent(Intent.ACTION_VIEW, uri);

				if (getPackageManager().queryIntentActivities(rateAppIntent, 0)
						.size() > 0) {
					startActivity(rateAppIntent);
				} else {
				}
			}

			@Override
			public void share() {
				Intent shareIntent = new Intent(Intent.ACTION_SEND);
				shareIntent.setType("text/plain");
				shareIntent.putExtra(android.content.Intent.EXTRA_TEXT,
						channel.getShareString());
				startActivity(shareIntent);
			}

		}, cfg);
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.MATCH_PARENT);
		gameView.setLayoutParams(params);
		return gameView;
	}

	@Override
	public void onResume() {
		// umeng
		MobclickAgent.onResume(this);

		super.onResume();

		if (channel.getAds() != null)
			channel.getAds().resume();
	}

	@Override
	public void onPause() {
		// umeng
		MobclickAgent.onPause(this);

		if (channel.getAds() != null)
			channel.getAds().pause();

		super.onPause();
	}

	@Override
	public void onDestroy() {
		if (channel.getAds() != null)
			channel.getAds().destroy();

		super.onDestroy();
	}
}
