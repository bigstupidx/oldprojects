package com.kivvi.theline.actors;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class Ball extends Actor {
	protected Image image;
	public float r = Data.ballR;
	public boolean isSmall;

	public Ball() {
		Texture t = GameAssets.getAssets().get("ball.png");
		image = new Image(t);
		image.setSize(Data.ballD, Data.ballD);
		image.setPosition(Data.ballX, Data.ballY);

		setPosition(Data.ballX, Data.ballY);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		image.setPosition(getX(), getY());
		image.setSize(2 * r, 2 * r);
		image.setColor(getColor());
		image.draw(batch, parentAlpha);
	}

	public void reset() {
		setPosition(Data.ballX, Data.ballY);
		r = Data.ballR;
		clearActions();
	}

	public void beSmall() {
		isSmall = true;
		r = Data.smallBallR;
		addAction(Actions.delay(10, Actions.run(new Runnable() {
			@Override
			public void run() {
				isSmall = false;
				r = Data.ballR;
			}
		})));

		addAction(Actions.delay(
				8,
				Actions.repeat(
						10,
						Actions.sequence(Actions.alpha(0, 0.1f),
								Actions.alpha(1, 0.1f)))));
	}
}
