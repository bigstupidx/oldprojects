package com.kivvi.crystalswan.android;

import android.os.Bundle;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.kivvi.crystalswan.CrystalSwan;

public class AndroidLauncher extends AndroidApplication {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		///config.useCompass = false;
		config.numSamples = 4;
		CrystalSwan crystalSwan = new CrystalSwan();
		initialize(crystalSwan, config);
	}
}
