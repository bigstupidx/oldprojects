package com.kivvi.theline.actors;

import com.kivvi.theline.resource.Data;

public class JumpBlock extends Block {
	public JumpBlock() {
		super("jump");
		float w = Data.blockWidth;
		float h = Data.blockHeight;
		setColor(1, 0.11f, 0.262f, 1);
		setSize(w, h);
	}

}
