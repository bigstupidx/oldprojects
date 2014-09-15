package com.kivvi.theline.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.theline.game.TheLineGame;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = 360;
		config.height = 640;
		new LwjglApplication(new TheLineGame() {

			@Override
			public void rate() {
				
			}

			@Override
			public void share() {
				
			}
			
		}, config);
	}
}
