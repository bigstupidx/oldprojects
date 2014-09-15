package com.kivvi.crystalswan.client;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.backends.gwt.GwtApplication;
import com.badlogic.gdx.backends.gwt.GwtApplicationConfiguration;
import com.kivvi.crystalswan.CrystalSwan;

public class HtmlLauncher extends GwtApplication {

	@Override
	public GwtApplicationConfiguration getConfig() {
		GwtApplicationConfiguration config = new GwtApplicationConfiguration(
				360, 600);
		config.antialiasing = true;
		return config;
	}

	@Override
	public ApplicationListener getApplicationListener() {
		return new CrystalSwan();
	}
}