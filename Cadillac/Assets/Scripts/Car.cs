using UnityEngine;
using System.Collections;

public class Car : MonoBehaviour {
	public static float currentSpeed = 0;
	public static float distanceTraveled;
	public GameObject cameraTo;
	public GameObject cameraOrigin;
//	public float minSpeed ;
//	public float maxSpead ;
	public float acceleration ;

	void Start () {
		GameEventManager.TestScene +=  TestScene;
		GameEventManager.GameOver +=  GameOver;
	}

	void Update() {
		//Debug.Log(currentSpeed.ToString());

		this.gameObject.transform.Translate( -Time.deltaTime * currentSpeed , 0, 0);
		distanceTraveled = Mathf.Abs(transform.localPosition.x);

//			if (currentSpeed >= minSpeed && currentSpeed <= maxSpead) {
//				currentSpeed +=  acceleration;
//			}

//			 if(distanceTraveled > 2000) {
//				currentSpeed = 0;// stop
//			}

		//Debug.Log(distanceTraveled.ToString());
	}

	// 训练场
	private void TestScene () {
		CameraScript cs = Camera.main.GetComponent<CameraScript> ();
		cs.enabled = false;

		TweenPosition tp = GetComponent<TweenPosition>();
		tp.Toggle();
		EventDelegate.Add (tp.onFinished, GameOver);

		WheelRot [] wheel = gameObject.GetComponentsInChildren<WheelRot> ();
		foreach (WheelRot w in wheel) {
			w.carStatus = WheelRot.CarStatus.forward;		
		}
	}

	public void GameOver(){
		WheelRot [] wheel = gameObject.GetComponentsInChildren<WheelRot> ();
		foreach (WheelRot w in wheel) {
			w.carStatus = WheelRot.CarStatus.stop;		
		}

		TweenTransform tt = Camera.main.GetComponent<TweenTransform> ();
		tt.to = cameraOrigin.transform;
		tt.Toggle ();
		EventDelegate.Add (tt.onFinished, ReuseCameraScript);

	}

	void ReuseCameraScript() {
		CameraScript cs = Camera.main.GetComponent<CameraScript> ();
		cs.enabled = true;
	}
}
