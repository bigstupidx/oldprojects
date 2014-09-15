package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.kivvi.livewallpaper.flowerzen.utils.IAnalyticsService;

public class LWPGame extends Game {
	private static final String TAG = LWPGame.class.getName();
	public Resolver resolver = null;
	public static IAnalyticsService statisticsService;

	@Override
	public void create() {
		setScreen(new MainScreen(this, resolver));
	}

	@Override
	public void dispose() {
		super.dispose();
		resolver = null;
		getScreen().dispose();
	}

	@Override
	public void pause() {
		super.pause();
		statisticsService.onPause();
		Gdx.app.debug(TAG, "pause");


	}

	@Override
	public void resume() {
		super.resume();
		statisticsService.onResume();
		Gdx.app.debug(TAG, "resume");
	}

	public static void setStatisticsService(IAnalyticsService statisticsService) {
		LWPGame.statisticsService = statisticsService;
	}
	public static IAnalyticsService getStatisticsService() {
		return statisticsService;
	}

}
