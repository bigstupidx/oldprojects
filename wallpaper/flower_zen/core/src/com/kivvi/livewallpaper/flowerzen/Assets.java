package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetDescriptor;
import com.badlogic.gdx.assets.AssetErrorListener;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.utils.Disposable;

public class Assets implements Disposable, AssetErrorListener {
	public static final String TAG = Assets.class.getName();

	public static final String FILE_NAME = "data/flower_zen.g3dj";
	public static final Assets instance = new Assets();
	public Model model;
	private AssetManager assetManager;
	public SceneObject water;

	// singleton
	private Assets() {
	}

	public void init(AssetManager assetManager) {
		this.assetManager = assetManager;
		// set asset manager error handler
		assetManager.setErrorListener(this);
		assetManager.load(FILE_NAME, Model.class);
		// start loading assets and wait until finished
		assetManager.finishLoading();
		Gdx.app.debug(TAG,
				"# of assets loaded: " + assetManager.getAssetNames().size);
		for (String a : assetManager.getAssetNames())
			Gdx.app.debug(TAG, "asset: " + a);
		
		model = assetManager.get(FILE_NAME ,Model.class);
		
		
		// FIXME it's not a good way 
		water = new SceneObject(model, "water");
		
		
	}

	@Override
	public void dispose() {
		assetManager.dispose();
		Gdx.app.debug(TAG, "dispose...");
	}

	@Override
	public void error(AssetDescriptor asset, Throwable throwable) {
		Gdx.app.error(TAG, "Couldn't load asset '"
				+ asset + "'", (Exception)throwable);
	}
}
