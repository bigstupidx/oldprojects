package com.kivvi.theline.screens;

import com.badlogic.gdx.Screen;
import com.kivvi.theline.game.TheLineGame;

public abstract class BaseScreen implements Screen {
	protected TheLineGame game = null;
	public BaseScreen(TheLineGame game) {
		this.game = game;
	}

	@Override
	public void resize(int width, int height) {
	}

	@Override
	public void show() {
	}

	@Override
	public void hide() {
	}

	@Override
	public void pause() {
	}

	@Override
	public void resume() {
	}

	@Override
	public void dispose() {
	}
}
