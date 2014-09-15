package com.kivvi.ripples;

import java.io.File;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.util.Log;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Mesh;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.VertexAttribute;
import com.badlogic.gdx.graphics.VertexAttributes;
import com.badlogic.gdx.math.Intersector;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.math.collision.Ray;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.utils.Drawable;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.Texture.TextureFilter;
import com.badlogic.gdx.graphics.VertexAttributes.Usage;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.kivvi.ripples.util.BitmapTexture;

public class Ripples extends Stage {
	Camera cam;
	PerspectiveCamera perspectiveCamera;

	private Mesh mesh;
	private VertexAttribute aa = null;
	private VertexAttribute bb = null;
	private VertexAttribute cc = null;
	private float[] vertices;

	private short WIDTH = 0;
	private short HEIGHT = 0;
	private float INV_WIDTH = 0;
	private float INV_HEIGHT = 0;
	private float DAMPING = 0.985f;
	private float DISPLACEMENT = -5;
	private int RADIUS = 3;
	private float bX = 0, bY = 0;

	private float[][] last = null;
	private float[][] curr = null;
	private float[][] intp = null;

	private Texture texture = null;

	private boolean begin = true;
	public boolean isOut = false;
	private boolean passBoolean = false;
	private boolean isOutBoolean = false;
	private boolean beginBoolean = false;
	private boolean beginBoolean1 = false;
	private boolean beginBoolean2 = false;

	protected ShaderProgram shader = null;

	private Plane plane = new Plane(new Vector3(), new Vector3(1, 0, 0),
			new Vector3(0, 1, 0));
	private Vector3 point = new Vector3(-1, -1, -1);

	int verticesNum = -1;
	private float passX = 0;
	private float passY = 0;
	private int touchX = 0;
	private int passXcont = 0;
	private int passYcont = 0;
	private float Bx = 0f;
	private float By = 0f;

	private int limitRipplesSpeed = 0;
	private float sTime = 0;
	private float frequency = 2.5f;
	private int range = 20;

	private float mXOffset;

	private IServer mIServer;

	private static boolean mFirst = true;
	private float screenWidthInCamera;

	public Ripples() {
		Gdx.app.log("diaosixu", " ripples create");
		this.getViewport().update(Gdx.graphics.getWidth(),
				Gdx.graphics.getHeight(), true);
		setTexture();
		setRangeAndFrequency();

		Gdx.input.setInputProcessor(this);
		addListener(new InputListener() {

			@Override
			public boolean touchDown(InputEvent event, float x, float y,
					int pointer, int button) {
				// TODO Auto-generated method stub
				// Gdx.app.log("diaosixu", "touch down x = " + x + " y = " + y);

				if (pointer > 0) {
					return true;
				}

				isOutBoolean = false;
				begin = true;

				passXcont = (int) x;
				passYcont = (int) y;

				point.x = (x / Gdx.graphics.getWidth()) * screenWidthInCamera;
				if (LibgdxLiveWallpaperAndroidService.ripplesSettings.scrollbackground) {
					point.x += cam.position.x - screenWidthInCamera / 2.0f;
				}
				point.y = y * HEIGHT / Gdx.graphics.getHeight();
				// Ray ray = Ripples.this.camera.getPickRay(x, y);
				// Intersector.intersectRayPlane(ray, plane, point);

				touchWater(point);
				passBoolean = true;

				return true;
			}

			@Override
			public void touchUp(InputEvent event, float x, float y,
					int pointer, int button) {
				// TODO Auto-generated method stub
				if (pointer > 0)
					return;
				if (isOut)
					return;
				/*
				 * if (inwddx || inwjdh) { mHandlerMain.postDelayed(mRunFlush,
				 * 700); } else
				 */if (Math.abs(x - passXcont) > 130 * Bx
						|| Math.abs(y - passYcont) > 130 * By) {
					return;
				}
				if (beginBoolean) {
					verticesNum = 25;
				}
				passBoolean = false;
				beginBoolean = false;
				beginBoolean1 = false;
				beginBoolean2 = false;
				return;
			}

			@Override
			public void touchDragged(InputEvent event, float x, float y,
					int pointer) {
				// TODO Auto-generated method stub
				if (pointer > 0)
					return;
				if (isOut)
					return;

				if (passX == x && passY == y) {
					return;
				}

				passX = x;
				passY = y;

				if ((Math.abs(x - passXcont) > 50 * Bx || Math.abs(y
						- passYcont) > 50 * By)
						&& !beginBoolean1) {
					verticesNum = 25;
					beginBoolean1 = true;
					passBoolean = false;

				}
				if ((Math.abs(x - passXcont) > 130 * Bx || Math.abs(y
						- passYcont) > 130 * By)
						&& !beginBoolean2) {
					verticesNum = 15;

					beginBoolean2 = true;
					passBoolean = false;
				}
				if (Math.abs(x - passXcont) > 150 * Bx
						|| Math.abs(y - passYcont) > 150 * By) {
					if (isOutBoolean)
						return;
					isOutBoolean = true;
				}

				touchX = (int) x;
				isOutBoolean = false;
				begin = true;

				passXcont = (int) x;
				passYcont = (int) y;

				point.x = (x / Gdx.graphics.getWidth()) * screenWidthInCamera;
				if (LibgdxLiveWallpaperAndroidService.ripplesSettings.scrollbackground) {
					point.x += cam.position.x - screenWidthInCamera / 2.0f;
				}
				point.y = y * HEIGHT / Gdx.graphics.getHeight();
				// Ray ray = Ripples.this.camera.getPickRay(x, y);
				// Intersector.intersectRayPlane(ray, plane, point);
				touchWater(point);

				passBoolean = true;

				return;
			}
		});

	}

	private void getTexturePosition() {
		String strFile = LibgdxLiveWallpaperAndroidService.ripplesSettings.custombackgroundpath;
		File file = new File(strFile);
		if (!file.exists()) {
			texture = new Texture(Gdx.files.internal("data/bg.png"));
		} else {
			try {
				Bitmap bitmap = BitmapFactory.decodeFile(LibgdxLiveWallpaperAndroidService.ripplesSettings.customPath);
				Bitmap finalBitmap;
				float scale = 1.0f;
				while (bitmap.getWidth() * scale > 2048
						|| bitmap.getHeight() * scale > 2048) {
					scale *= 0.5f;
				}
//				Log.v("diaosixu", "scale = " + scale);
//				Log.v("diaosixu", "width = " + bitmap.getWidth() + " height = " + bitmap.getHeight());
				if (scale == 1.0f) {
					finalBitmap = bitmap;
				} else {
					Matrix matrix = new Matrix();
					matrix.postScale(scale, scale);
					finalBitmap = Bitmap.createBitmap(bitmap, 0, 0,
							(int) bitmap.getWidth(),
							(int) bitmap.getHeight(), matrix, true);
//					Log.v("diaosixu", "final width = " + finalBitmap.getWidth() + " height = " + finalBitmap.getHeight());
					bitmap.recycle();
				}
				texture = new BitmapTexture(finalBitmap);
			} catch (Exception e) {
				texture = new Texture(Gdx.files.internal("data/bg.png"));
			}
		}
	}

	public void setTexture() {
		if (texture != null) {
			texture.dispose();
		}
//		Log.v("diaosixu", "setTexture = " + LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper);
		
		switch (LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper) {
		case 0:
			getTexturePosition();
			break;
		case 1:
			if (LibgdxLiveWallpaperAndroidService.ripplesSettings.bitmap != null) {
				texture = new BitmapTexture(
						LibgdxLiveWallpaperAndroidService.ripplesSettings.bitmap);
			} else {
				getTexturePosition();
			}
			break;
		case 2:
			File file = new File(
					LibgdxLiveWallpaperAndroidService.ripplesSettings.customPath);
			if (!file.exists()) {
				texture = new Texture(Gdx.files.internal("data/bg.jpg"));
			} else {
				
				try {
					Bitmap bitmap = BitmapFactory.decodeFile(LibgdxLiveWallpaperAndroidService.ripplesSettings.customPath);
					Bitmap finalBitmap;
					float scale = 1.0f;
					while (bitmap.getWidth() * scale > 2048
							|| bitmap.getHeight() * scale > 2048) {
						scale *= 0.5f;
					}
//					Log.v("diaosixu", "scale = " + scale);
//					Log.v("diaosixu", "width = " + bitmap.getWidth() + " height = " + bitmap.getHeight());
					if (scale == 1.0f) {
						finalBitmap = bitmap;
					} else {
						Matrix matrix = new Matrix();
						matrix.postScale(scale, scale);
						finalBitmap = Bitmap.createBitmap(bitmap, 0, 0,
								(int) bitmap.getWidth(),
								(int) bitmap.getHeight(), matrix, true);
//						Log.v("diaosixu", "final width = " + finalBitmap.getWidth() + " height = " + finalBitmap.getHeight());
						bitmap.recycle();
					}
					texture = new BitmapTexture(finalBitmap);

//					Log.v("diaosixu", "getTexturePosition");
				} catch (Exception e) {
//					Log.v("diaosixu", "exception");
					getTexturePosition();
				}
			}
			break;
		default:
			getTexturePosition();
		}
		texture.setFilter(TextureFilter.Linear, TextureFilter.Linear);
	}

	public void setRangeAndFrequency() {
		switch (Integer
				.parseInt(LibgdxLiveWallpaperAndroidService.ripplesSettings.range)) {
		case 1:
			range = 25;
			break;
		case 2:
			range = 17;
			break;
		case 3:
			range = 10;
			break;
		default:
			range = 17;
		}

		float rangeScale = 1f;

		if (LibgdxLiveWallpaperAndroidService.ripplesSettings.currentWallpaper == 2) {
			if (texture.getWidth() > texture.getHeight()) {
				rangeScale = (float) texture.getHeight()
						/ Wallpaper.mScreenHeight;
			} else {
				rangeScale = (float) texture.getWidth()
						/ Wallpaper.mScreenWidth;
			}
		}

		WIDTH = (short) (texture.getWidth() / (rangeScale * range));
		HEIGHT = (short) (texture.getHeight() / (rangeScale * range));

		float aspect = (float) Gdx.graphics.getWidth()
				/ (float) Gdx.graphics.getHeight();
		screenWidthInCamera = HEIGHT * aspect;

		last = new float[WIDTH + 1][HEIGHT + 1];
		curr = new float[WIDTH + 1][HEIGHT + 1];
		intp = new float[WIDTH + 1][HEIGHT + 1];

		vertices = new float[(WIDTH + 1) * (HEIGHT + 1) * 6];
		aa = VertexAttribute.Position();
		bb = VertexAttribute.TexCoords(0);
		cc = new VertexAttribute(100, 1, "a_energe");
		if (mesh != null) {
			mesh.dispose();
		}
		mesh = new Mesh(false, (WIDTH + 1) * (HEIGHT + 1), WIDTH * HEIGHT * 7,
				aa, bb, cc);

		INV_WIDTH = 1.0f / WIDTH;
		INV_HEIGHT = 1.0f / HEIGHT;

		createIndices();
		updateVertices(curr);

		if (perspectiveCamera == null) {
			perspectiveCamera = new PerspectiveCamera(90,
					Wallpaper.mScreenWidth, Wallpaper.mScreenHeight);
		}

		if (Wallpaper.mIsPreview) {
			if (Wallpaper.mScreenHeight < Wallpaper.mScreenWidth) {
				perspectiveCamera.fieldOfView = 90 * (Wallpaper.mScreenHeight / Wallpaper.mScreenWidth);
			} else {
				perspectiveCamera.fieldOfView = 90;
			}
		} else {
			perspectiveCamera.fieldOfView = 90;
		}

		cam = perspectiveCamera;

		setCameraPosition();
	}

	private void setCameraPosition() {
		cam.viewportWidth = Wallpaper.mScreenWidth;
		cam.viewportHeight = Wallpaper.mScreenHeight;
		cam.position.set(screenWidthInCamera / 2.0f, (HEIGHT) / 2.0f,
				HEIGHT / 2.0f);
		cam.lookAt(screenWidthInCamera / 2.0f, HEIGHT / 2.0f, 0);
		cam.near = 0.1f;
		cam.far = 1000;
		cam.update();

		Gdx.app.log("diaosi", "setCameraPosition " + cam.position.x);
	}

	private void createIndices() {
		short[] indices = new short[WIDTH * HEIGHT * 6];
		int idx = 0;
		short vidx = 0;
		for (int y = 0; y < HEIGHT; y++) {
			vidx = (short) (y * (WIDTH + 1));

			for (int x = 0; x < WIDTH; x++) {
				indices[idx++] = vidx;
				indices[idx++] = (short) (vidx + 1);
				indices[idx++] = (short) (vidx + WIDTH + 1);

				indices[idx++] = (short) (vidx + 1);
				indices[idx++] = (short) (vidx + WIDTH + 2);
				indices[idx++] = (short) (vidx + WIDTH + 1);
				vidx++;
			}
		}
		mesh.setIndices(indices);
		indices = null;
		System.gc();
	}

	private void updateVertices(float[][] curr) {//

		boolean isZero = true;
		if (vertices == null)
			return;

		int idx = 0;
		float minXOff = 1f * WIDTH / texture.getWidth();
		float minYOff = 1f * HEIGHT / texture.getHeight();

		for (int y = 0; y <= HEIGHT; y++) {
			for (int x = 0; x <= WIDTH; x++) {
				float xOffset = 0;
				float yOffset = 0;

				if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT) {
					xOffset = (curr[x - 1][y] - curr[x + 1][y]);
					yOffset = (curr[x][y - 1] - curr[x][y + 1]);
				}

				if (begin
						&& isZero
						&& (xOffset <= -minXOff || xOffset >= minXOff
								|| yOffset <= -minYOff || yOffset >= minYOff)) {
					isZero = false;
				}

				vertices[idx++] = x;
				vertices[idx++] = y;
				// vertices[idx++] = (xOffset+yOffset)/2f;
				vertices[idx++] = 0;
				// vertices[idx++] =curr[x][y]/15
				vertices[idx++] = (x + xOffset) * INV_WIDTH;
				vertices[idx++] = 1 - (y + yOffset) * INV_HEIGHT;
				vertices[idx++] = curr[x][y];
				/*
				 * if(vertices[idx-1] < 0){ vertices[idx-1] = 0; }else
				 * if(vertices[idx-1] > 0.99f){ vertices[idx-1] = 0.99f; }
				 */

				// vertices[idx++] = Color.toFloatBits(255, 255, 255, 255);
				// Gdx.app.debug("xxx", "z = ");
			}
		}
		mesh.setVertices(vertices);
		// if (begin)
		// Gdx.graphics.requestRendering();

		if (begin) {
			if (isZero) {
				idx = 0;
				for (int y = 0; y <= HEIGHT; y++) {
					for (int x = 0; x <= WIDTH; x++) {
						idx += 3;
						vertices[idx++] = x / (float) WIDTH;
						vertices[idx++] = y / (float) HEIGHT;
						// vertices[idx++] = Color.toFloatBits(255, 255, 255,
						// 255);
					}
				}
				begin = false;
			} else {
				Gdx.graphics.requestRendering();
			}
		}
	}

	private void updateWater() {
		if (isOut)
			return;

		for (int y = 0; y < HEIGHT + 1; y++) {
			for (int x = 0; x < WIDTH + 1; x++) {
				if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT) {
					curr[x][y] = (last[x - 1][y] + last[x + 1][y]
							+ last[x][y + 1] + last[x][y - 1])
							/ 2 - curr[x][y];
				}
				curr[x][y] *= DAMPING;//

				curr[x][y] *= DAMPING;//
				if (curr[x][y] < DISPLACEMENT)
					curr[x][y] = DISPLACEMENT;
				else if (curr[x][y] > -DISPLACEMENT)
					curr[x][y] = -DISPLACEMENT;

			}
		}
	}

	private void interpolateWater(float alpha) {

		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				intp[x][y] = (alpha * last[x][y] + (1 - alpha) * curr[x][y]);
			}
		}
	}

	private void touchWater(Vector3 point) {

		for (int y = Math.max(0, (int) point.y - RADIUS); y < Math.min(HEIGHT,
				(int) point.y + RADIUS); y++) {
			for (int x = Math.max(0, (int) point.x - RADIUS); x < Math.min(
					WIDTH, (int) point.x + RADIUS); x++) {
				float val = curr[x][y]
						+ DISPLACEMENT//
						* Math.max(
								0f,
								(float) Math.cos(((float) Math.PI) / 2
										* Math.sqrt(point.dst2(x, y, 0))
										/ RADIUS));
				if (val < DISPLACEMENT)
					val = DISPLACEMENT;
				else if (val > -DISPLACEMENT)
					val = -DISPLACEMENT;
				curr[x][y] = val;
			}
		}
	}

	public void render() {
		// Gdx.app.log("diaosixu", "camera.x is " + cam.position.x);
		cam.position.x = mXOffset * (WIDTH - screenWidthInCamera)
				+ screenWidthInCamera / 2.0f;
		cam.update();
		if (isOut)
			return;

		if (shader == null) {
			shader = createDefaultShader();
		}
		shader.begin();
		shader.setUniformMatrix("u_projTrans", cam.combined);
		shader.setUniformi("u_texture", 0);
		Color cur_color = new Color(1, 1, 1, 1);
		shader.setUniformf("u_color", cur_color);
		// Gdx.gl20.glEnable(GL10.GL_TEXTURE_2D);
		Gdx.gl.glEnable(GL20.GL_BLEND);
		Gdx.gl.glBlendFunc(770, 771);
		texture.bind();
		sTime += Gdx.graphics.getDeltaTime();

		switch (Integer
				.parseInt(LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency)) {
		case 1:
			frequency = 1f;
			break;
		case 2:
			frequency = 2.5f;
			break;
		case 3:
			frequency = 4f;
			break;
		default:
			frequency = 2.5f;
		}
		if (sTime > frequency) {
			sTime = 0;
			point.x = (float) Math.random() * WIDTH;
			point.y = (float) Math.random() * HEIGHT;
			if (!LibgdxLiveWallpaperAndroidService.ripplesSettings.frequency
					.equals("0")) {
				touchWater(point);
			}
		}
		updateWater();

		float[][] tmp = curr;
		curr = last;
		last = tmp;
		// if (verticesNum >= 0 && verticesNum % 5 == 0 && !passBoolean) {
		// point.x = (passX + 1f) / 2 * WIDTH;
		// point.y = (passY + 1f) / 2 * HEIGHT;
		// Ray ray = cam.getPickRay(passX, passY);
		// Intersector.intersectRayPlane(ray, plane, point);
		// touchWater(point);
		// }
		if (!passBoolean) {
			verticesNum--;
			if (verticesNum < -1)
				verticesNum = -1;
		}
		float alpha = 0.9f;
		interpolateWater(alpha);
		updateVertices(intp);

		// facePosX.render(shader, GL10.GL_TRIANGLES);
		mesh.render(shader, GL20.GL_TRIANGLES);
		shader.end();
	}

	// public void render()
	// {
	// GL10 gl = Gdx.graphics.getGL10();
	// gl.glViewport(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
	// gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
	// camera.update();
	// gl.glMatrixMode(GL10.GL_PROJECTION);
	// gl.glLoadMatrixf(camera.combined.val, 0);
	// gl.glMatrixMode(GL10.GL_MODELVIEW);
	//
	// gl.glLoadIdentity();
	// // updateWater();
	// // float[][] tmp = curr;//
	// // curr = last;
	// // last = tmp;
	// // if (verticesNum >= 0 && verticesNum % 5 == 0 && !passBoolean) {
	// // Ray ray = camera.getPickRay(passX, passY);
	// // Intersector.intersectRayPlane(ray, plane, point);
	// // touchWater(point);
	// // }
	// // if (!passBoolean) {
	// // verticesNum--;
	// // if (verticesNum < -1)
	// // verticesNum = -1;
	// // }
	// // float alpha = 0.9f;
	// // interpolateWater(alpha);
	// // updateVertices(intp);
	// gl.glEnable(GL10.GL_TEXTURE_2D);
	// texture.bind();
	// mesh.render(GL10.GL_TRIANGLES);
	// }

	static public ShaderProgram createDefaultShader() {
		String vertexShader = "";
		if (LibgdxLiveWallpaperAndroidService.ripplesSettings.reflectlight) {
			vertexShader = "attribute vec4 "
					+ ShaderProgram.POSITION_ATTRIBUTE
					+ ";\n" //
					+ "attribute vec4 "
					+ ShaderProgram.COLOR_ATTRIBUTE
					+ ";\n" //
					+ "attribute vec2 "
					+ ShaderProgram.TEXCOORD_ATTRIBUTE
					+ "0;\n" //
					+ "attribute float a_energe;\n"
					+ "uniform mat4 u_projTrans;\n" //
					+ "uniform vec4 u_color;\n" //
					+ "varying vec4 v_color;\n" //
					+ "varying vec2 v_texCoords;\n" //
					+ "varying float v_additionColor;\n" //
					+ "\n" //
					+ "void main()\n" //
					+ "{\n" //
					+ "   v_color = u_color"
					+ ";\n" //
					+ "   v_additionColor = abs(a_energe)"
					+ ";\n" //
					+ "   v_texCoords = "
					+ ShaderProgram.TEXCOORD_ATTRIBUTE
					+ "0;\n" //
					+ "   gl_Position =  u_projTrans * "
					+ ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
					+ "}\n";
		} else {
			vertexShader = "attribute vec4 "
					+ ShaderProgram.POSITION_ATTRIBUTE
					+ ";\n" //
					+ "attribute vec4 "
					+ ShaderProgram.COLOR_ATTRIBUTE
					+ ";\n" //
					+ "attribute vec2 "
					+ ShaderProgram.TEXCOORD_ATTRIBUTE
					+ "0;\n" //
					+ "uniform mat4 u_projTrans;\n" //
					+ "uniform vec4 u_color;\n" //
					+ "varying vec4 v_color;\n" //
					+ "varying vec2 v_texCoords;\n" //
					+ "varying float v_additionColor;\n" //
					+ "\n" //
					+ "void main()\n" //
					+ "{\n" //
					+ "   v_color = u_color"
					+ ";\n" //
					+ "   v_additionColor = abs(a_position.z)"
					+ ";\n" //
					+ "   v_texCoords = "
					+ ShaderProgram.TEXCOORD_ATTRIBUTE
					+ "0;\n" //
					+ "   gl_Position =  u_projTrans * "
					+ ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
					+ "}\n";
		}
		String fragmentShader = "#ifdef GL_ES\n" //
				+ "#define LOWP lowp\n" //
				+ "precision mediump float;\n" //
				+ "#else\n" //
				+ "#define LOWP \n" //
				+ "#endif\n" //
				+ "varying LOWP vec4 v_color;\n" //
				+ "varying vec2 v_texCoords;\n" //
				+ "varying float v_additionColor;\n" //
				+ "uniform sampler2D u_texture;\n" //
				+ "vec4 white = vec4(0.05, 0.05, 0.05, 1.0);\n"
				+ "void main()\n"//
				+ "{\n" //
				+ "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords) + white * v_additionColor;\n" //
				+ "}";

		ShaderProgram shader = new ShaderProgram(vertexShader, fragmentShader);
		if (shader.isCompiled() == false)
			throw new IllegalArgumentException("couldn't compile shader: "
					+ shader.getLog());
		return shader;
	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub
		super.dispose();
		texture.dispose();
	}

	public void onOffsetsChanged(float xOffset, float yOffset,
			float xOffsetStep, float yOffsetStep, int xPixelOffset,
			int yPixelOffset) {
		// TODO Auto-generated method stub
		// Gdx.app.log("diaosixu", "xOffset is " + xOffset);
		mXOffset = xOffset;

	}

	public void setIServer(IServer iserver) {
		mIServer = iserver;
	}

}
