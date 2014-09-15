package com.kivvi.lighter.simulator;

public final class AreaFlameSpineSimulator3D implements IFlameSpineSimulator {
	private float mBuoyancyDirX;
	private float mBuoyancyDirY;
	private float mBuoyancyDirZ;
	private float mBuoyancyFactor;
	private float mDt;
	private float mDtSqr;
	private float mEmissionStreamDirX;
	private float mEmissionStreamDirY;
	private float mEmissionStreamDirZ;
	private float[] mLastLeftSpinePoints;
	private float[] mLastRightSpinePoints;
	private float mLateralSpringDistance;
	private float[] mLeftSpineForces;
	private float mLeftSpineOriginX;
	private float mLeftSpineOriginY;
	private float mLeftSpineOriginZ;
	private float[] mLeftSpinePoints;
	private int mNumSpinePoints;
	private float[] mPointMasses;
	private float[] mRightSpineForces;
	private float mRightSpineOriginX;
	private float mRightSpineOriginY;
	private float mRightSpineOriginZ;
	private float[] mRightSpinePoints;
	private float mSpringDistance;
	private float mSpringInvDamping;
	private float mSpringStiffness;
	private float[] mTmpLeftSpinePoints;
	private float[] mTmpRightSpinePoints;

	private void computeIterationAreaNeighborSprings(
			float[] paramArrayOfFloat1, float[] paramArrayOfFloat2,
			float[] paramArrayOfFloat3, float[] paramArrayOfFloat4,
			float[] paramArrayOfFloat5, float[] paramArrayOfFloat6) {
		for (int i = 1;; i++) {
			int j = this.mNumSpinePoints - 1;
			if (i >= j)
				break;
			int i9 = i * 3;
			float f75 = paramArrayOfFloat1[(i9 - 3)];
			float f76 = paramArrayOfFloat1[(i9 - 2)];
			float f77 = paramArrayOfFloat1[(i9 - 1)];
			float f78 = paramArrayOfFloat1[i9];
			float f79 = paramArrayOfFloat1[(i9 + 1)];
			float f80 = paramArrayOfFloat1[(i9 + 2)];
			float f81 = paramArrayOfFloat1[(i9 + 3)];
			float f82 = paramArrayOfFloat1[(i9 + 4)];
			float f83 = paramArrayOfFloat1[(i9 + 5)];
			float f84 = paramArrayOfFloat4[i9];
			float f85 = paramArrayOfFloat4[(i9 + 1)];
			float f86 = paramArrayOfFloat4[(i9 + 2)];
			float f87 = f75 - f78;
			float f88 = f76 - f79;
			float f89 = f77 - f80;
			float f90 = f81 - f78;
			float f91 = f82 - f79;
			float f92 = f83 - f80;
			float f93 = f84 - f78;
			float f94 = f85 - f79;
			float f95 = f86 - f80;
			float f96 = (float) Math.sqrt(f87 * f87 + f88 * f88 + f89 * f89);
			float f97 = (float) Math.sqrt(f90 * f90 + f91 * f91 + f92 * f92);
			float f98 = (float) Math.sqrt(f93 * f93 + f94 * f94 + f95 * f95);
			float f99 = (f96 - this.mSpringDistance) / f96;
			float f100 = (f97 - this.mSpringDistance) / f97;
			float f101 = (f98 - this.mLateralSpringDistance) / f98;
			float f102 = f87 * (f99 * this.mSpringStiffness) + f90
					* (f100 * this.mSpringStiffness) + f93
					* (f101 * this.mSpringStiffness);
			float f103 = f88 * (f99 * this.mSpringStiffness) + f91
					* (f100 * this.mSpringStiffness) + f94
					* (f101 * this.mSpringStiffness);
			float f104 = f89 * (f99 * this.mSpringStiffness) + f92
					* (f100 * this.mSpringStiffness) + f95
					* (f101 * this.mSpringStiffness);
			paramArrayOfFloat3[i9] = (f102 * this.mDtSqr / this.mPointMasses[i]
					+ paramArrayOfFloat1[i9] + this.mSpringInvDamping
					* (paramArrayOfFloat1[i9] - paramArrayOfFloat2[i9]));
			paramArrayOfFloat3[(i9 + 1)] = (f103 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i9 + 1)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i9 + 1)] - paramArrayOfFloat2[(i9 + 1)]));
			paramArrayOfFloat3[(i9 + 2)] = (f104 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i9 + 2)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i9 + 2)] - paramArrayOfFloat2[(i9 + 2)]));
		}
		int k = this.mNumSpinePoints - 1;
		int m = k * 3;
		float f1 = paramArrayOfFloat1[(m - 3)];
		float f2 = paramArrayOfFloat1[(m - 2)];
		float f3 = paramArrayOfFloat1[(m - 1)];
		float f4 = paramArrayOfFloat1[m];
		float f5 = paramArrayOfFloat1[(m + 1)];
		float f6 = paramArrayOfFloat1[(m + 2)];
		float f7 = paramArrayOfFloat4[m];
		float f8 = paramArrayOfFloat4[(m + 1)];
		float f9 = paramArrayOfFloat4[(m + 2)];
		float f10 = f1 - f4;
		float f11 = f2 - f5;
		float f12 = f3 - f6;
		float f13 = f7 - f4;
		float f14 = f8 - f5;
		float f15 = f9 - f6;
		float f16 = (float) Math.sqrt(f10 * f10 + f11 * f11 + f12 * f12);
		float f17 = (float) Math.sqrt(f13 * f13 + f14 * f14 + f15 * f15);
		float f18 = (f16 - this.mSpringDistance) / f16;
		float f19 = (f17 - this.mLateralSpringDistance) / f17;
		float f20 = f10 * (f18 * this.mSpringStiffness) + f13
				* (f19 * this.mSpringStiffness);
		float f21 = f11 * (f18 * this.mSpringStiffness) + f14
				* (f19 * this.mSpringStiffness);
		float f22 = f12 * (f18 * this.mSpringStiffness) + f15
				* (f19 * this.mSpringStiffness);
		paramArrayOfFloat3[m] = (f20 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[m] + this.mSpringInvDamping
				* (paramArrayOfFloat1[m] - paramArrayOfFloat2[m]));
		paramArrayOfFloat3[(m + 1)] = (f21 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[(m + 1)] + this.mSpringInvDamping
				* (paramArrayOfFloat1[(m + 1)] - paramArrayOfFloat2[(m + 1)]));
		paramArrayOfFloat3[(m + 2)] = (f22 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[(m + 2)] + this.mSpringInvDamping
				* (paramArrayOfFloat1[(m + 2)] - paramArrayOfFloat2[(m + 2)]));
		for (int n = 1;; n++) {
			int i1 = this.mNumSpinePoints - 1;
			if (n >= i1)
				break;
			int i8 = n * 3;
			float f45 = paramArrayOfFloat4[(i8 - 3)];
			float f46 = paramArrayOfFloat4[(i8 - 2)];
			float f47 = paramArrayOfFloat4[(i8 - 1)];
			float f48 = paramArrayOfFloat4[i8];
			float f49 = paramArrayOfFloat4[(i8 + 1)];
			float f50 = paramArrayOfFloat4[(i8 + 2)];
			float f51 = paramArrayOfFloat4[(i8 + 3)];
			float f52 = paramArrayOfFloat4[(i8 + 4)];
			float f53 = paramArrayOfFloat4[(i8 + 5)];
			float f54 = paramArrayOfFloat1[i8];
			float f55 = paramArrayOfFloat1[(i8 + 1)];
			float f56 = paramArrayOfFloat1[(i8 + 2)];
			float f57 = f45 - f48;
			float f58 = f46 - f49;
			float f59 = f47 - f50;
			float f60 = f51 - f48;
			float f61 = f52 - f49;
			float f62 = f53 - f50;
			float f63 = f54 - f48;
			float f64 = f55 - f49;
			float f65 = f56 - f50;
			float f66 = (float) Math.sqrt(f57 * f57 + f58 * f58 + f59 * f59);
			float f67 = (float) Math.sqrt(f60 * f60 + f61 * f61 + f62 * f62);
			float f68 = (float) Math.sqrt(f63 * f63 + f64 * f64 + f65 * f65);
			float f69 = (f66 - this.mSpringDistance) / f66;
			float f70 = (f67 - this.mSpringDistance) / f67;
			float f71 = (f68 - this.mLateralSpringDistance) / f68;
			float f72 = f57 * (f69 * this.mSpringStiffness) + f60
					* (f70 * this.mSpringStiffness) + f63
					* (f71 * this.mSpringStiffness);
			float f73 = f58 * (f69 * this.mSpringStiffness) + f61
					* (f70 * this.mSpringStiffness) + f64
					* (f71 * this.mSpringStiffness);
			float f74 = f59 * (f69 * this.mSpringStiffness) + f62
					* (f70 * this.mSpringStiffness) + f65
					* (f71 * this.mSpringStiffness);
			paramArrayOfFloat6[i8] = (f72 * this.mDtSqr / this.mPointMasses[n]
					+ paramArrayOfFloat4[i8] + this.mSpringInvDamping
					* (paramArrayOfFloat4[i8] - paramArrayOfFloat5[i8]));
			paramArrayOfFloat6[(i8 + 1)] = (f73 * this.mDtSqr
					/ this.mPointMasses[n] + paramArrayOfFloat4[(i8 + 1)] + this.mSpringInvDamping
					* (paramArrayOfFloat4[(i8 + 1)] - paramArrayOfFloat5[(i8 + 1)]));
			paramArrayOfFloat6[(i8 + 2)] = (f74 * this.mDtSqr
					/ this.mPointMasses[n] + paramArrayOfFloat4[(i8 + 2)] + this.mSpringInvDamping
					* (paramArrayOfFloat4[(i8 + 2)] - paramArrayOfFloat5[(i8 + 2)]));
		}
		int i2 = this.mNumSpinePoints - 1;
		int i3 = i2 * 3;
		float f23 = paramArrayOfFloat4[(i3 - 3)];
		float f24 = paramArrayOfFloat4[(i3 - 2)];
		float f25 = paramArrayOfFloat4[(i3 - 1)];
		float f26 = paramArrayOfFloat4[i3];
		float f27 = paramArrayOfFloat4[(i3 + 1)];
		float f28 = paramArrayOfFloat4[(i3 + 2)];
		float f29 = paramArrayOfFloat1[i3];
		float f30 = paramArrayOfFloat1[(i3 + 1)];
		float f31 = paramArrayOfFloat1[(i3 + 2)];
		float f32 = f23 - f26;
		float f33 = f24 - f27;
		float f34 = f25 - f28;
		float f35 = f29 - f26;
		float f36 = f30 - f27;
		float f37 = f31 - f28;
		float f38 = (float) Math.sqrt(f32 * f32 + f33 * f33 + f34 * f34);
		float f39 = (float) Math.sqrt(f35 * f35 + f36 * f36 + f37 * f37);
		float f40 = (f38 - this.mSpringDistance) / f38;
		float f41 = (f39 - this.mLateralSpringDistance) / f39;
		float f42 = f32 * (f40 * this.mSpringStiffness) + f35
				* (f41 * this.mSpringStiffness);
		float f43 = f33 * (f40 * this.mSpringStiffness) + f36
				* (f41 * this.mSpringStiffness);
		float f44 = f34 * (f40 * this.mSpringStiffness) + f37
				* (f41 * this.mSpringStiffness);
		paramArrayOfFloat6[i3] = (f42 * this.mDtSqr / this.mPointMasses[i2]
				+ paramArrayOfFloat4[i3] + this.mSpringInvDamping
				* (paramArrayOfFloat4[i3] - paramArrayOfFloat5[i3]));
		paramArrayOfFloat6[(i3 + 1)] = (f43 * this.mDtSqr
				/ this.mPointMasses[i2] + paramArrayOfFloat4[(i3 + 1)] + this.mSpringInvDamping
				* (paramArrayOfFloat4[(i3 + 1)] - paramArrayOfFloat5[(i3 + 1)]));
		paramArrayOfFloat6[(i3 + 2)] = (f44 * this.mDtSqr
				/ this.mPointMasses[i2] + paramArrayOfFloat4[(i3 + 2)] + this.mSpringInvDamping
				* (paramArrayOfFloat4[(i3 + 2)] - paramArrayOfFloat5[(i3 + 2)]));
		for (int i4 = 3;; i4 += 3) {
			int i5 = 3 * this.mNumSpinePoints;
			if (i4 >= i5)
				break;
			paramArrayOfFloat2[i4] = paramArrayOfFloat1[i4];
			paramArrayOfFloat2[(i4 + 1)] = paramArrayOfFloat1[(i4 + 1)];
			paramArrayOfFloat2[(i4 + 2)] = paramArrayOfFloat1[(i4 + 2)];
			paramArrayOfFloat5[i4] = paramArrayOfFloat4[i4];
			paramArrayOfFloat5[(i4 + 1)] = paramArrayOfFloat4[(i4 + 1)];
			paramArrayOfFloat5[(i4 + 2)] = paramArrayOfFloat4[(i4 + 2)];
		}
		for (int i6 = 3;; i6 += 3) {
			int i7 = 3 * this.mNumSpinePoints;
			if (i6 >= i7)
				break;
			paramArrayOfFloat1[i6] = paramArrayOfFloat3[i6];
			paramArrayOfFloat1[(i6 + 1)] = paramArrayOfFloat3[(i6 + 1)];
			paramArrayOfFloat1[(i6 + 2)] = paramArrayOfFloat3[(i6 + 2)];
			paramArrayOfFloat4[i6] = paramArrayOfFloat6[i6];
			paramArrayOfFloat4[(i6 + 1)] = paramArrayOfFloat6[(i6 + 1)];
			paramArrayOfFloat4[(i6 + 2)] = paramArrayOfFloat6[(i6 + 2)];
		}
	}

	private void computeIterationNeighborSprings(float[] paramArrayOfFloat1,
			float[] paramArrayOfFloat2, float[] paramArrayOfFloat3) {
		for (int i = 1;; i++) {
			int j = this.mNumSpinePoints - 1;
			if (i >= j)
				break;
			int i4 = i * 3;
			float f15 = paramArrayOfFloat1[(i4 - 3)];
			float f16 = paramArrayOfFloat1[(i4 - 2)];
			float f17 = paramArrayOfFloat1[(i4 - 1)];
			float f18 = paramArrayOfFloat1[i4];
			float f19 = paramArrayOfFloat1[(i4 + 1)];
			float f20 = paramArrayOfFloat1[(i4 + 2)];
			float f21 = paramArrayOfFloat1[(i4 + 3)];
			float f22 = paramArrayOfFloat1[(i4 + 4)];
			float f23 = paramArrayOfFloat1[(i4 + 5)];
			float f24 = f15 - f18;
			float f25 = f16 - f19;
			float f26 = f17 - f20;
			float f27 = f21 - f18;
			float f28 = f22 - f19;
			float f29 = f23 - f20;
			float f30 = (float) Math.sqrt(f24 * f24 + f25 * f25 + f26 * f26);
			float f31 = (float) Math.sqrt(f27 * f27 + f28 * f28 + f29 * f29);
			float f32 = (f30 - this.mSpringDistance) / f30;
			float f33 = (f31 - this.mSpringDistance) / f31;
			float f34 = f24 * (f32 * this.mSpringStiffness) + f27
					* (f33 * this.mSpringStiffness);
			float f35 = f25 * (f32 * this.mSpringStiffness) + f28
					* (f33 * this.mSpringStiffness);
			float f36 = f26 * (f32 * this.mSpringStiffness) + f29
					* (f33 * this.mSpringStiffness);
			paramArrayOfFloat3[i4] = (f34 * this.mDtSqr / this.mPointMasses[i]
					+ paramArrayOfFloat1[i4] + this.mSpringInvDamping
					* (paramArrayOfFloat1[i4] - paramArrayOfFloat2[i4]));
			paramArrayOfFloat3[(i4 + 1)] = (f35 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i4 + 1)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i4 + 1)] - paramArrayOfFloat2[(i4 + 1)]));
			paramArrayOfFloat3[(i4 + 2)] = (f36 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i4 + 2)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i4 + 2)] - paramArrayOfFloat2[(i4 + 2)]));
		}
		int k = this.mNumSpinePoints - 1;
		int m = k * 3;
		float f1 = paramArrayOfFloat1[(m - 3)];
		float f2 = paramArrayOfFloat1[(m - 2)];
		float f3 = paramArrayOfFloat1[(m - 1)];
		float f4 = paramArrayOfFloat1[m];
		float f5 = paramArrayOfFloat1[(m + 1)];
		float f6 = paramArrayOfFloat1[(m + 2)];
		float f7 = f1 - f4;
		float f8 = f2 - f5;
		float f9 = f3 - f6;
		float f10 = (float) Math.sqrt(f7 * f7 + f8 * f8 + f9 * f9);
		float f11 = (f10 - this.mSpringDistance) / f10;
		float f12 = f7 * (f11 * this.mSpringStiffness);
		float f13 = f8 * (f11 * this.mSpringStiffness);
		float f14 = f9 * (f11 * this.mSpringStiffness);
		paramArrayOfFloat3[m] = (f12 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[m] + this.mSpringInvDamping
				* (paramArrayOfFloat1[m] - paramArrayOfFloat2[m]));
		paramArrayOfFloat3[(m + 1)] = (f13 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[(m + 1)] + this.mSpringInvDamping
				* (paramArrayOfFloat1[(m + 1)] - paramArrayOfFloat2[(m + 1)]));
		paramArrayOfFloat3[(m + 2)] = (f14 * this.mDtSqr / this.mPointMasses[k]
				+ paramArrayOfFloat1[(m + 2)] + this.mSpringInvDamping
				* (paramArrayOfFloat1[(m + 2)] - paramArrayOfFloat2[(m + 2)]));
		for (int n = 3;; n += 3) {
			int i1 = 3 * this.mNumSpinePoints;
			if (n >= i1)
				break;
			paramArrayOfFloat2[n] = paramArrayOfFloat1[n];
			paramArrayOfFloat2[(n + 1)] = paramArrayOfFloat1[(n + 1)];
			paramArrayOfFloat2[(n + 2)] = paramArrayOfFloat1[(n + 2)];
		}
		for (int i2 = 3;; i2 += 3) {
			int i3 = 3 * this.mNumSpinePoints;
			if (i2 >= i3)
				break;
			paramArrayOfFloat1[i2] = paramArrayOfFloat3[i2];
			paramArrayOfFloat1[(i2 + 1)] = paramArrayOfFloat3[(i2 + 1)];
			paramArrayOfFloat1[(i2 + 2)] = paramArrayOfFloat3[(i2 + 2)];
		}
	}

	private void computeIterationSecondNeighborSprings(
			float[] paramArrayOfFloat1, float[] paramArrayOfFloat2,
			float[] paramArrayOfFloat3) {
		for (int i = 2;; i++) {
			int j = this.mNumSpinePoints - 2;
			if (i >= j)
				break;
			int i5 = i * 3;
			float f15 = paramArrayOfFloat1[(i5 - 6)];
			float f16 = paramArrayOfFloat1[(i5 - 5)];
			float f17 = paramArrayOfFloat1[(i5 - 4)];
			float f18 = paramArrayOfFloat1[i5];
			float f19 = paramArrayOfFloat1[(i5 + 1)];
			float f20 = paramArrayOfFloat1[(i5 + 2)];
			float f21 = paramArrayOfFloat1[(i5 + 6)];
			float f22 = paramArrayOfFloat1[(i5 + 7)];
			float f23 = paramArrayOfFloat1[(i5 + 8)];
			float f24 = f15 - f18;
			float f25 = f16 - f19;
			float f26 = f17 - f20;
			float f27 = f21 - f18;
			float f28 = f22 - f19;
			float f29 = f23 - f20;
			float f30 = (float) Math.sqrt(f24 * f24 + f25 * f25 + f26 * f26);
			float f31 = (float) Math.sqrt(f27 * f27 + f28 * f28 + f29 * f29);
			float f32 = (f30 - 2.0F * this.mSpringDistance) / f30;
			float f33 = (f31 - 2.0F * this.mSpringDistance) / f31;
			float f34 = f24 * (f32 * this.mSpringStiffness) + f27
					* (f33 * this.mSpringStiffness);
			float f35 = f25 * (f32 * this.mSpringStiffness) + f28
					* (f33 * this.mSpringStiffness);
			float f36 = f26 * (f32 * this.mSpringStiffness) + f29
					* (f33 * this.mSpringStiffness);
			paramArrayOfFloat3[i5] = (f34 * this.mDtSqr / this.mPointMasses[i]
					+ paramArrayOfFloat1[i5] + this.mSpringInvDamping
					* (paramArrayOfFloat1[i5] - paramArrayOfFloat2[i5]));
			paramArrayOfFloat3[(i5 + 1)] = (f35 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i5 + 1)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i5 + 1)] - paramArrayOfFloat2[(i5 + 1)]));
			paramArrayOfFloat3[(i5 + 2)] = (f36 * this.mDtSqr
					/ this.mPointMasses[i] + paramArrayOfFloat1[(i5 + 2)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i5 + 2)] - paramArrayOfFloat2[(i5 + 2)]));
		}
		for (int k = this.mNumSpinePoints - 2;; k++) {
			int m = this.mNumSpinePoints;
			if (k >= m)
				break;
			int i4 = k * 3;
			float f1 = paramArrayOfFloat1[(i4 - 6)];
			float f2 = paramArrayOfFloat1[(i4 - 5)];
			float f3 = paramArrayOfFloat1[(i4 - 4)];
			float f4 = paramArrayOfFloat1[i4];
			float f5 = paramArrayOfFloat1[(i4 + 1)];
			float f6 = paramArrayOfFloat1[(i4 + 2)];
			float f7 = f1 - f4;
			float f8 = f2 - f5;
			float f9 = f3 - f6;
			float f10 = (float) Math.sqrt(f7 * f7 + f8 * f8 + f9 * f9);
			float f11 = (f10 - 2.0F * this.mSpringDistance) / f10;
			float f12 = f7 * (f11 * this.mSpringStiffness);
			float f13 = f8 * (f11 * this.mSpringStiffness);
			float f14 = f9 * (f11 * this.mSpringStiffness);
			paramArrayOfFloat3[i4] = (f12 * this.mDtSqr / this.mPointMasses[k]
					+ paramArrayOfFloat1[i4] + this.mSpringInvDamping
					* (paramArrayOfFloat1[i4] - paramArrayOfFloat2[i4]));
			paramArrayOfFloat3[(i4 + 1)] = (f13 * this.mDtSqr
					/ this.mPointMasses[k] + paramArrayOfFloat1[(i4 + 1)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i4 + 1)] - paramArrayOfFloat2[(i4 + 1)]));
			paramArrayOfFloat3[(i4 + 2)] = (f14 * this.mDtSqr
					/ this.mPointMasses[k] + paramArrayOfFloat1[(i4 + 2)] + this.mSpringInvDamping
					* (paramArrayOfFloat1[(i4 + 2)] - paramArrayOfFloat2[(i4 + 2)]));
		}
		for (int n = 3;; n += 3) {
			int i1 = 3 * this.mNumSpinePoints;
			if (n >= i1)
				break;
			paramArrayOfFloat2[n] = paramArrayOfFloat1[n];
			paramArrayOfFloat2[(n + 1)] = paramArrayOfFloat1[(n + 1)];
			paramArrayOfFloat2[(n + 2)] = paramArrayOfFloat1[(n + 2)];
		}
		for (int i2 = 3; i2 < 3 * this.mNumSpinePoints; i2 += 3) {
			paramArrayOfFloat1[i2] = paramArrayOfFloat3[i2];
			paramArrayOfFloat1[(i2 + 1)] = paramArrayOfFloat3[(i2 + 1)];
			paramArrayOfFloat1[(i2 + 2)] = paramArrayOfFloat3[(i2 + 2)];
		}
	}

	public void applyBuoyancyXYZ(float dirX, float dirY, float dirZ) {
		mBuoyancyDirX = (dirX * 3.5F);
		mBuoyancyDirY = (-2.0F + dirY * 3.0F);
		float f1 = 1.0F / mNumSpinePoints;
		float f2 = 0.0F;
		for (int j = 3, i = 0; j < 3 * mNumSpinePoints; j += 3, i++) {
			float f3 = f2 * f2;
			float f4 = mEmissionStreamDirX * (1.0F - f3) + f3 * mBuoyancyDirX;
			float f5 = 1.75F * mEmissionStreamDirY * (1.0F - f3) + f3
					* mBuoyancyDirY;
			float f6 = mNumSpinePoints - i / mNumSpinePoints * mBuoyancyFactor;
			float f7 = f4 * f6;
			float f8 = f5 * f6;
			mLeftSpineForces[j] = (f7 + mLeftSpineForces[j]);
			mLeftSpineForces[j + 1] = f8 + mLeftSpineForces[j + 1];
			mRightSpineForces[j] = (f7 + mRightSpineForces[j]);
			mRightSpineForces[j + 1] = (f8 + mRightSpineForces[j + 1]);
			f2 += f1;
		}
	}

	public void applyWindForceXYZ(float paramFloat1, float paramFloat2,
			float paramFloat3) {
		float f1 = 1.0F / this.mNumSpinePoints;
		float f2 = 0.0F;
		for (int i = 0, j = 1; j < this.mNumSpinePoints; i++, j++) {
			int k = j * 3;
			float f3 = f2 * f2;
			float f4 = mEmissionStreamDirX * (1.0F - f3) + paramFloat1 * f3;
			float f5 = mEmissionStreamDirY * (1.0F - f3) + paramFloat2 * f3;
			float f6 = mEmissionStreamDirZ * (1.0F - f3) + paramFloat3 * f3;
			float f7 = mNumSpinePoints - i / mNumSpinePoints / mPointMasses[j];
			float f8 = f4 * f7;
			float f9 = f5 * f7;
			float f10 = f6 * f7;
			float[] arrayOfFloat1 = this.mLeftSpineForces;
			arrayOfFloat1[k] = (f8 + arrayOfFloat1[k]);
			float[] arrayOfFloat2 = this.mLeftSpineForces;
			int m = k + 1;
			arrayOfFloat2[m] = (f9 + arrayOfFloat2[m]);
			float[] arrayOfFloat3 = this.mLeftSpineForces;
			int n = k + 2;
			arrayOfFloat3[n] = (f10 + arrayOfFloat3[n]);
			mRightSpineForces[k] = (f8 + mRightSpineForces[k]);
			mRightSpineForces[k + 1] = (f9 + mRightSpineForces[k + 1]);
			mRightSpineForces[k + 2] = (f10 + mRightSpineForces[k + 2]);
			f2 += f1;
		}
	}

	public float[] getLeftSpinePoints() {
		return this.mLeftSpinePoints;
	}

	public int getNumSpinePoints() {
		return this.mNumSpinePoints;
	}

	public float[] getRightSpinePoints() {
		return this.mRightSpinePoints;
	}

	public void init(int paramInt, float paramFloat1, float paramFloat2,
			float paramFloat3, float paramFloat4) {
		this.mNumSpinePoints = paramInt;
		this.mLeftSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mRightSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mLastLeftSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mLastRightSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mTmpLeftSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mTmpRightSpinePoints = new float[3 * this.mNumSpinePoints];
		this.mPointMasses = new float[this.mNumSpinePoints];
		this.mLeftSpineForces = new float[3 * this.mNumSpinePoints];
		this.mRightSpineForces = new float[3 * this.mNumSpinePoints];
		int i = this.mNumSpinePoints - 1;
		this.mSpringStiffness = 325.0F;
		this.mSpringDistance = (paramFloat1 / i);
		this.mSpringDistance = (1.35F * this.mSpringDistance);
		this.mLateralSpringDistance = (2.0F * 64.0F);

		mLeftSpineOriginX = (paramFloat2 - 64.0F);
		mLeftSpineOriginY = paramFloat3;
		mLeftSpineOriginZ = paramFloat4;

		this.mRightSpineOriginX = (paramFloat2 + 64.0F);
		this.mRightSpineOriginY = paramFloat3;
		this.mRightSpineOriginZ = paramFloat4;
		this.mBuoyancyDirX = 0.0F;
		this.mBuoyancyDirY = 1.0F;
		this.mBuoyancyDirZ = 0.0F;
		this.mBuoyancyFactor = 100.0F;
		this.mEmissionStreamDirX = 0.0F;
		this.mEmissionStreamDirY = 1.0F;
		this.mEmissionStreamDirZ = 0.0F;
		this.mDt = 0.015F;
		this.mDtSqr = (this.mDt * this.mDt);
		this.mSpringInvDamping = (1.0F - 1.0F / 65.0F);
		reset();
	}

	public void pause() {
	}

	public void proceed() {
	}

	public void reset() {
		for (int i = 0, j = 0; j < 3 * this.mNumSpinePoints; i++, j += 3) {
			mLeftSpinePoints[j] = mLeftSpineOriginX;
			mLeftSpinePoints[(j + 1)] = (mLeftSpineOriginY + i
					* mSpringDistance);
			mLeftSpinePoints[(j + 2)] = mLeftSpineOriginZ;

			this.mRightSpinePoints[j] = this.mRightSpineOriginX;
			this.mRightSpinePoints[(j + 1)] = (this.mRightSpineOriginY + i
					* this.mSpringDistance);
			this.mRightSpinePoints[(j + 2)] = this.mRightSpineOriginZ;

			this.mLastLeftSpinePoints[j] = this.mLeftSpinePoints[j];
			this.mLastLeftSpinePoints[(j + 1)] = this.mLeftSpinePoints[(j + 1)];
			this.mLastLeftSpinePoints[(j + 2)] = this.mLeftSpinePoints[(j + 2)];

			this.mLastRightSpinePoints[j] = this.mRightSpinePoints[j];
			this.mLastRightSpinePoints[(j + 1)] = this.mRightSpinePoints[(j + 1)];
			this.mLastRightSpinePoints[(j + 2)] = this.mRightSpinePoints[(j + 2)];

			this.mTmpLeftSpinePoints[j] = this.mLeftSpinePoints[j];
			this.mTmpLeftSpinePoints[(j + 1)] = this.mLeftSpinePoints[(j + 1)];
			this.mTmpLeftSpinePoints[(j + 2)] = this.mLeftSpinePoints[(j + 2)];

			this.mTmpRightSpinePoints[j] = this.mRightSpinePoints[j];
			this.mTmpRightSpinePoints[(j + 1)] = this.mRightSpinePoints[(j + 1)];
			this.mTmpRightSpinePoints[(j + 2)] = this.mRightSpinePoints[(j + 2)];

			mLeftSpineForces[j] = 0.0F;
			mLeftSpineForces[(j + 1)] = 0.0F;
			mLeftSpineForces[(j + 2)] = 0.0F;

			mRightSpineForces[j] = 0.0F;
			mRightSpineForces[(j + 1)] = 0.0F;
			mRightSpineForces[(j + 2)] = 0.0F;
		}
		for (int k = 0; k < this.mNumSpinePoints; k++)
			mPointMasses[k] = (1.0F + 0.15F * (mNumSpinePoints - k));
		mPointMasses[(this.mNumSpinePoints - 1)] = (2.0F * this.mPointMasses[0]);
	}

	public void setRadialForceXY(float paramFloat1, float paramFloat2,
			float paramFloat3, float paramFloat4, float paramFloat5,
			float paramFloat6) {
		float f1 = paramFloat5 * paramFloat5;
		for (int i = 3; i < 3 * this.mNumSpinePoints; i += 3) {
			float f2 = 0.5F * (this.mLeftSpinePoints[i] + this.mRightSpinePoints[i]);
			float f3 = 0.5F * (this.mLeftSpinePoints[(i + 1)] + this.mRightSpinePoints[(i + 1)]);
			float f4 = f2 - paramFloat1;
			float f5 = f3 - paramFloat2;
			float f6 = f4 * f4 + f5 * f5;
			if (f6 < f1) {
				float f7 = (float) Math.sqrt(f6);
				float f8 = f4 / (0.01F + f7);
				float f9 = f5 / (0.01F + f7);
				float f10 = f8 * (paramFloat6 * (paramFloat5 - f7));
				float f11 = f9 * (paramFloat6 * (paramFloat5 - f7));
				float[] arrayOfFloat1 = this.mLeftSpineForces;
				arrayOfFloat1[i] += f10 + paramFloat3;
				float[] arrayOfFloat2 = this.mLeftSpineForces;
				int j = i + 1;
				arrayOfFloat2[j] += f11 + paramFloat4;
				float[] arrayOfFloat3 = this.mRightSpineForces;
				arrayOfFloat3[i] += f10 + paramFloat3;
				float[] arrayOfFloat4 = this.mRightSpineForces;
				int k = i + 1;
				arrayOfFloat4[k] += f11 + paramFloat4;
			}
		}
	}

	public void shutdown() {
	}

	public void update() {
		for (int i = 1; i < this.mNumSpinePoints; i++) {
			int i2 = i * 3;
			float f5 = 1.0F / this.mPointMasses[i];
			float f6 = f5 * this.mLeftSpineForces[i2];
			float f7 = f5 * this.mLeftSpineForces[(i2 + 1)];
			float f8 = f5 * this.mLeftSpineForces[(i2 + 2)];
			mLeftSpinePoints[i2] += f6 * this.mDt;
			mLeftSpinePoints[i2 + 1] += f7 * this.mDt;
			mLeftSpinePoints[i2 + 2] += f8 * this.mDt;

			mLeftSpineForces[i2] = 0.0F;
			mLeftSpineForces[(i2 + 1)] = 0.0F;
			mLeftSpineForces[(i2 + 2)] = 0.0F;
		}
		for (int j = 1; j < this.mNumSpinePoints; j++) {
			int m = j * 3;
			float f1 = 1.0F / this.mPointMasses[j];
			float f2 = f1 * this.mRightSpineForces[m];
			float f3 = f1 * this.mRightSpineForces[(m + 1)];
			float f4 = f1 * this.mRightSpineForces[(m + 2)];
			mRightSpinePoints[m] += f2 * this.mDt;
			mRightSpinePoints[m + 1] += f3 * this.mDt;
			mRightSpinePoints[m + 2] += f4 * this.mDt;

			this.mRightSpineForces[m] = 0.0F;
			this.mRightSpineForces[(m + 1)] = 0.0F;
			this.mRightSpineForces[(m + 2)] = 0.0F;
		}
		for (int k = 0; k < 8; k++)
			computeIterationAreaNeighborSprings(this.mLeftSpinePoints,
					this.mLastLeftSpinePoints, this.mTmpLeftSpinePoints,
					this.mRightSpinePoints, this.mLastRightSpinePoints,
					this.mTmpRightSpinePoints);
	}
}
