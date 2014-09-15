package com.kivvi.avoidthecircles;

import com.badlogic.gdx.Game;
import com.kivvi.avoidthecircles.screens.GameScreen;

public class AvoidTheCircles extends Game {
	GameScreen game;

	@Override
	public void create() {
		game = new GameScreen();
		setScreen(game);
	}
}
