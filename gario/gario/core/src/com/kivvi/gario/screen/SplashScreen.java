package com.kivvi.gario.screen;

import aurelienribon.tweenengine.BaseTween;
import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenCallback;
import aurelienribon.tweenengine.TweenEquations;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.Scaling;
import com.badlogic.gdx.utils.viewport.ScalingViewport;
import com.kivvi.gario.Gario;
import com.kivvi.gario.utils.ActorAccessor;
import com.kivvi.gario.utils.TweenActor;

public class SplashScreen implements Screen {

	private Game game;
	private TweenActor splash;
	private Stage stage;
	private AssetManager manager;
	private Texture tex;

	private class Splash extends TweenActor {
		@Override
		public void draw(Batch batch, float parentAlpha) {
			batch.setColor(this.getColor());
			batch.draw(tex, 0, 0);
		}

		@Override
		public void onEvent(int type, BaseTween<?> source) {
			if (type == TweenCallback.END || type == TweenCallback.COMPLETE) {
				// go to next screen.
				game.setScreen(new MainScreen(game));
				SplashScreen.this.dispose();
			}
		}
	}

	/**
	 * Constructor for the splash screen
	 * 
	 * @param g
	 *            Game which called this splash screen.
	 */
	public SplashScreen(Game game) {
		this.game = game;

		// load texture.
		manager = new AssetManager();
		manager.load("logo.jpg", Texture.class);
		manager.finishLoading();

		tex = manager.get("logo.jpg", Texture.class);

		stage = new Stage(new ScalingViewport(Scaling.fill, tex.getWidth(),
				tex.getHeight(), new OrthographicCamera()));
		splash = new Splash();
		stage.addActor(splash);

		// start tween animation.
		Tween.to(splash, ActorAccessor.COLOR, 1).target(1, 1, 1, 0)
				.ease(TweenEquations.easeOutCubic)
				.start(Gario.getTweenManager()).delay(1).setCallback(splash);
	}

	@Override
	public void render(float delta) {
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		stage.draw();
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
		manager.dispose();
	}

}
