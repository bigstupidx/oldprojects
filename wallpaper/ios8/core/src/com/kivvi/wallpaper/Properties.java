package com.kivvi.wallpaper;

import java.io.IOException;
import java.io.StringReader;

import org.ini4j.Ini;
import org.ini4j.IniPreferences;
import org.ini4j.InvalidFileFormatException;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;

public class Properties {
	private static final String preferenceName = "setting";
	private static final String featureName = "feature";
	private static final String packageName = "com.kivvi.ios8.android";

	// setting
	private static BooleanValue wave = new BooleanValue("wave", true);
	private static BooleanValue twinkle = new BooleanValue("twinkle", true);
	private static BooleanValue gsensor = new BooleanValue("gsensor", true);

	// feature
	private static BooleanValue encrypt = new BooleanValue("encrypt", true,
			featureName);

	// preferences
	private static com.badlogic.gdx.Preferences prefs = null;

	public static void load() {
		FileHandle f = Gdx.files.internal("data/channel.properties");
		String text = f.readString();

		// load ini first.
		String channel = text.substring(text.lastIndexOf("=") + 1).trim();
		loadIni("data/" + channel + ".ini");

		// load preference then.
		loadPreference();

		// set encrypt.
		com.badlogic.gdx.Configs.setAssetEncrypt(Properties.get("encrypt"));
	}

	public static void loadIni(String path) {
		FileHandle f = Gdx.files.internal(path);
		String text = f.readString();
		try {
			java.util.prefs.Preferences iniPrefs = new IniPreferences(new Ini(
					new StringReader(text)));

			// setting
			wave.get(iniPrefs);
			twinkle.get(iniPrefs);
			gsensor.get(iniPrefs);

			// feature
			encrypt.get(iniPrefs);

			Gdx.app.log("Properties", "load ini");
			Gdx.app.log("Properties", "Properties: get wave = " + wave.value);
			Gdx.app.log("Properties", "Properties: get twinkle = "
					+ twinkle.value);
			Gdx.app.log("Properties", "Properties: get encrypt = "
					+ encrypt.value);
		} catch (InvalidFileFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void loadPreference() {
		if (prefs == null) {
			prefs = Gdx.app.getPreferences(packageName + "_preferences");
		}

		wave.get();
		twinkle.get();
		gsensor.get();

		Gdx.app.log("Properties", "loadPreference");
		Gdx.app.log("Properties", "Properties: get wave = " + wave.value);
		Gdx.app.log("Properties", "Properties: get twinkle = " + twinkle.value);
	}

	public static boolean get(String name) {
		if (name.equalsIgnoreCase(wave.name)) {
			return wave.value;
		} else if (name.equalsIgnoreCase(twinkle.name)) {
			return twinkle.value;
		} else if (name.equalsIgnoreCase(encrypt.name)) {
			return encrypt.value;
		} else if (name.equalsIgnoreCase(gsensor.name)) {
			return gsensor.value;
		}

		return false;
	}

	public static void set(String name, boolean value) {
		if (name.equalsIgnoreCase(wave.name)) {
			wave.set(value);
		} else if (name.equalsIgnoreCase(twinkle.name)) {
			twinkle.set(value);
		} else if (name.equalsIgnoreCase(encrypt.name)) {
			encrypt.set(value);
		} else if (name.equalsIgnoreCase(gsensor.name)) {
			gsensor.set(value);
		}
	}

	public static void flush() {
		prefs.flush();
	}

	public static class BooleanValue {
		public String name;
		public String type;
		public boolean defaultValue;
		public boolean value;

		public BooleanValue(String name, boolean defaultValue) {
			this(name, defaultValue, preferenceName);
		}

		public BooleanValue(String name, boolean defaultValue, String type) {
			this.name = name;
			this.type = type;
			this.defaultValue = defaultValue;
			this.value = defaultValue;
		}

		public void get(java.util.prefs.Preferences iniPrefs) {
			this.value = Boolean.valueOf(iniPrefs.node(this.type).get(
					this.name, new Boolean(this.defaultValue).toString()));
			this.defaultValue = this.value;
		}

		public void get() {
			this.value = prefs.getBoolean(this.name, this.defaultValue);
		}

		public void set(boolean value) {
			this.value = value;
			prefs.putBoolean(this.name, this.value);
		}
	};
}
