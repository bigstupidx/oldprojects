public static class GameEventManager {

	public delegate void GameEvent();

	public static event GameEvent GameStart,GameOver,MainMenuScene,GarageScene, UpgradeScene ,TrainingScene,TestScene;

	public static void TriggerGameStart(){

		if(GameStart != null){
			GameStart();

		}
	}

	public static void TriggerMainMenuScene(){
		if(MainMenuScene != null){
			MainMenuScene();
		}
	}
	public static void TriggerGarageScene(){
		if(GarageScene != null){
			GarageScene();
		}
	}
	public static void TriggerUpgradeScene(){

		if(UpgradeScene != null){
			UpgradeScene();
		
		}
	}


	public static void TriggerTrainingScene(){
		if(TrainingScene != null){
			TrainingScene();
		}
	}
	public static void TriggerTestScene(){
		if(TestScene != null){
			TestScene();
		}
	}
	
	public static void TriggerGameOver(){
		if(GameOver != null){
			GameOver();
		}
	}
}