package com.kivvi.bouncyninja.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.badlogic.gdx.physics.box2d.CircleShape;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.PolygonShape;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.GameStage;

public class Spike extends Actor {
	Texture texture;
	Texture textureBlood;
	Sprite sprite;
	boolean enable;
	int row;
	int col;
	Body body = null;

	public Spike(int row, int col) {
		this.row = row;
		this.col = col;

		texture = GameAssets.getAssets().get("spike.png", Texture.class);
		textureBlood = GameAssets.getAssets().get("spike_blood.png",
				Texture.class);

		setSize(Data.spikeWidth, Data.spikeHeight);

		float x = (Data.width - Data.gameWidth) / 2 + Data.spikeWidth * col
				- getWidth() / 2;
		float y = (Data.height - Data.gameHeight) / 2 + Data.gameHeight
				- Data.spikeHeight * row - getHeight() / 2;
		setPosition(x, y);

		sprite = new Sprite(texture);
		sprite.setOrigin(getWidth() / 2, getHeight() / 2);

		addAction(Actions.delay(0.2f, Actions.rotateTo(180, 0.5f)));

		enable = true;
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		if (body == null) {
			createBody();
		}

		sprite.setPosition(getX(), getY());
		sprite.setSize(getWidth(), getHeight());
		sprite.setAlpha(getColor().a);
		sprite.setRotation(getRotation() + 45);
		sprite.draw(batch);
	}

	public void setEnable(boolean enable) {
		if (this.enable != enable) {
			this.reset();

			this.enable = enable;

			float dx = 0;
			if (enable) {
				if (col == 0) {
					dx = Data.spikeWidth * 1.1f;
				} else {
					dx = -Data.spikeWidth * 1.1f;
				}
			} else {
				if (col == 0) {
					dx = -Data.spikeWidth * 1.1f;
				} else {
					dx = Data.spikeWidth * 1.1f;
				}
			}
			addAction(Actions.moveTo(getX() + dx, getY(), 0.2f));
		}
	}

	void reset() {
		float x = (Data.width - Data.gameWidth) / 2 + Data.spikeWidth * col
				- getWidth() / 2;
		float y = (Data.height - Data.gameHeight) / 2 + Data.gameHeight
				- Data.spikeHeight * row - getHeight() / 2;

		if (!this.enable) {
			if (col == 0) {
				x -= Data.spikeWidth * 1.1f;
			} else {
				x += Data.spikeWidth * 1.1f;
			}
		}

		setPosition(x, y);

		this.clearActions();
	}

	void createBody() {
		// create box2d stuff
		BodyDef bd = new BodyDef();
		bd.position.set(getX() / Data.box2dRadio, getY() / Data.box2dRadio);
		bd.type = BodyType.StaticBody;
		body = GameStage.getStage().world.createBody(bd);
		body.setUserData("spike");

		PolygonShape shape = new PolygonShape();
		// float shapeSize = (float) (Math.sqrt(getWidth() * getWidth() * 2) *
		// 0.995);
		float shapeSize = getWidth();
		final Vector2 shapes[][] = new Vector2[][] {
				// here we go
				{
						// top triangle
						new Vector2(1.0f / 2.0f, 1.0f), // vertice 1
						new Vector2(1.0f / 3.0f, 2.0f / 3.0f), // vertice 2
						new Vector2(2.0f / 3.0f, 2.0f / 3.0f), // vertice 3
				}, {
						// left triangle
						new Vector2(1.0f / 3.0f, 2.0f / 3.0f), // vertice 1
						new Vector2(0.0f, 1.0f / 2.0f), // vertice 2
						new Vector2(1.0f / 3.0f, 1.0f / 3.0f), // vertice 3
				}, {
						// right triangle
						new Vector2(2.0f / 3.0f, 2.0f / 3.0f), // vertice 1
						new Vector2(2.0f / 3.0f, 1.0f / 3.0f), // vertice 2
						new Vector2(1.0f, 1.0f / 2.0f), // vertice 3
				}, {
						// bottom triangle
						new Vector2(1.0f / 3.0f, 1.0f / 3.0f), // vertice 1
						new Vector2(1.0f / 2.0f, 0.0f), // vertice 2
						new Vector2(2.0f / 3.0f, 1.0f / 3.0f), // vertice 3
				}, {
						// center square
						new Vector2(1.0f / 3.0f, 2.0f / 3.0f), // vertice 1
						new Vector2(1.0f / 3.0f, 1.0f / 3.0f), // vertice 2
						new Vector2(2.0f / 3.0f, 1.0f / 3.0f), // vertice 3
						new Vector2(2.0f / 3.0f, 2.0f / 3.0f), // vertice 4
				} };
		for (int iShape = 0; iShape < shapes.length; iShape++) {
			Vector2 vertices[] = new Vector2[shapes[iShape].length];
			for (int i = 0; i < shapes[iShape].length; i++) {
				vertices[i] = new Vector2(shapeSize * shapes[iShape][i].x
						/ Data.box2dRadio, shapeSize * shapes[iShape][i].y
						/ Data.box2dRadio);
			}
			shape.set(vertices);
			
			FixtureDef fd = new FixtureDef();
			fd.shape = shape;
			fd.density = 1.0f;
			fd.friction = 0.6f;
			fd.restitution = 0.5f;
			body.createFixture(fd);
		}
		shape.dispose();

		body.setActive(true);

	}

	@Override
	public void setPosition(float x, float y) {
		super.setPosition(x, y);

		if (body != null) {
			body.setTransform(x / Data.box2dRadio, y / Data.box2dRadio, 0);
		}
	}
}
