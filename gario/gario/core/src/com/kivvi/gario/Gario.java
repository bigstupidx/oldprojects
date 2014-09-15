package com.kivvi.gario;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenManager;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.gario.screen.MainScreen;
import com.kivvi.gario.screen.SplashScreen;
import com.kivvi.gario.utils.ActorAccessor;

public class Gario extends Game {

	private static TweenManager tweenManager = null;

	@Override
	public void create() {
		// init tween manager.
		tweenManager = new TweenManager();
		Tween.setCombinedAttributesLimit(4);
		Tween.registerAccessor(Actor.class, new ActorAccessor());

		this.setScreen(new MainScreen(this));
	}

	@Override
	public void render() {
		super.render();

		tweenManager.update(Gdx.graphics.getDeltaTime());
	}

	public static TweenManager getTweenManager() {
		return tweenManager;
	}
}
