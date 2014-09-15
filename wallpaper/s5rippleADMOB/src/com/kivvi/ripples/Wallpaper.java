package com.kivvi.ripples;

import android.util.Log;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;


public class Wallpaper implements ApplicationListener {
	public PerspectiveCamera cam;
	Ripples ripples;
	float angle = 0;
	int a = 0;
	
	public static boolean mIsPreview;
	
	public static boolean mStatus;
	
	public static float mScreenRatio;
	
	public static float mScreenWidth;
	public static float mScreenHeight;
	
	public static boolean mFirstLoading = false;
	
	public boolean mImageChanged = false;
	public Wallpaper(){
	}
	
	@Override
	public void create() {
		// TODO Auto-generated method stub 
		if(Gdx.graphics.getWidth() > Gdx.graphics.getHeight()){
			mScreenRatio = (float)Gdx.graphics.getHeight()/Gdx.graphics.getWidth();
		}else{
			mScreenRatio = (float)Gdx.graphics.getWidth()/Gdx.graphics.getHeight();
		}
		
		setScreenWH();
		ripples = new Ripples();
	}

	@Override
	public void resize(int width, int height) {
		// TODO Auto-generated method stub
		if(Gdx.graphics.getWidth() > Gdx.graphics.getHeight()){
			mScreenRatio = (float)Gdx.graphics.getHeight()/Gdx.graphics.getWidth();
		}else{
			mScreenRatio = (float)Gdx.graphics.getWidth()/Gdx.graphics.getHeight();
		}
		
		setScreenWH();
	}

	@Override
	public void render() {
		// TODO Auto-generated method stub
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		if(ripples == null){
			ripples = new Ripples();
		}
		ripples.render();
	}
	
	@Override
	public void resume() {
		// TODO Auto-generated method stub
		Gdx.app.log("diaosixu", "on resume");
		if(true){
			mFirstLoading = false;
			ripples.setTexture();
		}
			ripples.setRangeAndFrequency();


	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub
		ripples.dispose();
	}

	@Override
	public void pause() {
		// TODO Auto-generated method stub
	}

	public void onOffsetsChanged(float xOffset, float yOffset,
			float xOffsetStep, float yOffsetStep, int xPixelOffset,
			int yPixelOffset) {
		// TODO Auto-generated method stub
		if(ripples != null){
			ripples.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep, xPixelOffset, yPixelOffset);
	
		}
	}

	public void setIServer(IServer iserver){
		if(ripples != null){
			ripples.setIServer(iserver);
		}
	}
	
	public void onVisibilityChanged(boolean visible) {
		mIsPreview = visible;
	}
	
	public void setScreenWH(){
		if(Gdx.graphics.getWidth() > Gdx.graphics.getHeight()){
			mScreenWidth = Gdx.graphics.getHeight();
			mScreenHeight = Gdx.graphics.getWidth();
		}else{
			mScreenWidth = Gdx.graphics.getWidth();
			mScreenHeight = Gdx.graphics.getHeight();
		}
	}

}
