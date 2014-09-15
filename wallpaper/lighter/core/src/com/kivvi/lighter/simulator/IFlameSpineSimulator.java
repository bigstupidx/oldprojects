package com.kivvi.lighter.simulator;

public abstract interface IFlameSpineSimulator {
	public abstract void init(int paramInt, float paramFloat1,
			float paramFloat2, float paramFloat3, float paramFloat4);

	public abstract void pause();

	public abstract void proceed();

	public abstract void reset();

	public abstract void shutdown();

	public abstract void update();
}
