package com.kivvi.bouncyninja.resources;

import com.badlogic.gdx.assets.AssetManager;

public class GameAssets {
	private static AssetManager assets = null;

	static public AssetManager getAssets() {
		if (assets == null) {
			assets = new AssetManager();
		}

		return assets;
	}

	static public void dispose() {
		assets.dispose();
		assets = null;
	}
}
