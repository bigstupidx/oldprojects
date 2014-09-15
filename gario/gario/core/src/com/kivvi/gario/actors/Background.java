package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.kivvi.gario.stages.MapStage;
import com.kivvi.gario.stages.MapStage.TileType;

public class Background extends Actor {
	public Background() {

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
				// Gdx.app.log("debug", "background, touchUp");
				MapStage stage = (MapStage) getStage();
				int i = (int) x / 96;
				int j = (int) y / 96;
				if (i >= 0 && i < 5 && j >= 0 && j < 6)
					// if (stage.map[i][j] == TileType.NONE)
					stage.fog.search(i, j);
			}
		});

		setSize(5 * 96, 6 * 96);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		Gdx.gl20.glClearColor(1, 1, 1, 1);
		Gdx.gl20.glClear(GL20.GL_COLOR_BUFFER_BIT);
	}
}
