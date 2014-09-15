package com.cooee.wallpaper.garden;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.cooee.wallpaper.framework.Logger;
import com.threed.jpct.Camera;
import com.threed.jpct.FrameBuffer;
import com.threed.jpct.GLSLShader;
import com.threed.jpct.Loader;
import com.threed.jpct.Matrix;
import com.threed.jpct.Object3D;
import com.threed.jpct.SimpleVector;
import com.threed.jpct.Texture;
import com.threed.jpct.TextureInfo;
import com.threed.jpct.TextureManager;
import com.threed.jpct.World;

import android.content.Context;
import android.view.MotionEvent;

public class Garden implements IRenderer {
	private final static String TAG = "Garden";

	// master
	private static Garden master = null;

	// Context
	private Context context;

	// jpct
	private FrameBuffer fb = null;
	private World world = null;
	private World bgWorld = null;
	private GLSLShader shader = null;

	private Object3D big_pot_light;
	private Object3D medium_pot_light;
	private Object3D small_pot_light;
	private Object3D pot;
	private Object3D light;
	private Object3D lightAxis;
	private Object3D mushBig;
	private Object3D mushSmall;
	private ArrayList<Object3D> waterfalls = new ArrayList<Object3D>();
	private ArrayList<Object3D> waters = new ArrayList<Object3D>();
	private ArrayList<Object3D> planes = new ArrayList<Object3D>();

	// camera
	private SimpleVector camPosition = new SimpleVector();
	private SimpleVector camLookAt = new SimpleVector();

	// fps
	private boolean showFPS = false;
	private int fps_count;
	private float fps_dt;
	private float fps;

	Garden(Context context) {
		this.context = context;
	}

	float x = 0;
	float light_offset = 0;
	boolean light_direction = false;

	@Override
	public void onDrawFrame(GL10 gl) {
		fb.clear();

		world.renderScene(fb);
		world.draw(fb);

		bgWorld.renderScene(fb);
		bgWorld.draw(fb);

		fb.display();

		animate();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int w, int h) {
		Logger.log(TAG, "onSurfaceChanged: w = " + w + ", h = " + h);
		Logger.ps("onSurfaceChanged");
		if (fb != null) {
			if (fb.getWidth() != w || fb.getHeight() != h) {
				fb.dispose();
				fb = null;
			} else {
				fb.dispose();
				fb = null;
			}
		}

		if (fb == null) {
			if (WallpaperService.useGLES2) {
				Logger.ps("new FrameBuffer");
				fb = new FrameBuffer(w, h);
				Logger.pt("new FrameBuffer");
			} else {
				fb = new FrameBuffer(gl, w, h);
			}
		}

		resetCamera();

		Logger.pt("onSurfaceChanged");
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		if (master == null) {
			world = new World();
			world.setAmbientLight(210, 210, 210);

			bgWorld = new World();
			bgWorld.setAmbientLight(210, 210, 210);

			try {
				// wall
				loadobj("garden_wall.obj", R.drawable.garden_wall);

				// clover
				Object3D clover = loadModel("garden_clover.obj",
						R.drawable.garden_clover);
				clover.setTransparency(255);

				// floor
				load3ds("garden_floor.3DS", R.drawable.garden_floor);
				// fences
				Object3D fences = loadobj("garden_fences.obj",
						R.drawable.garden_fences);
				fences.setTransparency(255);
				// grass
				for (int i = 1; i <= 6; i++) {
					Object3D grass = load3ds("garden_grass_" + i + ".3DS",
							R.drawable.garden_grass);
					grass.setTransparency(255);
					grass.setCulling(false);

					planes.add(grass);
				}

				// mush
				Object3D mush = load3ds("garden_mush_big.3DS",
						R.drawable.garden_mush);
				mush.setTransparency(255);
				mush.setCulling(false);
				planes.add(mush);
				mushBig = mush;

				mush = loadModel("garden_mush_small.3DS",
						R.drawable.garden_mush);
				mush.setTransparency(255);
				mush.setCulling(false);
				planes.add(mush);
				mushSmall = mush;

				// pot
				// pot = load3ds("garden_pot.3DS", R.drawable.garden_pot);
				// load3ds("garden_bowl.3DS", R.drawable.garden_pot);
				// loadobj("garden_bowl.obj", "garden_bowl.mtl",
				// R.drawable.garden_pot);
				pot = loadModel("garden_pot.obj", R.drawable.garden_pot);

				// bowl
				{
					Object3D water = loadModel("garden_bowl_water.obj",
							R.drawable.garden_water);
					water.setTransparency(255);
					water.setTransparencyMode(1);
					waters.add(water);

					// waterfall
					for (int i = 1; i <= 5; i++) {
						Object3D waterfall = loadModel("garden_bowl_waterfall_"
								+ i + ".3DS", R.drawable.garden_waterfall);
						waterfall.setTransparency(255);
						waterfall.setTransparencyMode(1);
						waterfall.setCulling(false);
						waterfalls.add(waterfall);
					}
				}

				// big pot
				{
					Object3D water = loadModel("garden_big_pot_water.obj",
							R.drawable.garden_water);
					water.setTransparency(255);
					water.setTransparencyMode(1);
					waters.add(water);

					Object3D waterfall1 = loadModel(
							"garden_big_pot_waterfall_1.obj",
							R.drawable.garden_waterfall);
					waterfall1.setTransparency(255);
					waterfall1.setTransparencyMode(1);
					waterfalls.add(waterfall1);

					Object3D waterfall2 = loadModel(
							"garden_big_pot_waterfall_2.obj",
							R.drawable.garden_waterfall);
					waterfall2.setTransparency(255);
					waterfall2.setTransparencyMode(1);
					waterfalls.add(waterfall2);

					// pot light
					loadTexture(R.drawable.garden_pot_light);
					big_pot_light = loadModel("garden_big_pot_light.obj",
							R.drawable.garden_pot_light);
					big_pot_light.setTransparency(255);
					big_pot_light.setTransparencyMode(1);
					big_pot_light.setCulling(false);
				}

				// medium pot
				{
					Object3D water = loadModel("garden_medium_pot_water.obj",
							R.drawable.garden_water);
					water.setTransparency(255);
					water.setTransparencyMode(1);
					waters.add(water);

					Object3D waterfall = loadModel(
							"garden_medium_pot_waterfall.obj",
							R.drawable.garden_waterfall);
					waterfall.setTransparency(255);
					waterfall.setTransparencyMode(1);
					waterfalls.add(waterfall);

					// pot light
					medium_pot_light = loadModel("garden_medium_pot_light.obj",
							R.drawable.garden_pot_light);
					medium_pot_light.setTransparency(255);
					medium_pot_light.setTransparencyMode(1);
					medium_pot_light.setCulling(false);
				}

				// small pot
				{
					Object3D water = loadModel("garden_small_pot_water.obj",
							R.drawable.garden_water);
					water.setTransparency(255);
					water.setTransparencyMode(1);
					waters.add(water);

					Object3D waterfall = loadModel(
							"garden_small_pot_waterfall.obj",
							R.drawable.garden_waterfall);
					waterfall.setTransparency(255);
					waterfall.setTransparencyMode(1);
					waterfalls.add(waterfall);

					// pot light
					small_pot_light = loadModel("garden_small_pot_light.obj",
							R.drawable.garden_pot_light);
					small_pot_light.setTransparency(255);
					small_pot_light.setTransparencyMode(1);
					small_pot_light.setCulling(false);
				}

				// light
				light = loadModel("garden_light.obj", R.drawable.garden_light);
				light.setTransparency(255);
				light.setTransparencyMode(1);
				light.setCulling(false);

				lightAxis = loadModel("garden_light_axis.obj",
						R.drawable.garden_light);
				lightAxis.setVisibility(false);

				// cam
				Object3D cam = loadModel("garden_camera.3DS",
						R.drawable.garden_pot_light);
				camPosition.set(cam.getCenter());
				Object3D lookat = load3ds("garden_lookat.3DS",
						R.drawable.garden_pot_light);
				camLookAt.set(lookat.getCenter());
				cam.setVisibility(false);
				lookat.setVisibility(false);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void onTouchEvent(MotionEvent event) {
	}

	private Object3D loadmd2(String modelName, int textureId)
			throws IOException {
		loadTexture(textureId);

		Object3D obj = null;
		obj = Loader.loadMD2(
				context.getResources().getAssets().open(modelName), 1.0f);
		obj.setTexture(textureId + "");
		obj.build();
		world.addObject(obj);

		obj.setCulling(false);

		return obj;
	}

	private Object3D loadModel(String modelName, int textureId)
			throws IOException {
		if (modelName.toUpperCase().contains(".OBJ")) {
			return loadobj(modelName, textureId);
		} else if (modelName.toUpperCase().contains(".3DS")) {
			return load3ds(modelName, textureId);
		} else {
			throw new IOException("wrong model file.");
		}
	}

	private Object3D load3ds(String modelName, int textureId)
			throws IOException {
		loadTexture(textureId);

		Object3D obj = null;
		obj = load3dsModel(modelName, 1.0f);
		obj.setTexture(textureId + "");

		// if (textureId == R.drawable.lotus_light) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// } else if (textureId == R.drawable.leaf) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// } else if (textureId == R.drawable.lotus_water) {
		// obj.setTransparency(11);
		// } else if (textureId == R.drawable.drip) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// }
		obj.build();
		//
		if (textureId == R.drawable.garden_light) {
			bgWorld.addObject(obj);
		} else {
			world.addObject(obj);
		}

		return obj;
	}

	private Object3D loadobj(String modelName, int textureId)
			throws IOException {
		return loadobj(modelName, null, textureId);
	}

	private Object3D loadobj(String modelName, String mtlName, int textureId)
			throws IOException {
		loadTexture(textureId);

		Object3D obj = null;
		obj = loadObjModel(modelName, mtlName, 1.0f);
		obj.setTexture(textureId + "");

		// if (textureId == R.drawable.lotus_light) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// } else if (textureId == R.drawable.leaf) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// } else if (textureId == R.drawable.lotus_water) {
		// obj.setTransparency(11);
		// } else if (textureId == R.drawable.drip) {
		// obj.setTransparency(255);
		// obj.setCulling(false);
		// }
		obj.build();
		//
		if (textureId == R.drawable.garden_light) {
			bgWorld.addObject(obj);
		} else {
			world.addObject(obj);
		}

		return obj;
	}

	// 载入模型
	private Object3D loadObjModel(String filename, String mtlfilename,
			float scale) throws IOException {
		// 将载入的3ds文件保存到model数组中
		Object3D[] model = Loader.loadOBJ(context.getResources().getAssets()
				.open(filename), null, scale);
		// 取第一个3ds文件
		Object3D o3d = new Object3D(0);
		// 临时变量temp
		Object3D temp = null;
		// 遍历model数组
		for (int i = 0; i < model.length; i++) {
			// 给temp赋予model数组中的某一个
			temp = model[i];
			// 设置temp的中心为 origin (0,0,0)
			temp.setCenter(SimpleVector.ORIGIN);
			// 沿x轴旋转坐标系到正常的坐标系(jpct-ae的坐标中的y,z是反的)
			temp.rotateX((float) (-1.0f * Math.PI));
			// 使用旋转矩阵指定此对象旋转网格的原始数据
			temp.rotateMesh();
			// new 一个矩阵来作为旋转矩阵
			temp.setRotationMatrix(new Matrix());

			// 合并o3d与temp
			o3d = Object3D.mergeObjects(o3d, temp);
			// 主要是为了从桌面版JPCT到android版的移徝(桌面版此处为o3d.build())
			o3d.compile();
		}
		// 返回o3d对象
		return o3d;
	}

	// 载入模型
	private Object3D load3dsModel(String filename, float scale)
			throws IOException {
		// 将载入的3ds文件保存到model数组中
		Object3D[] model = Loader.load3DS(context.getResources().getAssets()
				.open(filename), scale);
		// 取第一个3ds文件
		Object3D o3d = new Object3D(0);
		// 临时变量temp
		Object3D temp = null;
		// 遍历model数组
		for (int i = 0; i < model.length; i++) {
			// 给temp赋予model数组中的某一个
			temp = model[i];
			// 设置temp的中心为 origin (0,0,0)
			temp.setCenter(SimpleVector.ORIGIN);
			// 沿x轴旋转坐标系到正常的坐标系(jpct-ae的坐标中的y,x是反的)
			temp.rotateX((float) (-.5 * Math.PI));
			// 使用旋转矩阵指定此对象旋转网格的原始数据
			temp.rotateMesh();
			// new 一个矩阵来作为旋转矩阵
			temp.setRotationMatrix(new Matrix());
			// 合并o3d与temp
			o3d = Object3D.mergeObjects(o3d, temp);
			// 主要是为了从桌面版JPCT到android版的移徝(桌面版此处为o3d.build())
			o3d.compile();
		}
		// 返回o3d对象
		return o3d;
	}

	private Texture loadTexture(int textureId) {
		Texture tex = null;
		if (!TextureManager.getInstance().containsTexture(textureId + "")) {
			tex = new Texture(context.getResources().getDrawable(textureId),
					true);
			// if (textureId == R.drawable.lotus_bg_d_0) {
			// tex.setFiltering(true);
			// tex.setMipmap(false);
			// }
			TextureManager.getInstance().addTexture(textureId + "", tex);
		}
		return tex;
	}

	private int getTextureId(int resId) {
		String texname = resId + "";
		TextureManager texMan = TextureManager.getInstance();
		int number = texMan.getTextureID(texname);
		return number;
	}

	/**
	 * Show fps on lefttop of screen.
	 * 
	 * @param dt
	 *            delta time with ms.
	 */
	private void drawFPS(long dt) {
		if (!showFPS)
			return;

		fps_count++;
		fps_dt += dt;

		final int count = 15;
		if (fps_count == count) {
			fps = count * 1000.0f / fps_dt;
			fps_count = 0;
			fps_dt = 0;
		}

		// draw fps
		String fpsString = String.format("%.0f", fps);
		int destX = 0;
		int num_width = 33;
		int destY = 50;
		final int num_array[] = { 3, 6, 8, 9, 0, 5, 2, 4, 7, 1 };
		for (int i = 0; i < fpsString.length(); i++) {
			int num = fpsString.charAt(i) - 48; // 字符转数字
			int index = 0;
			for (index = 0; index < num_array.length; index++) {
				if (num == num_array[index])
					break;
			}
			if (num >= 0 && num <= 9) {
				fb.blit(TextureManager.getInstance().getTexture(
						"" + R.drawable.number), // src
						index * num_width, 0, // srcX, srcY
						destX, destY, // destX,
										// destY
						num_width, 60, // sourceWidth, sourceHeight
						num_width, 60, // destWidth,
										// destHeight,
						10, // transValue
						true, // additive
						null // addColor
				);
			}
			destX += num_width;
		}
	}

	private void resetCamera() {
		Camera cam = world.getCamera();
		if (fb.getWidth() > fb.getHeight()) {
			cam.setFOV(1.2f);
		} else {
			cam.setFOV(0.8f);
		}
		cam.setPosition(camPosition);
		cam.lookAt(camLookAt);

		bgWorld.setCameraTo(cam);
	}

	private void animate() {
		x += 0.1f / 60.0f; // 每秒加0.1

		// pot light
		if (!light_direction) {
			light_offset += 0.1f / 60.0f;
			if (light_offset > 0.2f) {
				light_direction = true;
			}
		} else {
			light_offset -= 0.1f / 60.0f;
			if (light_offset < 0.1f / 60.f) {
				light_direction = false;
			}
		}

		Matrix mat = new Matrix();
		mat.translate(light_offset, light_offset, 0);
		big_pot_light.setTextureMatrix(mat);
		medium_pot_light.setTextureMatrix(mat);
		small_pot_light.setTextureMatrix(mat);

		// waterfall
		mat = new Matrix();
		mat.translate(-4 * x, -4 * x, 0);
		for (Object3D waterfall : waterfalls) {
			waterfall.setTextureMatrix(mat);
		}

		// water
		mat = new Matrix();
		mat.translate(-1 * x, -1 * x, 0);
		for (Object3D water : waters) {
			water.setTextureMatrix(mat);
		}

		// light
		if (light != null) {
			SimpleVector axis = lightAxis.getCenter();
			axis.sub(light.getCenter());
			light.rotateAxis(axis, (float) (0.1f / 60.f * Math.PI));
		}

		// cam rotate
		float max_angle = 17.0f;
		if (!rotation_direction) {
			dRotation = max_angle / 3 / 60.f;
		} else {
			dRotation = -max_angle / 3 / 60.f;
		}
		rotation += dRotation;
		if (rotation > max_angle) {
			rotation_direction = true;
		} else if (rotation < -max_angle) {
			rotation_direction = false;
		}
		rotate(dRotation);

		// planes
		for (Object3D plane : planes) {
			plane.clearRotation();

			SimpleVector now = world.getCamera().getPosition();
			now.y = plane.getCenter().y;
			now.sub(plane.getCenter());

			SimpleVector ori = camPosition;
			ori.y = plane.getCenter().y;
			ori.sub(plane.getCenter());

			float angle = ori.calcAngle(now);
			if (plane == mushBig) {
				// Logger.log("mushBig angle = " + angle);
			}
			if (plane == mushSmall) {
				Logger.log("mushSmall angle = " + Math.toDegrees(angle));
			}
			if (now.x < 0) {
				plane.rotateY((float) (Math.PI - angle));
			} else {
				plane.rotateY(-(float) (Math.PI - angle));
			}
		}
	}

	float rotation = 0.0f;
	float dRotation = 0.0f;
	boolean rotation_direction = false;

	private void rotate(float degrees) {
		// rotate y around look at point
		Camera cam = world.getCamera();
		float angle = (float) Math.toRadians(degrees);
		Matrix m = new Matrix();
		m.rotateY(angle);
		SimpleVector v3 = cam.getPosition();
		v3.matMul(m);
		cam.setPosition(v3);
		cam.lookAt(camLookAt);

		bgWorld.setCameraTo(cam);
	}
}
