package com.kivvi.tween;

import aurelienribon.tweenengine.TweenManager;

public class Manager {
	private static TweenManager manager = new TweenManager();

	public static TweenManager get() {
		return Manager.manager;
	}
}
