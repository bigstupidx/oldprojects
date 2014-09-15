package com.cooee.wallpaper.mushroom;

import java.io.IOException;
import java.lang.reflect.Field;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.view.MotionEvent;

import com.cooee.wallpaper.common.IRenderer;
import com.cooee.wallpaper.common.ResourceManager;
import com.cooee.wallpaper.framework.ConfigMode;
import com.cooee.wallpaper.framework.Logger;
import com.threed.jpct.Camera;
import com.threed.jpct.FrameBuffer;
import com.threed.jpct.GLSLShader;
import com.threed.jpct.Interact2D;
import com.threed.jpct.Loader;
import com.threed.jpct.Matrix;
import com.threed.jpct.Object3D;
import com.threed.jpct.SimpleVector;
import com.threed.jpct.Texture;
import com.threed.jpct.TextureManager;
import com.threed.jpct.World;

public class MushRoom implements IRenderer {
	private final static String TAG = "MushRoom";

	// master
	private static MushRoom master = null;
	private static MushRoom gInstance = null;

	// Context
	private Context context;

	// jpct
	private FrameBuffer fb = null;
	private World world = null;
	private World bgWorld = null;
	private GLSLShader shader = null;

	// resource manager
	private ResourceManager rm = null;
	
	// 3ds
	private Object3D water = null;
	private Object3D light = null;
	private Object3D[] lens = new Object3D[6];

	// md2
	private Animation animations[];
	private float animationSecond = 18.0f; // 多少秒完成一次蝴蝶动画
	private long ct;

	// camera
	private final SimpleVector camPosition = new SimpleVector(0.0f - 0.65f,
			-0.56f - 0.7f, 3.2f + 0.85f);
	private final SimpleVector camLookAt = new SimpleVector(0, -1.05f, 0);
	public float camAngle;

	// touch event
	private float touchX;
	private float flingA;
	private float flingV;
	private final float minFlingV = 5.0f; // rotate 5 degrees per second

	// fps
	private boolean showFPS = false;
	private int fps_count;
	private float fps_dt;
	private float fps;

	public MushRoom(Context context) {
		this.context = context;
	}

	public static synchronized MushRoom getInstance(Context context) {
		if (gInstance == null) {
			gInstance = new MushRoom(context);
		}
		return gInstance;
	}

	public synchronized void onDrawFrame(GL10 gl) {
		// Logger.ps("onDrawFrame");
		fb.clear();

		bgWorld.renderScene(fb);
		bgWorld.draw(fb);

		drawLens();

		world.renderScene(fb);
		world.draw(fb);

		long nt = System.currentTimeMillis();
		long dt = 0;
		if (ct != 0) {
			dt = nt - ct;
			animate(dt / 1000.0f);
		}
		ct = nt;

		drawFPS(dt);

		fb.display();
		// Logger.pt("onDrawFrame");
	}

	public synchronized void onSurfaceChanged(GL10 gl, int w, int h) {
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
			Logger.ps("new FrameBuffer");
			if (WallpaperService.useGLES2) {
				fb = new FrameBuffer(w, h);
			} else {
				fb = new FrameBuffer(gl, w, h);
			}
			Logger.pt("new FrameBuffer");
		}

		resetCamera();

		Logger.pt("onSurfaceChanged");
	}

	public synchronized void onSurfaceCreated(GL10 gl, EGLConfig config) {
		Logger.log(TAG, "onSurfaceCreated");
		Logger.ps("onSurfaceCreated");

		if (master == null) {
			if (shader == null) {
				if (WallpaperService.useGLES2) {
					shader = new GLSLShader(
							Loader.loadTextFile(context.getResources()
									.openRawResource(R.raw.vertexshader)),
							Loader.loadTextFile(context.getResources()
									.openRawResource(R.raw.fragmentshader)));
				}
			}
			Logger.ps("new world");
			world = new World();
			world.setAmbientLight(255, 255, 255);
			world.setGlobalShader(shader);

			bgWorld = new World();
			bgWorld.setAmbientLight(255, 255, 255);
			bgWorld.setGlobalShader(shader);
			Logger.pt("new world");

			// load 3ds
			try {
				rm = new ResourceManager(context);
				
				rm.setWorld(bgWorld);
				rm.load3ds("bg.3DS", R.drawable.bg_d_0); // texture 94ms, 3ds 140ms

				rm.setWorld(world);
				water = rm.load3ds("water.3DS", R.drawable.water, true); // texture 70ms, 3ds 86ms 
				water.setTransparencyMode(1);
				water.setTransparency(11);
				
				rm.load3ds("floor.3DS", R.drawable.floor_d_0); // texture 73ms, 3ds 130ms
				
				rm.load3ds("mogu.3DS", R.drawable.mogu_d_01); // texture 173ms, 3ds 882ms
				
				Object3D grass = rm.load3ds("cao.3DS", R.drawable.cao_d_0, true); // texture 86ms, 3ds 153ms
				grass.setCulling(false);
				
				light = rm.load3ds("light.3DS", R.drawable.light_d, true); // texture 21ms, 3ds 37ms
				light.setTransparencyMode(1);

				for (int i = 0; i < 6; i++) {
					lens[i] = rm.load3ds((i + 1) + ".3DS", R.drawable.water);
					lens[i].setVisibility(false);
				}

				// loadmd2 684ms
				Logger.ps("loadmd2 functions");
				animations = new Animation[6];
				for (int i = 0; i < animations.length; i++) {
					animations[i] = new Animation();
				}
				animations[0].obj = rm.loadmd2("blue-left.md2",
						R.drawable.hudie_d_1);
				animations[1].obj = rm.loadmd2("blue-middle.md2", R.drawable.hudie);
				animations[2].obj = rm.loadmd2("blue-right.md2",
						R.drawable.hudie_d_1);
				animations[3].obj = rm.loadmd2("yellow-left.md2",
						R.drawable.hudie_d_2);
				animations[4].obj = rm.loadmd2("yellow-middle.md2",
						R.drawable.hudie);
				animations[5].obj = rm.loadmd2("yellow-right.md2",
						R.drawable.hudie_d_2);
				Logger.pt("loadmd2 functions");
			} catch (IOException e) {
				e.printStackTrace();
			}

			// lens
			loadLensTexture();

			// fps
			if (showFPS) {
				rm.loadTexture(R.drawable.number, true);
			}

			// compile object take 475ms
			Logger.ps("compile object");
			world.compileAllObjects();
			Logger.pt("compile object");

			master = this;
		} else {
			try {
				Logger.log(TAG, "Copying data from master Activity!");
				Field[] fs = master.getClass().getDeclaredFields();
				for (Field f : fs) {
					f.setAccessible(true);
					f.set(this, f.get(master));
				}
			} catch (Exception e) {
				throw new RuntimeException(e);
			}

			resetState();
		}
		Logger.pt("onSurfaceCreated"); // total 2768ms
	}

	public synchronized void onTouchEvent(MotionEvent event) {
		if (event.getAction() == MotionEvent.ACTION_DOWN) {
			touchX = event.getRawX();
		} else {
			if (event.getAction() == MotionEvent.ACTION_MOVE) {
				float dx = event.getRawX() - touchX;
				if (fb != null) {
					flingA += (dx * 120.0f / 480.0f) * (480.0f / fb.getWidth());
				}
				touchX = event.getRawX();
			}
		}
	}

	private void resetCamera() {
		Camera cam = world.getCamera();
		if (fb.getWidth() > fb.getHeight()) {
			cam.setFOV(1.5f);
		} else {
			cam.setFOV(0.5f);
		}
		cam.setPosition(camPosition);
		cam.lookAt(camLookAt);

		// re-rotate camera
		Matrix m = new Matrix();
		m.rotateY(camAngle);
		SimpleVector v3 = cam.getPosition();
		v3.matMul(m);
		cam.setPosition(v3);
		cam.lookAt(camLookAt);

		bgWorld.setCameraTo(cam);
	}

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

		// save cam angle
		camAngle += angle;
		if (master != null) {
			master.camAngle = this.camAngle;
		}

		// water
		angle = (float) Math.toRadians(Math.abs(degrees) * 4);
		water.rotateY(angle);
	}

	/**
	 * animate
	 * 
	 * @param dt
	 *            second
	 */
	private void animate(float dt) {
		// rotate y around look at point
		rotate(flingV * dt);

		// rotate acceleration
		flingV += flingA * 0.6f;
		flingA *= 0.91f;
		flingV *= 0.91f;
		if (flingV < 0 && flingV > -minFlingV)
			flingV = -minFlingV;
		else if (flingV > 0 && flingV < minFlingV)
			flingV = minFlingV;
		else if (flingV == 0.0f)
			flingV = minFlingV;

		for (Animation animation : animations) {
			animation.obj.animate(animation.ind, 0);
			animation.ind += (dt / (60 * animationSecond))
					* animation.obj.getAnimationSequence().getKeyFrames().length;
			if (animation.ind > 1.0f) {
				animation.ind -= 1.0f;
			}
		}
	}

	private void loadLensTexture() {
		rm.loadTexture(R.drawable.lens1, true); // 93ms
		rm.loadTexture(R.drawable.lens2, true); // 9ms
		rm.loadTexture(R.drawable.lens3, true); // 5ms
		rm.loadTexture(R.drawable.lens4, true); // 5ms
	}

	private void drawTexture(int textureId, int destX, int destY, float scale) {
		Texture tex = TextureManager.getInstance().getTexture(textureId + "");
		int sourceWidth = tex.getWidth();
		int sourceHeight = tex.getHeight();
		int destWidth = (int) (sourceWidth * scale);
		int destHeight = (int) (sourceHeight * scale);

		fb.blit(tex, // src
				0, 0, // srcX, srcY
				destX - (destWidth) / 2, destY - (destHeight) / 2, // destX,
																	// destY
				sourceWidth, sourceHeight, // sourceWidth, sourceHeight
				destWidth, destHeight, // destWidth,
										// destHeight,
				10, // transValue
				true, // additive
				null // addColor
		);
	}

	private void drawLens() {
		SimpleVector v;
		v = Interact2D.project3D2D(world.getCamera(), fb, light.getCenter());
		drawTexture(R.drawable.lens1, (int) v.x, (int) v.y, 0.4f);

		final int l[] = { 2, 1, 3, 1, 4, 1 };
		final float s[] = { 0.3f, 0.2f, 0.5f, 0.1f, 0.2f, 0.3f };

		float scale = 1.0f;
		int width = fb.getWidth() < fb.getHeight() ? fb.getWidth() : fb
				.getHeight();
		scale = scale * (width / 320.0f);

		for (int i = 0; i < 6; i++) {
			v = Interact2D.project3D2D(world.getCamera(), fb,
					lens[i].getCenter());
			drawTexture(R.drawable.lens1 + l[i] - 1, (int) v.x, (int) v.y, s[i]
					* scale);
		}
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

	/**
	 * reset state.
	 */
	private void resetState() {
		// reset current time
		ct = 0;

		fb = null;
	}
}
