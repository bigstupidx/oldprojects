using UnityEngine;

public class GUIManager : MonoBehaviour
{
		public GameObject _MainMenuScene;
		public GameObject _GarageScene;
		public GameObject _UpgradeScene;
		public GameObject _GameStartScene;
		public GameObject _TrainingScene;
		public GameObject _TestScene;
		public GameObject _Popup;
		public GameObject _Title;
		public Transform PositionA, PositionB, PositionC;

		public enum GameState
		{
				GameStart,
				GameOver,
				MainMenuScene,
				GarageScene,
				UpgradeScene,
				TrainingScene,
				TestScene,
		};

		private static GameState _currentState = GameState.GameStart;

		public static GameState GetGameState ()
		{
				return _currentState;
		}

		public GameState currentState {
				get {
						return _currentState;
				}

				set {
						_currentState = value;

						// set tile
						Component[] labels = _Title.GetComponentsInChildren<UILabel> ();
						string [] titles = new string[] {
								"Start",
								"Over",
								"Main Menu",
								"Garage",
								"Upgrade",
								"Train",
								"Test"
						};
						((UILabel)labels [1]).text = MultiLanguage.get (titles [(int)_currentState]);
						//Debug.Log ("title = " + labels [1].text);
				}
		}

		void Start ()
		{
				GameEventManager.GameStart += GameStart;
				GameEventManager.GameOver += GameOver;
				GameEventManager.MainMenuScene += MainMenuScene;
				GameEventManager.GarageScene += GarageScene;
				GameEventManager.UpgradeScene += UpgradeScene;
				GameEventManager.TrainingScene += TrainingScene;
				GameEventManager.TestScene += TestScene;
				_GameStartScene.SetActive (true);
		}

		// 启动页
		private void GameStart ()
		{
				_GameStartScene.SetActive (true);
				currentState = GUIManager.GameState.GameStart;
				TweenTransform.Begin (_MainMenuScene, 0.5f, PositionA, PositionB);
		}

		// 主菜单
		private void MainMenuScene ()
		{
				_GameStartScene.SetActive (false);

				if (currentState == GUIManager.GameState.GarageScene) {
						TweenTransform.Begin (_GarageScene, 0.5f, PositionA, PositionB);
						TweenTransform.Begin (_MainMenuScene, 0.5f, PositionB, PositionA);
				} else if (currentState == GUIManager.GameState.TrainingScene) {
						_TrainingScene.SetActive (false);
				} else if (currentState == GUIManager.GameState.TestScene) {
						_Popup.SetActive (false);
						Car.currentSpeed = 0;
						TweenTransform.Begin (_MainMenuScene, 0.5f, PositionB, PositionA);
				}

				TweenTransform.Begin (_MainMenuScene, 0.5f, PositionB, PositionA);
				currentState = GUIManager.GameState.MainMenuScene;
		}

		// 我的车库
		private void GarageScene ()
		{
				if (currentState == GUIManager.GameState.UpgradeScene) {
						TweenTransform.Begin (_UpgradeScene, 0.5f, PositionA, PositionB);
						TweenTransform.Begin (_GarageScene, 0.5f, PositionB, PositionA);
				}
				TweenTransform.Begin (_GarageScene, 0.5f, PositionB, PositionA);
				TweenTransform.Begin (_MainMenuScene, 0.5f, PositionA, PositionB);
				currentState = GUIManager.GameState.GarageScene;
		}

		// 改装
		private void UpgradeScene ()
		{
				TweenTransform.Begin (_UpgradeScene, 0.5f, PositionB, PositionA);
				TweenTransform.Begin (_GarageScene, 0.5f, PositionA, PositionB);
				currentState = GUIManager.GameState.UpgradeScene;
		}

		// 培训
		private void TrainingScene ()
		{
				_TrainingScene.SetActive (true);
				TweenTransform.Begin (_MainMenuScene, 0.5f, PositionA, PositionB);
				currentState = GUIManager.GameState.TrainingScene;
		}

		// 训练场
		private void TestScene ()
		{
				TweenTransform.Begin (_MainMenuScene, 0.5f, PositionA, PositionB);

				currentState = GUIManager.GameState.TestScene;
		}

		private void GameOver ()
		{
		}

}