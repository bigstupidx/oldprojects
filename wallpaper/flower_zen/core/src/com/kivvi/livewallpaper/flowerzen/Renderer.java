package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight;
import com.badlogic.gdx.graphics.g3d.utils.DefaultTextureBinder;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.graphics.glutils.FrameBuffer;
import com.badlogic.gdx.math.Vector3;
import com.kivvi.livewallpaper.flowerzen.shaders.WaterShader;
import com.kivvi.livewallpaper.flowerzen.utils.MirrorCamera;

public class Renderer {
	private static final String TAG = Renderer.class.getName();

	public PerspectiveCamera camera;
	Environment environment;

	private RenderContext renderContext;
	private WaterShader waterShader;

	private ModelBatch modelBatch;

	private int screenWidth = Gdx.graphics.getWidth();
	private int screenHeight = Gdx.graphics.getHeight();

	/* FrameBuffer */
	private FrameBuffer fbo;
	private int fbWidth = screenWidth;
	private int fbHeight = screenHeight;
	Vector3 dirPosion;
	//
	public MirrorCamera mirrorCamera;
	private Texture reflectTexture;

	public Renderer() {

		dirPosion = new Vector3(2.54308f, 3.71026f, -3.10952f).nor();
		environment = new Environment();
		environment.set(new ColorAttribute(ColorAttribute.AmbientLight, 0.4f,
				0.4f, 0.4f, 1f));
		environment
				.add(new DirectionalLight().set(0.6f, 0.6f, 0.6f, dirPosion));

		modelBatch = new ModelBatch();

		camera = new PerspectiveCamera(45, screenWidth, screenHeight);
		camera.position.set(0f, 0.18f, 3.2f);
		camera.lookAt(0f, 0.18f, 0);
		camera.near = 0.1f;
		camera.far = 1000f;
		camera.update();
		Gdx.app.log(TAG, "camera pos: " + camera.position);

		mirrorCamera = new MirrorCamera(45, screenWidth, screenHeight);
		mirrorCamera.updateMirrorFrom(camera);
		Gdx.app.log(TAG, "mirrcam pos: " + mirrorCamera.position + "");

		/* for debug */
		// cameraController = new CameraInputController(camera);
		// mirrorCameraController = new CameraInputController(mirrorCamera);
		// Gdx.input.setInputProcessor(mirrorCameraController);
		// Gdx.input.setInputProcessor(cameraController);

		waterShader = new WaterShader();
		waterShader.init(Assets.instance.water.getMyRenderable());
		initializeFBO();

		renderContext = new RenderContext(new DefaultTextureBinder(
				DefaultTextureBinder.WEIGHTED, 1));

	}

	private void initializeFBO() {
		if (fbo != null)
			fbo.dispose();
		fbo = new FrameBuffer(Pixmap.Format.RGB565, fbWidth, fbHeight, true);
		fbo.getColorBufferTexture().setFilter(TextureFilter.Nearest,
				TextureFilter.Nearest);
	}

	public void renderByShader(Simulation simulation, float delta) {
		// cameraController.update();
		camera.update();
		mirrorCamera.updateMirrorFrom(camera);
		Assets.instance.water.setDiffuseTexture(reflectTexture);

		renderContext.begin();
		waterShader.begin(camera, renderContext);
		waterShader.render(Assets.instance.water.getMyRenderable());
		waterShader.end();
		renderContext.end();
	};

	public void renderByFrameBuffer(Simulation simulation) {
		// Start rendering into the framebuffer
		fbo.begin();

		// Clear the viewport
		Gdx.gl.glViewport(0, 0, fbo.getWidth(), fbo.getHeight());
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);

		// Draw all model instances using the mirror
		modelBatch.begin(mirrorCamera);
		modelBatch.render(simulation.background);
		modelBatch.render(simulation.flower_1);
		modelBatch.render(simulation.flower_2);
		modelBatch.render(simulation.stone);
		modelBatch.render(simulation.petal_1);
		modelBatch.render(simulation.petal_2);
		modelBatch.render(simulation.branch_1);
		modelBatch.render(simulation.branch_2);
		modelBatch.end();
		fbo.end();

		reflectTexture = fbo.getColorBufferTexture();

		// debug Test framebuffer to the mini screen
		// fboBatch.begin();
		// fboBatch.draw(fbo.getColorBufferTexture(), 0, 0, screenWidth/4,
		// screenHeight/4, 0, 0, 1, 1);
		// fboBatch.end();

	}

	/**
	 * render scene
	 */
	public void renderScene(Simulation simulation, float delta) {

		modelBatch.begin(camera);
		modelBatch.render(simulation.background);
		modelBatch.render(simulation.flower_1);
		modelBatch.render(simulation.flower_2);
		modelBatch.render(simulation.stone, environment);
		modelBatch.render(simulation.petal_1);
		modelBatch.render(simulation.petal_2);
		modelBatch.render(simulation.branch_1);
		modelBatch.render(simulation.branch_2);
		modelBatch.end();

	}

	public void dispose() {
		modelBatch.dispose();
		fbo.dispose();
	}

}
