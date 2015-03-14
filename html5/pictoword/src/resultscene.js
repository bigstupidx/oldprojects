/**
 * Created by Yu on 2014/8/31.
 */
ResultScene = cc.Scene.extend({
    pass: null,
    over: null,
    score: null,

    ctor: function (isRight, score, pass, over) {
        this._super();

        this.pass = pass;
        this.over = over;
        this.score = score;

        // bg
        this.bg = new Decorate(false, true, true, false);
        this.addChild(this.bg);

        // button
        var button = null;
        var bg = null;
        if (over) {
            // button
            var sprite = cc.Sprite.create(res.result_restart_button_png);
            button = cc.MenuItemSprite.create(sprite, null, this.next, this);
            button.setPosition(320, 1136 - 612);

            bg = cc.Sprite.create(res.result_failed_png);
        } else {
            if (isRight) {
                // button
                var sprite = cc.Sprite.create(res.common_goon_button_png);
                button = cc.MenuItemSprite.create(sprite, null, this.next, this);

                if (this.pass) {
                    bg = cc.Sprite.create(res.result_won_png);

                    button.setPosition(320, 1136 - 612);
                } else {
                    bg = cc.Sprite.create(res.result_right_png);

                    button.setPosition(320, 1136 - 566);
                }
            } else {
                // button
                var sprite = cc.Sprite.create(res.result_next_button_png);
                button = cc.MenuItemSprite.create(sprite, null, this.next, this);

                if (this.pass) {
                    bg = cc.Sprite.create(res.result_lose_png);

                    button.setPosition(320, 1136 - 612);
                } else {
                    bg = cc.Sprite.create(res.result_wrong_png);

                    button.setPosition(320, 1136 - 566);
                }
            }
        }

        // score bg
        if (this.pass || this.over) {
            bg.setPosition(640 / 2, 1136 - 500);
        } else {
            bg.setPosition(640 / 2, 1136 - 476);
        }
        this.addChild(bg);

        // menu
        this.menu = cc.Menu.create(button);
        this.menu.setPosition(0, 0);
        this.menu.setAnchorPoint(0, 0);
        this.addChild(this.menu);

        // label
        if (this.pass || this.over) {
            this.scoreLabel = new cc.LabelTTF("" + this.score, "Arial", 30,
                cc.size(225, 36), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
            this.scoreLabel.attr({
                x: 320,
                y: 1136 - 542
            });
            this.scoreLabel.setColor(new cc.color(239, 59, 54, 255));
            this.addChild(this.scoreLabel);
        }
    },

    next: function () {
        // pop to game scene
        cc.director.popScene();

        var boss = storage.getCurrentBoss();
        var levelScore = this.score;

        var level = storage.getCurrentLevel();

        if (this.over) {
            // save boss score
            storage.setLevelScore(level, levelScore, false);

            // pop to level scene
            cc.director.popScene();

            // pop to selector scene
            cc.director.popScene();
        } else {
            if (this.pass) {
                // pop to level scene
                cc.director.popScene();

                // save level score
                storage.setLevelScore(level, levelScore, true);

                // set just won flag
                storage.setJustWon(1);

                // if last boss level
                if ((level % 3) == 2) {
                    // go to rank scene
                    cc.director.runScene(new RankScene());
                }
            }
        }
    }
})
;