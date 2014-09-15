package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class Cover extends Actor {
	private Texture texture;
	private boolean map[][] = new boolean[5][6];

	public Cover() {
		texture = new Texture(Gdx.files.internal("cover.png"));
	}
}
