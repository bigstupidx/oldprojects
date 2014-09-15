package com.kivvi.ios8;

import aurelienribon.tweenengine.Tween;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Pixmap.Format;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.glutils.FrameBuffer;
import com.badlogic.gdx.utils.Scaling;
import com.badlogic.gdx.utils.viewport.ScalingViewport;
import com.kivvi.tween.Entity;
import com.kivvi.tween.EntityAccessor;
import com.kivvi.tween.Manager;
import com.kivvi.wallpaper.Properties;

public class IOS8 extends ApplicationAdapter {

	public static AssetManager manager;
	boolean loaded = false;

	// scene
	Scene scene;
	Background bg;
	Lights lights;
	Spots spots;

	Scene finalScene;
	DistortBackground finalBg;
	DistortLights distortLights;

	public static Accelerometer acceler;

	public final static float borderWidth = 0.08f;
	public final static float borderHeight = 0.05f;

	FrameBuffer fb;

	@Override
	public void create() {
		// Load properties first always.
		Properties.load();

		// Asset manager.
		manager = new AssetManager();
		manager.load("data/background.png", Texture.class);
		manager.load("data/spot.png", Texture.class);
		manager.load("data/spot-weak.png", Texture.class);
		for (int i = 1; i < 9; i++) {
			manager.load("data/" + i + ".png", Texture.class);
		}

		// Tween ready.
		Tween.registerAccessor(Entity.class, new EntityAccessor());
	}

	@Override
	public void render() {
		if (manager.update()) {
			if (!loaded) {
				setupScene();
				loaded = true;
			}
		} else {
			// waiting for asset loading
			return;
		}

		// update accelerometer.
		acceler.update();

		if (Properties.get("wave")) {
			fb.begin();
			scene.draw();
			fb.end();

			finalScene.draw();
		} else {
			scene.draw();
		}

		Manager.get().update(Gdx.graphics.getDeltaTime());
	}

	public void setupScene() {
		// background texture
		Texture texBg = manager.get("data/background.png", Texture.class);

		// create accelerometer
		acceler = new Accelerometer(texBg.getWidth(), texBg.getHeight());

		// create scene
		// keep 5% for g-sensor
		scene = new Scene(new ScalingViewport(Scaling.fill, texBg.getWidth()
				* (1.0f - 2 * borderWidth), texBg.getHeight()
				* (1.0f - 2 * borderHeight)));

		// create and add bg
		bg = new Background(texBg);
		scene.addActor(bg);

		// create and add spots
		spots = new Spots();
		scene.addActor(spots);

		// create and add lights
		lights = new Lights();
		scene.addActor(lights);

		// create final scene
		finalScene = new Scene(new ScalingViewport(Scaling.fill,
				texBg.getWidth() * (1.0f - 2 * borderWidth), texBg.getHeight()
						* (1.0f - 2 * borderHeight)));

		// create framebuffer
		fb = new FrameBuffer(Format.RGB888, texBg.getWidth(),
				texBg.getHeight(), false);
		finalBg = new DistortBackground(fb.getColorBufferTexture());
		finalScene.addActor(finalBg);

		// create and add lights
		distortLights = new DistortLights();
		finalScene.addActor(distortLights);
	}

	@Override
	public void dispose() {
		super.dispose();

		scene.dispose();
		manager.dispose();
	}

	@Override
	public void resume() {
		super.resume();

		// Load properties when resume.
		Properties.load();

		// Gdx.app.log("debug", "resume");
		if (spots != null) {
			spots.reset();
		}
	}

	@Override
	public void resize(int width, int height) {
		super.resize(width, height);

		if (finalBg != null) {
			finalBg.resize();
		}
	}
}
