package com.cooee.wallpaper.framework;

public class ConfigMode {
	private static boolean textureCompression = false;

	public static void setAAMode(int configMode) {
		com.threed.jpct.Config.aaMode = configMode;
	}

	public static void setTextureCompression(boolean compression) {
		textureCompression = compression;
	}

	public static boolean getTextureCompression() {
		return textureCompression;
	}
}
