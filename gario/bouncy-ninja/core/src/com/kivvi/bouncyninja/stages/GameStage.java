package com.kivvi.bouncyninja.stages;

import com.badlogic.gdx.utils.viewport.FitViewport;
import com.kivvi.bouncyninja.resources.Data;

public class GameStage {
	private static CommonStage stage = null;

	public static CommonStage getStage() {
		if (stage == null) {
			if (Data.box2dDebug)
				stage = new CommonStage(new FitViewport(Data.width
						/ Data.box2dRadio, Data.height / Data.box2dRadio));
			else
				stage = new CommonStage(
						new FitViewport(Data.width, Data.height));
		}
		return stage;
	}

	public static void dispose() {
		stage.dispose();
		stage = null;
	}
}
