package com.kivvi.ripples;

import java.io.ByteArrayOutputStream;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

import android.preference.PreferenceManager;
import android.service.wallpaper.WallpaperService.Engine;
import android.util.Log;
import android.view.SurfaceHolder;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidLiveWallpaperService;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;

import android.app.WallpaperManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;

import com.kivvi.ripples.config.parser.configInfo;
import com.kivvi.ripples.config.parser.xmlParser;
import com.kivvi.ripples.util.*;
import com.umeng.analytics.MobclickAgent;


public class LibgdxLiveWallpaperAndroidService extends AndroidLiveWallpaperService{
	
	public static RipplesSettings ripplesSettings = new RipplesSettings();
	
	private Wallpaper wallpaper;
	
	private LibgdxLiveWallpaperAndroidServiceEngine llwase;
	
	public static xmlParser xmlparser = new xmlParser();
	
	private configInfo configinfo;
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		MobclickAgent.updateOnlineConfig(this);
		MobclickAgent.openActivityDurationTrack(false);
		super.onCreate();
	}

	@Override
	public void onCreateApplication(){
		super.onCreateApplication();
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		config.useAccelerometer = false;
		config.useCompass = false;
		config.useWakelock = true;
		
		getContent();

		
		SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
		ripplesSettings.range = sp.getString("range", getRange());
		ripplesSettings.frequency = sp.getString("frequency", getFrequency());
		ripplesSettings.currentWallpaper = sp.getInt("current_wallpaper", getBackgroundOption());
		ripplesSettings.customPath = sp.getString("current_path", "");
		ripplesSettings.scrollbackground = sp.getBoolean("scrollbackground", getScrollBackroundSwitch());
		ripplesSettings.custombackgroundpath = getCustombackgroundpath();
		ripplesSettings.reflectlight = getReflectlight();
		
		if (ripplesSettings.currentWallpaper == 1) {
			WallpaperManager wallpaperManager = WallpaperManager.getInstance(this);
			Drawable drawable = wallpaperManager.getDrawable();
			BitmapDrawable bitmapDrawable = (BitmapDrawable)drawable;
			Bitmap bitmap = bitmapDrawable.getBitmap();
			
			if(bitmap != null){
				ripplesSettings.bitmap = bitmap;
			}
		}

		if(wallpaper == null){
			wallpaper = new Wallpaper();
		}
	    
		initialize(wallpaper, config);
	}
	
	
	
	@Override
	public Engine onCreateEngine() {
		// TODO Auto-generated method stub
		llwase = new LibgdxLiveWallpaperAndroidServiceEngine();
		if(wallpaper != null){
			wallpaper.setIServer(llwase);
		}
		return llwase;
	}

	class LibgdxLiveWallpaperAndroidServiceEngine extends AndroidLiveWallpaperService.AndroidWallpaperEngine implements IServer{
		
		@Override
		public void onCreate(SurfaceHolder surfaceHolder) {
			// TODO Auto-generated method stub
			super.onCreate(surfaceHolder);
		}

		@Override
		public void onOffsetsChanged(float xOffset, float yOffset,
				float xOffsetStep, float yOffsetStep, int xPixelOffset,
				int yPixelOffset) {
			// TODO Auto-generated method stub
			super.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep,
					xPixelOffset, yPixelOffset);
			if(wallpaper != null){
				wallpaper.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep, xPixelOffset, yPixelOffset);
			}
		}

		@Override
		public void onVisibilityChanged(boolean visible) {
			// TODO Auto-generated method stub
			super.onVisibilityChanged(visible);

			if(wallpaper != null){
				wallpaper.onVisibilityChanged(isPreview());
			}
			
			if (isPreview()){
				if (visible){
					MobclickAgent.onPageStart("preview");
				} else {
					MobclickAgent.onPageEnd("preview");
				}
			} else {
				if (visible){
					MobclickAgent.onPageStart("wallpaper");
					MobclickAgent.onResume(LibgdxLiveWallpaperAndroidService.this);
				} else {
					MobclickAgent.onPageEnd("wallpaper");
					MobclickAgent.onPause(LibgdxLiveWallpaperAndroidService.this);
				}
			}
				
			
			if(!visible){
				wallpaper.mStatus = true;
			}else{
				wallpaper.mStatus = false;
			}
		}
		
		@Override
		public boolean getIsPreview() {
			// TODO Auto-generated method stub
			return isPreview();
		}
	}
	
	private String getFrequency(){
		String str = "";
		if(configinfo.getFrequencyswitch().equals("close")){
			str = "0";
		}else if(configinfo.getFrequencyswitch().equals("fase")){
			str = "1";
		}else if(configinfo.getFrequencyswitch().equals("normal")){
			str = "2";
		}else if(configinfo.getFrequencyswitch().equals("slow")){
			str = "3";
		}else{
			str = "0";
	 	}
		return str;
	}
	
	private String getRange(){
		String str = "";
		if(configinfo.getRangeswitch().equals("big")){
			str = "1";
		}else if(configinfo.getRangeswitch().equals("normal")){
			str = "2";
		}else if(configinfo.getRangeswitch().equals("small")){
			str = "3";
		}else{
			str = "2";
	 	}
		return str;
	}
	
	private boolean getScrollBackroundSwitch(){
		return configinfo.isScrollbackgroundswitch();
	}
	
	private int getBackgroundOption(){
		return configinfo.getBackgroundoption();
	}
	
	private boolean getReflectlight(){
		return configinfo.getReflectlight();
	}
	
	private String getCustombackgroundpath(){
		return configinfo.getCustombackgroundpath();
	}
	
	public void getContent(){
		try{
			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser parser = factory.newSAXParser();
			XMLReader reader = parser.getXMLReader();
			reader.setContentHandler(xmlparser);
			InputSource stream = new InputSource(getResources().getAssets().open("config.xml"));
			reader.parse(stream);
			configinfo = xmlparser.getConfig();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
}
