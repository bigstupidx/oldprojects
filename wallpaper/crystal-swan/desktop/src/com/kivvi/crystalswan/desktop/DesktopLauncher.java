package com.kivvi.crystalswan.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.crystalswan.CrystalSwan;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = 360;
		config.height = 600;
		config.samples = 4;
		CrystalSwan crystalSwan = new CrystalSwan();
		
		new LwjglApplication(crystalSwan, config);
	}
}
