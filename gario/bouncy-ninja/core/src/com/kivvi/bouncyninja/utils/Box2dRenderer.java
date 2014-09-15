package com.kivvi.bouncyninja.utils;

import com.badlogic.gdx.physics.box2d.Box2DDebugRenderer;

public class Box2dRenderer {
	public static Box2DDebugRenderer renderer = null;

	public static Box2DDebugRenderer getRenderer() {
		if (renderer == null) {
			renderer = new Box2DDebugRenderer();
		}
		return renderer;
	}

	public static void dispose() {
		if (renderer != null) {
			renderer.dispose();
			renderer = null;
		}
	}
}
