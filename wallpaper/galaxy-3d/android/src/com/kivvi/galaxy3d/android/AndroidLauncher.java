package com.kivvi.galaxy3d.android;

import android.os.Bundle;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.kivvi.galaxy3d.Galaxy3D;

public class AndroidLauncher extends AndroidApplication {
	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		com.badlogic.gdx.Configs.setAssetEncrypt(false);
		AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		initialize(new Galaxy3D(), config);
	}
}
