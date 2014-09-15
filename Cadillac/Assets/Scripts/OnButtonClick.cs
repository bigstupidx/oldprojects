using UnityEngine;
using System.Collections;

public class OnButtonClick : MonoBehaviour
{
		private string m_name ;

		void Start ()
		{
				m_name = this.gameObject.name;
		}

		void OnClick ()
		{
				Debug.Log (m_name + " is clicked.");

				if (m_name == "Play Button") {
						// 进入游戏
						GameEventManager.TriggerMainMenuScene ();
				} else if (m_name == "Back Button") {
						// 返回
						switch (GUIManager.GetGameState ()) {
						case GUIManager.GameState.MainMenuScene:
								GameEventManager.TriggerGameStart ();
								break;
						case GUIManager.GameState.GarageScene:
								GameEventManager.TriggerMainMenuScene ();
								break;
						case GUIManager.GameState.UpgradeScene:
								GameEventManager.TriggerGarageScene ();					
								break;
						case GUIManager.GameState.TrainingScene:
								GameEventManager.TriggerMainMenuScene ();					
								break;
						case GUIManager.GameState.TestScene:
								GameEventManager.TriggerGameOver ();
								GameEventManager.TriggerMainMenuScene ();					
								break;
						}
				} else if (m_name == "Garage Button") {
						// 我的车库
						GameEventManager.TriggerGarageScene ();
				} else if (m_name == "Upgrade Button") {
						// 改装
						GameEventManager.TriggerUpgradeScene ();
				} else if (m_name == "Train Button") {
						// 培训
						GameEventManager.TriggerTrainingScene ();
				} else if (m_name == "Test Button") {
						// 
						GameEventManager.TriggerTestScene ();
				}

				Debug.Log ("Current Sence is  " + GUIManager.GetGameState ().ToString ());
		}

		public void SetButtonName (string name)
		{
				m_name = name;
		}

		public string getName ()
		{
				return m_name;
		}
}
