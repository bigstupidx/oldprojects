package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Event;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.kivvi.gario.stages.MapStage;

public class Door extends Tile {
	private Texture texture;

	public Door() {
		super();

		texture = new Texture(Gdx.files.internal("door.png"));

		setTouchable(Touchable.enabled);

		addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				MapStage stage = (MapStage) getStage();
				if (stage.hero.hasKey()) {
					stage.gotoNextLevel();
				} else {
					Gdx.app.log("info", "you don't have a key!");
				}
			}
		});
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		batch.draw(texture, this.getX(), this.getY(), this.getWidth(),
				this.getHeight());
	}

	@Override
	public boolean fire(Event event) {
		// Gdx.app.log("debug", "fire: " + event);
		return super.fire(event);
	}
}
