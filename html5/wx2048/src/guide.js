/**
 * Created by Yu on 2014/8/18.
 */
var Guide = cc.LayerColor.extend({
    ctor: function() {
        this._super();

        var winSize = cc.director.getWinSize();

        this.init(cc.color(0, 0, 0, 255 * 0.5), winSize.width, winSize.height);
        this.setPosition(0, 0);

        // finger
        this.finger = cc.Sprite.create(res.guide_finger_png);
        this.finger.setPosition(46, 1136 - 910);
        this.finger.setAnchorPoint(0, 1);
        this.addChild(this.finger, 1);

        // text
        this.text = cc.Sprite.create(res.guide_text_png);
        this.text.setAnchorPoint(0, 0);
        this.text.setPosition(35, 1136 - 816);
        this.addChild(this.text, 1);

        // 2 tiles
        this.grid = new cc.Layer();
        this.grid.setPosition(16, 1136 - 1010);
        this.addChild(this.grid, 0);

        this.tile1 = new Tile({x: 0, y: 3}, 1);
        this.grid.addChild(this.tile1);

        this.tile2 = new Tile({x: 1, y: 3}, 1);
        this.grid.addChild(this.tile2);
    },

    onEnter: function() {
        this._super();

        this.addListener();

        // Set body background to gray.
        document.body.style["background-color"] = "rgb(128, 128, 128)";
    },

    onExit: function() {
        this._super();

        // Restore body background to white.
        document.body.style["background-color"] = "white";
    },

    addListener: function () {
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan: function (touch, event) {
                g_wx2048Layer.restart();
            }
        }, this);
    }
});