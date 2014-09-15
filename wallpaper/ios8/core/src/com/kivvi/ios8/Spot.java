package com.kivvi.ios8;

import java.util.Random;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.equations.Quad;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.kivvi.tween.Entity;
import com.kivvi.tween.EntityAccessor;
import com.kivvi.tween.Manager;
import com.kivvi.wallpaper.Properties;

public class Spot extends Entity {
	public static Texture texture = null;
	public static Texture weakTexture = null;
	boolean weak = false;

	public static void resetTextures() {
		texture = null;
		weakTexture = null;
	}

	public Spot(Random rand) {
		this(rand, false);
	}

	public Spot(Random rand, boolean weak) {
		super();

		this.weak = weak;

		if (texture == null) {
			texture = IOS8.manager.get("data/spot.png", Texture.class);
		}
		if (weakTexture == null) {
			weakTexture = IOS8.manager.get("data/spot-weak.png", Texture.class);
		}

		if (Properties.get("twinkle")) {
			float delayTime = rand.nextFloat() * 3;
			float duration = rand.nextFloat() * 2.0f + 1.0f;
			Tween.to(this, EntityAccessor.TWEEN_ALPHA, duration).target(0.0f)
					.repeatYoyo(Tween.INFINITY, 0).ease(Quad.INOUT)
					.delay(delayTime).start(Manager.get());
		}
	}

	public void draw(Batch batch) {
		Color c = batch.getColor();
		batch.setColor(this.getColor());
		Texture tex;
		if (weak) {
			tex = weakTexture;
		} else {
			tex = texture;
		}
		batch.draw(tex, getX() + IOS8.acceler.getX(),
				getY() + IOS8.acceler.getY(), tex.getWidth() * getScale(),
				tex.getHeight() * getScale());
		batch.setColor(c);
	}
}
