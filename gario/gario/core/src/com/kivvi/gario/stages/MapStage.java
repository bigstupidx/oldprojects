package com.kivvi.gario.stages;

import java.util.Random;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.kivvi.gario.actors.Background;
import com.kivvi.gario.actors.Door;
import com.kivvi.gario.actors.Fog;
import com.kivvi.gario.actors.Hero;
import com.kivvi.gario.actors.Monster;

public class MapStage extends Stage {
	private Background bg;
	public Fog fog;
	public Door door;
	public Hero hero;
	private Monster monsters[];
	private Random rand;

	public TileType map[][] = new TileType[5][6];
	private int level;
	private int monsterCount;

	public enum TileType {
		NONE, DOOR, MONSTER,
	};

	public MapStage(Viewport viewport) {
		super(viewport);

		rand = new Random();
		rand.setSeed(System.currentTimeMillis());

		level = 1;

		clear();
		gen();

		hero = new Hero();
		this.addActor(hero);
		
		hero.log();
	}

	public void gen() {
		clear();

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 6; j++) {
				map[i][j] = TileType.NONE;
			}

		bg = new Background();
		this.addActor(bg);

		Vector2 vec2 = genRandPosition();
		door = new Door();
		door.setX(vec2.x);
		door.setY(vec2.y);
		map[(int) vec2.x][(int) vec2.y] = TileType.DOOR;
		this.addActor(door);

		monsters = null;
		monsterCount = genMonsterCount();
		monsters = new Monster[monsterCount];
		for (int i = 0; i < monsterCount; i++) {
			monsters[i] = new Monster(level);
			vec2 = genRandPosition();
			monsters[i].setX(vec2.x);
			monsters[i].setY(vec2.y);
			map[(int) vec2.x][(int) vec2.y] = TileType.MONSTER;
			// Gdx.app.log("debug", "monster[" + i + "]" + ": " + vec2);
			this.addActor(monsters[i]);
		}

		// gen key
		int temp = rand.nextInt(monsterCount);
		monsters[temp].setKey();

		fog = new Fog();
		this.addActor(fog);
		fog.init();
	}

	public Vector2 genRandPosition() {
		int x;
		int y;
		do {
			x = rand.nextInt(5);
			y = rand.nextInt(6);
		} while (map[x][y] != TileType.NONE);
		return new Vector2(x, y);
	}

	public int genMonsterCount() {
		// 7 - 10
		return rand.nextInt(5) + 3;
	}

	public void gotoNextLevel() {
		level++;
		clear();

		hero.nextLevel();
		this.addActor(hero);

		gen();

		this.addActor(fog);
		fog.init();
	}
	
	public TileType getMap(int i, int j) {
		if (i >= 0 && i < 5 && j >= 0 && j < 6) {
			return map[i][j];
		}
		return TileType.NONE;
	}
}
