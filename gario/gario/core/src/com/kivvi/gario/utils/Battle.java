package com.kivvi.gario.utils;

import com.badlogic.gdx.Gdx;
import com.kivvi.gario.actors.Hero;
import com.kivvi.gario.actors.Monster;
import com.kivvi.gario.stages.MapStage;
import com.kivvi.gario.stages.MapStage.TileType;

public class Battle {
	public static void fight(Hero hero, Monster monster) {
		hero.hp -= monster.ap;
		Gdx.app.log("battle", "monster attack hero, hero hp - " + monster.ap);
		Gdx.app.log("battle", "hero's hp is " + hero.hp);

		monster.hp -= hero.ap;
		Gdx.app.log("battle", "hero attack monster, monster hp - " + hero.ap);
		Gdx.app.log("battle", "monster hp is " + monster.hp);
		if (monster.hp <= 0) {
			MapStage stage = (MapStage) monster.getStage();
			stage.map[(int) monster.getX() / 96][(int) monster.getY() / 96] = TileType.NONE;
			monster.remove();
			Gdx.app.log("battle", "monster is dead");
			
			if (monster.key) {
				hero.key = true;
				Gdx.app.log("battle", "get key!");
			}
		}
	}
}
