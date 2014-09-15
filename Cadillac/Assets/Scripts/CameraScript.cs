using UnityEngine;
using System.Collections;


public class CameraScript : MonoBehaviour {
	public GameObject car;

	public float distance = 10;
	public float dragSpeed = 8;
	public float threshold = 0;

	public float yMax = 10;
	public float yMin = 0;
	
	private Vector3 to;
	private Vector3 mLast;

	// Use this for initialization
	void Start () {
		to = new Vector3 (transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown(0)) {
			mLast = Input.mousePosition;
			//to = new Vector3 (transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
			return;
		}

		if (Input.GetMouseButton (0)) {
			Vector3 offset = Camera.main.ScreenToViewportPoint(Input.mousePosition - mLast);
			Vector3 mTranslation = new Vector3();
			mTranslation.y = offset.y * dragSpeed;

			to = to - mTranslation;
			Quaternion rotation = Quaternion.Euler(0, offset.x * dragSpeed * distance, 0);

			to = rotation * to;
			mLast = Input.mousePosition;
		}

		//if (!transform.localPosition.Equals (to)) {
			Vector3 p = Vector3.Slerp (transform.localPosition, to, Time.deltaTime);
			if (p.y > yMax) { 
				p.y = yMax;
				to.y = yMax;
			} else if (p.y < yMin) {
				p.y = yMin;
				to.y = yMin;
			}
			transform.localPosition = new Vector3(p.x, p.y, p.z);
			transform.LookAt (car.transform.localPosition);
		//}
		////transform.Translate(move, Space.World);
		//Vector3.Lerp
	}
}
