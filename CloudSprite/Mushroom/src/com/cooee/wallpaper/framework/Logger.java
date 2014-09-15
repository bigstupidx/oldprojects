package com.cooee.wallpaper.framework;

import java.util.HashMap;

import android.util.Log;

public class Logger {
	private static final String TAG = "wallpaper";
	public static final int ERROR = 0;
	public static final int WARNING = 1;
	public static final int MESSAGE = 2;
	public static final int DEBUG = 3;

	public static final int ON_ERROR_THROW_EXCEPTION = 2;
	public static final int ON_ERROR_EXIT = 1;
	public static final int ON_ERROR_RESUME_NEXT = 0;

	public static final int LL_ONLY_ERRORS = 0;
	public static final int LL_ERRORS_AND_WARNINGS = 1;
	public static final int LL_VERBOSE = 2;
	public static final int LL_DEBUG = 3;

	private static int mode = ON_ERROR_THROW_EXCEPTION;
	private static int logLevel = LL_VERBOSE;
	private static final String[] HEAD = { "ERROR: ", "WARNING: ", "MESSAGE: " };

	public static HashMap<String, Long> map = new HashMap<String, Long>();

	public static void setOnError(int mode) {
		Logger.mode = mode;
	}

	public static void setLogLevel(int level) {
		Logger.logLevel = level;
	}

	public static boolean isDebugEnabled() {
		return logLevel == LL_DEBUG;
	}

	static public void log(String message) {
		log(message, MESSAGE);
	}

	public static void log(String tag, String message) {
		log(tag, message, MESSAGE);
	}

	public static void log(String msg, int type) {
		log(TAG, msg, type);
	}

	public static void log(String tag, String msg, int type) {
		if (type <= logLevel) {
			if ((type < LL_ONLY_ERRORS) || (type > LL_DEBUG)) {
				type = LL_DEBUG;
			}
			if (type < LL_VERBOSE) {
				msg = "[ " + System.currentTimeMillis() + " ] - " + HEAD[type]
						+ msg;
			}

			if (tag == null)
				tag = TAG;
			Log.i(tag, msg);

			if (type == LL_ONLY_ERRORS) {
				if (mode == ON_ERROR_EXIT) {
					System.exit(-99);
				} else if (mode == ON_ERROR_THROW_EXCEPTION) {
					throw new RuntimeException(msg);
				}
			}
		}
	}

	public static void log(Throwable tw) {
		log(Log.getStackTraceString(tw), ERROR);
	}

	public static void log(Throwable tw, int type) {
		log(Log.getStackTraceString(tw), type);
	}

	public static void ps(String key) {
		if (map.containsKey(key)) {
			map.remove(key);
		}
		map.put(key, System.currentTimeMillis());
	}

	public static void pt(String key) {
		if (map.containsKey(key)) {
			Logger.log("Profile",
					"profile: "
							+ key
							+ " take "
							+ (System.currentTimeMillis() - map.get(key)
									.longValue()) + " ms");

			map.remove(key);
		}
	}
}
