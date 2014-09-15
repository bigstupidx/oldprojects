package com.kivvi.avoidthecircles.actors;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.avoidthecircles.stages.GameStage;
import com.kivvi.avoidthecircles.utils.Data;

public class Hero extends Actor {
	Texture texture;

	public Hero() {
		this.setSize(Data.heroSize, Data.heroSize);
		this.setX((Data.screenWidth - Data.heroSize) / 2);
		this.setY(Data.heroInitY);

		texture = GameStage.assetManager.get("hero.png", Texture.class);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		batch.draw(texture, this.getX(), this.getY() + this.getHeight() / 2,
				this.getWidth(), this.getHeight());
	}
}
