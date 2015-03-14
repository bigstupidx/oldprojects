/**
 * Created by Yu on 2014/8/15.
 */
FirstScene = cc.Scene.extend({
    _length: 0,
    _count: 0,

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
    },

    onExit: function () {
        cc.Node.prototype.onExit.call(this);
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