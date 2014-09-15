package com.kivvi.theline.actors;

import com.kivvi.theline.resource.Data;

public class TouchPad extends Block {
	public TouchPad() {
		super("touchpad");
		float w = Data.touchPadWidth;
		float h = Data.touchPadHeight;
		setColor(0.298f, 0.85f, 0.392f, 1);
		setSize(w, h);
	}
}
