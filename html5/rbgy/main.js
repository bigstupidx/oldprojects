var DESIGN_WIDTH = 450;
var DESIGN_HEIGHT = 800;

cc.game.onStart = function(){
    cc.view.adjustViewPort(true);
    cc.view.setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, cc.ResolutionPolicy.SHOW_ALL);
	cc.view.resizeWithBrowserSize(true);

    //load resources
    cc.LoaderScene.preload(g_resources, function () {
        cc.director.runScene(new RbgyScene());
    }, this);
};
cc.game.run();