package com.kivvi.avoidthecircles.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.FillViewport;
import com.kivvi.avoidthecircles.actors.Hero;
import com.kivvi.avoidthecircles.stages.GameStage;

public class GameScreen implements Screen {

	Hero hero;
	Stage stage;
	SpriteBatch batch;

	public GameScreen() {
		batch = new SpriteBatch();
		
		stage = new GameStage(new FillViewport(480, 800));

		hero = new Hero();

		stage.addActor(hero);
	}

	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(0.11f, 0.71f, 0.54f, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		batch.begin();
		stage.draw();
		batch.end();
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
		batch.dispose();
		
		stage.dispose();
	}

}
