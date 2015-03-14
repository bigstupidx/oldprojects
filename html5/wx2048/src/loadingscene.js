LoadingScene = cc.Scene.extend({
    _length: 0,
    _count: 0,

    init: function () {
        var self = this;

        // bg
        var bg = cc.Sprite.create(res.Loading_png);
        bg.setAnchorPoint(0, 0);
        self.addChild(bg, 0);

        // progressbar background
        var progressBarBg = cc.Sprite.create(res.Loading_progressbar_bg_png);
        progressBarBg.setAnchorPoint(0, 0);
        progressBarBg.setPosition(90, 420 - STATUS_BAR_HEIGHT);
        self.addChild(progressBarBg, 2);

        // progressbar content
        self.progressBarContent = cc.Sprite.create(res.Loading_progressbar_content_png);
        self.progressBarContent.setAnchorPoint(0, 0);
        self.progressBarContent.setPosition(90, 420 - STATUS_BAR_HEIGHT);
        self.progressBarContent.setTextureRect(new cc.Rect(0, 0, 0, 0));
        self.addChild(self.progressBarContent, 1);

        // loading text
        self.texts = new Array();
        self.texts[0] = cc.Sprite.create(res.Loading_text_1_png);
        self.texts[1] = cc.Sprite.create(res.Loading_text_2_png);
        self.texts[2] = cc.Sprite.create(res.Loading_text_3_png);
        self.texts[3] = cc.Sprite.create(res.Loading_text_4_png);
        self.texts[4] = cc.Sprite.create(res.Loading_text_5_png);

        for (var i = 0; i < 5; i++) {
            self.texts[i].setAnchorPoint(0, 0);
            if (i == 0) {
                self.texts[i].setPosition(250, 350 - STATUS_BAR_HEIGHT);
            } else {
                var lastText = self.texts[i - 1];
                var x = lastText.getPosition().x;
                var w = lastText.getTexture().width;
                self.texts[i].setPosition(x + w, 350 - STATUS_BAR_HEIGHT);
            }
            self.addChild(self.texts[i], 2);
        }
    },

    /**
     * init with resources
     * @param {Array} resources
     * @param {Function|String} cb
     */
    initWithResources: function (resources, cb) {
        if (typeof resources == "string") resources = [resources];
        this.resources = resources || [];
        this.cb = cb;
    },

    onEnter: function () {
        var self = this;
        cc.Node.prototype.onEnter.call(self);
        self.schedule(self._startLoading, 0.3);
    },

    onExit: function () {
        cc.Node.prototype.onExit.call(this);

        //self.progressBarContent.setTextureRect(new cc.Rect(0, 0, 0, 0));
    },

    _startLoading: function () {
        var self = this;
        self.unschedule(self._startLoading);
        var res = self.resources;
        self._length = res.length;
        self._count = 0;
        cc.loader.load(res, function (result, count, loadedCount) {
            self._count = loadedCount + 1;
        }, function () {
            if (self.cb)
                self.cb();
        });
        self.schedule(self._updatePercent);
    },

    _updatePercent: function () {
        var self = this;
        var count = self._count;
        var length = self._length;
        var percent = (count / length * 100) | 0;
        percent = Math.min(percent, 100);

        // draw percent
        var w = self.progressBarContent.getTexture().width;
        var h = self.progressBarContent.getTexture().height;
        console.log(w * percent / 100);
        self.progressBarContent.setTextureRect(new cc.Rect(w * (100 - percent) / 100, 0, w * percent / 100, h));

        if (count >= length) self.unschedule(self._updatePercent);
    }
});

LoadingScene.preload = function (resources, cb) {
    var scene = new LoadingScene();
    scene.init();
    scene.initWithResources(resources, cb);
    cc.director.runScene(scene);
    return scene;
};