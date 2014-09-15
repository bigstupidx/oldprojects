package com.kivvi.theline.game;

import com.badlogic.gdx.Game;
import com.kivvi.theline.screens.GameOverScreen;
import com.kivvi.theline.screens.GameScreen;
import com.kivvi.theline.screens.MenuScreen;

public abstract class TheLineGame extends Game {
	public GameScreen gameScreen;
	public MenuScreen menuScreen;
	public GameOverScreen gameOverScreen;

	@Override
	public void create() {
		gameScreen = new GameScreen(this);
		menuScreen = new MenuScreen(this);
		gameOverScreen = new GameOverScreen(this);

		setScreen(gameScreen);
	}

	@Override
	public void dispose() {
		super.dispose();
		gameScreen.dispose();
		menuScreen.dispose();
		gameOverScreen.dispose();
	}

	abstract public void rate();

	abstract public void share();

}
