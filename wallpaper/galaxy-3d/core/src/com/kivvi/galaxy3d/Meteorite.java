package com.kivvi.galaxy3d;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.math.Vector3;

public class Meteorite {
	public ModelInstance instance;

	// 3d particle part
	private Vector3 birth = new Vector3();
	private float speed;
	private Vector3 dir = new Vector3();
	private float rotSpeed;
	private Vector3 rotDir = new Vector3();
	private Vector3 scale = new Vector3();

	public Meteorite(Model model, float birthX, float birthY, float birthZ, float destX,
			float destY, float destZ, float tSpeed, float rotX, float rotY,
			float rotZ, float rotateSpeed, float scaleX, float scaleY,
			float scaleZ) {
		birth.set(birthX, birthY, birthZ);
		speed = tSpeed;
		dir.set(destX - birthX, destY - birthY, destZ - birthZ);
		dir.nor();
		rotSpeed = rotateSpeed;
		rotDir.set(rotX, rotY, rotZ);
		scale.set(scaleX, scaleY, scaleZ);
		instance = new ModelInstance(model);
		instance.transform.setTranslation(birth);
//		instance.materials.get(0).set(ColorAttribute.createDiffuse(0.8f, 0.3f, 0.6f, 1));
//		instance.materials.get(0).set(ColorAttribute.createSpecular(0.8f, 0.3f, 0.6f, 1));
		instance.materials.get(0).set(ColorAttribute.createAmbient(0, 0, 0, 1));
		
//		instance.transform.scl(scale);
//		Gdx.app.log("diaosixu", String.format("dir = [%f, %f, %f]", dir.x, dir.y, dir.z));
	}

	public void update(float delta) {
		Vector3 position = new Vector3();
		instance.transform.getTranslation(position);
		instance.transform.setTranslation(position.x + dir.x * speed * delta, position.y + dir.y * speed * delta, position.z + dir.z * speed * delta);
		instance.transform.rotate(rotDir, rotSpeed);
//		instance.transform.scale(scale.x, scale.y, scale.z);
	}

}
