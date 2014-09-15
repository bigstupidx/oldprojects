package com.kivvi.avoidthecircles.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.avoidthecircles.AvoidTheCircles;

public class DesktopLauncher {
	public static void main(String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = 360;
		config.height = 600;
		new LwjglApplication(new AvoidTheCircles(), config);
	}
}
