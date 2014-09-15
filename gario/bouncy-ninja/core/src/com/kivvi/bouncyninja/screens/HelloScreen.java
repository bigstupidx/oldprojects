package com.kivvi.bouncyninja.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.CommonStage;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.Box2dRenderer;
import com.kivvi.bouncyninja.utils.TapGestureListener;

public class HelloScreen implements Screen {

	AssetManager assets = null;
	boolean isInit = false;
	CommonStage stage = null;
	BouncyNinjaGame game;
	Label title;
	Label prompt;
	GestureDetector gestureDetector;

	public HelloScreen(BouncyNinjaGame game) {
		this.game = game;

		assets = GameAssets.getAssets();
		loadResources();
	}

	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(0, 0, 0, 0);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		if (!assets.update()) {
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
			Gdx.input.setInputProcessor(new InputMultiplexer(stage,
					gestureDetector));
		}
	}

	@Override
	public void hide() {
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
		title.remove();
		title = null;

		prompt.remove();
		prompt = null;

		stage = null;

		Gdx.input.setInputProcessor(null);
	}

	void loadResources() {
		assets.load("ninja.png", Texture.class);
		assets.load("spike.png", Texture.class);
		assets.load("spike_blood.png", Texture.class);
		assets.load("whiteDot.png", Texture.class);
		assets.load("blackDot.png", Texture.class);
		assets.load("size60.fnt", BitmapFont.class);
		assets.load("size80.fnt", BitmapFont.class);

		assets.load("tap_jump.wav", Sound.class);
		assets.load("game_over.wav", Sound.class);
		assets.load("new_item.wav", Sound.class);
		assets.load("wall_jump.wav", Sound.class);
		assets.load("record.wav", Sound.class);
	}

	void init() {
		stage = GameStage.getStage();
		stage.setGame(this.game);

		// Labels
		title = new Label("BOUNCY NINJA", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.WHITE));
		title.setPosition((Data.width - title.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 2.0f
						* Data.spikeHeight);
		stage.addActor(title);

		prompt = new Label("TAP TO START", new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Color.WHITE));
		prompt.setPosition((Data.width - prompt.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + 2.0f * Data.spikeHeight);
		prompt.addAction(Actions.delay(
				2,
				Actions.repeat(
						-1,
						Actions.sequence(Actions.alpha(0, 1.0f),
								Actions.alpha(1, 1.0f), Actions.delay(1.5f)))));
		stage.addActor(prompt);

		// Input Processor.
		TapGestureListener gesture = new TapGestureListener() {
			@Override
			public boolean tap(float x, float y, int count, int button) {
				Gdx.app.log("debug", "tap on screen.");
				HelloScreen.this.game.toGameScreen();
				return true;
			}
		};
		gestureDetector = new GestureDetector(gesture);
		Gdx.input
				.setInputProcessor(new InputMultiplexer(stage, gestureDetector));

		// set init flag to true.
		isInit = true;
	}
}
