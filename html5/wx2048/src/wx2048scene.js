var g_wx2048Layer;

var wx2048Scene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new wx2048Layer();
        this.addChild(layer);

        g_wx2048Layer = layer;
    }
});