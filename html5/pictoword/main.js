cc.game.onStart = function () {
    var NoBorderCenter = cc.ContentStrategy.extend({
        apply: function (view, designedResolution) {
            var containerW = cc._canvas.width, containerH = cc._canvas.height,
                designW = designedResolution.width, designH = designedResolution.height,
                scaleX = containerW / designW, scaleY = containerH / designH, scale;

            scaleX < scaleY ? ( scale = scaleY ) : ( scale = scaleX );

            var contentW = designW * scale;
            var contentH = designH * scale;

            return this._buildResult(containerW, containerH, contentW, contentH, scale, scale);
        },
    });

    var width = window.screen.availWidth;
    var height = window.screen.availHeight;
    //var width = document.body.clientWidth;
    //var height = document.body.clientHeight;
    console.log("width: " + width + ", height: " + height);

    if (height > width) {
        var no_border_center = new cc.ResolutionPolicy(cc.ContainerStrategy.EQUAL_TO_FRAME,
            new NoBorderCenter());
        cc.view.setDesignResolutionSize(640, 1136, no_border_center);
    }
    else {
        cc.view.setDesignResolutionSize(640, 1136, cc.ResolutionPolicy.SHOW_ALL);
    }

    cc.view.adjustViewPort(true);
    cc.view.resizeWithBrowserSize(true);
    cc.director.setProjection(cc.Director.PROJECTION_2D);

    // enter first scene
    FirstScene.preload(g_loading_resources, function () {
        LoadingScene.preload(g_resources, null);
    }, this);
};

cc.game.run();