/**
 * Created by Yu on 2014/8/15.
 */
FirstScene = cc.Scene.extend({
    _length: 0,
    _count: 0,
    FrameNamePrefix: "preload_",
    FrameCount: 52,
    sprite: null,
    frame: 0,

    init: function () {
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

        // load sprite sheet
        cc.loader.load(res.preload_sheet_plist, function () {
            cc.spriteFrameCache.addSpriteFrames(res.preload_sheet_plist);

            self.sprite = cc.Sprite.create("#" + self.FrameNamePrefix + self.frame + ".png");
            self.sprite.setPosition(640 / 2, 1136 / 2);
            self.sprite.setAnchorPoint(0.5, 0.5);
            self.sprite.setScale(2.0);
            self.addChild(self.sprite);

            self.schedule(self._updateSprite, 0.05);
        });

        // add label
        var label = new cc.LabelTTF("使劲加载中…", "Arial", 30,
            cc.size(640, 40), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        label.attr({
            x: 320,
            y: 1136 / 2 - 128
        });
        label.setColor(new cc.color(0, 0, 0, 255));
        this.addChild(label);
    },

    _updateSprite: function () {
        var self = this;
        self.frame++;
        if (self.frame == self.FrameCount) {
            self.frame = 0;
        }

        self.sprite.setSpriteFrame(self.FrameNamePrefix + self.frame + ".png");
    },

    onExit: function () {
        cc.Node.prototype.onExit.call(this);

        cc.spriteFrameCache.removeSpriteFrames();
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

        if (count >= length) self.unschedule(self._updatePercent);
    }
});

FirstScene.preload = function (resources, cb) {
    var scene = new FirstScene();
    scene.init();
    scene.initWithResources(resources, cb);
    cc.director.runScene(scene);
    return scene;
};