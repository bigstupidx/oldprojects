package com.kivvi.bouncyninja.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.bouncyninja.game.BouncyNinjaGame;

public class DesktopLauncher {
	public static void main(String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		final float scale = 1.0f;
		config.width = (int) (360 * scale);
		config.height = (int) (640 * scale);
		new LwjglApplication(new BouncyNinjaGame() {
			@Override
			public void rate() {
			}

			@Override
			public void share() {
			}
		}, config);
	}
}
