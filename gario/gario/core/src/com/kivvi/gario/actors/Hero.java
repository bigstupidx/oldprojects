package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class Hero extends Tile {
	public int ap;
	public int mp;
	public int hp;
	public boolean key;

	public Hero() {
		super();

		ap = 1;
		hp = 100;
		mp = 3;
		key = false;
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {

	}

	public void nextLevel() {
		key = false;
	}

	public void setKey() {
		key = true;
	}

	public boolean hasKey() {
		return key;
	}

	public void log() {
		Gdx.app.log("info", "hero: ap " + ap + ", hp " + hp);
	}
}
