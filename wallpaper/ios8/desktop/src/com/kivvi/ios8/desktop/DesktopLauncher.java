package com.kivvi.ios8.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.ios8.IOS8;

public class DesktopLauncher {
	public static void main (String[] arg) {
		com.badlogic.gdx.Configs.setAssetEncrypt(false);
		
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = 360;
		config.height = 600;
		new LwjglApplication(new IOS8(), config);
	}
}
