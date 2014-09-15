package com.kivvi.ripples.livewallpapersettings;

import android.content.Context;
import android.preference.DialogPreference;
import android.util.AttributeSet;

public class MyDialogPreference extends DialogPreference{

	public MyDialogPreference(Context context, AttributeSet attrs) {
		super(context, attrs);
		setNegativeButtonText("");
	}

}
