package com.kivvi.bouncyninja.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.kivvi.bouncyninja.resources.Data;

public class Touchpad extends Actor {
	public Touchpad() {
		// set size to full screen
		setSize(Data.width, Data.height);
		
		setTouchable(Touchable.enabled);
		
		addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				Gdx.app.log("debug", "touch pad touch down.");
				return true;
			}
		});
	}
}
