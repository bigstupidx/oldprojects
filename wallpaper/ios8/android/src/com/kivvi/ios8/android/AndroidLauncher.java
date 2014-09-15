package com.kivvi.ios8.android;

import android.os.Bundle;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.kivvi.ios8.IOS8;

public class AndroidLauncher extends AndroidApplication {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		com.badlogic.gdx.Configs.setAssetEncrypt(false);
		config.useWakelock = true;
		config.numSamples = 4;
		config.useAccelerometer = true;
		initialize(new IOS8(), config);
	}
}
