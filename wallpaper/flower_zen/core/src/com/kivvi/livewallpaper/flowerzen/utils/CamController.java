/*******************************************************************************
 * Copyright 2013 Andreas Oehlke
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

package com.kivvi.livewallpaper.flowerzen.utils;

import aurelienribon.tweenengine.Tween;
import aurelienribon.tweenengine.TweenManager;
import aurelienribon.tweenengine.equations.Linear;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.input.GestureDetector.GestureAdapter;
import com.badlogic.gdx.math.MathUtils;

public class CamController extends GestureAdapter {
	private static final String TAG = CamController.class.getName();

	private  float xOffset = 0f;
	public  float currentCamPos = 0f;
	public final float  MAX_DISTANCE = 0.2f;
	public final float  MIN_DISTANCE = 0.0f;

	private TweenManager tweenManager = new TweenManager();

	public CamController() {
		Tween.registerAccessor(CamController.class, new Accessor());
	}
	

	@Override
	public boolean fling(float velocityX, float velocityY, int button) {
		
//		Gdx.app.debug(TAG, "xOffset: " + Math.abs(xOffset));
//		Gdx.app.debug(TAG, "velocityX: " + velocityX);
//		Gdx.app.debug(TAG, "currentCamPos: " +currentCamPos);

		
		if (velocityX > 0) {
			if (currentCamPos < MAX_DISTANCE)
				Tween.to(this, Accessor.POSITION_X, 0.5f).ease(Linear.INOUT)
					.target( xOffset * MAX_DISTANCE).start(tweenManager);	
		}
		
		if (velocityX < 0)	{
			if (currentCamPos < MAX_DISTANCE)
				Tween.to(this, Accessor.POSITION_X, 0.5f).ease(Linear.INOUT)
				.target(xOffset * MAX_DISTANCE).start(tweenManager);	
		}
		
		return super.fling(velocityX, velocityY, button);
	}

	public void applyTo(PerspectiveCamera cam) {
		tweenManager.update(Gdx.graphics.getDeltaTime());
		cam.position.x = currentCamPos;
	}

	// FIXME 
	public void updateOffset(float xPixelOffset) {
		xOffset = xPixelOffset;
	}

}
