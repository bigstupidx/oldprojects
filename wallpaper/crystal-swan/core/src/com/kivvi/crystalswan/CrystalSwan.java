package com.kivvi.crystalswan;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.Texture.TextureWrap;
import com.badlogic.gdx.graphics.g2d.ParticleEffect;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.Renderable;
import com.badlogic.gdx.graphics.g3d.attributes.BlendingAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.IntAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.TextureAttribute;
import com.badlogic.gdx.graphics.g3d.utils.DefaultTextureBinder;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.StretchViewport;
import com.badlogic.gdx.utils.viewport.Viewport;

public class CrystalSwan implements ApplicationListener {
	private PerspectiveCamera camera;
	private ModelBatch batch;

	private Model swanScene;
	private SwanShader swanShader;
	private LightShader lightShader;

	private RenderContext renderContext;

	private Renderable swan = new Renderable();
	private Renderable leaf = new Renderable();
	private Renderable light = new Renderable();
	private Renderable background = new Renderable();
	private ModelInstance swanSceneInstance;

	private AssetManager assetManager = new AssetManager();
	private boolean sceneSeparated = false;

	private GestureDetector gestureDetector;
	private CameraController cameraControl;

	private Stage stage;
	private Viewport viewport;
	private ParticleEffect particles;

	private int currBackground = 0;
	private boolean doubleClickExcuted = false;

	private TextureAttribute ta1;
	private TextureAttribute ta2;
	private TextureAttribute ta3;

	private ColorAttribute colorAttribute;

	@Override
	public void create() {
		// get properties first of all.
		Properties.load("data/channel.properties");

		float w = Gdx.graphics.getWidth();
		float h = Gdx.graphics.getHeight();

		assetManager.load("data/swan.g3db", Model.class);

		camera = new PerspectiveCamera(50, w, h);
		camera.position.set(0, 60, 218);
		camera.lookAt(0, 59, 0);
		camera.near = 0.1f;
		camera.far = 10000;
		camera.update();

		viewport = new StretchViewport(720, 1280);
		viewport.update((int) w, (int) h, true);
		stage = new Stage(viewport);
		stage.getSpriteBatch().setProjectionMatrix(stage.getCamera().combined);
		batch = new ModelBatch();

		// camController
		cameraControl = new CameraController(camera);
		gestureDetector = new GestureDetector(cameraControl);
		Gdx.input.setInputProcessor(gestureDetector);

		swanShader = new SwanShader();
		swanShader.init();
		renderContext = new RenderContext(new DefaultTextureBinder(
				DefaultTextureBinder.WEIGHTED));

		lightShader = new LightShader();
		lightShader.init();

		particles = new ParticleEffect();
		particles.load(Gdx.files.internal("data/a.p"),
				Gdx.files.internal("data"));
		particles.start();
	}

	public void separateScene() {
		swanScene = assetManager.get("data/swan.g3db");
		swanScene.getNode("light").parts.get(0).material
				.set(new BlendingAttribute());

		swanSceneInstance = new ModelInstance(swanScene);
		swanSceneInstance.getRenderable(light,
				swanSceneInstance.getNode("light"));
		swanSceneInstance
				.getRenderable(leaf, swanSceneInstance.getNode("leaf"));

		swanSceneInstance.getRenderable(background,
				swanSceneInstance.getNode("background"));
		swanSceneInstance
				.getRenderable(swan, swanSceneInstance.getNode("swan"));

		sceneSeparated = true;

		if (Properties.getChangeBackground()) {
			ta1 = (TextureAttribute) background.material
					.get(TextureAttribute.Diffuse);
			Texture t2 = new Texture("data/bg02.png");
			t2.setFilter(TextureFilter.Linear, TextureFilter.Linear);
			t2.setWrap(TextureWrap.Repeat, TextureWrap.Repeat);
			Texture t3 = new Texture("data/bg03.png");
			t3.setFilter(TextureFilter.Linear, TextureFilter.Linear);
			t3.setWrap(TextureWrap.Repeat, TextureWrap.Repeat);
			ta2 = TextureAttribute.createDiffuse(t2);
			ta3 = TextureAttribute.createDiffuse(t3);

			background.material.set(ta1);
			colorAttribute = (ColorAttribute) background.material
					.get(ColorAttribute.Diffuse);
			background.material.set(IntAttribute.createCullFace(GL20.GL_BACK));
		}
	}

	@Override
	public void dispose() {
		batch.dispose();
		swanShader.dispose();
		lightShader.dispose();

		stage.dispose();
		particles.dispose();

		assetManager.dispose();
	}

	@Override
	public void render() {
		Gdx.gl.glClearColor(0.0f, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);

		if (assetManager.update()) {
			if (!sceneSeparated) {
				separateScene();
			}
		} else
			return;

		if (!cameraControl.getControlStatus()) {
			float angle = cameraControl.getCameraRotateAngle();
			camera.rotateAround(new Vector3(0, camera.position.y, 0),
					new Vector3(0, 1, 0), angle);
		}

		camera.update();

		// render scene
		batch.begin(camera);
		batch.render(background);
		batch.end();

		renderContext.begin();
		lightShader.begin(camera, renderContext);
		renderContext.setBlending(true, GL20.GL_SRC_ALPHA,
				GL20.GL_ONE_MINUS_SRC_ALPHA);
		renderContext.setCullFace(GL20.GL_BACK);
		lightShader.render(light);
		lightShader.end();

		// renderContext.setDepthMask(true);
		// renderContext.setDepthTest(GL20.GL_LEQUAL);

		swanShader.begin(camera, renderContext);

		renderContext.setCullFace(GL20.GL_FRONT);
		swanShader.setRenderFace(1);
		renderContext.setBlending(false, 0, 0);
		swanShader.setColor(0.45f, 0.32f, 0.72f, 1.0f);
		swanShader.render(leaf);
		swanShader.setRenderFace(0);
		renderContext.setCullFace(GL20.GL_BACK);
		renderContext.setBlending(true, GL20.GL_ONE, GL20.GL_ONE);
		swanShader.setColor(0.45f, 0.32f, 0.72f, 1.0f);
		swanShader.render(leaf);

		renderContext.setCullFace(GL20.GL_FRONT);
		swanShader.setRenderFace(1);
		renderContext.setBlending(false, 0, 0);
		swanShader.setColor(1.0f, 0.55f, 0.63f, 1.0f);
		swanShader.render(swan);
		swanShader.setRenderFace(0);
		renderContext.setCullFace(GL20.GL_BACK);
		renderContext.setBlending(true, GL20.GL_ONE, GL20.GL_ONE);
		swanShader.setColor(1.0f, 0.55f, 0.63f, 1.0f);
		swanShader.render(swan);

		swanShader.end();

		renderContext.end();
		stage.getSpriteBatch().begin();
		particles.draw(stage.getSpriteBatch(), Gdx.graphics.getDeltaTime());
		stage.getSpriteBatch().end();

		final float y1 = 201;
		final float y2 = 14;
		final float z1 = 212;
		final float z2 = 283;
		float pitch = Gdx.input.getPitch();
		float percent = MathUtils.clamp(pitch / (-90.0f), 0, 1);
		camera.position.y += (y2 + (y1 - y2) * percent - camera.position.y) * 2
				* Gdx.graphics.getDeltaTime();
		float currDist = (float) Math.sqrt(camera.position.z
				* camera.position.z + camera.position.x * camera.position.x);
		float deltaDist = (z2 + (z1 - z2) * percent - currDist) * 2
				* Gdx.graphics.getDeltaTime();
		float k = 1.0f + deltaDist / currDist;
		camera.position.x *= k;
		camera.position.z *= k;
		// Gdx.app.log("diaosixu", "pitch = " + pitch + "y = " +
		// camera.position.y);
		// Gdx.app.log("diaosixu", "pitch = " + pitch + "z = " +
		// camera.position.z);
		camera.lookAt(0, 59, 0);
		camera.update();

		if (Properties.getDoubleTap()) {
			if (cameraControl.getTapCount() == 2) {
				if (!doubleClickExcuted) {
					changeWallpaper();
					doubleClickExcuted = true;
				}
			} else {
				doubleClickExcuted = false;
			}
			cameraControl.update(Gdx.graphics.getDeltaTime());
		}

		if (Properties.getChangeBackground()) {
			int brightness = Properties.getBrightness();
			colorAttribute.color.r = 0.01f * (float) brightness;
			colorAttribute.color.g = 0.01f * (float) brightness;
			colorAttribute.color.b = 0.01f * (float) brightness;
			colorAttribute.color.a = 0.01f * (float) brightness;
			background.material.set(colorAttribute);
		}
	}

	@Override
	public void resize(int width, int height) {
	}

	@Override
	public void pause() {
	}

	@Override
	public void resume() {
		// get properties again when resume.
		Properties.load("data/channel.properties");
	}

	public void changeWallpaper() {
		if (Properties.getChangeBackground()) {
			TextureAttribute[] ta = { ta1, ta2, ta3 };
			currBackground++;
			if (currBackground == 3) {
				currBackground = 0;
			}
			background.material.set(ta[currBackground]);
			// Gdx.app.log("diaosixu", "change wallpaper");
		}
	}
}
