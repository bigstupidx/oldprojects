package com.kivvi.theline.actors;

import com.badlogic.gdx.scenes.scene2d.Stage;
import com.kivvi.theline.resource.Data;

public class YellowBlock extends Block {
	static public int count = 0;

	private float w = Data.blockWidth;
	private float h = Data.blockHeight;
	public BonusBlock bonus = null;

	public YellowBlock() {
		super("yellow");
		setColor(0.992f, 0.917f, 0.686f, 1);
		setSize(w, h);

		if (count++ > 100) {
			bonus = new BonusBlock();
			count = 0;
		}
	}

	@Override
	public void addToStage(Stage stage) {
		super.addToStage(stage);
		if (bonus != null) {
			bonus.setPosition(getX() + (w - Data.bonusSize) / 2.0f, getY()
					+ (h - Data.bonusSize) / 2.0f);
			stage.addActor(bonus);
		}
	}

	@Override
	public String checkCollision(float x, float y, boolean isSmall) {
		return null;
	}

}
