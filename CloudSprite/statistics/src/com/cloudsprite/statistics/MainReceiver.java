package com.cloudsprite.statistics;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class MainReceiver extends BroadcastReceiver {

	/**
	 * Start MainService when receive: /
	 * 1. boot complete message 
	 * 2.
	 */
	@Override
	public void onReceive(Context context, Intent intent) {
		MainService.startService(context);
	}

}
