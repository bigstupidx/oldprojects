package com.kivvi.avoidthecircles.utils;

import java.util.Random;

public class RandTool {
	public Random rand;

	public RandTool() {
		rand = new Random(System.currentTimeMillis());
	}

	public int nextInt() {
		return rand.nextInt();
	}

	public int nextInt(int n) {
		return rand.nextInt(n);
	}

	public float nextFloat() {
		return rand.nextFloat();
	}
}
