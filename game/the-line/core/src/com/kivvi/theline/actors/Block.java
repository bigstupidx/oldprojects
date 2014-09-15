package com.kivvi.theline.actors;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class Block extends Actor {
	private String blockName = null;
	protected Sprite sprite;

	public String checkCollision(float x, float y, boolean isSmall) {
		if (y > getY() + getHeight() || y + Data.ballD < getY())
			return null;

		Rectangle rect = new Rectangle();
		rect.x = getX();
		rect.y = getY();
		rect.width = getWidth();
		rect.height = getHeight();

		float r;
		float a;

		if (!isSmall) {
			r = Data.ballR;
			a = 0.707f;
		} else {
			r = Data.smallBallR;
			a = (float) Math.sqrt(r);
		}

		float x1 = -r;
		float y1 = 0;
		float x2 = -a;
		float y2 = a;
		float x3 = 0;
		float y3 = r;
		float x4 = a;
		float y4 = a;
		float x5 = r;
		float y5 = 0;
		float x6 = a;
		float y6 = -a;
		float x7 = 0;
		float y7 = -r;
		float x8 = -a;
		float y8 = -a;

		x = x + r;
		y = y + r;

		if (rect.contains(new Vector2(x + x1, y + y1))
				|| rect.contains(new Vector2(x + x2, y + y2))
				|| rect.contains(new Vector2(x + x3, y + y3))
				|| rect.contains(new Vector2(x + x4, y + y4))
				|| rect.contains(new Vector2(x + x5, y + y5))
				|| rect.contains(new Vector2(x + x6, y + y6))
				|| rect.contains(new Vector2(x + x7, y + y7))
				|| rect.contains(new Vector2(x + x8, y + y8))) {
			return blockName;
		}

		return null;
	}

	protected Block(String name) {
		blockName = name;
		sprite = new Sprite();
		Texture t = GameAssets.getAssets().get("c.png");
		sprite.setTexture(t);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		sprite.setPosition(getX(), getY());
		sprite.setSize(getWidth(), getHeight());
		sprite.setColor(getColor());
		sprite.draw(batch, parentAlpha);
	}

	public String getBlockName() {
		return blockName;
	}

	public void addToStage(Stage stage) {
		stage.addActor(this);
	}
}
