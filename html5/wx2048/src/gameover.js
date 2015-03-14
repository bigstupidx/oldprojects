/**
 * Created by Yu on 2014/8/17.
 */
var GameOver = cc.Layer.extend({
    ctor: function () {
        this._super();

        var self = this;

        // bg
        this.bg = cc.Sprite.create(res.grid_bg_png);
        this.bg.setAnchorPoint(0, 0);
        this.bg.setPosition(0, 0);
        this.bg.setColor(cc.color(139, 127, 117, 255 * 0.7));
        this.addChild(this.bg, 0);

        // game over text
        var textSprite = cc.Sprite.create(res.game_over_text_png);
        textSprite.setPosition(640 / 2, 450);
        this.addChild(textSprite);

        // score label
        self.scoreLabel = new cc.LabelTTF("" + g_wx2048Layer.score, "Arial", 50,
            cc.size(210, 60), cc.TEXT_ALIGNMENT_LEFT, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        self.scoreLabel.setAnchorPoint(0, 0);
        self.scoreLabel.attr({
            x: 380,
            y: 380
        });
        self.scoreLabel.setColor(cc.color.WHITE);
        self.addChild(self.scoreLabel, 2);

        // restart button
        var restartSprite = cc.Sprite.create(res.restart_button_png);
        var restartMenuItem = new cc.MenuItemSprite(restartSprite, null, this.restart, this);
        restartMenuItem.setPosition(640 / 2, 300);

        // enable share when browser is wechat
        var shareMenuItem = null;
        if (needShare()) {
            // share button
            var shareSprite = cc.Sprite.create(res.share_button_png);
            shareMenuItem = new cc.MenuItemSprite(shareSprite, null, this.share, this);
            shareMenuItem.setPosition(640 / 2, 150);
        }

        // add to menu
        this.menu = new cc.Menu(shareMenuItem, restartMenuItem, null);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu, 1);

        // eat all input event
        this.addListener();
    },

    addListener: function () {
        // use game state...
    },

    share: function () {
        g_wx2048Layer.share();
    },

    restart: function () {
        g_wx2048Layer.restart();
    }
});