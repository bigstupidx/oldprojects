package com.kivvi.bouncyninja.screens;

import java.util.Random;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.CommonStage;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.Box2dRenderer;
import com.kivvi.bouncyninja.utils.SoundManager;
import com.kivvi.bouncyninja.utils.TapGestureListener;

public class GameScreen implements Screen {
	CommonStage stage = null;
	boolean isInit = false;
	Image pauseImage;
	Label scoreLabel;
	Label pauseLabel;
	AssetManager assets;
	Random rand;
	BouncyNinjaGame game;
	GestureDetector gestureDetector;
	boolean pause = false;
	boolean newRecord = false;

	// Game data
	public int score = 0;

	public GameScreen(BouncyNinjaGame game) {
		this.game = game;

		assets = GameAssets.getAssets();
		loadResources();

		rand = new Random(System.currentTimeMillis());
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
		if (!pause) {
			stage.act(Gdx.graphics.getDeltaTime());
		}

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
		Gdx.app.log("game screen", "show");
		if (isInit) {
			// add actors.
			stage.addActor(pauseImage);
			stage.addActor(scoreLabel);

			this.reset();
			this.start();

			// set input processor.
			Gdx.input.setInputProcessor(new InputMultiplexer(stage,
					gestureDetector));

			// Background color
			stage.background.setColor(Data.initColor);

			// score label
			scoreLabel.setText("" + score);
			scoreLabel.setPosition(
					(Data.width - scoreLabel.getTextBounds().width) / 2,
					(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 2.3f
							* Data.spikeHeight);
			
			pause = false;
			newRecord = false;
		}
	}

	@Override
	public void hide() {
		Gdx.app.log("game screen", "hide");

		// save score
		Preferences pref = Gdx.app.getPreferences(Data.prefName);
		pref.putInteger(Data.lastScoreName, score);

		int best = pref.getInteger(Data.bestScoreName);
		if (score > best) {
			pref.putInteger(Data.bestScoreName, score);
		}
		pref.flush();
		Gdx.app.log("game screen", "save score: " + score + ", best = " + best);

		// Input processor
		Gdx.input.setInputProcessor(null);

		// remove actors.
		pauseImage.remove();
		scoreLabel.remove();
		pauseLabel.remove();
	}

	@Override
	public void pause() {
		pauseGame();
	}

	@Override
	public void resume() {
	}

	@Override
	public void dispose() {
		// actors and stage
		if (pauseImage != null) {
			pauseImage.remove();
			pauseImage = null;
		}

		if (scoreLabel != null) {
			scoreLabel.remove();
			scoreLabel = null;
		}

		stage = null;

		// assets
		assets = null;
	}

	void loadResources() {
		assets.load("pause.png", Texture.class);
	}

	void init() {
		stage = GameStage.getStage();
		stage.setGame(this.game);

		// add pause image
		pauseImage = new Image(assets.get("pause.png", Texture.class));
		pauseImage.setSize(Data.pauseImageWidth * Data.pauseImageScale,
				Data.pauseImageHeight * Data.pauseImageScale);
		pauseImage.setPosition((Data.width - pauseImage.getWidth()) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 1.5f
						* Data.spikeHeight);
		stage.addActor(pauseImage);

		pauseImage.setTouchable(Touchable.enabled);
		pauseImage.setColor(Data.scoreColor);
		pauseImage.addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				Gdx.app.log("Game Screen", "pause image touchdown");
				if (pause) {
					resumeGame();
				} else {
					pauseGame();
				}
				return true;
			}
		});

		// add lavel score
		scoreLabel = new Label("" + score, new Label.LabelStyle(assets.get(
				"size80.fnt", BitmapFont.class), Data.scoreColor));
		scoreLabel.setPosition(
				(Data.width - scoreLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 2.3f
						* Data.spikeHeight);
		stage.addActor(scoreLabel);

		// create pause label but not add
		pauseLabel = new Label("TAP TO RESUME", new Label.LabelStyle(
				assets.get("size80.fnt", BitmapFont.class), Color.WHITE));
		pauseLabel.setPosition(
				(Data.width - pauseLabel.getTextBounds().width) / 2,
				(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 5.0f
						* Data.spikeHeight);

		// stop actions.
		for (int i = 0; i < stage.topSpikes.length; i++) {
			stage.topSpikes[i].clearActions();
			stage.topSpikes[i].setRotation(0);

			stage.bottomSpikes[i].clearActions();
			stage.bottomSpikes[i].setRotation(0);
		}

		// remove left & right spikes.
		for (int i = 0; i < stage.leftSpikes.length; i++) {
			stage.leftSpikes[i].setRotation(0);
			stage.leftSpikes[i].setEnable(false);

			stage.rightSpikes[i].setRotation(0);
			stage.rightSpikes[i].setEnable(false);
		}

		// Start game
		this.start();

		// Input processor
		TapGestureListener gesture = new TapGestureListener() {
			@Override
			public boolean tap(float x, float y, int count, int button) {
				Gdx.app.log("Game Screen", "tap");
				if (pause) {
					resumeGame();
				} else {
					stage.ninja.jump();
				}
				return true;
			}
		};
		gestureDetector = new GestureDetector(gesture);
		Gdx.input
				.setInputProcessor(new InputMultiplexer(stage, gestureDetector));

		// Background color
		stage.background.setColor(Data.initColor);

		isInit = true;
	}

	void genSpikes() {
		// get count
		int difficult = Math.min(score / 2, 5);
		int count = 0;
		if (difficult > 0)
			count = rand.nextInt((int) difficult) + 1;

		// init spikes array
		int spikes[] = new int[Data.row - 1];
		for (int i = 0; i < Data.row - 1; i++)
			spikes[i] = -1;

		// get spikes array
		int length = 0;
		while (length < count) {
			int index = rand.nextInt(Data.row - 1);
			if (spikes[length] == -1) {
				spikes[length] = index;
				length++;
			}
		}

		for (int i = 0; i < count; i++) {
			if (spikes[i] != -1) {
				Gdx.app.log("genSpikes", "" + spikes[i]);
				if (stage.ninja.toRight) {
					stage.rightSpikes[spikes[i]].setEnable(true);
				} else {
					stage.leftSpikes[spikes[i]].setEnable(true);
				}
			}
		}
	}

	public void turnOver() {
		if (game.getScreen() == this) {
			score++;
			scoreLabel.setText("" + score);
			scoreLabel.setPosition(
					(Data.width - scoreLabel.getTextBounds().width) / 2,
					(Data.height - Data.gameHeight) / 2 + Data.gameHeight - 2.3f
							* Data.spikeHeight);
			
			// remove left & right spikes.
			for (int i = 0; i < stage.leftSpikes.length; i++) {
				stage.leftSpikes[i].setRotation(0);
				stage.leftSpikes[i].setEnable(false);

				stage.rightSpikes[i].setRotation(0);
				stage.rightSpikes[i].setEnable(false);
			}

			genSpikes();

			stage.background.switchColor(score);
			
			// New Record
			Preferences pref = Gdx.app.getPreferences(Data.prefName);
			int best = pref.getInteger(Data.bestScoreName);
			if (score > best && best != 0 && !newRecord) {
				SoundManager.play(SoundManager.Type.NewRecord);
				newRecord = true;
			}
		}
	}

	public void reset() {
		if (stage != null) {
			stage.ninja.reset();

			// remove left & right spikes.
			for (int i = 0; i < stage.leftSpikes.length; i++) {
				stage.leftSpikes[i].setRotation(0);
				stage.leftSpikes[i].setEnable(false);

				stage.rightSpikes[i].setRotation(0);
				stage.rightSpikes[i].setEnable(false);
			}
		}

		score = 0;
	}

	public void start() {
		if (stage != null) {
			stage.ninja.setActive(true);
			stage.ninja.jump();
		}

		genSpikes();
	}

	void pauseGame() {
		pause = true;

		stage.addActor(pauseLabel);
	}

	void resumeGame() {
		pause = false;

		pauseLabel.remove();

		stage.ninja.jump();
	}
}
