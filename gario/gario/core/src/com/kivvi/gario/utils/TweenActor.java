package com.kivvi.gario.utils;

import aurelienribon.tweenengine.BaseTween;
import aurelienribon.tweenengine.TweenCallback;

import com.badlogic.gdx.scenes.scene2d.Actor;

public abstract class TweenActor extends Actor implements TweenCallback {

	@Override
	public abstract void onEvent(int type, BaseTween<?> source);

}
