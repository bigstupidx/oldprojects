package com.kivvi.theline.actors;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.kivvi.theline.resource.Data;

public class BonusBlock extends Block {
	private float w = Data.bonusSize;
	private float h = Data.bonusSize;

	public BonusBlock() {
		super("bonus");
		setColor(0.992f, 0.917f, 0.686f, 1);
		setSize(w, h);

		addAction(Actions.repeat(-1, Actions.sequence(
				Actions.color(new Color(1, 0.87f, 0.47f, 1), 0.2f),
				Actions.color(new Color(0.3f, 0.917f, 0.286f, 1), 0.2f))));
	}

	public String checkCollision(float x, float y, boolean isSmall) {
		String ret = null;

		Rectangle rect = new Rectangle();
		rect.x = getX();
		rect.y = getY();
		rect.width = getWidth();
		rect.height = getHeight();

		Rectangle rect2 = new Rectangle();
		rect2.x = x;
		rect2.y = y;

		float r;
		if (isSmall) {
			r = Data.smallBallR;
		} else {
			r = Data.ballR;
		}
		rect2.width = r;
		rect2.height = r;

		boolean overlap = rect.overlaps(rect2);

		if (overlap) {
			ret = getBlockName();
		}

		return ret;
	}
}
