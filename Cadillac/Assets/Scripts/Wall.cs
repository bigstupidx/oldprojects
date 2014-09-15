using UnityEngine;
using System.Collections;

public class Wall : MonoBehaviour {

	public GameObject _popup, _wallBack, _wallFront, _wallLeft, _wallRight, _wallFloor ;
	public Transform _wallBackTo, _wallFrontTo, _wallLeftTo, _wallRightTo;

	public float durationTime;
	void Start () {
		GameEventManager.TestScene 		+=  TestScene;
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	// 训练场
	private void TestScene () {
		Debug.Log(this.name + " event is called.");
		//_popup.SetActive(true);
		//TweenAlpha.Begin(_popup,3f, 0f);

		// wall anim


		//TweenRotation.Begin(_wallBack,0.5f,Quaternion.Euler(180, 0, 0));
		TweenTransform.Begin(_wallBack, durationTime, _wallBack.transform, _wallBackTo);
		TweenTransform.Begin(_wallFront, durationTime, _wallFront.transform, _wallFrontTo);
		TweenTransform.Begin(_wallLeft, durationTime, _wallLeft.transform, _wallLeftTo);
		TweenTransform.Begin(_wallRight, durationTime, _wallRight.transform, _wallRightTo);



	}
}
