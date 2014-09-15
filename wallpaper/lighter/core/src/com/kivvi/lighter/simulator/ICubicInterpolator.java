package com.kivvi.lighter.simulator;

public abstract interface ICubicInterpolator {
	public abstract void evaluate(float paramFloat, float[] paramArrayOfFloat);

	public abstract void init(int paramInt);

	public abstract void updateControlPointsFromSpine3D(
			float[] paramArrayOfFloat, int paramInt, float paramFloat1,
			float paramFloat2);
}