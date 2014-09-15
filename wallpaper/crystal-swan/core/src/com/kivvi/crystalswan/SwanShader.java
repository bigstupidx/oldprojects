package com.kivvi.crystalswan;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Cubemap;
import com.badlogic.gdx.graphics.g3d.Renderable;
import com.badlogic.gdx.graphics.g3d.Shader;
import com.badlogic.gdx.graphics.g3d.shaders.BaseShader;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.badlogic.gdx.math.Matrix4;

public class SwanShader extends BaseShader {
	private ShaderProgram program;
	private Camera cam;
	private Cubemap reflect;
	private Cubemap refract;
	private int renderFace = 0;
	private Color color = new Color();
	@Override
	public void init() {
		program = createDefaultShader();
		reflect = new Cubemap(
				Gdx.files.internal("data/cubemapreflect/posx.png"),
				Gdx.files.internal("data/cubemapreflect/negx.png"),
				Gdx.files.internal("data/cubemapreflect/posy.png"),
				Gdx.files.internal("data/cubemapreflect/negy.png"),
				Gdx.files.internal("data/cubemapreflect/posz.png"),
				Gdx.files.internal("data/cubemapreflect/negz.png"), true);
		// reflect.setFilter(TextureFilter.Linear, TextureFilter.Linear);

		refract = new Cubemap(
				Gdx.files.internal("data/cubemaprefract/posx.png"),
				Gdx.files.internal("data/cubemaprefract/negx.png"),
				Gdx.files.internal("data/cubemaprefract/negy.png"),
				Gdx.files.internal("data/cubemaprefract/posy.png"),
				Gdx.files.internal("data/cubemaprefract/posz.png"),
				Gdx.files.internal("data/cubemaprefract/negz.png"), true);
		// refract.setFilter(TextureFilter.Linear, TextureFilter.Linear);
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

	public void setColor(float r, float g, float b, float a) {
		this.color.set(r, g, b, a);
	}
	
	@Override
	public void render(Renderable renderable) {
		program.setUniformMatrix("uProjTrans", cam.combined);
		program.setUniformMatrix("uWorldmatrix", renderable.worldTransform);
		Matrix4 m = new Matrix4(renderable.worldTransform);
		m.toNormalMatrix();
		program.setUniformMatrix("uNormalmatrix", m);
		program.setUniformf("uEye", cam.position);
		program.setUniformf("uColor", color);
		program.setUniformi("uBack", renderFace);
	
		reflect.bind();
		refract.bind(1);
		program.setUniformi("uCubemapReflect", 0);
		program.setUniformi("uCubemapRefract", 1);
		renderable.mesh.render(program, renderable.primitiveType,
				renderable.meshPartOffset, renderable.meshPartSize, true);
	}

	public void setRenderFace(int face) {
		renderFace = face;
	}

	static public ShaderProgram createDefaultShader() {
		String vertexShader = "attribute vec4 "
				+ ShaderProgram.POSITION_ATTRIBUTE
				+ ";\n" //
				+ "attribute vec4 "
				+ ShaderProgram.NORMAL_ATTRIBUTE
				+ ";\n" //
				+ "uniform mat4 uWorldmatrix;\n"
				+ "uniform mat4 uNormalmatrix;\n"
				+ "uniform mat4 uProjTrans;\n" //
				+ "\n" //
				+ "varying vec4 vNormal;\n"
				+ "varying vec4 vPosition;\n"
				+ "void main()\n" //
				+ "{\n" //
				+ "   gl_Position =  uProjTrans * uWorldmatrix *"
				+ ShaderProgram.POSITION_ATTRIBUTE
				+ ";\n" //
				+ "	  vNormal = uNormalmatrix * a_normal;\n"
				+ "   vPosition = uWorldmatrix * a_position;\n"
				+ "}\n";

		String fragmentShader = "\n" //
				+ "#ifdef GL_ES\n" //
				+ "precision mediump float;\n" //
				+ "#endif\n" //
				+ "uniform int uBack;\n"
				+ "uniform samplerCube uCubemapReflect;\n"
				+ "uniform samplerCube uCubemapRefract;\n"
				+ "uniform vec4 uColor;\n"
				+ "uniform vec3 uEye;\n" //
				+ "varying vec4 vNormal;\n"
				+ "varying vec4 vPosition;\n"
				+ "void main()\n"//
				+ "{\n" //
				+ "    vec3 ray = vPosition.xyz - uEye;\n"
				+ "    vec3 eyeRay = normalize(ray);\n"
				+ "    vec3 refl = reflect(eyeRay, normalize(vNormal.xyz));\n"
				+ "    vec4 reflColor = textureCube(uCubemapReflect, refl);\n"
				+ "    vec3 refr = reflect(eyeRay, normalize(vNormal.xyz));\n"
				+ "    vec4 refrColor = textureCube(uCubemapRefract, refr);\n"
				+ "    vec4 finalColor;\n"
				+ "    if (uBack == 1)\n"
				+ "    {\n"
				+ "        finalColor = refrColor * uColor;\n"
				+ "        finalColor.a = 1.0;\n"
				+ "        finalColor.a = (finalColor.a + reflColor.a) - 0.5;\n"
				+ "    }\n"
				+ "    else\n"
				+ "    {\n"
				+ "        finalColor = refrColor * uColor;\n"
				+ "        finalColor.rgb = (finalColor.rgb + reflColor.rgb);\n"
				+ "        finalColor.a = (finalColor.a + reflColor.a) - 0.5;\n"
				+ "    }\n" + "    gl_FragColor = finalColor;\n" + "}";

		ShaderProgram shader = new ShaderProgram(vertexShader, fragmentShader);
		if (shader.isCompiled() == false)
			throw new IllegalArgumentException("couldn't compile shader: "
					+ shader.getLog());
		return shader;
	}

	@Override
	public void dispose() {
		reflect.dispose();
		refract.dispose();
		program.dispose();
		super.dispose();
	}

}
