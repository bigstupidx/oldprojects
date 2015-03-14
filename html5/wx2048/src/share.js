/**
 * Created by Yu on 2014/8/17.
 */
{
    function needShare() {
        return cc.sys.browserType == cc.sys.BROWSER_TYPE_WECHAT || FORCE_ENABLE_SHARE;
    }
}

var Share = cc.LayerColor.extend({
    ctor: function () {
        this._super();

        var winSize = cc.director.getWinSize();

        // bg
        this.bg = cc.Sprite.create(res.share_png);
        this.bg.setAnchorPoint(0, 0);
        this.bg.setPosition(0, winSize.height - this.bg.getTexture().height);
        this.addChild(this.bg);

        this.init(cc.color(0, 0, 0, 255 * 0.9), winSize.width, winSize.height);
        this.setPosition(0, 0);
    },

    addListener: function () {
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function (touch, event) {
                this.touchDowned = true;
                return true;
            },
            onTouchMoved: function (touch, event) {

            },
            onTouchEnded: function (touch, event) {
                if (this.touchDowned)
                    g_wx2048Layer.restart();
            }
        }, this);
    },

    onEnter: function () {
        this._super();

        this.touchDowned = false;

        // eat all event
        this.addListener();

        // Set body background to gray.
        document.body.style["background-color"] = "rgb(25, 25, 25)";
    },

    onExit: function () {
        this._super();

        cc.eventManager.removeListeners(this);

        // Restore body background to white.
        document.body.style["background-color"] = "white";
    }
});