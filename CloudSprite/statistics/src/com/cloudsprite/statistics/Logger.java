package com.cloudsprite.statistics;

import android.util.Log;

public class Logger {
	static final String TAG = "statistics";

	static public void log(String message) {
		Log.v(TAG, message);
	}
}
