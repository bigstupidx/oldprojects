package com.cooee.wallpaper.mushroom;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;

import com.cooee.wallpaper.framework.AAConfigChooser;

public class MainActivity extends Activity {

	private GLSurfaceView mGLView;
	private Renderer renderer = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// no title
		requestWindowFeature(Window.FEATURE_NO_TITLE);

		// set full screen
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		mGLView = new GLSurfaceView(getApplication());
		if (WallpaperService.useGLES2) {
			// Enable the OpenGL ES2.0 context
			mGLView.setEGLContextClientVersion(2);
			mGLView.setEGLConfigChooser(new AAConfigChooser(2, true));
		} else {
			mGLView.setEGLConfigChooser(new AAConfigChooser(1, true));
		}

		renderer = new Renderer(this);
		mGLView.setRenderer(renderer);
		mGLView.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				renderer.onTouchEvent(event);
				return true;
			}
		});
		setContentView(mGLView);
	}

	@Override
	protected void onPause() {
		super.onPause();

		mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();

		mGLView.onResume();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();

		// remove all textures
		// HashSet<String> names = TextureManager.getInstance().getNames();
		// for (String name : names) {
		// TextureManager.getInstance().removeTexture(name);
		// }
	}
}
