package com.kivvi.ios8;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Actor;

public class DistortBackground extends Actor {
	Texture bg;
	ShaderProgram shader;
	float time;
	Vector2 invSize = new Vector2();
	Vector2 magicSize = new Vector2();

	DistortBackground(Texture bg) {
		this.bg = bg;

		shader = createShader();
		time = 0;
		this.resize();
	}

	@Override
	public void draw(Batch batch, float parentAlpha) {
		batch.setShader(shader);

		time += Gdx.graphics.getDeltaTime();
		if (time > 2 * Math.PI) {
			time -= 2 * Math.PI;
		}
		if (false) {
			time = 0;
			magicSize.x = 10000;
			magicSize.y = 10000;
		}
		shader.setUniformf("uInvSize", invSize);
		shader.setUniformf("uTime", time);
		shader.setUniformf("u_magicSize", magicSize);

		batch.draw(bg, IOS8.acceler.getX(), IOS8.acceler.getY());
		batch.setShader(null);
	}

	public ShaderProgram createShader() {
		ShaderProgram shader = new ShaderProgram(
				Gdx.files.internal("data/distort.vs"),
				Gdx.files.internal("data/distort.fs"));
		if (shader.isCompiled() == false)
			throw new IllegalArgumentException("Error compiling shader: "
					+ shader.getLog());
		return shader;
	}

	public void resize() {
		float w = Gdx.graphics.getWidth();
		float h = Gdx.graphics.getHeight();
		invSize.x = 1.0f / w;
		invSize.y = 1.0f / h;
		magicSize.x = w / 16;
		magicSize.y = h / 16;
	}
}
