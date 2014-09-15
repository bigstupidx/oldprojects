package com.kivvi.theline.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.Group;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.badlogic.gdx.utils.viewport.StretchViewport;
import com.kivvi.theline.game.TheLineGame;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class GameOverScreen extends BaseScreen {
	private Stage stage = null;
	private Image gameOver = null;
	private Image scoreBoard = null;
	private Image scoreString = null;
	private Image bestString = null;
	private Image tryAgain = null;
	private Image share = null;
	
	private Group score = null;
	private Group best = null;

	private int scoreNum;
	private int bestNum;
	private boolean isNewBest;
	private boolean volumn;
	private Sound stepSound = null;
	
	public GameOverScreen(TheLineGame game) {
		super(game);
	}

	@Override
	public void show() {
		Preferences prefs =  Gdx.app.getPreferences(Data.prefName);
		
		scoreNum = prefs.getInteger("score");
		bestNum = prefs.getInteger("best");
		isNewBest = prefs.getBoolean("new best");
		volumn = prefs.getBoolean("volumn");
		
		score = new Group();
		best = new Group();
		
		stage = new Stage(new StretchViewport(720, 1280));
		Texture gameOverTexture = GameAssets.getAssets().get("gameover.png");
		gameOver = new Image(gameOverTexture);
		gameOver.setSize(605, 86);
		gameOver.setPosition(60, 1116);
		stage.addActor(gameOver);
		
		Texture tryAgainTexture = GameAssets.getAssets().get("tryagain.png");
		tryAgain = new Image(tryAgainTexture);
		tryAgain.setSize(451, 135);
		tryAgain.setPosition(135, 388);
		tryAgain.addListener(new InputListener(){

			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				toGameScreen();
				if (volumn) stepSound.play(1);
			}
			
		});
		
		Texture scoreStringTexture = GameAssets.getAssets().get("sc.png");
		scoreString = new Image(scoreStringTexture);
		scoreString.setSize(112, 27);
		scoreString.setPosition(304, 979);
		
		Texture bestStringTexture = GameAssets.getAssets().get("best.png");
		bestString = new Image(bestStringTexture);
		bestString.setSize(112, 27);
		bestString.setPosition(304, 854);
		
		Texture shareTexture = GameAssets.getAssets().get("share.png");
		share = new Image(shareTexture);
		share.setSize(451, 135);
		share.setPosition(135, 568);
		share.addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				game.share();
				if (volumn) stepSound.play(1);
			}
		});
		
		if (isNewBest) {
			Texture scoreBoardTexture = GameAssets.getAssets().get("newbest.png");
			scoreBoard = new Image(scoreBoardTexture);
			scoreBoard.setSize(451, 284);
			scoreBoard.setPosition(135, 748);

			bestString.setPosition(304, 854);
			share.setPosition(135, 568);
			tryAgain.setPosition(135, 388);
			
			stage.addActor(tryAgain);
			stage.addActor(scoreBoard);
			stage.addActor(score);
			stage.addActor(share);
		} else {
			Texture scoreBoardTexture = GameAssets.getAssets().get("scoreboard.png");
			scoreBoard = new Image(scoreBoardTexture);
			scoreBoard.setSize(451, 284);
			scoreBoard.setPosition(135, 748);
			
			stage.addActor(tryAgain);
			stage.addActor(scoreBoard);
			stage.addActor(scoreString);
			stage.addActor(bestString);
			stage.addActor(score);
			stage.addActor(best);
			stage.addActor(share);
		}

		
		updateScore(isNewBest);
		
		stepSound = GameAssets.getAssets().get("step.wav");
		
		Gdx.input.setInputProcessor(stage);
	}

	public void updateScore(boolean isNewBest) {
		AssetManager assets = GameAssets.getAssets();
		
		score.clearChildren();
		best.clearChildren();
		
		float gap = 7f;
		float w = 28;
		String scoreString = String.valueOf(scoreNum);
		int length = scoreString.length();
		float startX = 346;
		startX -= (length - 1) * (14f + 3.5f);
		for (int i = 0; i < length; i++) {
			Texture texture = assets.get("white/" + scoreString.charAt(i) + ".png");
			Image num = new Image(texture);
			num.setSize(28, 40);	
			num.setPosition(startX + (w + gap) * i, 912);
			if (isNewBest) {
				num.setColor(0.992f, 0.917f, 0.686f, 1);
				num.setY(num.getY() - 90);
			} else {
				num.setColor(1, 0.11f, 0.262f, 1);	
			}
			
			score.addActor(num);
		}
		
		if (!isNewBest) {
			String bestString = String.valueOf(bestNum);
			length = bestString.length();
			startX = 346 - (length - 1) * (14f + 3.5f);
			for (int i = 0; i < length; i++) {
				Texture texture = assets.get("white/" + bestString.charAt(i) + ".png");
				Image num = new Image(texture);
				num.setSize(28, 40);	
				num.setPosition(startX + (w + gap) * i, 781);
				num.setColor(1, 0.11f, 0.262f, 1);
				best.addActor(num);
			}
		}
	}
	
	public void toGameScreen() {
		game.setScreen(game.gameScreen);
	}
	
	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(1, 0.11f, 0.262f, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		stage.draw();
	}

	@Override
	public void hide() {
		stage.dispose();
	}

	@Override
	public void dispose() {

	}

}
