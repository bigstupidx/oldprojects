package com.kivvi.tween;

import com.badlogic.gdx.graphics.Color;

public class Entity {
	private Color color;
	private float x;
	private float y;
	private float scale;

	public Entity() {
		color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
		x = 0;
		y = 0;
		scale = 1.0f;
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
	}

	public float getX() {
		return x;
	}

	public void setX(float x) {
		this.x = x;
	}

	public float getY() {
		return y;
	}

	public void setY(float y) {
		this.y = y;
	}

	public float getScale() {
		return scale;
	}

	public void setScale(float scale) {
		this.scale = scale;
	}
}
