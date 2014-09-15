package com.kivvi.lighter.simulator;

public final class BezierCubicInterpolator2D implements ICubicInterpolator {
	float[] mControlPoints;
	int mNumControlPoints;

	public void evaluate(float t, float[] outPos) {
		float f1 = t * t;
		float f2 = f1 * t;
		float f3 = 3.0F * t;
		float f4 = 3.0F * f1;
		float f5 = 3.0F * f2;
		float f6 = 1.0F + (f4 + -f2 - f3);
		float f7 = f3 + (f5 - 2.0F * f4);
		float f8 = f4 + -f5;
		outPos[0] = (f6 * this.mControlPoints[0] + f7
				* this.mControlPoints[2] + f8 * this.mControlPoints[4] + f2
				* this.mControlPoints[6]);
		outPos[1] = (f6 * this.mControlPoints[1] + f7
				* this.mControlPoints[3] + f8 * this.mControlPoints[5] + f2
				* this.mControlPoints[7]);
	}

	public void init(int num) {
		mNumControlPoints = num;
		mControlPoints = new float[2 * mNumControlPoints];
	}

	public void updateControlPointsFromSpine3D(float[] spinePoints3D,
			int numSpinePoints, float spineDirX, float spineDirY) {
		int midSpinePointIndex = (numSpinePoints - 1) >> 1;
		mControlPoints[0] = spinePoints3D[0];
		mControlPoints[1] = spinePoints3D[1];
		mControlPoints[6] = spinePoints3D[(3 * (numSpinePoints - 1))];
		mControlPoints[7] = spinePoints3D[(1 + 3 * (numSpinePoints - 1))];
		mControlPoints[2] = mControlPoints[0];
		mControlPoints[3] = spinePoints3D[(1 + midSpinePointIndex * 3)];
		mControlPoints[4] = spinePoints3D[(3 * (midSpinePointIndex + 1))];
		mControlPoints[5] = spinePoints3D[(1 + 3 * (midSpinePointIndex + 1))];
	}
}