package com.kivvi.bouncyninja.resources;

import com.badlogic.gdx.graphics.Color;

public class Data {
	public static int width = 720;
	public static int height = 1280;
	public static int spikeWidth = 90;
	public static int spikeHeight = 90;
	public static int ninjaWidth = 65;
	public static int ninjaHeight = 50;
	public static int pauseImageWidth = 40;
	public static int pauseImageHeight = 40;
	public static float pauseImageScale = 1.5f;
	public static int col = 7;
	public static int row = 10;
	public static int gameWidth = col * spikeWidth;
	public static int gameHeight = row * spikeHeight;

	public static float box2dRadio = 96.0f;
	public static float jumpVelocity = 5.0f;
	public static float fowardVelocity = 2.5f;
	public static float speedScale = 1.8f;
	public static float gravity = 10.0f;

	public static boolean box2dDebug = false;

	public static Color initColor = new Color(0.48f, 0, 0.48f, 1.0f);
	public static Color level2Color = new Color(0, 0, 0.98f, 1.0f);
	public static Color level3Color = new Color(0, 0.98f, 0f, 1.0f);
	public static Color gameOverColor = new Color(0.97f, 0, 0, 1.0f);
	public static Color scoreColor = new Color(0.6f, 0.6f, 0.98f, 1.0f);
	public static Color levelColors[] = new Color[] { initColor, level2Color,
			level3Color };

	// preference
	public static String prefName = "game";
	public static final String lastScoreName = "lastScore";
	public static final String bestScoreName = "bestScore";
	public static final String soundPref = "sound";
}
