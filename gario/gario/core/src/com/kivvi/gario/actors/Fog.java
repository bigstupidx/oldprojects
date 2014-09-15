package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.kivvi.gario.stages.MapStage;
import com.kivvi.gario.stages.MapStage.TileType;

public class Fog extends Actor {
	private Texture texture;
	private boolean map[][] = new boolean[5][6];

	public Fog() {
		texture = new Texture(Gdx.files.internal("fog.png"));

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
				//Gdx.app.log("debug", "fog, touchUp");
			}
		});

		setSize(5 * 96, 6 * 96);
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 6; j++) {
				if (map[i][j]) {
					batch.draw(texture, i * 96, j * 96);
				}
			}
	}

	public void open(int x, int y) {
		MapStage stage = (MapStage) getStage();
		if (x >= 0 && x < 5)
			if (y >= 0 && y < 6) {
				if (stage.getMap(x + 1, y) == TileType.MONSTER
						&& getMap(x + 1, y) == false)
					return;
				if (stage.getMap(x - 1, y) == TileType.MONSTER
						&& getMap(x - 1, y) == false)
					return;
				if (stage.getMap(x, y + 1) == TileType.MONSTER
						&& getMap(x, y + 1) == false)
					return;
				if (stage.getMap(x, y - 1) == TileType.MONSTER
						&& getMap(x, y - 1) == false)
					return;
				map[x][y] = false;
			}
	}

	public void init() {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 6; j++) {
				map[i][j] = true;
			}

		MapStage stage = (MapStage) getStage();
		int x = (int) (stage.door.getX() / 96);
		int y = (int) (stage.door.getY() / 96);

		search(x, y);
	}

	public void search(int x, int y) {
		open(x, y);
		open(x + 1, y);
		open(x, y + 1);
		open(x - 1, y);
		open(x, y - 1);
	}

	@Override
	public Actor hit(float x, float y, boolean touchable) {
		int i = (int) x / 96;
		int j = (int) y / 96;
		if (getMap(i, j)) {
			return this;
		}
		return null;
	}

	public boolean getMap(int i, int j) {
		if (i < 0 || i >= 5 || j < 0 || j >= 6) {
			return false;
		}
		return map[i][j];
	}
}
