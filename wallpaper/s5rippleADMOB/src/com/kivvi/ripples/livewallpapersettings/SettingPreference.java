package com.kivvi.ripples.livewallpapersettings;

import com.kivvi.livewallpaper.ripples.R;

import android.os.Bundle;
import android.preference.PreferenceFragment;

public class SettingPreference extends PreferenceFragment{

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		addPreferencesFromResource(R.xml.preferences);
	}

}
