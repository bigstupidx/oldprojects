package com.kivvi.bouncyninja.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.CircleShape;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.PolygonShape;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;
import com.kivvi.bouncyninja.stages.GameStage;
import com.kivvi.bouncyninja.utils.SoundManager;

public class Ninja extends Actor {
	Texture texture;
	Sprite sprite;
	Body body;
	public boolean toRight = true;
	public boolean die = false;

	public Ninja() {
		texture = GameAssets.getAssets().get("ninja.png", Texture.class);
		texture.setFilter(TextureFilter.Linear, TextureFilter.Linear);

		setSize(Data.ninjaWidth, Data.ninjaHeight);

		sprite = new Sprite(texture);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		if (body == null) {
			createBody();
		}
		setX(body.getPosition().x * Data.box2dRadio);
		setY(body.getPosition().y * Data.box2dRadio);
		setOrigin(0, 0);
		setRotation(MathUtils.radiansToDegrees * body.getAngle());

		sprite.setSize(getWidth(), getHeight());
		sprite.setPosition(getX(), getY());
		sprite.setFlip(!toRight, false);
		sprite.setRotation(getRotation());
		sprite.setOrigin(getOriginX(), getOriginY());

		sprite.draw(batch);
	}

	void createBody() {
		// create box2d stuff
		BodyDef bd = new BodyDef();
		bd.position.set(getX() / Data.box2dRadio, getY() / Data.box2dRadio);
		bd.type = BodyType.DynamicBody;
		body = GameStage.getStage().world.createBody(bd);
		body.setUserData("ninja");

		PolygonShape shape = new PolygonShape();
		Vector2 vertices[] = new Vector2[4];
		vertices[0] = new Vector2(0, 0);
		vertices[1] = new Vector2(getWidth() / Data.box2dRadio, 0);
		vertices[2] = new Vector2(getWidth() / Data.box2dRadio, getHeight()
				/ Data.box2dRadio);
		vertices[3] = new Vector2(0, getHeight() / Data.box2dRadio);
		shape.set(vertices);

		FixtureDef fd = new FixtureDef();
		fd.shape = shape;
		fd.density = 1.0f;
		fd.friction = 0.4f;
		fd.restitution = 0.3f;
		body.createFixture(fd);

		shape.dispose();

		body.setActive(false);
	}

	public void setActive(boolean active) {
		body.setActive(active);
		body.setLinearVelocity(Data.fowardVelocity, 0);
	}

	public void jump() {
		// body.applyForceToCenter(new Vector2(0, 40 * 9.0f), true);
		Vector2 v = body.getLinearVelocity();
		body.setLinearVelocity(v.x, Data.jumpVelocity);

		SoundManager.play(SoundManager.Type.Jump);
	}

	public void turnOver() {
		toRight = !toRight;

		GameStage.getStage().game.gameScreen.turnOver();

		SoundManager.play(SoundManager.Type.Wall);
	}

	@Override
	public void setPosition(float x, float y) {
		super.setPosition(x, y);

		if (body != null) {
			body.setTransform(x / Data.box2dRadio, y / Data.box2dRadio, 0);
		}
	}

	public void die() {
		if (!die) {
			die = true;

			BouncyNinjaGame game = GameStage.getStage().game;
			game.toGameOverScreen();

			SoundManager.play(SoundManager.Type.GameOver);
		}
	}

	public void reset() {
		toRight = true;
		die = false;

		body.setLinearVelocity(0, 0);

		this.setPosition(Data.width / 2 - Data.ninjaWidth / 2, Data.height / 2
				- Data.ninjaHeight / 2);
	}

	public boolean isAwake() {
		return body.isAwake();
	}
}
