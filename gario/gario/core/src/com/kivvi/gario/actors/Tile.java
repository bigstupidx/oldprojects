package com.kivvi.gario.actors;

import com.badlogic.gdx.scenes.scene2d.Actor;

public class Tile extends Actor {
	public Tile() {
		this.setSize(96, 96);
	}
	
	@Override
	public void setX(float x) {
		x = x * this.getWidth();
		super.setX(x);
	}
	
	@Override
	public void setY(float y) {
		y = y * this.getHeight();
		super.setY(y);
	}
}
