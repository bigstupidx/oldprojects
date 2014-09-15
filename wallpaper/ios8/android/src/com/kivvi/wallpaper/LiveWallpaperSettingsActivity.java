package com.kivvi.wallpaper;

import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceActivity;
import android.preference.PreferenceScreen;
import android.provider.MediaStore;
import android.util.Log;

import com.badlogic.gdx.Gdx;
import com.kivvi.ios8.android.R;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperSettingsActivity extends PreferenceActivity {

	// private SharedPreferences sharedPreferences = null;
	// private Editor editor = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		MobclickAgent.openActivityDurationTrack(false);
		MobclickAgent.updateOnlineConfig(this);

		addPreferencesFromResource(R.xml.preferences);

		initProperties();

		init();
	}

	private void init() {
		CheckBoxPreference doubleClicked = (CheckBoxPreference) findPreference("wave");
		doubleClicked
				.setOnPreferenceChangeListener(new OnPreferenceChangeListener() {
					@Override
					public boolean onPreferenceChange(Preference arg0,
							Object newValue) {
						return true;
					}
				});

	}

	@Override
	protected void onStart() {
		super.onStart();
	}

	@Override
	protected void onResume() {
		super.onResume();
		MobclickAgent.onPageStart("preference setting");
		MobclickAgent.onResume(this);
	}

	@Override
	protected void onPause() {
		super.onPause();
		MobclickAgent.onPageEnd("preference setting");
		MobclickAgent.onPause(this);
	}

	@Override
	public boolean onPreferenceTreeClick(PreferenceScreen preferenceScreen,
			Preference preference) {
		if (preference == (PreferenceScreen) findPreference("rate")) {
			/* This code assumes you are inside an activity */
			final Uri uri = Uri.parse("market://details?id="
					+ getApplicationContext().getPackageName());
			final Intent rateAppIntent = new Intent(Intent.ACTION_VIEW, uri);

			if (getPackageManager().queryIntentActivities(rateAppIntent, 0)
					.size() > 0) {
				// Log.v("diaosixu", "rate go");
				startActivity(rateAppIntent);
			} else {
				// Log.v("diaosixu", "rate get error");
			}
		}

		if (preference == (PreferenceScreen) findPreference("share")) {
			Intent shareIntent = new Intent(Intent.ACTION_SEND);
			shareIntent.setType("text/plain");
			shareIntent.putExtra(android.content.Intent.EXTRA_TEXT,
					getResources().getText(R.string.share_message)
							+ " https://play.google.com/store/apps/details?id="
							+ getApplicationContext().getPackageName());
			startActivity(shareIntent);
		}

		return super.onPreferenceTreeClick(preferenceScreen, preference);
	}

	// FIXME: should we apply the setting when libgdx app is not running?
	private void initProperties() {
		if (Gdx.app == null) {
			// sharedPreferences = this.getSharedPreferences("setting",
			// Context.MODE_PRIVATE);
		}
	}

	private void flush() {
		if (Gdx.app == null) {
			// editor.commit();
			// editor = null;
		} else {
			Properties.flush();
		}
	}
}
