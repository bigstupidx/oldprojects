using UnityEngine;
using System.Collections;

public class WheelRot : MonoBehaviour {
	public WheelType type = WheelType.left;
	public CarStatus carStatus; // stop, foward, backward
	public float carSpeed = 50;
	public float rotateFactor = 0.2f;


	public enum CarStatus{
		stop, 
		forward, 
		backward,
	};

	public enum WheelType{
		left, 
		right, 
	};

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (carStatus == CarStatus.stop) {

		} else if (carStatus == CarStatus.backward) {
			Quaternion curr = transform.localRotation;
			float factor = 1;
			if (type == WheelType.right) factor = -1;
			Quaternion rot = Quaternion.Euler (0, 0, factor * carSpeed * rotateFactor);
			transform.localRotation = curr * rot;
		} else if (carStatus == CarStatus.forward) {
			Quaternion curr = transform.localRotation;
			float factor = 1;
			if (type == WheelType.right) factor = -1;
			Quaternion rot = Quaternion.Euler (0, 0, - factor * carSpeed * rotateFactor);
			transform.localRotation = curr * rot;
		} else {
			Debug.Log("Cannot get here!!");
		}

	}
}
