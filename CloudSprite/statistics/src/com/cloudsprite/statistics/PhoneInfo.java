package com.cloudsprite.statistics;

import java.lang.reflect.Constructor;
import java.net.URLEncoder;

import android.content.Context;
import android.telephony.TelephonyManager;

public class PhoneInfo {
	/** Get imei with sim id */
	public static String getImei(Context context, int sim_id) {
		String IMEI = null;
		if (sim_id == 0) {
			TelephonyManager telephonyManager = (TelephonyManager) context
					.getSystemService(Context.TELEPHONY_SERVICE);
			IMEI = telephonyManager.getDeviceId();
		} else {
			// SPD
			try {
				Constructor<TelephonyManager> cons = TelephonyManager.class
						.getDeclaredConstructor(Context.class, int.class);
				TelephonyManager instance = cons.newInstance(context, 1);
				IMEI = instance.getDeviceId();
			} catch (Exception e) {
				e.printStackTrace();
			}
			// MTK
			// if (IMEI == null) {
			// try {
			// Constructor<TelephonyManager> cons = TelephonyManager.class
			// .getDeclaredConstructor(Context.class);
			// TelephonyManager instance = cons.newInstance(context);
			// IPhoneSubInfo iPhoneSubInfo = (IPhoneSubInfo) invokeJarMethod(
			// "getSubscriberInfo", new Class[] { int.class },
			// new Object[] { 1 }, TelephonyManager.class,
			// instance);
			// IMEI = iPhoneSubInfo.getDeviceId();
			// } catch (Exception e) {
			// e.printStackTrace();
			// }
			// }
		}
		if (IMEI == null) {
			IMEI = "";
		}
		return IMEI;
	}

	/** Get imsi with sim id */
	public static String getImsi(Context context, int sim_id) {
		String IMSI = null;
		if (sim_id == 0) {
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Context.TELEPHONY_SERVICE);
			IMSI = tm.getSubscriberId();
		} else {
			// SPD
			try {
				Constructor<TelephonyManager> cons = TelephonyManager.class
						.getDeclaredConstructor(Context.class, int.class);
				TelephonyManager instance = cons.newInstance(context, 1);
				IMSI = instance.getSubscriberId();
			} catch (Exception e) {
				e.printStackTrace();
			}
			// MTK
			// if (IMSI == null) {
			// try {
			// Constructor<TelephonyManager> cons = TelephonyManager.class
			// .getDeclaredConstructor(Context.class);
			// TelephonyManager instance = cons.newInstance(context);
			// IPhoneSubInfo iPhoneSubInfo = (IPhoneSubInfo) invokeJarMethod(
			// "getSubscriberInfo", new Class[] { int.class },
			// new Object[] { 1 }, TelephonyManager.class,
			// instance);
			// IMSI = iPhoneSubInfo.getSubscriberId();
			// } catch (Exception e) {
			// e.printStackTrace();
			// }
			// }
		}
		if (IMSI == null) {
			IMSI = "";
		}
		return IMSI;
	}

	public static String getUrlParams(Context context) {
		String str = null;
		try {
			str = "?imei=" + URLEncoder.encode(getImei(context, 0), "UTF-8")
					+ "&imsi="
					+ URLEncoder.encode(getImsi(context, 0), "UTF-8")
					+ "&factory=" + URLEncoder.encode("a01", "UTF-8")
					+ "&device=" + URLEncoder.encode("mtk012", "UTF-8");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return str;
	}
}
