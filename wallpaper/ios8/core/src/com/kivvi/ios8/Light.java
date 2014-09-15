package com.kivvi.ios8;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.equations.Quad;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.kivvi.tween.Entity;
import com.kivvi.tween.EntityAccessor;
import com.kivvi.tween.Manager;

public class Light extends Entity {

	private Texture texture;
	float positionY = 70;

	public Light(int index) {
		texture = IOS8.manager.get("data/" + index + ".png", Texture.class);

		float delayTime = 0.0f;
		delayTime = (index % 4) * 0.5f;

		float deltaX;
		deltaX = (index % 4) * 40.0f;

		Tween.to(this, EntityAccessor.TWEEN_ALPHA, 2.0f).target(0.5f)
				.repeatYoyo(Tween.INFINITY, 0).ease(Quad.INOUT)
				.delay(delayTime).start(Manager.get());

		Tween.to(this, EntityAccessor.TWEEN_POSITION, 3.0f)
				.target(deltaX, 0.0f).repeatYoyo(Tween.INFINITY, 0)
				.ease(Quad.INOUT).delay(delayTime).start(Manager.get());
	}

	public void draw(Batch batch) {
		Color c = batch.getColor();
		int src = batch.getBlendSrcFunc();
		int dst = batch.getBlendDstFunc();
		batch.setColor(this.getColor());
		batch.setBlendFunction(GL20.GL_BLEND_SRC_ALPHA,
				GL20.GL_ONE_MINUS_SRC_ALPHA);
		batch.draw(texture, this.getX() + IOS8.acceler.getX(),
				positionY + IOS8.acceler.getY());
		batch.setColor(c);
		batch.setBlendFunction(src, dst);
	}

	public void setPositionY(float positionY) {
		this.positionY = positionY;
	}
}
