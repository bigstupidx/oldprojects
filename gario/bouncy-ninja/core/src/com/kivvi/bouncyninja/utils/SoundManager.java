package com.kivvi.bouncyninja.utils;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Sound;
import com.kivvi.bouncyninja.resources.Data;
import com.kivvi.bouncyninja.resources.GameAssets;

public class SoundManager {

	public enum Type {
		Jump, Wall, GameOver, NewRecord, NewItem
	};

	public static void play(Type type) {
		boolean enable = Gdx.app.getPreferences(Data.prefName).getBoolean(
				Data.soundPref, true);
		if (!enable)
			return;

		AssetManager assets = GameAssets.getAssets();
		switch (type) {
		case Jump:
			assets.get("tap_jump.wav", Sound.class).play();
			break;
		case Wall:
			assets.get("wall_jump.wav", Sound.class).play();
			break;
		case GameOver:
			assets.get("game_over.wav", Sound.class).play();
			break;
		case NewRecord:
			assets.get("record.wav", Sound.class).play();
			break;
		case NewItem:
			assets.get("new_item.wav", Sound.class).play();
			break;
		default:
			break;
		}
	}
}
