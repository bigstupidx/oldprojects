package com.kivvi.avoidthecircles.stages;

import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.kivvi.avoidthecircles.utils.RandTool;

public class GameStage extends Stage {
	public static AssetManager assetManager;
	public static RandTool randTool;

	public GameStage(Viewport viewport) {
		super(viewport);

		assetManager = new AssetManager();
		assetManager.load("hero.png", Texture.class);
		assetManager.finishLoading();
		
		randTool = new RandTool();
	}
	
	@Override
	public void dispose() {
		super.dispose();
		
		assetManager.dispose();
	}
}
