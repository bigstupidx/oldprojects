package com.kivvi.crystalswan.android.setting;

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
import com.kivvi.crystalswan.Properties;
import com.kivvi.crystalswan.android.R;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperSettingsActivity extends PreferenceActivity implements
		Preference.OnPreferenceChangeListener {

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
		Preference seekbar = findPreference("seekBar");
		seekbar.setOnPreferenceChangeListener(this);

		CheckBoxPreference doubleClicked = (CheckBoxPreference) findPreference("check_doubleclick");
		doubleClicked
				.setOnPreferenceChangeListener(new OnPreferenceChangeListener() {
					@Override
					public boolean onPreferenceChange(Preference arg0,
							Object newValue) {
						LiveWallpaperSettingsActivity.this
								.setDoubleTap((Boolean) newValue);
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

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode != RESULT_OK) {
			return;
		}

		boolean status = false;
		if (requestCode == 0) {
			Uri originalUri = data.getData();
			String[] proj = { MediaStore.Images.Media.DATA };
			String path = null;
			if (originalUri != null) {
				if (originalUri.getScheme().compareTo("content") == 0) {
					ContentResolver resolver = getContentResolver();
					Cursor cursor = resolver.query(originalUri, proj, null,
							null, null);
					if (cursor != null && cursor.moveToFirst()) {
						int column_index = cursor
								.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
						path = cursor.getString(column_index);
						status = true;
					}
					cursor.close();
				} else if (originalUri.getScheme().compareTo("file") == 0) {
					path = originalUri.toString().replace("file://", "");
					status = true;
				}

				// Log.v("diaosixu", "path = " + path);
			} else {
				status = false;
			}
		}
		finish();
	}

	@Override
	public boolean onPreferenceChange(Preference preference, Object newValue) {
		if (preference.getKey().equals("seekBar")) {
			this.setBrightness((Integer) newValue);
			return true;
		}
		return false;
	}

	// FIXME: should we apply the setting when libgdx app is not running?
	private void initProperties() {
		if (Gdx.app == null) {
			// sharedPreferences = this.getSharedPreferences("setting",
			// Context.MODE_PRIVATE);
		}
	}

	private void setDoubleTap(boolean doubleTap) {
		if (Gdx.app == null) {
			// this.edit();
			// editor.putBoolean("check_doubleclick", doubleTap);
			// Log.v("suyu", "setting activity: set doubleTap = " + doubleTap);
		} else {
			Properties.setDoubleTap(doubleTap);
			// Gdx.app.log("suyu", "app: set doubleTap = " + doubleTap);
			this.flush();
		}
	}

	private void setBrightness(int brightness) {
		if (Gdx.app == null) {
			// this.edit();
			// editor.putInt("seekBar", brightness);
			// Log.v("suyu", "setting activity: set brightness = " +
			// brightness);
		} else {
			Properties.setBrightness(brightness);
			// Gdx.app.log("suyu", "app: set brightness = " + brightness);
			this.flush();
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
