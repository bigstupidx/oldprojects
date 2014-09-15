package com.kivvi.theline.actors;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.kivvi.theline.resource.Data;

public class BlockRow {
	public float y;
	private Block[] blocks = new Block[7];

	public BlockRow(float y, int roadType) {
		this.y = y;
		for (int i = 0; i < 7; i++) {
			int a = (1 << (i * 4));
			int b = a | roadType;
			if (b == roadType) {
				blocks[i] = new YellowBlock();
			} else {
				blocks[i] = new RedBlock();
			}

			blocks[i].setPosition(Data.blockWidth * (6 - i), y);
		}
	}

	public BlockRow(float y, String s) {
		this.y = y;
		for (int i = 0; i < 7; i++) {
			switch (s.charAt(i)) {
			case 'y':
				blocks[i] = new YellowBlock();
				break;
			case 'r':
				blocks[i] = new RedBlock();
				break;
			case 's': // score
				blocks[i] = new ScoreBlock();
				break;
			case 'j': // jump
				blocks[i] = new RedBlock();
				break;
			case 'b': // blue
				blocks[i] = new RedBlock();
				break;
				default:
					Gdx.app.log("diaosixu", "BlockRow error");
			}

			blocks[i].setPosition(Data.blockWidth * (6 - i), y);
		}
	}

	
	public void removeFromStage() {
		for (int i = 0; i < 7; i++) {
			blocks[i].remove();
		}
	}

	public void addToStage(Stage stage) {
		for (int i = 0; i < 7; i++) {
			blocks[i].addToStage(stage);
		}
	}

}
