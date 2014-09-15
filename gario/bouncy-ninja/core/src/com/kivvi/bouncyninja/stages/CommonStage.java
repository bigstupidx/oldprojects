package com.kivvi.bouncyninja.stages;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Contact;
import com.badlogic.gdx.physics.box2d.ContactImpulse;
import com.badlogic.gdx.physics.box2d.ContactListener;
import com.badlogic.gdx.physics.box2d.Fixture;
import com.badlogic.gdx.physics.box2d.Manifold;
import com.badlogic.gdx.physics.box2d.World;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.kivvi.bouncyninja.actors.Background;
import com.kivvi.bouncyninja.actors.Ninja;
import com.kivvi.bouncyninja.actors.Spike;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;

public class CommonStage extends Stage {
	public World world;

	public Background background;
	public Ninja ninja;
	public Spike topSpikes[];
	public Spike bottomSpikes[];
	public Spike leftSpikes[];
	public Spike rightSpikes[];
	public Label sound;

	public BouncyNinjaGame game;

	public CommonStage(FitViewport fitViewport) {
		super(fitViewport);

		// box2d
		Vector2 gravity = new Vector2(0, -1.0f * Data.gravity);
		world = new World(gravity, true);

		// contact listener
		ContactListener contactListener = new ContactListener() {
			@Override
			public void beginContact(Contact contact) {
				Fixture a = contact.getFixtureA();
				Fixture b = contact.getFixtureB();
				// Gdx.app.log("contact", "a = " + a.getBody().getUserData()
				// + ", b = " + b.getBody().getUserData());
				if (a.getBody().getUserData() == "spike"
						&& b.getBody().getUserData() == "ninja") {
					// game over.
					ninja.die();
				}

				if (a.getBody().getUserData() == "background"
						&& b.getBody().getUserData() == "ninja") {
					// turn over
					// We use post runnable to avoid set body's transform in
					// world.step().
					Gdx.app.postRunnable(new Runnable() {
						@Override
						public void run() {
							ninja.turnOver();
						}
					});
				}
			}

			@Override
			public void endContact(Contact contact) {
			}

			@Override
			public void preSolve(Contact contact, Manifold oldManifold) {
			}

			@Override
			public void postSolve(Contact contact, ContactImpulse impulse) {
			}
		};

		world.setContactListener(contactListener);

		// add actors.
		addActors();
	}

	void addActors() {
		// background
		background = new Background();
		this.addActor(background);

		// ninja
		ninja = new Ninja();
		ninja.setPosition(background.getX() + background.getWidth() / 2
				- Data.ninjaWidth / 2,
				background.getY() + background.getHeight() / 2
						- Data.ninjaHeight / 2);
		this.addActor(ninja);

		// Spikes.
		topSpikes = new Spike[Data.col + 1];
		bottomSpikes = new Spike[Data.col + 1];
		leftSpikes = new Spike[Data.row - 1];
		rightSpikes = new Spike[Data.row - 1];

		// top & bottom
		for (int j = 0; j < Data.col + 1; j++) {
			topSpikes[j] = new Spike(0, j);
			bottomSpikes[j] = new Spike(Data.row, j);

			this.addActor(topSpikes[j]);
			this.addActor(bottomSpikes[j]);
		}

		// left & right
		for (int i = 1; i < Data.row; i++) {
			leftSpikes[i - 1] = new Spike(i, 0);
			rightSpikes[i - 1] = new Spike(i, Data.col);

			this.addActor(leftSpikes[i - 1]);
			this.addActor(rightSpikes[i - 1]);
		}

		// Sound Label or Image
		sound = new Label("SOUND", new Label.LabelStyle(GameAssets.getAssets()
				.get("size60.fnt", BitmapFont.class), Color.WHITE));
		sound.setPosition(
				(Data.width - Data.gameWidth) / 2,
				(Data.height - Data.gameHeight)
						/ 2
						+ Data.gameHeight
						+ ((Data.height - Data.gameHeight) / 2 - sound
								.getTextBounds().height) / 2
						- sound.getTextBounds().height / 2);
		sound.addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				switchSound();
				return true;
			}
		});
		this.addActor(sound);
	}

	@Override
	public void act() {
		super.act();

		world.step(Gdx.graphics.getDeltaTime() * Data.speedScale, 8, 8);
	}

	@Override
	public void act(float delta) {
		super.act(delta);

		world.step(delta * Data.speedScale, 8, 8);
	}

	@Override
	public void dispose() {
		super.dispose();

		world.dispose();
	}

	public void setGame(BouncyNinjaGame game) {
		this.game = game;
	}

	public void switchSound() {
		Preferences pref = Gdx.app.getPreferences(Data.prefName);
		boolean enable = pref.getBoolean(Data.soundPref, true);
		if (enable) {
			sound.setColor(Color.GRAY);
			enable = false;
		} else {
			sound.setColor(Color.WHITE);
			enable = true;
		}
		pref.putBoolean(Data.soundPref, enable);
		pref.flush();
	}
}
