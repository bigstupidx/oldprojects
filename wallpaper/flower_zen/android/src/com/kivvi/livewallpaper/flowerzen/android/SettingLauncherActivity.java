package com.kivvi.livewallpaper.flowerzen.android;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import com.umeng.analytics.MobclickAgent;


public class SettingLauncherActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		MobclickAgent.openActivityDurationTrack(false);		
		MobclickAgent.updateOnlineConfig(this);
		
		setContentView(R.layout.main);
		
		
		Button button = (Button)findViewById(R.id.buttonSetting);
		button.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent(WallpaperManager.ACTION_LIVE_WALLPAPER_CHOOSER);
				startActivity(Intent.createChooser(intent, "Select Wallpaper"));
			    
			}
		});

	}
	
	
	
}
