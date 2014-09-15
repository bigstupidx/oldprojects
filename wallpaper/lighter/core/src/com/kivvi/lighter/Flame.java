package com.kivvi.lighter;

import java.lang.reflect.Array;
import java.util.Random;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Mesh;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.VertexAttribute;
import com.badlogic.gdx.graphics.VertexAttributes;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g3d.utils.RenderContext;
import com.badlogic.gdx.graphics.glutils.ShaderProgram;
import com.kivvi.lighter.simulator.AreaFlameSpineSimulator3D;
import com.kivvi.lighter.simulator.BezierCubicInterpolator2D;

class Flame {
	public static final String TAG = "Flame";
	private boolean mFlameActive;

	private int mNumColumns;
	private int mNumHeightLevels;
	private int mNumVertices;
	private int mNumVerticesPerColumn;

	private float[][] mPoints;
	private float[][] mTexCoords;
	private float[] mOuterLeftPoints;
	private float[] mOuterRightPoints;

	private int mFrameCount;

	private float mFlameTopBorder;
	private float mFlameBottomBorder;
	private float mFlameLeftBorder;
	private float mFlameRightBorder;

	private float mMaxU;
	private float mMaxV;
	private float mMinU;
	private float mMinV;

	float mWindForceDirX;
	float mWindForceDirY;
	float mWindForceDirZ;

	private float mBuoyancyDirX;
	private float mBuoyancyDirY;
	private float mBuoyancyDirZ;

	private float mStepSizeVertexY;
	private float mMinStepSizeVertexY;
	private float mTargetStepSizeVertexY;

	private float mStepSizeTexCoordY;

	private Mesh mMesh[];
	public Texture mTexture;
	private ShaderProgram shader;
	private RenderContext renderContext;

	private OrthographicCamera camera;

	private BezierCubicInterpolator2D mLeftCubicInterpolator2D = new BezierCubicInterpolator2D();
	private BezierCubicInterpolator2D mRightCubicInterpolator2D = new BezierCubicInterpolator2D();
	private static final float[] cubicInterpolatorOutput = new float[2];

	private AreaFlameSpineSimulator3D mFlameSpineSimulator3D = new AreaFlameSpineSimulator3D();

	private boolean useNewFlame = false;
	private boolean useRandomFlame = false;
	private String[] mFlameFiles = { "flame.png", "flame_crimson.png",
			"flame_golden.png", "flame_liquid.png", "flame_mystic.png",
			"flame_radioactive.png" };

	private int maxNumFilterAccelValues = 5;
	private int numFilterAccelValues = 0;
	private int accelValueIndex = 0;
	private float[] accelXArray = null;
	private float[] accelYArray = null;
	private float sensorVelX = 0.0F;
	private float sensorVelY = 0.0F;
	private float sensorVelZ = 0.0F;
	private float filteredAccelX = 0.0F;
	private float filteredAccelY = 0.0F;

	private boolean mTouchSensorActive;
	private float mTouchSensorPosX;
	private float mTouchSensorPosY;
	private float mTouchSensorVelX;
	private float mTouchSensorVelY;
	private float mTouchSensorRadius;
	private float mTouchSensorRadiusSquared;
	private float mTouchSensorForceFactor;

	private int mNumTouchParticles;
	private int mTouchParticleIndex;
	private float[] mTouchParticles;
	private float[] mTouchParticleFactors;
	private float mMinTouchParticleFactor;
	private float mMaxTouchParticleFactor;

	private float mPositionX;
	private float mPositionY;

	public Flame() {
		initFlameState();

		mMesh = new Mesh[mNumColumns];

		for (int i = 0; i < mNumColumns; i++) {
			mMesh[i] = new Mesh(false, mNumVerticesPerColumn,
					mNumVerticesPerColumn * 4, new VertexAttribute(
							VertexAttributes.Usage.Position, 2,
							ShaderProgram.POSITION_ATTRIBUTE),
					new VertexAttribute(
							VertexAttributes.Usage.TextureCoordinates, 2,
							ShaderProgram.TEXCOORD_ATTRIBUTE));
		}

		String file;
		if (!useNewFlame) {
			if (useRandomFlame) {
				Random ran = new Random(System.currentTimeMillis());
				file = mFlameFiles[ran.nextInt(mFlameFiles.length)];
			} else {
				file = mFlameFiles[0];
			}
		} else {
			file = "flame_new.png";
		}
		mTexture = new Texture(Gdx.files.internal(file));

		if (false) {
			// keep aspect ratio
			float stageHeight;
			stageHeight = 800;

			float scale = (float) Gdx.graphics.getWidth() / 480;
			if (scale > (float) Gdx.graphics.getHeight() / stageHeight) {
				scale = (float) Gdx.graphics.getHeight() / stageHeight;
			}

			float width = Gdx.graphics.getWidth() / scale;
			float height = Gdx.graphics.getHeight() / scale;
			camera = new OrthographicCamera(width, height);
			camera.position.set(width / 2, height / 2, 0);
		} else {
			camera = new OrthographicCamera(2.0f, 2.0f);
		}

		shader = SpriteBatch.createDefaultShader();
		shader = new ShaderProgram(Gdx.files.internal("default.vs"),
				Gdx.files.internal("default.fs"));

		
		// accel
		sensorVelX = 0.0F;
		sensorVelY = 0.0F;
		sensorVelZ = 0.0F;
		accelXArray = new float[maxNumFilterAccelValues];
		accelYArray = new float[maxNumFilterAccelValues];
		clearFilteredAccelValuesXY();
	}

	void trace() {
		String s = "";
		if (false) {
			for (int j = 0; j < 16; j++) {
				s = s + j + ": " + mTexCoords[0][j] + ",";
			}
			Gdx.app.log(TAG, s);
		}

		if (false) {
			s = "";
			for (int j = 0; j < 16; j++) {
				s = s + j + ": " + mPoints[0][j] + ",";
			}
			Gdx.app.log(TAG, s);
		}

		if (false) {
			float[] left = mFlameSpineSimulator3D.getLeftSpinePoints();
			for (int j = 0; j < 3 * 5; j++) {
				s = s + left[j] + ", ";
			}
			Gdx.app.log(TAG, s);
		}
	}

	void draw() {
		addFilteredAccelValueXY(0.5F * filteredAccelX, 0.5F * filteredAccelY);
		computeFilteredAccelXY();

		updateFrame();

		render();

		// trace();
	}

	void render() {
		if (!mFlameActive) {
			return;
		}

		Gdx.gl.glViewport(0, 0, Gdx.graphics.getWidth(),
				Gdx.graphics.getHeight());
		camera.update();

		Gdx.gl.glEnable(GL20.GL_TEXTURE_2D);
		mTexture.bind();

		shader.begin();
		shader.fetchUniformLocation(name, pedantic);
		shader.setUniformMatrix("u_projTrans", camera.combined);
		shader.setUniformi("u_texture", 0);
		shader.end();

		trace();

		for (int i = 0; i < mNumColumns; i++) {
			float vertices[] = new float[4 * mNumVerticesPerColumn];
			int l = 0;
			for (int j = 0; j < mNumVerticesPerColumn; j++) {
				if (true) {
					vertices[l++] = mPoints[i][j * 2] / mTexture.getWidth();
					vertices[l++] = mPoints[i][j * 2 + 1]
							/ mTexture.getHeight();
					vertices[l++] = mTexCoords[i][j * 2];
					vertices[l++] = mTexCoords[i][j * 2 + 1];
				} else {
					vertices[l++] = mPoints[i][j * 2];
					vertices[l++] = mPoints[i][j * 2 + 1];
					vertices[l++] = mTexCoords[i][j * 2];
					vertices[l++] = mTexCoords[i][j * 2 + 1];
				}
			}
			mMesh[i].setVertices(vertices);

			short[] indices = new short[mNumVerticesPerColumn];
			for (short j = 0; j < mNumVerticesPerColumn; j++) {
				indices[j] = j;
			}

			mMesh[i].setIndices(indices);

			mMesh[i].render(shader, GL20.GL_TRIANGLE_STRIP);
		}
	}

	int getHeight() {
		return mTexture.getHeight();
	}

	void setPosition(float x, float y) {
		if (!useNewFlame) {
			x += 14;
		}
		camera.translate(-x, -y, 0);

		mPositionX = x;
		mPositionY = y;
	}

	void initFlameState() {
		mFlameActive = true;
		mFrameCount = 0;

		mNumHeightLevels = 16;
		mNumColumns = 8;
		mNumVerticesPerColumn = 2 * mNumHeightLevels;
		mNumVertices = mNumColumns * mNumVerticesPerColumn;

		int[] dims = new int[] { mNumColumns, 2 * mNumVerticesPerColumn };
		mPoints = (float[][]) Array.newInstance(Float.TYPE, dims);
		mTexCoords = (float[][]) Array.newInstance(Float.TYPE, dims);

		mOuterLeftPoints = new float[2 * mNumHeightLevels];
		mOuterRightPoints = new float[2 * mNumHeightLevels];

		if (!useNewFlame) {
			mFlameBottomBorder = 150.0F;
			mFlameTopBorder = 480.0F;
			mFlameLeftBorder = 107.0F;
			mFlameRightBorder = 203.0F;
		} else {
			mFlameBottomBorder = 175.0F;
			mFlameTopBorder = 422.0F;
			mFlameLeftBorder = 122.0F;
			mFlameRightBorder = 230.0F;
		}

		mStepSizeTexCoordY = (1.0F / mNumHeightLevels);
		mTargetStepSizeVertexY = (1.0F / mNumHeightLevels);
		mMinStepSizeVertexY = (0.4F * mTargetStepSizeVertexY);
		mStepSizeVertexY = mMinStepSizeVertexY;

		mMinU = 0.2F;
		mMaxU = 0.8F;
		mMinV = 0.0F;
		mMaxV = (1.0F - mStepSizeTexCoordY);

		mWindForceDirX = 0.0F;
		mWindForceDirY = 0.0F;
		mWindForceDirZ = 0.0F;

		// Buoyancy
		mBuoyancyDirX = 0.0F;
		mBuoyancyDirY = 1.0F;
		mBuoyancyDirZ = 0.0F;

		mLeftCubicInterpolator2D.init(4);
		mRightCubicInterpolator2D.init(4);

		float f1 = mFlameTopBorder - mFlameBottomBorder;
		float f2 = 0.5F * (mFlameLeftBorder + mFlameRightBorder);
		float f3 = mFlameBottomBorder;
		mFlameSpineSimulator3D.init(5, 0.7F * f1, f2, f3, 0.0F);

		mNumTouchParticles = 5;
		mTouchParticles = new float[2 * this.mNumTouchParticles];
		mTouchParticleFactors = new float[this.mNumTouchParticles];
		mMinTouchParticleFactor = 0.025F;
		mMaxTouchParticleFactor = 1.0F;
		mTouchParticleIndex = 0;

		resetFlame();
	}

	void resetFlame() {
		mFrameCount = 0;

		mStepSizeVertexY = mMinStepSizeVertexY;

		float f1 = mFlameLeftBorder;
		float f2 = (mFlameRightBorder - mFlameLeftBorder) / mNumColumns;
		float f3 = mMinU;
		float f4 = (mMaxU - mMinU) / mNumColumns;
		for (int i = 0; i < mNumColumns; i++) {
			int m = 0;
			while (m < this.mNumHeightLevels) {
				int n = m * 2;
				int i1 = n * 2;
				mPoints[i][i1] = f1;
				mPoints[i][(i1 + 1)] = mFlameBottomBorder;
				mPoints[i][(i1 + 2)] = (f1 + f2);
				mPoints[i][(i1 + 3)] = mFlameBottomBorder;
				mTexCoords[i][i1] = f3;
				mTexCoords[i][(i1 + 1)] = mMaxV;
				mTexCoords[i][(i1 + 2)] = (f3 + f4);
				mTexCoords[i][(i1 + 3)] = mMaxV;

				if (i == 0) {
					mOuterLeftPoints[n] = mPoints[i][i1];
					mOuterLeftPoints[(n + 1)] = mPoints[i][(i1 + 1)];
				} else if (mNumColumns - 1 == i) {
					mOuterRightPoints[n] = mPoints[i][(i1 + 2)];
					mOuterRightPoints[(n + 1)] = mPoints[i][(i1 + 3)];
				}

				m++;
			}
			f1 += f2;
			f3 += f4;
		}

		mFlameSpineSimulator3D.reset();
	}

	void updateFrame() {
		if (!mFlameActive) {
			return;
		}

		mFrameCount++;
		if ((mFrameCount % 20) != 0) {
			// return;
		}

		float f1 = 1.0F;
		int new_flame = 0;
		if (mFrameCount < 30) {
			new_flame = 1;
			f1 = mStepSizeVertexY / mTargetStepSizeVertexY;
			mStepSizeVertexY = mStepSizeVertexY * (2.0F - f1);
			if (mStepSizeVertexY > mTargetStepSizeVertexY)
				mStepSizeVertexY = mTargetStepSizeVertexY;
		}

		for (int ii = 0; ii < 1; ii++) {
			setFlameForces();
		}

		for (int ii = 0; ii < 1; ii++) {
			// Buoyancy
			float f2 = 1.001F + mBuoyancyDirY;
			if (f2 > 1.0F)
				f2 = 1.0F;
			else if (f2 < 0.0F)
				f2 = 0.0F;

			if (true) {
				float f3 = mMinStepSizeVertexY * (1.0F - f2) + f2
						* mTargetStepSizeVertexY;
				this.mStepSizeVertexY += 0.1F * (f3 - mStepSizeVertexY);
				this.mFlameSpineSimulator3D.update();
				int j = mFlameSpineSimulator3D.getNumSpinePoints();
				float[] leftSpinePoints = mFlameSpineSimulator3D
						.getLeftSpinePoints();
				float[] rightSpinePoints = mFlameSpineSimulator3D
						.getRightSpinePoints();
				mLeftCubicInterpolator2D.updateControlPointsFromSpine3D(
						leftSpinePoints, j, mBuoyancyDirX, mBuoyancyDirY);
				mRightCubicInterpolator2D.updateControlPointsFromSpine3D(
						rightSpinePoints, j, mBuoyancyDirX, mBuoyancyDirY);

				float f4 = mStepSizeVertexY;
				for (int k = 1; k < mNumHeightLevels; k++) {
					int i42 = k * 2;
					mLeftCubicInterpolator2D.evaluate(f4,
							cubicInterpolatorOutput);
					mOuterLeftPoints[i42] = cubicInterpolatorOutput[0];
					mOuterLeftPoints[(i42 + 1)] = cubicInterpolatorOutput[1];

					mRightCubicInterpolator2D.evaluate(f4,
							cubicInterpolatorOutput);
					mOuterRightPoints[i42] = cubicInterpolatorOutput[0];
					mOuterRightPoints[(i42 + 1)] = cubicInterpolatorOutput[1];

					f4 += mStepSizeVertexY;
				}
			}

			if (true) {
				float f5 = (mMaxU - mMinU) / mNumColumns;
				float f6 = mStepSizeTexCoordY;
				float f7 = mMinU;
				float f8 = 0.0F;
				float f9 = 1.0F / mNumColumns;
				for (int n = 0; n < mNumColumns; n++) {
					float f57 = mMaxV;
					float f58 = 0.0F;
					float f59 = f8 + f9;
					for (int i37 = 1; i37 < mNumHeightLevels; i37++) {
						int i39 = i37 * 2;
						int i40 = i39 * 2;
						float f60 = (1.0F - f8) * mOuterLeftPoints[i39] + f8
								* mOuterRightPoints[i39];
						float f61 = (1.0F - f58) * mOuterLeftPoints[(i39 + 1)]
								+ f58 * mOuterRightPoints[(i39 + 1)];
						float f62 = (1.0F - f59) * mOuterLeftPoints[i39] + f59
								* mOuterRightPoints[i39];
						mPoints[n][i40] = f60;
						mPoints[n][(i40 + 1)] = f61;
						mPoints[n][(i40 + 2)] = f62;
						mPoints[n][(i40 + 3)] = f61;
						f57 -= f6;
						mTexCoords[n][i40] = f7;
						mTexCoords[n][(i40 + 1)] = f57;
						mTexCoords[n][(i40 + 2)] = (f7 + f5);
						mTexCoords[n][(i40 + 3)] = f57;
						if (new_flame != 0) {
							float f63 = f7;
							float f64 = f7 + f5;
							mTexCoords[n][i40] -= 0.2F * ((1.0F - f1) * (f63 - 0.5F));
							int i41 = i40 + 2;
							mTexCoords[n][i41] -= 0.2F * ((1.0F - f1) * (f64 - 0.5F));
						}
						f58 += mStepSizeTexCoordY;
					}
					f7 += f5;
					f8 += f9;
				}
			}
		}

		// BlowForce

		// BlowStrength

		// TouchParticles

		// random shake with mFrameCount
		if (true) {
			for (int i4 = 0; i4 < mNumColumns; i4++) {
				float f11 = -1.0F;
				float f12 = mPoints[i4][0];
				float f13 = mPoints[i4][2];
				float f14 = 0.13F * ((float) Math
						.sin(0.17F * (f12 + mFrameCount)) * mStepSizeTexCoordY);
				float f15 = 0.13F * ((float) Math
						.sin(0.17F * (f13 + mFrameCount)) * mStepSizeTexCoordY);
				float f16 = 0.16F * ((float) Math.cos(0.37F * mFrameCount) * mStepSizeTexCoordY);
				float f17 = 0.1F * ((float) Math.sin(0.27F * mFrameCount) * mStepSizeTexCoordY);
				for (int i10 = 1; i10 < mNumHeightLevels; i10++) {
					int i12 = 2 * (i10 * 2);
					float f18 = 1.0F - f11 * f11;
					mTexCoords[i4][i12] += f16 * f18;
					float[] arrayOfFloat6 = mTexCoords[i4];
					int i13 = i12 + 1;
					arrayOfFloat6[i13] += f18 * (f14 + f17);
					float[] arrayOfFloat7 = mTexCoords[i4];
					int i14 = i12 + 2;
					arrayOfFloat7[i14] += f16 * f18;
					float[] arrayOfFloat8 = mTexCoords[i4];
					int i15 = i12 + 3;
					arrayOfFloat8[i15] += f18 * (f15 + f17);
					f11 += 2.0F * mStepSizeTexCoordY;
				}
			}
		}

		// mMinTouchParticleFactor
	}

	public void activateFlame() {
		mFlameActive = true;
	}

	void deactivateFlame() {
		mFlameActive = false;
	}

	public void setFlameForces() {
		if (!mFlameActive)
			return;

		int n;
		if (Math.abs(mBuoyancyDirX) > 0.5f) {
			n = 3;
		} else if (Math.abs(mBuoyancyDirX) > 0.2f) {
			n = 2;
		} else {
			n = 1;
		}
		for (int i = 0; i < n; i++) {
			mFlameSpineSimulator3D.applyBuoyancyXYZ(mBuoyancyDirX,
					mBuoyancyDirY, mBuoyancyDirZ);
		}

		mFlameSpineSimulator3D.applyWindForceXYZ(1500.0F * mWindForceDirX,
				1500.0F * mWindForceDirY, 1500.0F * mWindForceDirZ);

		if (mTouchSensorActive) {
			float f1 = 0.5F * (mFlameLeftBorder + mFlameRightBorder);
			float f2 = 1.0F - Math.abs(mTouchSensorPosX - f1) / f1;
			mFlameSpineSimulator3D.setRadialForceXY(mTouchSensorPosX,
					mTouchSensorPosY, 2.0F * mTouchSensorVelX,
					2.0F * mTouchSensorVelY, mTouchSensorRadius, f2
							* mTouchSensorForceFactor);
		}
	}

	public void setBuoyancyDir(float dirX, float dirY, float dirZ) {
		// Log.v(TAG, "x = " + dirX + ", y = " + dirY);
		mBuoyancyDirX = dirX;
		mBuoyancyDirY = dirY;
		mBuoyancyDirZ = dirZ;
	}

	public void setWindForce(float paramFloat1, float paramFloat2,
			float paramFloat3) {
		mWindForceDirX = paramFloat1;
		mWindForceDirY = paramFloat2;
		mWindForceDirZ = paramFloat3;
	}

	public void clearFilteredAccelValuesXY() {
		for (int i = 0; i < maxNumFilterAccelValues; i++) {
			accelXArray[i] = 0.0F;
			accelYArray[i] = 0.0F;
		}
		accelValueIndex = 0;
		numFilterAccelValues = 0;
	}

	public void addFilteredAccelValueXY(float paramFloat1, float paramFloat2) {
		this.accelXArray[this.accelValueIndex] = paramFloat1;
		this.accelYArray[this.accelValueIndex] = paramFloat2;
		this.accelValueIndex = (1 + this.accelValueIndex);
		if (this.accelValueIndex >= this.maxNumFilterAccelValues)
			this.accelValueIndex = 0;
		if (this.numFilterAccelValues < this.maxNumFilterAccelValues)
			this.numFilterAccelValues = (1 + this.numFilterAccelValues);
	}

	public void setSensorAcceleration(float x, float y, float z) {
		// Log.v(TAG, "x = " + x);
		addFilteredAccelValueXY(x, y);
		computeFilteredAccelXY();
		float f1 = filteredAccelX;
		float f2 = filteredAccelY;
		sensorVelX = f1;
		sensorVelY = f2;
		sensorVelZ = z;
		setWindForce(-sensorVelX, -sensorVelY, -sensorVelZ);
	}

	public void computeFilteredAccelXY() {
		float f1 = 0.0F;
		float f2 = 0.0F;
		float f3 = 1.0F;
		float f4 = 0.0F;
		int i = accelValueIndex;
		for (int j = 0; j < numFilterAccelValues; j++) {
			i--;
			if (i < 0)
				i = maxNumFilterAccelValues - 1;
			f1 += f3 * accelXArray[i];
			f2 += f3 * accelYArray[i];
			f4 += f3;
			f3 *= 0.5F;
		}
		filteredAccelX = (f1 / f4);
		filteredAccelY = (f2 / f4);
	}

	public void handleTouchSensorOnBegin(float x, float y) {
		x = x - mPositionX;
		y = y - mPositionY;

		mTouchSensorActive = true;
		mTouchSensorForceFactor = 7.5F;
		mTouchSensorRadius = 85.0F;
		mTouchSensorRadiusSquared = (mTouchSensorRadius * mTouchSensorRadius);
		mTouchSensorPosX = x;
		mTouchSensorPosY = y;
	}

	public void handleTouchSensorOnEnd() {
		mTouchSensorActive = false;
		mTouchParticles[(2 * mTouchParticleIndex)] = mTouchSensorPosX;
		mTouchParticles[(1 + 2 * mTouchParticleIndex)] = mTouchSensorPosY;
		mTouchParticleFactors[mTouchParticleIndex] = mMaxTouchParticleFactor;
		mTouchParticleIndex = (1 + mTouchParticleIndex);
		if (mTouchParticleIndex > mNumTouchParticles - 1)
			mTouchParticleIndex = 0;
	}

	public void handleTouchSensorOnMove(float x, float y) {
		x = x - mPositionX;
		y = y - mPositionY;

		if (false) {
			mTouchSensorVelX = (x - mTouchSensorPosX);
			mTouchSensorVelY = (y) - mTouchSensorPosY;
			mTouchSensorPosX = x;
			mTouchSensorPosY = y;
			mTouchParticles[(2 * mTouchParticleIndex)] = mTouchSensorPosX;
			mTouchParticles[(1 + 2 * mTouchParticleIndex)] = mTouchSensorPosY;
			mTouchParticleFactors[mTouchParticleIndex] = (0.05F * mMaxTouchParticleFactor);
			mTouchParticleIndex = (1 + mTouchParticleIndex);
			if (mTouchParticleIndex > mNumTouchParticles - 1)
				mTouchParticleIndex = 0;
		}
	}
}