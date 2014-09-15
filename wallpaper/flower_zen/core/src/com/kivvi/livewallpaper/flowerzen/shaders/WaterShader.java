package com.kivvi.livewallpaper.flowerzen.shaders;

import java.sql.Time;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureWrap;
import com.badlogic.gdx.graphics.g3d.Renderable;
import com.badlogic.gdx.graphics.g3d.Shader;
import com.badlogic.gdx.graphics.g3d.shaders.BaseShader;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.utils.GdxRuntimeException;

public class WaterShader extends BaseShader {
	public final int waveScale = register("waveScale");
	public final int reflecDistort = register("reflecDistort");
	public final int refracDistort = register("refracDistort");
	public final int fresnel = register("fresnel");
	public final int waveSpeed = register("waveSpeed");
	public final int refracColor = register("refracColor");
	public final int u_resolution = register("u_resolution");

	public final int u_projTrans = register("u_projTrans");
	public final int u_viewTrans = register("u_viewTrans");
	public final int u_projViewTrans = register("u_projViewTrans");
	public final int u_cameraPosition = register("u_cameraPosition");
	public final int u_time = register("u_time");
	public final int u_worldTrans = register("u_worldTrans");
	public final int u_normalMatrix = register("u_normalMatrix");
	public final int u_normalTexture = register("u_normalTexture");

	// use default shader uniform
	// u_normalTexture
	// u_fogColor
	// u_dirLights0color
	// u_dirLights0direction
	private float currentTime = 0;
	

	Texture normalTexture;

	public void init(Renderable renderable) {
//		normalTexture = new Texture(Gdx.files.internal("data/waternormals.png"));
		normalTexture = new Texture(Gdx.files.internal("data/normal1.png"));
		normalTexture.setWrap(TextureWrap.Repeat, TextureWrap.Repeat);
		program = new ShaderProgram(
				Gdx.files.internal("shaders/water.vertex.glsl"),
				Gdx.files.internal("shaders/water.fragment.glsl"));
		if (!program.isCompiled())
			throw new GdxRuntimeException(program.getLog());

		super.init(program, renderable);
	}

	@Override
	public void begin(Camera camera, RenderContext context) {
		super.begin(camera, context);
		program.begin();
		
		if (currentTime < 1000000) {
			currentTime += Gdx.graphics.getDeltaTime();
		}else {
			currentTime = 0;
			currentTime += Gdx.graphics.getDeltaTime();
		}
		

		// set uniform
		set(u_projTrans, camera.combined);
		set(u_viewTrans, camera.view);
		set(refracColor, 1.0f, 1.0f, 1.0f, 1.0f);
		set(u_resolution,
				new Vector2(Gdx.graphics.getWidth(), Gdx.graphics.getHeight()));
		set(u_time, currentTime);
		set(u_normalTexture, normalTexture);

		context.setCullFace(GL20.GL_BACK);
		context.setDepthTest(GL20.GL_DEPTH_TEST);
		context.setBlending(true, GL20.GL_SRC_ALPHA,
				GL20.GL_ONE_MINUS_SRC_ALPHA);
		context.setDepthMask(true);

	}

	@Override
	public void render(Renderable renderable) {
		super.render(renderable);

		set(u_worldTrans, renderable.worldTransform);
	}

	@Override
	public int compareTo(Shader other) {
		return 0;
	}

	@Override
	public boolean canRender(Renderable instance) {
		return true;
	}

	@Override
	public void init() {

	}

}
