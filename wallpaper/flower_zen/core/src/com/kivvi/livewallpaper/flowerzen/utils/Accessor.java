package com.kivvi.livewallpaper.flowerzen.utils;

import aurelienribon.tweenengine.TweenAccessor;



public class Accessor implements TweenAccessor<CamController> {
	public static final int POSITION_X = 1;

	public int getValues(CamController target, int tweenType, float[] returnValues) {
		switch (tweenType) {
		case POSITION_X:
			returnValues[0] = target.currentCamPos;
			return 1;
		default:
			assert false;
			return -1;
		}
	}

	public void setValues(CamController target, int tweenType, float[] newValues) {
		 switch (tweenType) {
         case POSITION_X: target.currentCamPos = newValues[0]; break;
         default: assert false; break;
     }

	}

	

}
