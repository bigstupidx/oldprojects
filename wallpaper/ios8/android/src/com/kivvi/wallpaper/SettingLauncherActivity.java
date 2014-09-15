package com.kivvi.wallpaper;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import com.kivvi.ios8.android.R;
import com.umeng.analytics.MobclickAgent;


public class SettingLauncherActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		MobclickAgent.openActivityDurationTrack(false);		
		MobclickAgent.updateOnlineConfig(this);
		
		setContentView(R.layout.main);
		
		Button button1 = (Button) findViewById(R.id.buttonSetWallpaper);
		button1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent intent = new Intent(SettingLauncherActivity.this,
						LiveWallpaperSettingsActivity.class);
				startActivity(intent);

				finish();
			}
		});
		
		Button button2 = (Button)findViewById(R.id.buttonSetting);
		button2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				ComponentName component = new ComponentName(SettingLauncherActivity.this, LiveWallpaperService.class);
			    Intent intent = new Intent(WallpaperManager.ACTION_CHANGE_LIVE_WALLPAPER);
			    intent.putExtra(WallpaperManager.EXTRA_LIVE_WALLPAPER_COMPONENT, component);
			    
			    if (tryStartActivity(intent)) {	   
			    	finish();
			    	return;
			    }
			    
			    intent = new Intent(WallpaperManager.ACTION_LIVE_WALLPAPER_CHOOSER);
			    if (tryStartActivity(intent)) {
			    	finish();
			    	return;
			    }
			    
			    intent = new Intent("com.bn.nook.CHANGE_WALLPAPER");
			    if (tryStartActivity(intent)) {
			    	finish();
			    	return;
			    }
			}
		});

	}
	
	@Override
	protected void onResume() {
		super.onResume();
		MobclickAgent.onPageStart("mainmenu");
		MobclickAgent.onResume(this);
	}

	@Override
	public void onPause() {
		super.onPause();
		MobclickAgent.onPageEnd("mainmenu");
		MobclickAgent.onPause(this);
	}
	
	private boolean tryStartActivity(Intent intent) {
		PackageManager pm = getPackageManager();
		ResolveInfo ri = pm.resolveActivity(intent, PackageManager.MATCH_DEFAULT_ONLY);
		if (ri == null) {
			return false;
		}
		startActivity(intent);
		return true;
	}
	
	
}
