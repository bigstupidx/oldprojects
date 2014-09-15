package com.kivvi.ripples.livewallpapersettings;

import android.app.WallpaperManager;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.preference.PreferenceScreen;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.Toast;

import com.kivvi.livewallpaper.ripples.R;
import com.kivvi.ripples.LibgdxLiveWallpaperAndroidService;
import com.kivvi.ripples.config.parser.configInfo;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperSettingsActivity extends PreferenceActivity implements
		Preference.OnPreferenceChangeListener {

	private static String CUSTOM_WALLPAPER = "custom_wallpaper";
	private static String SYS_WALLPAPER = "sys_wallpaper";
	private static String DEF_WALLPAPER = "def_wallpaper";
	private static String SCROLLBACKGROUND = "scrollbackground";
	private static String FREQUENCY = "frequency";
	private static String RANGE = "range";

	private PreferenceScreen custom_wallpaper;
	private PreferenceScreen sys_wallpaper;
	private PreferenceScreen def_wallpaper;
	private ListPreference frequency;
	private ListPreference range;
	private CheckBoxPreference scrollbackground;

	private SharedPreferences sharedPreferences;

	private Editor editor;

	private configInfo configinfo;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		MobclickAgent.openActivityDurationTrack(false);		
		MobclickAgent.updateOnlineConfig(this);
		addPreferencesFromResource(R.xml.preferences);

		sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
		editor = sharedPreferences.edit();
		init();
	}

	private void init() {
		custom_wallpaper = (PreferenceScreen) findPreference(CUSTOM_WALLPAPER);
		sys_wallpaper = (PreferenceScreen) findPreference(SYS_WALLPAPER);
		def_wallpaper = (PreferenceScreen) findPreference(DEF_WALLPAPER);
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
		// TODO Auto-generated method stub
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
//				Log.v("diaosixu", "rate go");
				startActivity(rateAppIntent);
			} else {
//				Log.v("diaosixu", "rate get error");
			}
		}

		if (preference == (PreferenceScreen) findPreference("share")) {
			Intent shareIntent = new Intent(Intent.ACTION_SEND);
			shareIntent.setType("text/plain");
			shareIntent.putExtra(android.content.Intent.EXTRA_TEXT, getResources().getText(R.string.share_message) + " https://play.google.com/store/apps/details?id=" + getApplicationContext().getPackageName());
			startActivity(shareIntent);   
		}

		if (preference == custom_wallpaper) {
			Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
			intent.setType("image/*");
			startActivityForResult(intent, 0);
		} else if (preference == sys_wallpaper) {
			editor.putInt("current_wallpaper", 1);
			LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 1;

			WallpaperManager wallpaperManager = WallpaperManager
					.getInstance(this);
			Drawable drawable = wallpaperManager.getDrawable();
			BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;
			Bitmap bitmap = bitmapDrawable.getBitmap();
			LibgdxLiveWallpaperAndroidService.ripplesSettings.bitmap = bitmap;
			finish();
		} else if (preference == def_wallpaper) {
			editor.putInt("current_wallpaper", 0);
			LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 0;
			finish();
		}
		editor.commit();
		return super.onPreferenceTreeClick(preferenceScreen, preference);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
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
				
				Log.v("diaosixu", "path = " + path);
			} else {
				status = false;
			}

			if (status) {
				editor.putInt("current_wallpaper", 2);
				LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 2;
				editor.putString("current_path", path);
				LibgdxLiveWallpaperAndroidService.ripplesSettings.customPath = path;
			} else {
				editor.putInt("current_wallpaper", 0);
				LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 0;
				Toast.makeText(this, R.string.failed, Toast.LENGTH_LONG).show();
			}

			editor.commit();
		}
		finish();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
	}

	@Override
	public boolean onPreferenceChange(Preference preference, Object newValue) {
		return false;
	}

}
