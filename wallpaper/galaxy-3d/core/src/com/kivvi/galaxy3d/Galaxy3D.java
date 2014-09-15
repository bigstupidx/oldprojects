package com.kivvi.galaxy3d;

import java.awt.peer.LightweightPeer;
import java.io.File;
import java.nio.ByteBuffer;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Pixmap.Format;
import com.badlogic.gdx.graphics.PixmapIO;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.Texture.TextureWrap;
import com.badlogic.gdx.graphics.g2d.ParticleEffect;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.IntAttribute;
import com.badlogic.gdx.graphics.g3d.attributes.TextureAttribute;
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight;
import com.badlogic.gdx.graphics.g3d.utils.DefaultTextureBinder;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.utils.viewport.StretchViewport;
import com.badlogic.gdx.utils.viewport.Viewport;

public class Galaxy3D implements ApplicationListener {
	private String assetName = "mm1.g3db";
	private String assetName2 = "mm2.g3db";
	private String assetName3 = "mm3.g3db";
	private String assetComet = "comet.g3db";
	private PerspectiveCamera camera;
	private ModelBatch batch;
	private Model model;
	private Model model2;
	private Model model3;
	private Model modelComet;
	private ModelInstance instance;
	private ModelInstance instance2;
	private ModelInstance instance3;
	private ModelInstance instanceComet;
	
	private RenderContext renderContext;
	private Environment env;
	
	private AssetManager assetManager = new AssetManager();
	private boolean sceneSeparated = false;
	
	private Stage bgStage;
	private Image background;
	private Image planet;
	
	private ParticleEmitter particleEmitter;
	private ParticleEmitter particleEmitter2;
	private ParticleEmitter particleEmitter3;
	private ParticleEmitter particleEmitter4;
	
	private Stage stage;
	private Viewport viewport;
	private ParticleEffect particles;
	private ParticleEffect particles2;
	private ParticleEffect particles3;
	
	private DirectionalLight dLight;
	
	private Texture [] bgs = new Texture[6];
	private Color [] lightColors = new Color[6];
	private int currBg = 0;
	
	@Override
	public void create() {		
		float w = Gdx.graphics.getWidth();
		float h = Gdx.graphics.getHeight();
		camera = new PerspectiveCamera(90, w, h);
		camera.position.set(0, 0, 0);
		camera.lookAt(0, 0, 0);
		camera.near = 1f; 
		camera.far = 2000;
		camera.update();
		
		env = new Environment();
		dLight = new DirectionalLight();
		dLight.direction.set(0, 0f, -1);
		dLight.color.set(0.8f, 0.4f, 0.6f, 1.0f);
		
		env.add(dLight);
		
		batch = new ModelBatch();

		renderContext = new RenderContext(new DefaultTextureBinder(
				DefaultTextureBinder.WEIGHTED));

		bgStage = new Stage(new StretchViewport(720, 1280));	
		
		stage = new Stage(bgStage.getViewport());
//		bgStage.getCamera().position.x += 300; 
		bgStage.getCamera().update();
		
		particles = new ParticleEffect();
		particles.load(Gdx.files.internal("aa.p"),
				Gdx.files.internal(""));
		particles.start();
		
		particles2 = new ParticleEffect();
		particles2.load(Gdx.files.internal("bb.p"),
				Gdx.files.internal(""));
		particles2.start();
		
		particles3 = new ParticleEffect();
		particles3.load(Gdx.files.internal("cc.p"),
				Gdx.files.internal(""));
		particles3.start();
		
		assetManager.load(assetName, Model.class);
		assetManager.load(assetName2, Model.class);
		assetManager.load(assetName3, Model.class);
		assetManager.load(assetComet, Model.class);
		
		assetManager.load("bg.jpg", Texture.class);
		assetManager.load("bg2.jpg", Texture.class);
		assetManager.load("bg3.jpg", Texture.class);
		assetManager.load("bg4.jpg", Texture.class);
		assetManager.load("bg5.jpg", Texture.class);
		assetManager.load("bg6.jpg", Texture.class);
		assetManager.load("planet.png", Texture.class);
		assetManager.load("rock1.jpg", Texture.class);
		
		bgStage.addListener(new ClickListener() {
			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				
				if (currBg == 5) {
					currBg = 0;
				} else {
					currBg++;
				}
				
				background.setDrawable(new TextureRegionDrawable(new TextureRegion(bgs[currBg])));
				dLight.color.set(lightColors[currBg]);
				super.touchUp(event, x, y, pointer, button);
			}
			
		});
		
		Gdx.input.setInputProcessor(bgStage);
		
		lightColors[0] = new Color(0.8f, 0.4f, 0.6f, 1.0f);
		lightColors[1] = new Color(0.9f, 0.4f, 0.3f, 1.0f);
		lightColors[2] = new Color(0.7f, 0.35f, 0.15f, 1.0f);
		lightColors[3] = new Color(0.8f, 0.1f, 0.1f, 1.0f);
		lightColors[4] = new Color(0.1f, 0.5f, 0.7f, 1.0f);
		lightColors[5] = new Color(0.1f, 0.6f, 0.5f, 1.0f);
	}

	public void separateScene() {
		model = assetManager.get(assetName);
		model2 = assetManager.get(assetName2);
		model3 = assetManager.get(assetName3);
		modelComet = assetManager.get(assetComet);
		
		Texture texture = assetManager.get("rock1.jpg");
		texture.setFilter(TextureFilter.Linear, TextureFilter.Linear);
		texture.setWrap(TextureWrap.ClampToEdge, TextureWrap.ClampToEdge);
		model.materials.get(0).set(TextureAttribute.createDiffuse(texture));
		model2.materials.get(0).set(TextureAttribute.createDiffuse(texture));
		model3.materials.get(0).set(TextureAttribute.createDiffuse(texture));
		model3.materials.get(0).set(TextureAttribute.createDiffuse(texture));

		instance = new ModelInstance(model);
		instance2 = new ModelInstance(model2);
		instance3 = new ModelInstance(model3);
		
		Texture texturePlanet = assetManager.get("planet.png");
		planet = new Image(texturePlanet);
		planet.setSize(349, 350);
		planet.setPosition(375, 205);
		//stage.addActor(planet);
		
		particleEmitter = new ParticleEmitter(model);
		ParticleDescription pd = new ParticleDescription();
//		pd.speedHigh = 100;
//		pd.speedLow = 20;
//		pd.birthLow = new Vector3(400, -400, -300);
//		pd.birthHigh = new Vector3(400, 400,  -50);
//		pd.destinationLow = new Vector3(-400, -400, -300);
//		pd.destinationHigh = new Vector3(-400, 400,  -50);
		particleEmitter2 = new ParticleEmitter(model2, pd);
		
		ParticleDescription pd2 = new ParticleDescription();
//		pd2.speedHigh = 100;
//		pd2.speedLow = 20;
//		pd2.birthLow = new Vector3(-400, -400, -300);
//		pd2.birthHigh = new Vector3(-400, 400,  -50);
//		pd2.destinationLow = new Vector3(400, -400, -300);
//		pd2.destinationHigh = new Vector3(400, 400,  -50);
		particleEmitter3 = new ParticleEmitter(model3, pd2);
		Texture bg = assetManager.get("bg.jpg");
		Texture bg2 = assetManager.get("bg2.jpg");
		Texture bg3 = assetManager.get("bg3.jpg");
		Texture bg4 = assetManager.get("bg4.jpg");
		Texture bg5 = assetManager.get("bg5.jpg");
		Texture bg6 = assetManager.get("bg6.jpg");
		
		bgs[0] = bg;
		bgs[1] = bg2;
		bgs[2] = bg3;
		bgs[3] = bg4;
		bgs[4] = bg5;
		bgs[5] = bg6;
		
		bg.setWrap(TextureWrap.ClampToEdge, TextureWrap.ClampToEdge);
		bg.setFilter(TextureFilter.Linear, TextureFilter.Linear);
		background = new Image(bg);
		background.setSize(720, 1280);	
		bgStage.addActor(background);
		
		instance2.transform.setTranslation(0, 0, -1000);
		
		particleEmitter.update(30);
		particleEmitter2.update(30);
		particleEmitter3.update(30);
		
		sceneSeparated = true;
	}
	
	@Override
	public void render() {		
		Gdx.gl.glClearColor(0.0f, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		
		if (assetManager.update()) {
			if (!sceneSeparated) {
				separateScene();
			}
		} else {
			return;
		}
		
		bgStage.draw();
		
		stage.getSpriteBatch().begin();
		particles.draw(stage.getSpriteBatch(), Gdx.graphics.getDeltaTime());
		particles2.draw(stage.getSpriteBatch(), Gdx.graphics.getDeltaTime());
		particles3.draw(stage.getSpriteBatch(), Gdx.graphics.getDeltaTime());
		stage.getSpriteBatch().end();
		stage.draw();
		
		batch.begin(camera);
		particleEmitter.update(Gdx.graphics.getDeltaTime());
		Array<Meteorite> meteorites = particleEmitter.getMeteoriteArray();
		for (int i = 0; i < meteorites.size; i++) {
			batch.render(meteorites.get(i).instance, env);	
		}
		
		particleEmitter2.update(Gdx.graphics.getDeltaTime());
		Array<Meteorite> meteorites2 = particleEmitter2.getMeteoriteArray();
		for (int i = 0; i < meteorites2.size; i++) {
			batch.render(meteorites2.get(i).instance, env);	
		}
		
		particleEmitter3.update(Gdx.graphics.getDeltaTime());
		Array<Meteorite> meteorites3 = particleEmitter3.getMeteoriteArray();
		for (int i = 0; i < meteorites3.size; i++) {
			batch.render(meteorites3.get(i).instance, env);	
		}
//		Vector3 v = new Vector3();
//		instance2.transform.getTranslation(v);
//		instance2.transform.setTranslation(0, 0, v.z + Gdx.graphics.getDeltaTime() * 200);
//		instance2.transform.rotate(new Vector3(1, 1, 1), 0.5f);
		batch.end();
		
//		Gdx.app.log("diaosixu", "fps = " + Gdx.graphics.getFramesPerSecond());
	}


	@Override
	public void resize(int width, int height) {
	}

	@Override
	public void pause() {
	}

	@Override
	public void resume() {
	}
	
	@Override
	public void dispose() {
		assetManager.dispose();
		batch.dispose();
		stage.dispose();
		bgStage.dispose();
		particles.dispose();
		particles2.dispose();
		particles3.dispose();
	}
	
	
}
