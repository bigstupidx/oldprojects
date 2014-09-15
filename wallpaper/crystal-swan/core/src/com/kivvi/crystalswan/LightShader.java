package com.kivvi.crystalswan;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Pixmap.Format;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.g3d.Renderable;
import com.badlogic.gdx.graphics.g3d.Shader;
import com.badlogic.gdx.graphics.g3d.shaders.BaseShader;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;

public class LightShader extends BaseShader {
	private ShaderProgram program;
	private Camera cam;
	private Texture texture;

	@Override
	public void init() {
		program = createDefaultShader();
		texture = new Texture(Gdx.files.internal("data/lights.png"),
				Format.RGBA8888, true);
		texture.setFilter(TextureFilter.MipMapLinearLinear,
				TextureFilter.Linear);
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
	public void begin(Camera camera, RenderContext context) {
		cam = camera;
		program.begin();
	}

	@Override
	public void end() {
		program.end();
	}

	@Override
	public void render(Renderable renderable) {
		program.setUniformMatrix("uProjTrans", cam.combined);
		program.setUniformMatrix("uWorldmatrix", renderable.worldTransform);
		program.setUniformi("texture", 0);
		program.setUniformf("uColor", new Color(1.0f, 0.94f, 0.86f,
				1.0f));

		texture.bind();
		renderable.mesh.render(program, renderable.primitiveType,
				renderable.meshPartOffset, renderable.meshPartSize, true);
	}

	static public ShaderProgram createDefaultShader() {
		String vertexShader = "attribute vec4 "
				+ ShaderProgram.POSITION_ATTRIBUTE
				+ ";\n" //
				+ "attribute vec2 " + ShaderProgram.TEXCOORD_ATTRIBUTE
				+ "0"
				+ ";\n" //
				+ "\n" //
				+ "uniform mat4 uWorldmatrix;\n"
				+ "uniform mat4 uProjTrans;\n" //
				+ "varying vec2 vTextureCoords;\n"
				+ "void main()\n" //
				+ "{\n" //
				+ "   gl_Position =  uProjTrans * uWorldmatrix *"
				+ ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
				+ "   vTextureCoords = a_texCoord0;\n" + "}\n";

		String fragmentShader = "\n" //
				+ "#ifdef GL_ES\n" //
				+ "precision mediump float;\n" //
				+ "#endif\n" //
				+ "uniform sampler2D texture;\n"
				+ "uniform vec4 uColor;\n"
				+ "varying vec2 vTextureCoords;\n"
				+ "void main()\n"//
				+ "{\n" //
				+ "    gl_FragColor = texture2D(texture, vTextureCoords) * uColor;\n"
				+ "}";

		ShaderProgram shader = new ShaderProgram(vertexShader, fragmentShader);
		if (shader.isCompiled() == false)
			throw new IllegalArgumentException("couldn't compile shader: "
					+ shader.getLog());
		return shader;
	}

	@Override
	public void dispose() {
		texture.dispose();
		program.dispose();
		super.dispose();
	}

}
