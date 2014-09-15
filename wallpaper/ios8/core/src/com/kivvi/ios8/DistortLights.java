package com.kivvi.ios8;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class DistortLights extends Actor {
	private Light lights[];

	public DistortLights() {
		lights = new Light[8];
		for (int i = 0; i < 8; i++) {
			lights[i] = new Light(i + 1);
			lights[i].setPositionY(300);
		}
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		for (int i = 0; i < 8; i++) {
			lights[i].draw(batch);
		}
	}

}
