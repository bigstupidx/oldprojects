using UnityEngine;
using System.Collections;

public class _Rotate : MonoBehaviour {

	public float m_rotatespeed;

	void Update () {
		transform.RotateAround(Vector3.zero, Vector3.up, Time.deltaTime * m_rotatespeed);
	}
}
