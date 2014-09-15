package com.kivvi.livewallpaper.flowerzen;


import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.input.GestureDetector;
import com.kivvi.livewallpaper.flowerzen.utils.CamController;
import com.kivvi.livewallpaper.flowerzen.utils.MirrorCamera;

public class MainScreen extends Base {
	
	private static final String TAG = MainScreen.class.getName();
	// resolver
	private Simulation simulation;
	private Renderer renderer;
	private CamController camController;
	private GestureDetector gestureDetector;
	
	public MainScreen(Game game, Resolver resolver) {
		super(game, resolver);
		// Never put "show" part here
	}

	@Override
	public void show() {
		Gdx.app.setLogLevel(Gdx.app.LOG_NONE);
		Gdx.app.log(TAG, "create...");
		
		Config.load();
	
		Assets.instance.init(new AssetManager());
		simulation = new Simulation();
		renderer = new Renderer();
		resetCamera();
		
		camController = new CamController();
		gestureDetector = new GestureDetector(camController);
		Gdx.input.setInputProcessor(gestureDetector);
	}

	@Override
	public void dispose() {
		renderer.dispose();
		simulation.dispose();
	}

	@Override
	public void resize(int width, int height) {
		super.resize(width, height);
		resetCamera();
		Gdx.app.debug(TAG, "width" + width);
		Gdx.app.debug(TAG, "height" + height);
	}

	@Override
	public void render(float delta) {
		camController.applyTo(renderer.camera);
		if (isAndroid)
			limitFPS();
		
		draw(delta);   // Main draw part
		update(delta); // update animation ...
		
		if (isAndroid) {
			camController.updateOffset(this.resolver.getxPixelOffset() / sW );
		}

	}

	/**
	 *   Main draw part
	 */
	private void draw(float delta) {
		super.render(delta);
		
		// if (isAndroid && resolver != null) // In daydream resolver is null
			// Camera ..do something

		renderer.renderScene(simulation, delta);             // scene
		renderer.renderByFrameBuffer(simulation);           // reflect 
		renderer.renderByShader(simulation, delta);         // water
	}
	
	private void update(float delta) {
		simulation.update(delta);
	}


	private void resetCamera() {
		renderer.camera = new PerspectiveCamera(45, sW, sH);
		renderer.camera.position.set(0f, 0.18f, 3.2f);
		renderer.camera.lookAt(0f, 0.18f, 0);
		renderer.camera.near = 0.1f;
		renderer.camera.far = 1000f;
		renderer.camera.update();
		
		renderer.mirrorCamera = new MirrorCamera(45, sW, sH);
		renderer.mirrorCamera.updateMirrorFrom(renderer.camera);
	}
	
	


	
    

}

