package com.kivvi.crystalswan;

import java.io.IOException;
import java.io.StringReader;
import java.util.prefs.Preferences;

import org.ini4j.Ini;
import org.ini4j.IniPreferences;
import org.ini4j.InvalidFileFormatException;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;

public class Properties {
	private static final String preferenceName = "setting";
	// setting
	private static boolean doubleTap;
	private static int brightness;
	// feature
	private static boolean changeBackground;
	private static boolean encrypt;
	private static com.badlogic.gdx.Preferences prefs = null;

	public static void load(String path) {
		FileHandle f = Gdx.files.internal(path);
		String text = f.readString();

		// load ini first.
		String channel = text.substring(text.lastIndexOf("=") + 1).trim();
		loadIni("data/" + channel + ".ini");

		// load preference then.
		loadPreference();
		
		// set encrypt.
		com.badlogic.gdx.Configs.setAssetEncrypt(Properties.getEncrypt());
	}

	public static void loadIni(String path) {
		FileHandle f = Gdx.files.internal(path);
		String text = f.readString();
		try {
			Preferences prefs = new IniPreferences(new Ini(new StringReader(
					text)));
			// setting
			doubleTap = Boolean.valueOf(prefs.node(preferenceName).get(
					"check_doubleclick", "true"));
			brightness = Integer.valueOf(prefs.node(preferenceName).get(
					"seekBar", "100"));
			// feature
			changeBackground = Boolean.valueOf(prefs.node("feature").get(
					"change background", "true"));
			encrypt = Boolean.valueOf(prefs.node("feature").get(
					"encrypt", "false"));

			// Gdx.app.log("suyu", "load ini");
			// Gdx.app.log("suyu", "Properties: get doubleTap = " + doubleTap);
			// Gdx.app.log("suyu", "Properties: get brightness = " +
			// brightness);
		} catch (InvalidFileFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void loadPreference() {
		if (prefs == null) {
			prefs = Gdx.app.getPreferences(preferenceName);
		}
		doubleTap = prefs.getBoolean("check_doubleclick", doubleTap);
		brightness = prefs.getInteger("seekBar", brightness);

		// Gdx.app.log("suyu", "loadPreference");
		// Gdx.app.log("suyu", "Properties: get doubleTap = " + doubleTap);
		// Gdx.app.log("suyu", "Properties: get brightness = " + brightness);
	}

	public static boolean getDoubleTap() {
		return Properties.doubleTap && Properties.changeBackground;
	}

	public static void setDoubleTap(boolean doubleTap) {
		Properties.doubleTap = doubleTap;
		prefs.putBoolean("check_doubleclick", doubleTap);
		// Gdx.app.log("suyu", "Properties: set doubleTap = " + doubleTap);
	}

	public static boolean getChangeBackground() {
		return Properties.changeBackground;
	}
	
	public static boolean getEncrypt() {
		return Properties.encrypt;
	}

	public static int getBrightness() {
		return Properties.brightness;
	}

	public static void setBrightness(int brightness) {
		Properties.brightness = brightness;
		prefs.putInteger("seekBar", brightness);
		// Gdx.app.log("suyu", "Properties: set brightness = " + brightness);
	}

	public static void flush() {
		prefs.flush();
	}
}
