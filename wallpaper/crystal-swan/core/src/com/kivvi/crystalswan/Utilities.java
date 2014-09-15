package com.kivvi.crystalswan;

import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector3;

public class Utilities {
	public static Matrix4 getReflectedCamera(Plane plane) {
		Matrix4 ret = new Matrix4();
		float[] val = ret.val;
		Vector3 n = plane.normal;
		float d = plane.d;
		val[0] = 1.0f - 2.0f * n.x * n.x;
		val[1] = -2.0f * n.x * n.y;
		val[2] = -2.0f * n.x * n.z;
		val[3] = 0;

		val[4] = -2.0f * n.x * n.y;
		val[5] = 1.0f - 2.0f * n.y * n.y;
		val[6] = -2.0f * n.y * n.z;
		val[7] = 0;

		val[8] = -2.0f * n.x * n.y;
		val[9] = -2.0f * n.y * n.z;
		val[10] = 1.0f - 2.0f * n.z * n.z;
		val[11] = 0;

		val[12] = 2.0f * n.x * d;
		val[13] = 2.0f * n.y * d;
		val[14] = 2.0f * n.z * d;
		val[15] = 1.0f;

		return ret;
	}
}
