package com.kivvi.bouncyninja.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.PolygonShape;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.SoundManager;

public class Background extends Actor {
	Texture texture;
	Body body;

	public Background() {
		setColor(Data.initColor);
		texture = GameAssets.getAssets().get("whiteDot.png", Texture.class);

		setSize(Data.gameWidth, Data.gameHeight);
		setPosition((Data.width - Data.gameWidth) / 2,
				(Data.height - Data.gameHeight) / 2);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		if (body == null) {
			createBody();
		}
		Color savedColor = batch.getColor();
		batch.setColor(getColor());
		batch.draw(texture, getX(), getY(), getWidth(), getHeight());
		batch.setColor(savedColor);
	}

	void createBody() {
		// create box2d stuff
		BodyDef bd = new BodyDef();
		bd.position.set(getX() / Data.box2dRadio, getY() / Data.box2dRadio);
		bd.type = BodyType.StaticBody;
		body = GameStage.getStage().world.createBody(bd);
		body.setUserData("background");

		// edges
		{
			PolygonShape shape = new PolygonShape();
			Vector2 vertices[] = new Vector2[4];
			vertices[0] = new Vector2(-10.0f / Data.box2dRadio, 0);
			vertices[1] = new Vector2(0.0f / Data.box2dRadio, 0);
			vertices[2] = new Vector2(0.0f / Data.box2dRadio, getHeight()
					/ Data.box2dRadio);
			vertices[3] = new Vector2(-10.0f / Data.box2dRadio, getHeight()
					/ Data.box2dRadio);
			shape.set(vertices);

			FixtureDef fd = new FixtureDef();
			fd.shape = shape;
			fd.density = 1.0f;
			fd.friction = 0.0f;
			fd.restitution = 1.0f;
			body.createFixture(fd);

			shape.dispose();
		}
		{
			PolygonShape shape = new PolygonShape();
			Vector2 vertices[] = new Vector2[4];
			vertices[0] = new Vector2(getWidth() / Data.box2dRadio, 0);
			vertices[1] = new Vector2((getWidth() + 10.0f) / Data.box2dRadio, 0);
			vertices[2] = new Vector2((getWidth() + 10.0f) / Data.box2dRadio,
					getHeight() / Data.box2dRadio);
			vertices[3] = new Vector2(getWidth() / Data.box2dRadio, getHeight()
					/ Data.box2dRadio);
			shape.set(vertices);

			FixtureDef fd = new FixtureDef();
			fd.shape = shape;
			fd.density = 1.0f;
			fd.friction = 0.0f;
			fd.restitution = 1.0f;
			body.createFixture(fd);

			shape.dispose();
		}
	}

	public void switchColor(int score) {
		int level = score / 5;
		int index = level % Data.levelColors.length;
		Gdx.app.log("background", "Data.levelColors[index] = "
				+ Data.levelColors[index]);
		Gdx.app.log("background", "getColor() = " + getColor());
		if (!getColor().equals(Data.levelColors[index])) {
			setColor(Data.levelColors[index]);

			SoundManager.play(SoundManager.Type.NewItem);
		}
	}
}
