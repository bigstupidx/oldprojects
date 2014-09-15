package com.kivvi.theline.screens;

import java.nio.ByteBuffer;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.Group;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.Touchable;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.ByteArray;
import com.badlogic.gdx.utils.SnapshotArray;
import com.badlogic.gdx.utils.viewport.ExtendViewport;
import com.badlogic.gdx.utils.viewport.FillViewport;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.StretchViewport;
import com.kivvi.theline.actors.Ball;
import com.kivvi.theline.actors.Block;
import com.kivvi.theline.actors.BlockRow;
import com.kivvi.theline.actors.TouchPad;
import com.kivvi.theline.actors.YellowBlock;
import com.kivvi.theline.game.TheLineGame;
import com.kivvi.theline.resource.Data;
import com.kivvi.theline.resource.GameAssets;

public class GameScreen extends BaseScreen {
	private Stage stage;
	private Stage stage2;
	private AssetManager assets = null;
	private Image menu;
	private Image scorePad;
	private Image arrowLeft;
	private Image arrowRight;
	private Image helpText;
	private Image greyBar;
	private Image timeCount;
	
	private Group score;
	private TouchPad tp; 
	private Image [] number = new Image[10];
	private Ball ball = null;
	
	private boolean isInit = false;
	
	private Array<BlockRow> blockRowArray = new Array<BlockRow>();
	
	private int lineCount = 1;
	
	private boolean volumn = false;
	
	private boolean debug = false;
	
	private enum State {
		start, gameover, ready
	}
	
	private State gameState = State.ready;
	
	public float scoreNumber = 0;
	
	private Sound stepSound = null;
	private Sound fallSound = null;
	private Sound bonusSound = null;
	
	public GameScreen(TheLineGame game) {
		super(game);
		assets = GameAssets.getAssets();
		loadResource();
	}

	private void init() {
		
		for (int i = 0; i < 10; i++) {
			number[i] = new Image();
			number[i].setSize(28, 40);
		}
		
		score = new Group();
		score.setTouchable(Touchable.disabled);
		
		tp = new TouchPad();
		ball = new Ball();
		
		stage = new Stage(new FillViewport(720, 1280));
		stage.addActor(ball);
		
		stage2 = new Stage(new StretchViewport(720, 1280));
		stage2.addActor(tp);
		
		
		Texture menuTexture = assets.get("menu.png");
		Texture scoreTexture = assets.get("score.png");
		Texture arrowTexture = assets.get("arrow.png");
		Texture helpTextTexture = assets.get("helptext.png");
		Texture c = assets.get("c.png");
		
		greyBar = new Image(c);
		greyBar.setPosition(0, Data.touchPadHeight);
		greyBar.setSize(720, 40);
		greyBar.setColor(0.5f, 0.5f, 0.5f, 1);
		
		timeCount = new Image();
		timeCount.setPosition(345, Data.touchPadHeight);
		timeCount.setSize(30, 30);
		timeCount.setColor(1, 1, 1, 1);
		
		menu = new Image(menuTexture);
		menu.setSize(181, 142);
		menu.setPosition(11, 1127);
		menu.addListener(new InputListener(){
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				if(gameState != State.gameover) {
					if (volumn) stepSound.play(1);
					toMenuScreen();	
				}
			}
		});
		
		scorePad = new Image(scoreTexture);
		scorePad.setSize(181, 142);
		scorePad.setPosition(269, 1127);
		scorePad.setTouchable(Touchable.disabled);
		
		arrowLeft = new Image(arrowTexture);
		arrowLeft.setSize(72, 33);
		arrowLeft.setPosition(109, 166);
		arrowLeft.setTouchable(Touchable.disabled);
		
		arrowRight = new Image(arrowTexture);
		arrowRight.setSize(72, 33);
		arrowRight.setPosition(540 + 72, 166);
		arrowRight.setScaleX(-1);
		arrowRight.setTouchable(Touchable.disabled);
		
		helpText = new Image(helpTextTexture);
		helpText.setSize(532, 27);
		helpText.setPosition(98, 223);
		helpText.setTouchable(Touchable.disabled);
		
		stage2.addActor(menu);
		stage2.addActor(scorePad);
		stage2.addActor(score);
		stage2.addActor(arrowLeft);
		stage2.addActor(arrowRight);
		stage2.addActor(helpText);
//		stage2.addActor(greyBar);
//		stage2.addActor(timeCount);
		
		tp.addListener(new InputListener() {
			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				
				Gdx.app.log("diaosixu", "pointer " + pointer);
				
				if (pointer > 0) return false;
				
				Gdx.app.log("diaosixu", "game state = " + gameState);
				
				if (gameState == State.ready) {
					gameState = State.start;
					
					arrowLeft.addAction(Actions.delay(0.5f, Actions.alpha(0, 1)));
					arrowRight.addAction(Actions.delay(0.5f, Actions.alpha(0, 1)));
					helpText.addAction(Actions.delay(0.5f, Actions.alpha(0, 1)));
					
					if (volumn) stepSound.play(1);
				}
				
				if (gameState == State.gameover) {
					return false;
				}
				
				ball.setX(x - ball.r);
				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				super.touchUp(event, x, y, pointer, button);
			}

			@Override
			public void touchDragged(InputEvent event, float x, float y,
					int pointer) {
				if (gameState != State.gameover) ball.setX(x - ball.r);
			}
		});
		
		generateRoad(0x1111111);
		generateRoad(0x0111110);
		generateRoad(0x0011100);
		generateRoad(0x0001000);
		generateRoad(0x0001000);
		generateRoad(0x0001000);
		generateRoad(0x0001000);
		
//		Music bgMusic = assets.get("fall.wav");
//		
//		Preferences pref = Gdx.app.getPreferences(Data.prefName);
//		volumn = pref.getBoolean("volumn");
//		
//		if (volumn) {
//			bgMusic.play();
//			bgMusic.setLooping(true);
//		}
		
		Preferences pref = Gdx.app.getPreferences(Data.prefName);
		volumn = pref.getBoolean("volumn", true);
		
		stepSound = assets.get("step.wav");
		fallSound = assets.get("fall.wav");
		bonusSound = assets.get("bonus.wav");
		
		Gdx.input.setInputProcessor(stage2);
		
		isInit = true;
	}

	private void loadResource() {
		assets.load("c.png", Texture.class);
		assets.load("gameover.png", Texture.class);
		assets.load("tryagain.png", Texture.class);
		assets.load("menu.png", Texture.class);
		assets.load("score.png", Texture.class);
		assets.load("ball.png", Texture.class);
		assets.load("scoreboard.png", Texture.class);
		assets.load("share.png", Texture.class);
		assets.load("arrow.png", Texture.class);
		assets.load("helptext.png", Texture.class);
		assets.load("best.png", Texture.class);
		assets.load("sc.png", Texture.class);
		assets.load("scoreboard.png", Texture.class);
		assets.load("newbest.png", Texture.class);
		assets.load("menutitle.png", Texture.class);
		assets.load("rate.png", Texture.class);
		assets.load("volumnoff.png", Texture.class);
		assets.load("volumnon.png", Texture.class);
//		assets.load("music.wav", Music.class);
		assets.load("fall.wav", Sound.class);
		assets.load("step.wav", Sound.class);
		assets.load("bonus.wav", Sound.class);
		assets.load("x6.png", Texture.class);
		
		for (int i = 0; i < 10; i++) {
			assets.load("white/" + i + ".png", Texture.class);
		}
	}
	
	public void logic() {
		float delta = Gdx.graphics.getDeltaTime();
		float scoreScale = 1.0f;
		
		if (gameState == State.start) {
			
			score.setColor(1, 1, 1, 1);
			
			float deltaY = delta * Data.ballSpeed;
			
			ball.setY(ball.getY() + deltaY);

			stage.getCamera().position.y += deltaY;	
			
			Block blockCollision = checkCollision();
			
			if (debug) {
				Gdx.app.log("diaosixu", "blockCollision is " + blockCollision);
				if (blockCollision != null && blockCollision.getBlockName().equals("red")) {
					blockCollision = null;	
				}
			} 
			
			if (blockCollision != null && blockCollision.getBlockName().equals("red")) {
				gameState = State.gameover;
				Preferences pref = Gdx.app.getPreferences(Data.prefName);
				pref.putInteger("score", (int) scoreNumber);
				int best = pref.getInteger("best");
				
				if ((int)scoreNumber > best) {
					pref.putInteger("best", (int) scoreNumber);
					pref.putBoolean("new best", true);
				} else {
					pref.putBoolean("new best", false);	
				}
				
				pref.flush();
				if (volumn) fallSound.play(1);
				blockCollision.addAction(Actions.repeat(-1, Actions.sequence(Actions.color(new Color(1, 0.87f, 0.47f, 1), 0.2f), Actions.color(blockCollision.getColor(), 0.2f)) ));
				ball.addAction(Actions.delay(3, Actions.run(new Runnable() {
					@Override
					public void run() {
						toGameOverScreen();
					}
				})));
			} else if (blockCollision != null && blockCollision.getBlockName().equals("score")) {
				if (blockCollision.getBlockName().equals("score")) {
					scoreScale = 6.0f;
					score.setColor(0.992f, 0.917f, 0.686f, 1);
				}
			} else {
				
			}
			
			if (blockCollision != null && blockCollision.getBlockName().equals("bonus")) {
				blockCollision.addAction(Actions.removeActor());
				ball.beSmall();
				if (volumn) bonusSound.play(1);
			}
			
			scoreNumber += delta * 10 * scoreScale;
		}
		
		updateScore();
		
		ball.toFront();
	}
	
	public void updateScore() {
		score.clearChildren();
		
		float gap = 7f;
		float w = 28;
		String scoreString = String.valueOf((int)scoreNumber);
		int length = scoreString.length();
		float startX = 346;
		startX -= (length - 1) * (14f + 3.5f);
		for (int i = 0; i < length; i++) {
			Texture texture = assets.get("white/" + scoreString.charAt(i) + ".png");
			Image num = new Image(texture);
			num.setColor(score.getColor());
			num.setSize(28, 40);
			num.setPosition(startX + (w + gap) * i, 1159);
			score.addActor(num);
		}
	}
	
	public Block checkCollision() {
		Block ret = null;
		
		Group root = stage.getRoot();
		SnapshotArray<Actor> array = root.getChildren();
		
		for (int i = 0; i < array.size; i++) {
			if (array.get(i) == ball) continue;
			
			Block block = (Block)array.get(i);
			String blockName = block.checkCollision(ball.getX(), ball.getY(), ball.isSmall);
			
			if ("red".equals(blockName) || "score".equals(blockName) || "bonus".equals(blockName)) {
				ret = block;
				break;
			}
		}
		
		return ret;
	}
	
	public void toGameOverScreen() {
		game.setScreen(game.gameOverScreen);
	}
	
	public void toMenuScreen() {
		game.setScreen(game.menuScreen);
	}
	
	@Override
	public void render(float delta) {
		Gdx.gl.glClearColor(0, 0, 0, 0);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
		
//		Gdx.app.log("fps", "fps = " + Gdx.graphics.getFramesPerSecond());
		
		if (!assets.update()) {
			return;
		} else {
			if (!isInit) {
				init();
			}
		}
		
		logic();
		
		stage.getViewport().update();
		stage.act(Gdx.graphics.getDeltaTime());
		stage.draw();
		
		stage2.getViewport().update();
		stage2.act(Gdx.graphics.getDeltaTime());
		stage2.draw();
		
		if (gameState == State.start) {
			if (blockRowArray.size > 0) {
				if (blockRowArray.get(0).y < ball.getY() - Data.screenHeight) {
					blockRowArray.get(0).removeFromStage();
					blockRowArray.removeIndex(0);
				}	
			}
			
			if (blockRowArray.size < 16) {
				if (MathUtils.random() > 0.5) {
					for (int i = 0; i < road1.length; i++) {
						generateRoad(road1[i]);
					}
				} else {
					for (int i = 0; i < road2.length; i++) {
						generateRoad(road2[i]);
					}
				}
			}
		}
	}
	
	@Override
	public void show() {
		if (isInit) {
			Preferences pref = Gdx.app.getPreferences(Data.prefName);
			volumn = pref.getBoolean("volumn", true);
			
			ball.reset();
			YellowBlock.count = 0;
			stage.getCamera().position.set(360, 640, 0);
			
			stage.addActor(ball);
			
			generateRoad(0x1111111);
			generateRoad(0x0111110);
			generateRoad(0x0011100);
			generateRoad(0x0001000);
			generateRoad(0x0001000);
			generateRoad(0x0001000);
			generateRoad(0x0001000);
			
			gameState = State.ready;
			
			arrowLeft.addAction(Actions.alpha(1, 0));
			arrowRight.addAction(Actions.alpha(1, 0));
			helpText.addAction(Actions.alpha(1, 0));
			
			Gdx.input.setInputProcessor(stage2);
		}
	}

	@Override
	public void hide() {
		stage.clear();
		blockRowArray.clear();
		lineCount = 1;
		scoreNumber = 0;
	}

	@Override
	public void dispose() {
		stage.dispose();
		stage2.dispose();
		GameAssets.release();
	}

	public void generateRoad (int roadType) {
		BlockRow br = new BlockRow(lineCount * Data.blockHeight, roadType);
		br.addToStage(stage);
		blockRowArray.add(br);
		lineCount++;
	}
	
	public void generateRoad (String roadType) {
		BlockRow br = new BlockRow(lineCount * Data.blockHeight, roadType);
		br.addToStage(stage);
		blockRowArray.add(br);
		lineCount++;
	}
		
	private String [] road1 = {
		"rrryrrr",
		"rrryyrr",
		"rrrryrr",
		"rrrryrr",
		"rrrryrr",
		"rrryyrr",
		"rrryrrr",
		"rrryyyr",
		"rrrrryr",
		"rrrrryr",
		"rrrrryr",
		"ryyyyyr",
		"ryrrrrr",
		"ryrrrrr",
		"ryyyrrr",
		"rrryrrr",
		"rrryyrr",
		"rrrryrr",
		"rrrryyr",
		"rrrrryr",
		"rssyyyr",
		"rsryrrr",
		"rsryyrr",
		"rsrryyr",
		"rssrryr",
		"rrssyyr",
		"rrrryrr",
		"rrryyrr",
		"rrryrrr",
		"rrryyrr",
		"rrrryyr",
		"rrrrryr",
		"rrryyyr",
		"rryyrrr",
		"ryyrrrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryyyyrr",
		"rrrryrr",
		"rryyyrr",
		"rryrrrr",
		"rryyyyr",
		"rrrrryr",
		"rrrrryr",
		"rrryyyr",
		"rrryrrr",
		"ryyyrrr",
		"ryrrrrr",
		"ryyyrrr",
		"rrryssr",
		"rrryrsr",
		"rrryrsr",
		"rrryrsr",
		"rryyrsr",
		"rryrrsr",
		"rrysssr",
		"rryrrrr",
		"rryyyrr",
		"rrrryrr",
		"rrryyrr",
		"rrryrrr",
		"rrryrrr",
		"rrryrrr",
	};
	
	
	private String [] road2 = {
		"rrryrrr",
		"rrryyrr",
		"rrrryrr",
		"ryyyyrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryyrrrr",
		"rryyrrr",
		"rrryrrr",
		"rrryrrr",
		"rrryrrr",
		"ryyyrrr",
		"ryrrrrr",
		"ryyyyyr",
		"rrrrryr",
		"rssssyr",
		"rsrrryr",
		"rsrryyr",
		"ryyyyrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryrrrrr",
		"ryyrrrr",
		"rryyrrr",
		"rrryyrr",
		"rrrryrr",
		"rrryyrr",
		"rryyrrr",
		"rryrrrr",
		"ryyrrrr",
		"ryrrrrr",
		"ryyyyrr",
		"rrrryrr",
		"rrrryrr",
		"rrryyrr",
		"rrryrrr",
		"rryyrrr",
		"rryrrrr",
		"rryyyyr",
		"rrrrryr",
		"rrrryyr",
		"rrrryrr",
		"ryyyyrr",
		"ryrrrrr",
		"ryyyrrr",
		"rrryrrr",
		"rssyrrr",
		"rsryrrr",
		"rsryrrr",
		"rssyssr",
		"rrryrsr",
		"rrryrsr",
		"rrryssr",
		"rrryrrr",
		"rrryrrr",
	};
}
