package com.kivvi.livewallpaper.flowerzen.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kivvi.livewallpaper.flowerzen.LWPGame;
import com.kivvi.livewallpaper.flowerzen.MainScreen;

public class LandscapeLauncher {
	public static void main(String[] args) {
		LwjglApplicationConfiguration cfg = new LwjglApplicationConfiguration();
		cfg.title = "Flower Zen 800 * 400";
		cfg.width = 800 / 1;
		cfg.height = 480 / 1;
		cfg.samples = 4;
		cfg.vSyncEnabled = false;
		cfg.resizable    = false;
		cfg.fullscreen   = false;
		cfg.foregroundFPS = 61;
		cfg.backgroundFPS = -1;
		 LWPGame.setStatisticsService(new DesktopAnalyticsService());
		
		new LwjglApplication(new LWPGame(), cfg);
	}
}
