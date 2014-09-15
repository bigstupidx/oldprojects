package com.kivvi.bouncyninja.game;

import com.badlogic.gdx.Configs;
import com.badlogic.gdx.Game;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.screens.GameOverScreen;
import com.kivvi.bouncyninja.screens.GameScreen;
import com.kivvi.bouncyninja.screens.HelloScreen;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.Box2dRenderer;

public abstract class BouncyNinjaGame extends Game {
	public HelloScreen helloScreen;
	public GameScreen gameScreen;
	public GameOverScreen gameOverScreen;

	@Override
	public void create() {
		Configs.setAssetEncrypt(false);
		
		helloScreen = new HelloScreen(this);
		gameScreen = new GameScreen(this);
		gameOverScreen = new GameOverScreen(this);

		setScreen(helloScreen);
	}

	@Override
	public void dispose() {
		super.dispose();

		if (helloScreen != null)
			helloScreen.dispose();

		if (gameScreen != null) {
			gameScreen.dispose();
		}

		GameStage.dispose();
		GameAssets.dispose();
		Box2dRenderer.dispose();
	}

	abstract public void rate();

	abstract public void share();

	public void toGameScreen() {
		if (helloScreen != null) {
			helloScreen.dispose();
			helloScreen = null;
		}

		setScreen(gameScreen);
	}

	public void toGameOverScreen() {
		if (getScreen() != gameOverScreen) {
			setScreen(gameOverScreen);
		}
	}
}
