var RbgyScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new RbgyLayer();
        this.addChild(layer);
    }
});
