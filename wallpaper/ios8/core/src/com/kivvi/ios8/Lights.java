package com.kivvi.ios8;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.wallpaper.Properties;

public class Lights extends Actor {
	private Light lights[];

	public Lights() {
		lights = new Light[8];
		for (int i = 0; i < 8; i++) {
			lights[i] = new Light(i + 1);
		}
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		if (Properties.get("wave")) {
			return;
		}

		for (int i = 0; i < 8; i++) {
			lights[i].draw(batch);
		}
	}

}
