package com.kivvi.gario.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.kivvi.gario.stages.MapStage;
import com.kivvi.gario.utils.Battle;

public class Monster extends Tile {
	public int ap;
	public int hp;
	public int level;
	public boolean key;
	private Texture texture;

	public Monster(int level) {
		super();

		this.level = level;
		this.ap = 1;
		this.hp = 1;
		this.key = false;

		texture = new Texture(Gdx.files.internal("monster.png"));
		
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
				Battle.fight(stage.hero, Monster.this);
			}
		});
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		batch.draw(texture, this.getX(), this.getY(), this.getWidth(),
				this.getHeight());
	}

	public void setKey() {
		key = true;
	}
}
