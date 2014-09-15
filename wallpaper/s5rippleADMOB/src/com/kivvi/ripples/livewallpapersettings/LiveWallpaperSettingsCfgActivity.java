package com.kivvi.ripples.livewallpapersettings;

import android.app.Activity;
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
import android.preference.PreferenceManager;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.kivvi.livewallpaper.ripples.R;
import com.cooeeui.contentadvert.AdvertService;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;
import com.kivvi.ripples.LibgdxLiveWallpaperAndroidService;
import com.kivvi.ripples.Wallpaper;
import com.umeng.analytics.MobclickAgent;

public class LiveWallpaperSettingsCfgActivity extends Activity {

	private static String CUSTOM_WALLPAPER = "custom_wallpaper";
	private static String SYS_WALLPAPER = "sys_wallpaper";
	private static String DEF_WALLPAPER = "def_wallpaper";
	private static String SCROLLBACKGROUND = "scrollbackground";
	private static String FREQUENCY = "frequency";
	private static String RANGE = "range";

	private TextView tvCustomWallpaper;
	private TextView tvSysWallpaper;
	private TextView tvDefWallpaper;
	private ToggleButton tbScroll;
	private RadioGroup rgFrequency;
	private RadioGroup rgRipplesSize;

	private SharedPreferences sharedPreferences;
	private boolean isFirstRun = true;
	
	protected String LOG_TAG = "SettingCfgActivity";
	private AdView adView;
	private LinearLayout linearLayout;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		
		isFirstRun = true;
		
		//MobclickAgent.setDebugMode(true);
		MobclickAgent.openActivityDurationTrack(false);		
		MobclickAgent.updateOnlineConfig(this);
		
		Log.d("LiveWallpaperSettingsCfgActivity", "updateOnlineConfig");

		setContentView(R.layout.setting);

		sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
		tvCustomWallpaper = (TextView) this.findViewById(R.id.tvCustomWallpaper);
		tvSysWallpaper = (TextView) this.findViewById(R.id.tvSysWallpaper);
		tvDefWallpaper = (TextView) this.findViewById(R.id.tvDefWallpaper);
		//tbScroll = (ToggleButton) this.findViewById(R.id.tbScroll);
		rgFrequency = (RadioGroup) this.findViewById(R.id.rgFrequency);
		rgRipplesSize = (RadioGroup) this.findViewById(R.id.rgRipplesSize);
		loadConfig();

//		tbScroll.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
//
//			@Override
//			public void onCheckedChanged(CompoundButton buttonView,
//					boolean isChecked) {
//				LibgdxLiveWallpaperAndroidService.ripplesSettings.scrollbackground = tbScroll
//						.isChecked();
//				Editor edit = sharedPreferences.edit();
//				edit.putBoolean(
//						SCROLLBACKGROUND,
//						LibgdxLiveWallpaperAndroidService.ripplesSettings.scrollbackground);
//				edit.commit();
//			}
//		});

		rgFrequency
				.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {

					@Override
					public void onCheckedChanged(RadioGroup group, int checkedId) {
						switch (rgFrequency.getCheckedRadioButtonId()) {
						case R.id.rbClose:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency = "0";
							break;
						case R.id.rbFast:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency = "1";
							break;
						case R.id.rbNormal:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency = "2";
							break;
						case R.id.rbSlow:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency = "3";
							break;
						default:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency = "0";
							break;
						}
						Editor edit = sharedPreferences.edit();
						edit.putString(
								FREQUENCY,
								LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency);
						edit.commit();
					}
				});

		rgRipplesSize
				.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {

					@Override
					public void onCheckedChanged(RadioGroup group, int checkedId) {
						switch (rgRipplesSize.getCheckedRadioButtonId()) {
						case R.id.rbRipplesBig:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.range = "1";
							break;
						case R.id.rbRipplesNormal:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.range = "2";
							break;
						case R.id.rbRipplesSmall:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.range = "3";
							break;
						default:
							LibgdxLiveWallpaperAndroidService.ripplesSettings.range = "2";
							break;
						}
						Editor edit = sharedPreferences.edit();
						edit.putString(
								RANGE,
								LibgdxLiveWallpaperAndroidService.ripplesSettings.range);
						edit.commit();
					}
				});

//		ImageView iv = (ImageView) this.findViewById(R.id.ivAd);
//		iv.setImageBitmap(AdvertService.getAdvertImage(this));
//		iv.setOnClickListener(new OnClickListener() {
//
//			@Override
//			public void onClick(View v) {
//				AdvertService.gotoUiCenter(LiveWallpaperSettingsCfgActivity.this);
//			}
//		});
		
		tvCustomWallpaper.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
			    intent.setType("image/*");
			    startActivityForResult(intent, 0);
			}
		});
		
		tvSysWallpaper.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if (LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper != 1) {
					Editor editor = sharedPreferences.edit();
					editor.putInt("current_wallpaper", 1);
					LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 1;
					Wallpaper.mFirstLoading = true;
					WallpaperManager wallpaperManager = WallpaperManager.getInstance(LiveWallpaperSettingsCfgActivity.this);
					Drawable drawable = wallpaperManager.getDrawable();
					BitmapDrawable bitmapDrawable = (BitmapDrawable)drawable;
					Bitmap bitmap = bitmapDrawable.getBitmap();
					LibgdxLiveWallpaperAndroidService.ripplesSettings.bitmap = bitmap;
					editor.commit();
				}
				finish();
			}
		});
		
		tvDefWallpaper.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if (LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper != 0) {
					Editor editor = sharedPreferences.edit();
					editor.putInt("current_wallpaper", 0);
					LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 0;
					editor.commit();
					Wallpaper.mFirstLoading = true;
				}
				finish();
			}
		});
		
//		adView = new AdView(this, AdSize.BANNER, "a153301b742b855");
//		linearLayout = (LinearLayout) findViewById(R.id.LinearLayout);
//		linearLayout.addView(adView);
//		adView.loadAd(new AdRequest());
	}

	private void loadConfig() {

		//tbScroll.setChecked(LibgdxLiveWallpaperAndroidService.ripplesSettings.scrollbackground);

		if (sharedPreferences.getString(FREQUENCY, "0").equals("0")) {
			rgFrequency.check(R.id.rbClose);
		} else if (sharedPreferences.getString(FREQUENCY, "0").equals("1")) {
			rgFrequency.check(R.id.rbFast);
		} else if (sharedPreferences.getString(FREQUENCY, "0").equals("2")) {
			rgFrequency.check(R.id.rbNormal);
		} else if (sharedPreferences.getString(FREQUENCY, "0").equals("3")) {
			rgFrequency.check(R.id.rbSlow);
		} else {
			rgFrequency.check(R.id.rbClose);
		}

		if (sharedPreferences.getString(RANGE, "2").equals("1")) {
			rgRipplesSize.check(R.id.rbRipplesBig);
		} else if (sharedPreferences.getString(RANGE, "2").equals("2")) {
			rgRipplesSize.check(R.id.rbRipplesNormal);
		} else if (sharedPreferences.getString(RANGE, "2").equals("3")) {
			rgRipplesSize.check(R.id.rbRipplesSmall);
		} else {
			rgRipplesSize.check(R.id.rbRipplesNormal);
		}
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode != RESULT_OK) {
	        return;
	    }
		Editor editor = sharedPreferences.edit();
	    boolean status = false;
	    if (requestCode == 0) {
			Uri originalUri = data.getData();
			String[] proj = {MediaStore.Images.Media.DATA};
			String path = null;
			if(originalUri != null){
				if (originalUri.getScheme().compareTo("content") == 0){
					ContentResolver resolver = getContentResolver();
					Cursor cursor = resolver.query(originalUri, proj, null, null, null);
					if(cursor != null && cursor.moveToFirst()){
						int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
			            path = cursor.getString(column_index);
			            status = true;
					}
					cursor.close();
				}else if (originalUri.getScheme().compareTo("file") == 0){
					path = originalUri.toString().replace("file://", "");
					status = true;
			   	}
			}else{
				status = false;
			}
			
			if(status){
				editor.putInt("current_wallpaper", 2);
				LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 2;
				editor.putString("current_path", path);
				LibgdxLiveWallpaperAndroidService.ripplesSettings.customPath = path;
			}else{
		   		editor.putInt("current_wallpaper", 0);
	        	LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper = 0;
	        	Toast.makeText(this, R.string.failed, Toast.LENGTH_LONG).show();
		   	}
			
	        editor.commit();
	    }
	    Wallpaper.mFirstLoading = true;
	    finish();
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d("SettingCfgActivity", "onResume");
		
		MobclickAgent.onPageStart("setting");
		MobclickAgent.onResume(this);
	}

	@Override
	public void onPause() {
		if (isFirstRun) {
			isFirstRun = false;
			AdvertService.eventEnterSetting(this);
			AdvertService.checkActiveState(LiveWallpaperSettingsCfgActivity.this);
			
		}
		
		super.onPause();
		Log.d("SettingCfgActivity", "onPause");
		MobclickAgent.onPageEnd("setting");
		MobclickAgent.onPause(this);
	}
	
	@Override
	protected void onDestroy() {
		if (adView != null) {
			adView.destroy();
		}
		super.onDestroy();
	}
}
