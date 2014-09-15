package com.kivvi.theline.resource;

import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.utils.Disposable;

public class GameAssets{
	private static AssetManager assets = null;
	
	static public AssetManager getAssets() {
		if (assets == null) {
			assets = new AssetManager();
		}
		
		return assets;
	}

	static public void release() {
		assets.dispose();
		assets = null;
	} 
}
