/**
 * yltian 
 */
package com.kivvi.livewallpaper.flowerzen.utils;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector3;

public class MirrorCamera extends PerspectiveCamera {
	private static final String TAG = MirrorCamera.class.getName();

	Plane plane = new Plane(new Vector3(0,1,0),0);
	

	

	@Override
	public void update() {
		super.update();
	}
	
	public void updateMirrorFrom(Camera other) {
		this.copyPDU(other);
		this.reflect();
		this.update();
	}
	
	public void setMirrorPlane(Plane plane) {
		this.plane = plane;
	}


	public MirrorCamera(float fieldOfView, float viewportWidth, float viewportHeight) {
		super(fieldOfView, viewportWidth, viewportHeight);
	}

	/**
	 * p:position
	 * d:direction
	 * u:up
	 * 
	 * @param other
	 */
	public void copyPDU(Camera other) {
		if (this != other) {
			this.position.set(other.position);
			this.direction.set(other.direction);
			this.up.set(other.up);
			this.near = other.near;
			this.far = other.far;
		}
	}
	
	public void reflect(){
		Matrix4 mat = MatrixUtils.getReflectedMatrix(this.plane);
		this.transform(mat);
	}
	
	
}
