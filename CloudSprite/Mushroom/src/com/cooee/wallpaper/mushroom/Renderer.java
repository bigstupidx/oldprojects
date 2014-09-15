package com.cooee.wallpaper.mushroom;

import android.content.Context;

import com.cooee.wallpaper.common.CommonRenderer;
import com.cooee.wallpaper.framework.Logger;

public class Renderer extends CommonRenderer {
	private final static String TAG = "Renderer";

	public Renderer(Context context) {
		super(context);
		
		// set iRenderer
		// iRenderer = MushRoom.getInstance(context);
		iRenderer = new MushRoom(context);

		Logger.log(TAG, "new Renderer");
	}
}
