package com.kivvi.theline.actors;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class ScoreBlock extends Block {
	private Image x6 = null;

	public ScoreBlock() {
		super("score");
		float w = Data.blockWidth;
		float h = Data.blockHeight;
		setColor(0.992f, 0.917f, 0.686f, 1);
		setSize(w, h);

		addAction(Actions.repeat(-1, Actions.sequence(
				Actions.color(new Color(1, 0.87f, 0.47f, 1), 0.6f),
				Actions.color(new Color(0.992f, 0.917f, 0.686f, 1), 0.6f))));

		Texture t = GameAssets.getAssets().get("x6.png");
		x6 = new Image(t);
		x6.setSize(44, 44);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		super.draw(batch, parentAlpha);
		x6.setPosition(getX() + (Data.blockWidth - 44) / 2, getY()
				+ (Data.blockHeight - 44) / 2);
		x6.draw(batch, parentAlpha);
	}

}
