package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;

public class Config {
	private static final String TAG = Config.class.getName();
	// DON'T CHANGE FILE NAME!!!
	// Android have a lot of shit in shared preferences part.
	// Just don't touch a name ))
	public static final Preferences preferences = Gdx.app.getPreferences("preferences");

	public static boolean checkBoxTest = false;
	public static String listTest = "0";

	public static void load() {
		if (!preferences.contains("checkBoxTest") ||
			!preferences.contains("listTest"))
			save();

		listTest = preferences.getString("listTest", "0");
		checkBoxTest = preferences.getBoolean("checkBoxTest", false);
		Gdx.app.debug(TAG, "load preferences");
	}

	public static void save() {
		preferences.putString("listTest", listTest);
		preferences.putBoolean("checkBoxTest", checkBoxTest);
		preferences.flush();
	}
}
