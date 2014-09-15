package com.kivvi.ios8;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class Background extends Actor {
	Texture bg;

	Background(Texture bg) {
		this.bg = bg;
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		batch.draw(bg, IOS8.acceler.getX(), IOS8.acceler.getY());
	}
}
