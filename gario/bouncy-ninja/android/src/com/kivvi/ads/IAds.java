package com.kivvi.ads;

import android.app.Activity;
import android.view.View;

public interface IAds {
	public View getView();

	public void init(Activity activity);

	public void show();

	public void close();

	public void resume();

	public void pause();

	public void destroy();
}
