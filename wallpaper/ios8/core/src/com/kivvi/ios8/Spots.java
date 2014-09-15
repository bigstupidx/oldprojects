package com.kivvi.ios8;

import java.util.Random;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class Spots extends Actor {

	private Spot spots[];
	private int num;
	final int count = 200;

	Spots() {
		spots = new Spot[count];
		num = 0;

		init();
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		for (int i = 0; i < count; i++) {
			if (spots[i] != null)
				spots[i].draw(batch);
		}
	}

	void createArea(Rectangle rect, int count) {
		createAreaWithWeak(rect, count, false);
	}

	void createAreaWithWeak(Rectangle rect, int count, boolean weak) {
		Random rand = new Random(System.currentTimeMillis());
		for (int i = num; i < num + count; i++) {
			float x = rect.x + rand.nextInt((int) rect.width);
			float y = rect.y + rand.nextInt((int) rect.height);
			Color c = new Color(1, 1, 1, 1);
			// 0.5 - 1.0
			c.a = rand.nextFloat() / 2 + 0.5f;
			float scale;
			if (weak) {
				// 0.4 - 0.7
				scale = rand.nextFloat() / 3 + 0.4f;
			} else {
				// 0.3 - 1.3
				scale = rand.nextFloat() + 0.3f;
			}
			spots[i] = new Spot(rand, weak);
			spots[i].setX(x);
			spots[i].setY(y);
			spots[i].setColor(c);
			spots[i].setScale(scale);
		}
		num += count;
	}

	void createAreaEx(Rectangle rect, int widths[], int heights[],
			int counts[], int count) {
		Rectangle newRect = new Rectangle();
		float x = rect.x;
		float y = rect.y;
		int size = widths.length;
		for (int i = 0; i < size; i++) {
			newRect.width = rect.width * widths[i] / 100;
			newRect.height = rect.height * heights[i] / 100;
			newRect.x = x;
			// keep center
			newRect.y = y + (rect.height - newRect.height) / 2;
			// Gdx.app.log("debug", i + "-newRect = " + newRect.toString());
			createArea(newRect, count * counts[i] / 100);
			x += newRect.width;
		}
	}

	public void reset() {
		spots = new Spot[count];
		num = 0;

		init();
	}

	void init() {
		Spot.resetTextures();

		// create 70 spots in area 1.
		Rectangle rect = new Rectangle();
		rect.set(0, 1136 - 330, 250, 30);
		int widths[] = { 10, 20, 30, 20, 10, 10 };
		int heights[] = { 33, 66, 100, 66, 33, 17 };
		int counts[] = { 10, 20, 30, 20, 10, 5 };
		createAreaEx(rect, widths, heights, counts, 70);

		// create 70 spots in area 2.
		rect.set(640 - 360, 1136 - 300, 60, 20);
		createArea(rect, 15);
		rect.set(640 - 360 + 60, 1136 - 300, 240, 30);
		createArea(rect, 50);
		rect.set(640 - 360 + 300, 1136 - 300, 60, 20);
		createArea(rect, 15);

		// create 20 spots in area 3.
		rect.set(640 - 300, 1136 - 400, 300, 10);
		createAreaWithWeak(rect, 20, true);
	}
}
