package com.kivvi.avoidthecircles.actors;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.avoidthecircles.stages.GameStage;
import com.kivvi.avoidthecircles.utils.Data;

public class Enemy extends Actor {
	Texture texture;
	Vector2 target;
	float angle;
	int radius;

	public Enemy() {
		this.setSize(Data.enemySize, Data.enemySize);

		texture = GameStage.assetManager.get("hero.png", Texture.class);
		
		angle = Data.enemyAngle;
		radius = Data.enemyRadius;
	}

	@Override
	public void act(float delta) {
		super.act(delta);

	}
}
