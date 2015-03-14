var FORCE_ENABLE_SHARE = false;

var STATUS_BAR_HEIGHT = 128;

cc.game.onStart = function () {
    cc.view.setDesignResolutionSize(640, 1136 - STATUS_BAR_HEIGHT, cc.ResolutionPolicy.SHOW_ALL);

    cc.view.adjustViewPort(true);
    cc.view.resizeWithBrowserSize(true);
    cc.director.setProjection(cc.Director.PROJECTION_2D);

    // enter first scene
    FirstScene.preload(g_firstResources, function () {
        LoadingScene.preload(g_resources, function () {
            cc.director.runScene(new wx2048Scene());
        });
    }, this);
};

cc.game.run();