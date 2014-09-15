package com.kivvi.lighter;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Lighter extends ApplicationAdapter {
	
	SpriteBatch batch;
	Flame flame;
	
	@Override
	public void create () {
		flame = new Flame();
		flame.setPosition(72, 800 - 38 - flame.getHeight());
		flame.activateFlame();
		
		batch = new SpriteBatch();
	}

	@Override
	public void render () {
		Gdx.gl.glClearColor(0, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
		
		flame.draw();
		
		batch.begin();
		//batch.draw(flame.mTexture, 0, 0);
		batch.end();
	}
}
