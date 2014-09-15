package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.graphics.g3d.attributes.BlendingAttribute;
import com.badlogic.gdx.utils.Disposable;
import com.kivvi.livewallpaper.flowerzen.utils.CamController;

public class Simulation  implements Disposable {
	private static final String TAG = Simulation.class.getName();

	SceneObject  background, 
				stone,
				petal_1,
				petal_2,
				flower_1,
				flower_2,
				branch_1,
				branch_2;

	
	public Simulation() {
		init();
	}

	// init game objects
	private void init() {
		background = new SceneObject(Assets.instance.model, "background");
		background.transform.setTranslation(0, -0.5f, 0);
		stone = new SceneObject(Assets.instance.model, "stone");
		stone.transform.setTranslation(0, 0, 0.4f);
		branch_1 = new SceneObject(Assets.instance.model, "branch-01");
		branch_2 = new SceneObject(Assets.instance.model, "branch-02");
		flower_1 = new SceneObject(Assets.instance.model, "flower-01");
		flower_1.materials.get(0).set(new BlendingAttribute(true , 1.0f));
		flower_2 = new SceneObject(Assets.instance.model, "flower-02");
		flower_2.materials.get(0).set(new BlendingAttribute(true , 0.9f));
		petal_1 = new SceneObject(Assets.instance.model, "petal-01");
		petal_2 = new SceneObject(Assets.instance.model, "petal-02");
		
		

	}
	
	/*
	 * To see how wallpaper scroll with screen
	 * 
	 * As i said before - you can't get count of screens, so, just try use (sW * 2 or * 3)
	 * to remove empty space on the screen.
	 * It's easiest and only way.
	 */
	
	public void update(float delta) {
//		Gdx.app.log(TAG, "deltaTime update");
	}
	
    
	@Override
	public void dispose() {
		Assets.instance.dispose();
	}
	

}
