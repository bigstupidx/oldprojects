package com.kivvi.theline.screens;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.badlogic.gdx.utils.viewport.StretchViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.kivvi.theline.game.TheLineGame;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class MenuScreen extends BaseScreen {
	private Stage stage = null;
	private Image menuString = null;
	private Image tryAgain = null;
	private Image rate = null;
	private Image volumnSwitch = null;
	private Sound stepSound = null;
	private boolean volumn = false;
	
	public MenuScreen(TheLineGame game) {
		super(game);
	}

	@Override
	public void show() {
		Preferences prefs =  Gdx.app.getPreferences(Data.prefName);
		
		volumn = prefs.getBoolean("volumn");
		
		stage = new Stage(new StretchViewport(720, 1280));
		
		Texture menuTexture = GameAssets.getAssets().get("menutitle.png");
		menuString = new Image(menuTexture);
		menuString.setSize(605, 86);
		menuString.setPosition(60, 1116);
		
		String volumnImagePath;
		if (volumn) {
			volumnImagePath = "volumnon.png";
		} else {
			volumnImagePath = "volumnoff.png";
		}
		
		Texture volumnTexture = GameAssets.getAssets().get(volumnImagePath);
		volumnSwitch = new Image(volumnTexture);
		volumnSwitch.setSize(96, 90);
		volumnSwitch.setPosition(580, 1116);
		volumnSwitch.addListener(new InputListener(){

			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				Preferences prefs =  Gdx.app.getPreferences(Data.prefName);
//				Music bgMusic = GameAssets.getAssets().get("music.wav");
				
				if (prefs.getBoolean("volumn")) {
					prefs.putBoolean("volumn", false);
//					bgMusic.pause();
					Texture volumnTexture = GameAssets.getAssets().get("volumnoff.png");
					volumnSwitch.setDrawable(new TextureRegionDrawable(new TextureRegion(volumnTexture)));
				} else {
					prefs.putBoolean("volumn", true);
//					bgMusic.play();
//					bgMusic.setLooping(true);
					Texture volumnTexture = GameAssets.getAssets().get("volumnon.png");
					volumnSwitch.setDrawable(new TextureRegionDrawable(new TextureRegion(volumnTexture)));
				}
				prefs.flush();
			}
		});
		
		Texture tryAgainTexture = GameAssets.getAssets().get("tryagain.png");
		tryAgain = new Image(tryAgainTexture);
		tryAgain.setSize(451, 135);
		tryAgain.setPosition(135, 900);
		tryAgain.addListener(new InputListener(){

			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				if (volumn) stepSound.play(1);
				toGameScreen();
			}
		});
		
		Texture rateTexture = GameAssets.getAssets().get("rate.png");
		rate = new Image(rateTexture);
		rate.setSize(451, 135);
		rate.setPosition(135, 720);	
		rate.addListener(new InputListener(){
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				game.rate();
				if (volumn) stepSound.play(1);
			
			}
			
		});
		
		stage.addActor(menuString);
		stage.addActor(tryAgain);
		stage.addActor(rate);
		stage.addActor(volumnSwitch);
		
		stepSound = GameAssets.getAssets().get("step.wav");
		
		Gdx.input.setInputProcessor(stage);
	}

	public void toGameScreen() {
		game.setScreen(game.gameScreen);
	}
	
	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(1, 0.11f, 0.262f, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
		
		Gdx.app.log("fps", "fps = " + Gdx.graphics.getFramesPerSecond());
		
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
