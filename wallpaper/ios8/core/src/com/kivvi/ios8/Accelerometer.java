package com.kivvi.ios8;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.math.Vector2;
import com.kivvi.tween.Entity;
import com.kivvi.wallpaper.Properties;

public class Accelerometer extends Entity {
	Vector2 avg = new Vector2(0, 0);
	float accDeltaTime = 1.0f;
	float bgWidth;
	float bgHeight;
	final int nos = 10;

	Accelerometer(float width, float height) {
		super();

		bgWidth = width;
		bgHeight = height;

		setX(-bgWidth * IOS8.borderWidth);
		setY(-bgHeight * IOS8.borderHeight);
	}

	void update() {
		if (Properties.get("gsensor")) {
			// offset's range: (-2 * width * border, -2 * height * border) - (0,
			// 0)
			Vector2 acc = new Vector2(Gdx.input.getAccelerometerX(),
					Gdx.input.getAccelerometerY());
			avg.x = (avg.x * (nos - 1) + acc.x) / nos;
			avg.y = (avg.y * (nos - 1) + acc.y) / nos;
			float x = bgWidth * IOS8.borderWidth * (-1.0f + avg.x / 10.0f);
			float y = bgHeight * IOS8.borderHeight * (-1.0f + avg.y / 10.0f);

			setX(x);
			setY(y);
		}
	}
}
