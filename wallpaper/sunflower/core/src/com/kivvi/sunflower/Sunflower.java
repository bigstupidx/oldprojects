package com.kivvi.sunflower;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputAdapter;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight;
import com.badlogic.gdx.graphics.g3d.utils.AnimationController;
import com.badlogic.gdx.graphics.g3d.utils.AnimationController.AnimationDesc;
import com.badlogic.gdx.graphics.g3d.utils.AnimationController.AnimationListener;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.input.GestureDetector.GestureAdapter;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Quaternion;
import com.badlogic.gdx.math.Vector3;

public class Sunflower extends ApplicationAdapter {
	private PerspectiveCamera camera;
	private ModelBatch batch;
	private Model model;
	private ModelInstance instance;
	private AnimationController aniController;
	private AssetManager assets;
	private Environment env;
	private GestureDetector gestureDetector;
	private GestureAdapter gestureAdapter;
	private final Vector3 camPosition = new Vector3(58.587914f, 133.024673f,
			300);
	private final Vector3 camLookAt = new Vector3(38.708702f, 129.697052f,
			24.000000f);

	private boolean isInit = false;

	float w;
	float h;

	private float idleAniTimer = 0;
	
	private enum AnimationType {
		SHAKE_STRONG, SHAKE_WEAK, SHAKE_SENSOR, NOD_STRONG, NOD_WEAK, NOD_SENSOR, IDLE, PAN, INIT
	};

	@Override
	public void create() {
		assets = new AssetManager();
		assets.load("sunflower.g3db", Model.class);

		env = new Environment();

		DirectionalLight dLight = new DirectionalLight();
		dLight.direction.set(0, 0f, -1);
		dLight.color.set(0.5f, 0.5f, 0.5f, 1.0f);
		// env.add(dLight);

		batch = new ModelBatch();

		w = Gdx.graphics.getWidth();
		h = Gdx.graphics.getHeight();

		camera = new PerspectiveCamera(42, w, h);
		camera.position.set(camPosition);
		camera.lookAt(camLookAt);
		camera.near = 100f;
		camera.far = 500;
		camera.update();

		gestureAdapter = new GestureAdapter() {
			float xOffset;
			float yOffset;

			float tLeft1 = 0.633f;
			float tLeft2 = 0.699f;
			float tRight1 = 0.733f;
			float tRight2 = 0.766f;

			float tUp1 = 1.633f;
			float tUp2 = 1.699f;
			float tDown1 = 1.733f;
			float tDown2 = 1.766f;
			float maxOffset = w / 2.0f;

			float t;
			int type = 0;

			boolean processDrag = false;
			
			@Override
			public boolean touchDown(float x, float y, int pointer, int button) {
				
				xOffset = 0;
				yOffset = 0;
				
				if ((x > w * 2 / 3) || y < h * 1 / 5) {
					processDrag = false;
				} else {
					processDrag = true;
					idleAniTimer = 0;
				}
				
				Gdx.app.log("diaosixu", "x = " + x + " y = " + y);
				return true;
			}

			@Override
			public boolean pan(float x, float y, float deltaX, float deltaY) {
				if (!processDrag)
					return true;
				
				xOffset += deltaX;
				yOffset += deltaY;

				if (Math.abs(xOffset) > Math.abs(yOffset)) {
					type = 0;
					if (xOffset > maxOffset) {
						xOffset = maxOffset;
					} else if (xOffset < -maxOffset) {
						xOffset = -maxOffset;
					}

					if (xOffset > 0) {
						float offset = Math.abs(xOffset);
						t = tRight1 + (tRight2 - tRight1) * offset / maxOffset;
					} else if (xOffset < 0) {
						float offset = Math.abs(xOffset);
						t = tLeft1 + (tLeft2 - tLeft1) * offset / maxOffset;
					} else {
						t = 0;
					}
				} else {
					type = 1;
					if (yOffset > maxOffset) {
						yOffset = maxOffset;
					} else if (yOffset < -maxOffset) {
						yOffset = -maxOffset;
					}

					if (yOffset > 0) {
						float offset = Math.abs(yOffset);
						t = tDown1 + (tDown2 - tDown1) * offset / maxOffset;
					} else if (yOffset < 0) {
						float offset = Math.abs(yOffset);
						t = tUp1 + (tUp2 - tUp1) * offset / maxOffset;
					} else {
						t = 0;
					}
				}

				setAnimation(AnimationType.PAN, t);
				return true;
			}

			@Override
			public boolean panStop(float x, float y, int pointer, int button) {
				if (!processDrag)
					return true;
				
				if (type == 0) {
					if (Math.abs(xOffset) > w / 4.0f) {
						setAnimation(AnimationType.SHAKE_STRONG);
					} else {
						setAnimation(AnimationType.SHAKE_WEAK);
					}
				} else if (type == 1) {
					if (Math.abs(yOffset) > w / 4.0f) {
						setAnimation(AnimationType.NOD_STRONG);
					} else {
						setAnimation(AnimationType.NOD_WEAK);
					}
				}

				return true;
			}

			@Override
			public boolean tap(float x, float y, int count, int button) {
				if ((x < w * 2 / 3) && y > h * 1 / 5) {
					setAnimation(AnimationType.NOD_STRONG);
				}

				return super.tap(x, y, count, button);
			}
			
		};

		gestureDetector = new GestureDetector(gestureAdapter);

		Gdx.input.setInputProcessor(gestureDetector);
	}

	
	
	@Override
	public void render() {
		Gdx.gl.glClearColor(0, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);

		if (!assets.update())
			return;
		if (!isInit)
			initAfterLoaded();

		float delta = Gdx.graphics.getDeltaTime();
		idleAniTimer += delta;
		
		if (idleAniTimer > 12f) {
			setAnimation(AnimationType.IDLE);
			idleAniTimer = 0;
		}
		
		aniController.update(delta);

		updateCamera();

		updateSensor();

		batch.begin(camera);
		batch.render(instance);
		batch.end();
	}

	public void initAfterLoaded() {
		model = assets.get("sunflower.g3db");
		for (int i = 0; i < model.materials.size; i++) {
			model.materials.get(i)
					.set(ColorAttribute.createDiffuse(1, 1, 1, 1));
		}

		instance = new ModelInstance(model);

		aniController = new AnimationController(instance);
		setAnimation(AnimationType.INIT);

		isInit = true;
	}

	public void updateCamera() {
		// rotate by x-axis
		{
			final float offsetY = 0.2f;
			final float offsetZ = 0.05f;
			final float y1 = camPosition.y * (1.0f - offsetY);
			final float y2 = camPosition.y * (1.0f + offsetY);
			final float z1 = camPosition.z * (1.0f - offsetZ);
			final float z2 = camPosition.z * (1.0f + offsetZ);
			float pitch = Gdx.input.getPitch();
			
			Gdx.app.log("diaosixu", "pitch = " + pitch);
			
			float percent = MathUtils.clamp(pitch / (-90.0f), 0, 1);
			camera.position.y += (y2 + (y1 - y2) * percent - camera.position.y)
					* 2 * Gdx.graphics.getDeltaTime();
			float currDist = (float) Math
					.sqrt(camera.position.z * camera.position.z
							+ camera.position.x * camera.position.x);
			float deltaDist = (z2 + (z1 - z2) * percent - currDist) * 2
					* Gdx.graphics.getDeltaTime();
			float k = 1.0f + deltaDist / currDist;
			camera.position.x *= k;
			camera.position.z *= k;
			camera.lookAt(camLookAt);
		}
		// rotate by y-axis
		{
			final float offsetX = 0.6f;
			final float offsetZ = 0.05f;
			final float x1 = camPosition.x * (1.0f - offsetX);
			final float x2 = camPosition.x * (1.0f + offsetX);
			final float z1 = camPosition.z * (1.0f - offsetZ);
			final float z2 = camPosition.z * (1.0f + offsetZ);
			float roll = Gdx.input.getRoll();
			float percent = MathUtils.clamp((roll + 90) / (180.0f), 0, 1);
			camera.position.x += (x2 + (x1 - x2) * percent - camera.position.x)
					* 2 * Gdx.graphics.getDeltaTime();
			float currDist = (float) Math
					.sqrt(camera.position.z * camera.position.z
							+ camera.position.y * camera.position.y);
			float deltaDist = (z2 + (z1 - z2) * percent - currDist) * 2
					* Gdx.graphics.getDeltaTime();
			float k = 1.0f + deltaDist / currDist;
			camera.position.y *= k;
			camera.position.z *= k;
			camera.lookAt(camLookAt);
		}
		camera.update();
	}

	private float accX[] = new float[4];
	private float accZ[] = new float[4];
	private boolean sensorAnimation = false;
	private AnimationListener sensorAniLis = new AnimationListener() {
		@Override
		public void onEnd(AnimationDesc animation) {
			sensorAnimation = false;
		}

		@Override
		public void onLoop(AnimationDesc animation) {
		}
	};

	public void updateSensor() {
		if (sensorAnimation)
			return;

		final float sensitivity = 10.0f;

		// X direction
		accX[0] = -Gdx.input.getAccelerometerX();

		if (accX[3] != 0) {
			if (accX[1] - accX[2] > sensitivity) {
				// run shake animation.
				setAnimation(AnimationType.SHAKE_SENSOR);
				Gdx.app.log("debug", "shake");
			}
		}

		accX[3] = accX[2];
		accX[2] = accX[1];
		accX[1] = accX[0];

		// Z direction
		accZ[0] = Gdx.input.getAccelerometerZ();
		if (accZ[3] != 0) {
			if (accZ[1] - accZ[2] > sensitivity) {
				// run nod animation.
				setAnimation(AnimationType.NOD_SENSOR);
				Gdx.app.log("debug", "nod");
			}
		}

		accZ[3] = accZ[2];
		accZ[2] = accZ[1];
		accZ[1] = accZ[0];
	}

	public void setAnimation(AnimationType type) {
		sensorAnimation = false;
		float speed = 0.17f;
		
		if (type == AnimationType.SHAKE_STRONG) {
			aniController.setAnimation("Take 001", 0.633f, 0.03333f * 30, 1,
					speed, null);
		} else if (type == AnimationType.SHAKE_WEAK) {
			aniController.setAnimation("Take 001", 0.633f + 0.03333f * 16,
					0.03333f * 14, 1, speed, null);
		} else if (type == AnimationType.SHAKE_SENSOR) {
			aniController.setAnimation("Take 001", 0.633f, 0.03333f * 30, 1,
					speed, sensorAniLis).time = 0;
			sensorAnimation = true;
		} else if (type == AnimationType.NOD_STRONG) {
			aniController.setAnimation("Take 001", 0.633f + 0.03333f * 30,
					0.03333f * 25, 1, speed, null);
		} else if (type == AnimationType.NOD_WEAK) {
			aniController.setAnimation("Take 001", 0.633f + 0.03333f * 45,
					0.03333f * 10, 1, speed, null);
		} else if (type == AnimationType.NOD_SENSOR) {
			aniController.setAnimation("Take 001", 0.633f + 0.03333f * 30,
					0.03333f * 25, 1, speed, sensorAniLis).time = 0;
			sensorAnimation = true;
		} else if (type == AnimationType.INIT) {
			aniController.setAnimation("Take 001", 0.633f, 0.2f, -1, 0.000001f,
					null);
		} else if (type == AnimationType.IDLE) {
			aniController.setAnimation("Take 001", 0.633f + 0.03333f * 55,
					0.03333f * 15, 1, speed, sensorAniLis).time = 0;
		}
	}

	public void setAnimation(AnimationType type, float t) {
		sensorAnimation = false;
		
		if (type == AnimationType.PAN) {
			AnimationDesc desc = aniController.setAnimation("Take 001", t,
					0.2f, -1, 0.00001f, null);
			desc.time = 0;
		}
	}



	@Override
	public void dispose() {
		batch.dispose();
		assets.dispose();
	}
	
	
}
