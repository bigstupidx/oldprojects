LoadingScene = cc.Scene.extend({
    _length: 0,
    _count: 0,

    init: function () {
        var self = this;

        this.bg = new Decorate(true, true, true, true);
        this.addChild(this.bg);

        this.decorate = cc.Sprite.create(res.loading_decorate_png);
        this.decorate.setPosition(0, 0);
        this.decorate.setAnchorPoint(0, 0);
        this.addChild(this.decorate);

        // button
        this.button = cc.Sprite.create(res.loading_button_png);

        // menu item
        this.menuItem = new cc.MenuItemSprite(this.button, null, null, this.start, this);
        this.menuItem.setPosition(320 + 8, 1136 - 800);
        this.menuItem.runAction(cc.sequence(cc.scaleTo(1.5, 0.8), cc.scaleTo(1.5, 1)).repeatForever());

        // menu
        this.menu = cc.Menu.create(this.menuItem);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu, 1);

        // label
        this.label = new cc.LabelTTF("0%", "Arial", 30,
            cc.size(300, 40), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        this.label.setColor(cc.color(122, 43, 30, 255));
        this.label.setPosition(320 + 14, 1136 - 690);
        this.addChild(this.label);
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

        // loading user info
        user.init();
    },

    onExit: function () {
        cc.Node.prototype.onExit.call(this);

        this.label.setString("0%");
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

            //self.menuItem.setEnabled(true);
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
        this.label.setString(percent + "%");

        if (count >= length) self.unschedule(self._updatePercent);
    },

    start: function () {
        if (this._count == this._length) {
            console.log("loading scene: start");
            cc.director.runScene(new PromptScene());

            // notice: the HTML audio element has bug, we should play it after load a while.
            // play music
            if (!cc.audioEngine.isMusicPlaying())
                cc.audioEngine.playMusic(res.background_mp3, true);
        }
    }
});

LoadingScene.preload = function (resources, cb) {
    var scene = new LoadingScene();
    scene.init();
    scene.initWithResources(resources, cb);
    cc.director.runScene(scene);
    return scene;
};