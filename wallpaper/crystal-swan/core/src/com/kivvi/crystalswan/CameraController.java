package com.kivvi.crystalswan;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.input.GestureDetector.GestureAdapter;
import com.badlogic.gdx.math.Vector3;

public class CameraController extends GestureAdapter {
	private Camera camera;
	private float damping = 0.96f;
	private boolean rotationDirection = true;
	private boolean isInControl = false;
	private Vector3 rotateAxis = new Vector3(0, 1, 0);
	private Vector3 rotateCenter = new Vector3(0, 0, 0);
	private float defaultVelocity = 0.5f;
	private float velocity = 0;

	private float tapCountInterval = 0.2f;
	private int tapCount = 0;
	private float timePast = 0;

	public CameraController(Camera cam) {
		camera = cam;
	}

	@Override
	public boolean touchDown(float x, float y, int pointer, int button) {
		return super.touchDown(x, y, pointer, button);
	}

	@Override
	public boolean panStop(float x, float y, int pointer, int button) {
		isInControl = false;
		return super.panStop(x, y, pointer, button);
	}

	@Override
	public boolean fling(float velocityX, float velocityY, int button) {
		velocity = -velocityX / 600.0f;
		return true;
	}

	@Override
	public boolean pan(float x, float y, float deltaX, float deltaY) {
		isInControl = true;
		float rotate = deltaX / 3.0f;

		if (deltaX < 0)
			rotationDirection = false;
		else
			rotationDirection = true;

		camera.rotateAround(rotateCenter, rotateAxis, -rotate);

		return true;
	}

	public float getCameraRotateAngle() {
		float ret;
		if (Math.abs(velocity) > defaultVelocity) {
			velocity = velocity * damping;
			ret = velocity;
		} else {
			// use delta time to control default velocity. 
			float s = 20.0f * Gdx.graphics.getDeltaTime();
			ret = defaultVelocity * s;
			if (rotationDirection)
				ret = -ret;
		}

		return ret;
	}

	public boolean getControlStatus() {
		return isInControl;
	}

	@Override
	public boolean tap(float x, float y, int count, int button) {
		tapCount++;
		return true;
	}

	public void update(float delta) {
		if (tapCount > 0)
			timePast += delta;

		if (timePast > tapCountInterval) {
			tapCount = 0;
			timePast = 0;
		}
	}

	public int getTapCount() {
		return tapCount;
	}

}
