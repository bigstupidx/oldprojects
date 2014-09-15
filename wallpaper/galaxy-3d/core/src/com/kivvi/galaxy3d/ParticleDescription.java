package com.kivvi.galaxy3d;

import com.badlogic.gdx.math.Vector3;

public class ParticleDescription {
	// for a single particle

	float a = 100;
	float b = 1000;
	public Vector3 birthLow = new Vector3(-b, -b, -2 * b);
	public Vector3 birthHigh = new Vector3(b, b, -2 * b);
	public float speedLow = 30;
	public float speedHigh = 100;
	public Vector3 destinationLow = new Vector3(-a, -a, 2 * a);
	public Vector3 destinationHigh = new Vector3(a, a, 2 * a);
	public float rotateSpeedLow = 1;
	public float rotateSpeedHigh = 3;
	public Vector3 rotateDirctionLow = new Vector3();
	public Vector3 rotateDirctionHigh = new Vector3();
	public float scaleLow = 0.5f;
	public float scaleHigh = 10f;

//	float a = 100;
//	float b = 500;
//	public Vector3 birthLow = new Vector3(b, -800, -800);
//	public Vector3 birthHigh = new Vector3(b, 800,  -100);
//	public float speedLow = 20;
//	public float speedHigh = 50;
//	public Vector3 destinationLow = new Vector3(-b, -800, -800);
//	public Vector3 destinationHigh = new Vector3(-b, 800,  -400);
//	public float rotateSpeedLow = 1;
//	public float rotateSpeedHigh = 3;
//	public Vector3 rotateDirctionLow = new Vector3();
//	public Vector3 rotateDirctionHigh = new Vector3();
//	public float scaleLow = 0.5f;
//	public float scaleHigh = 2f;
	
	// for particles
	public int maxParticleCount = 5;
}
