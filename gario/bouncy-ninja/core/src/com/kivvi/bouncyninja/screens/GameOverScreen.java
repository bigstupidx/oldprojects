package com.kivvi.bouncyninja.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.CommonStage;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.Box2dRenderer;
import com.kivvi.bouncyninja.utils.TapGestureListener;

public class GameOverScreen implements Screen {
	BouncyNinjaGame game;
	AssetManager assets;
	CommonStage stage;
	boolean isInit = false;
	Label gameOverLabel;
	Label scoreTextLabel;
	Label scoreLabel;
	Label bestTextLabel;
	Label bestLabel;
	Label replayLabel;
	GestureDetector gestureDetector;

	public GameOverScreen(BouncyNinjaGame game) {
		this.game = game;

		assets = GameAssets.getAssets();
		loadResources();
	}

	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(0, 0, 0, 0);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		if (!GameAssets.getAssets().update()) {
			return;
		} else {
			if (!isInit) {
				init();
			}
		}

		// draw stage
		stage.act(Gdx.graphics.getDeltaTime());
		if (Data.box2dDebug) {
			stage.draw();

			Gdx.gl.glClearColor(0, 0, 0, 0);
			Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

			Box2dRenderer.getRenderer().render(stage.world,
					stage.getCamera().combined);
		} else {
			stage.draw();
		}
	}

	@Override
	public void resize(int width, int height) {
	}

	@Override
	public void show() {
		if (isInit) {
			stage.addActor(gameOverLabel);
			stage.addActor(scoreTextLabel);
			stage.addActor(scoreLabel);
			stage.addActor(bestTextLabel);
			stage.addActor(bestLabel);
			stage.addActor(replayLabel);

			// set text
			Preferences pref = Gdx.app.getPreferences(Data.prefName);
			int last = pref.getInteger(Data.lastScoreName, 0);
			scoreLabel.setText("" + last);

			int best = pref.getInteger(Data.bestScoreName, 0);
			bestLabel.setText("" + best);

			Gdx.app.log("game over screen", "last = " + last + ", best = "
					+ best);

			// Input processor.
			Gdx.input.setInputProcessor(new InputMultiplexer(stage,
					gestureDetector));

			// Background color
			stage.background.setColor(Data.gameOverColor);
		}
	}

	@Override
	public void hide() {
		Gdx.app.log("game over screen", "hide");

		// remove actors.
		gameOverLabel.remove();
		scoreTextLabel.remove();
		scoreLabel.remove();
		bestTextLabel.remove();
		bestLabel.remove();
		replayLabel.remove();

		// Input processor
		Gdx.input.setInputProcessor(null);
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

	void loadResources() {
	}

	void init() {
		stage = GameStage.getStage();
		stage.setGame(this.game);

		// Labels
		gameOverLabel = new Label("GAME OVER", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.WHITE));
		gameOverLabel.setPosition(
				(Data.width - gameOverLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 2.0f
						* Data.spikeHeight);
		stage.addActor(gameOverLabel);

		scoreTextLabel = new Label("SCORE", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.WHITE));
		scoreTextLabel.setPosition(
				(Data.width - scoreTextLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 4.0f
						* Data.spikeHeight);
		stage.addActor(scoreTextLabel);

		scoreLabel = new Label("" + 10, new Label.LabelStyle(assets.get(
				"size60.fnt", BitmapFont.class), Color.WHITE));
		scoreLabel.setPosition(
				(Data.width - scoreLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 5.0f
						* Data.spikeHeight);
		stage.addActor(scoreLabel);

		bestTextLabel = new Label("BEST", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.YELLOW));
		bestTextLabel.setPosition(
				(Data.width - bestTextLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 6.0f
						* Data.spikeHeight);
		stage.addActor(bestTextLabel);

		bestLabel = new Label("" + 13, new Label.LabelStyle(assets.get(
				"size60.fnt", BitmapFont.class), Color.YELLOW));
		bestLabel.setPosition(
				(Data.width - bestLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 7.0f
						* Data.spikeHeight);
		stage.addActor(bestLabel);

		replayLabel = new Label("REPLAY", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.BLACK));
		replayLabel.setPosition(
				(Data.width - replayLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 8.0f
						* Data.spikeHeight);
		stage.addActor(replayLabel);

		// set text
		int last = Gdx.app.getPreferences(Data.prefName).getInteger(
				Data.lastScoreName);
		scoreLabel.setText("" + last);

		int best = Gdx.app.getPreferences(Data.prefName).getInteger(
				Data.bestScoreName);
		bestLabel.setText("" + best);

		// Input processor
		TapGestureListener gesture = new TapGestureListener() {
			@Override
			public boolean tap(float x, float y, int count, int button) {
				Gdx.app.log("game over screen", "tap");
				if (!stage.ninja.isAwake()) {
					game.toGameScreen();
				}
				return true;
			}
		};
		gestureDetector = new GestureDetector(gesture);
		Gdx.input
				.setInputProcessor(new InputMultiplexer(stage, gestureDetector));

		// Background color
		stage.background.setColor(Data.gameOverColor);

		isInit = true;
	}
}
