package com.kivvi.tween;

import aurelienribon.tweenengine.TweenAccessor;

import com.badlogic.gdx.graphics.Color;

public class EntityAccessor implements TweenAccessor<Entity> {

	public static final int TWEEN_POSITION = 0;
	public static final int TWEEN_ALPHA = 1;

	@Override
	public int getValues(Entity target, int tweenType, float[] returnValues) {
		switch (tweenType) {
		case TWEEN_POSITION:
			returnValues[0] = target.getX();
			returnValues[1] = target.getY();
			return 2;
		case TWEEN_ALPHA:
			returnValues[0] = target.getColor().a;
			return 1;
		default:
			break;
		}
		return 0;
	}

	@Override
	public void setValues(Entity target, int tweenType, float[] newValues) {
		switch (tweenType) {
		case TWEEN_POSITION:
			target.setX(newValues[0]);
			target.setY(newValues[1]);
			break;
		case TWEEN_ALPHA:
			Color c = target.getColor();
			c.a = newValues[0];
			target.setColor(c);
			break;
		default:
			break;
		}
	}

}
