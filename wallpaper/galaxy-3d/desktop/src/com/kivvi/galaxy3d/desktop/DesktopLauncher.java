package com.kivvi.galaxy3d.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.galaxy3d.Galaxy3D;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = 360;
		config.height = 640;
		com.badlogic.gdx.Configs.setAssetEncrypt(false);
		new LwjglApplication(new Galaxy3D(), config);
	}
}
