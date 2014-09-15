using UnityEngine;
using System.Collections.Generic;

// 生成道路
public class GroundManager : MonoBehaviour {
	
	public Transform prefab;
	public int numberOfObjects;
	public float recycleOffset;
	public Vector3 startPosition;
	public float groudLength;
	
	private Vector3 nextPosition;
	private Queue<Transform> objectQueue;
	//private bool isbegin = false;
	
	void Start () {

		// 在start里创建不太好。

		GameEventManager.TestScene +=  TestScene;
		GameEventManager.GameOver +=  GameOver;

			objectQueue = new Queue<Transform>(numberOfObjects);
			nextPosition = startPosition;
			for (int i = 0; i < numberOfObjects; i++) {
				Transform o = (Transform)Instantiate(prefab);
				o.localPosition = nextPosition ;
				nextPosition.x -= o.localScale.x;;  // 40
				objectQueue.Enqueue(o);
			}
	


	}

	private void TestScene () {
		Debug.Log(this.name + " event is called.");
		//isbegin = true;


	}

	private void GameOver () {
		// TODO
	}
	
	void Update () {

		if (Mathf.Abs(objectQueue.Peek().localPosition.x + recycleOffset) < Car.distanceTraveled ) {
			Transform o = objectQueue.Dequeue();
			o.localPosition = nextPosition ;
			nextPosition.x -= o.localScale.x;;
			objectQueue.Enqueue(o);
		}
	}
}