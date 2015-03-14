/**
 * Created by Yu on 2014/8/24.
 */
SelectorScene = cc.Scene.extend({
    ctor: function () {
        this._super();

        // bg
        this.bg = new Decorate(true, true, true, false);
        this.addChild(this.bg);

        // start button
        this.startButtonSprite = new cc.Sprite.create(res.selector_start_button_png);
        this.startButtonDisableSprite = new cc.Sprite.create(res.selector_start_disable_button_png);
        this.startButton = new cc.MenuItemSprite(this.startButtonSprite, null, null, this.start, this);
        this.startButton.setPosition(320, 1136 - 800);

        // rank button
        var rankButtonSprite = cc.Sprite.create(res.selector_rank_button_png);
        var rankButton = new cc.MenuItemSprite(rankButtonSprite, null, null, this.goRank, this);
        rankButton.setPosition(320, 1136 - 890);

        // left button
        var leftButtonSprite = new cc.Sprite.create(res.selector_left_button_png);
        var leftButton = new cc.MenuItemSprite(leftButtonSprite, null, null, this.left, this);
        leftButton.setPosition(60, 1136 - 600);

        {
            // start animation
            var duration = 0.5;
            var moveByLeft = cc.moveBy(duration, cc.p(-8, 0));
            var moveByRight = cc.moveBy(duration, cc.p(8, 0));
            var swing = cc.sequence(moveByLeft, moveByRight).repeatForever();
            leftButton.runAction(swing);
        }

        // right button
        var rightButtonSprite = new cc.Sprite.create(res.selector_right_button_png);
        var rightButton = new cc.MenuItemSprite(rightButtonSprite, null, null, this.right, this);
        rightButton.setPosition(580, 1136 - 600);

        {
            // start animation
            var duration = 0.5;
            var moveByLeft = cc.moveBy(duration, cc.p(-8, 0));
            var moveByRight = cc.moveBy(duration, cc.p(8, 0));
            var swing = cc.sequence(moveByRight, moveByLeft).repeatForever();
            rightButton.runAction(swing);
        }

        // menu
        this.menu = cc.Menu.create(this.startButton, rankButton, leftButton, rightButton);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // best score text
        var bestScoreTextSprite = cc.Sprite.create(res.selector_bestscore_text_png);
        bestScoreTextSprite.setPosition(320, 1136 - 160);
        this.addChild(bestScoreTextSprite);

        // best score label
        this.bestScoreLabel = new cc.LabelAtlas("", res.selector_score_number_png, 23, 39, "0");
        this.bestScoreLabel.setAnchorPoint(0.5, 0.5);
        this.bestScoreLabel.attr({
            x: 320,
            y: 1136 - 224
        });
        this.addChild(this.bestScoreLabel);

        // chance bg
        var chanceBg = cc.Sprite.create(res.selector_chance_bg_png);
        chanceBg.setPosition(320, 1136 - 1031);
        this.addChild(chanceBg);

        // chance label
        this.chanceLabel = new cc.LabelTTF("", "Arial", 24,
            cc.size(75, 38), cc.TEXT_ALIGNMENT_LEFT, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        this.chanceLabel.attr({
            x: 296,
            y: 1136 - 1034
        });
        this.chanceLabel.setColor(cc.color(0, 0, 0, 255));
        this.addChild(this.chanceLabel);

        // reset chance by date
        var date = storage.getDate();
        var nowDate = new Date();
        //console.log("date = " + date + ", now date = " + nowDate.getDate());
        if (date != nowDate.getDate()) {
            storage.setDate(nowDate.getDate());
            storage.setChance(config.MaxChance);
        }
    },

    _canStart: function () {
        var ret = true;
        var chance = storage.getChance();
        if (this.selector.getLocked() || chance <= 0) {
            ret = false;
        }
        return ret;
    },

    _updateButton: function () {
        if (!this._canStart()) {
            this.startButton.setNormalImage(this.startButtonDisableSprite);
        } else {
            this.startButton.setNormalImage(this.startButtonSprite);
        }
    },

    _updateLabel: function () {
        var score = 0;
        score = storage.getTotalScore();
        this.bestScoreLabel.setString("" + score);

        // chance
        var chance = storage.getChance();
        this.chanceLabel.setString(chance + "/" + config.MaxChance);
    },

    onEnter: function () {
        this._super();

        // create and add level selector
        this.selector = new Selector();
        this.addChild(this.selector);

        // update start button
        this._updateButton();

        // update best score
        this._updateLabel();
    },

    onExit: function () {
        this._super();

        // remove selector
        this.removeChild(this.selector);
        this.selector = null;
    },

    start: function () {
        console.log("selector scene: start");

        // ignore locked boss
        if (this._canStart()) {
            var boss = this.selector.getFocus();

            // sub 1 to chance
            var chance = storage.getChance();
            storage.setChance(chance - 1);

            // go to game scene
            cc.director.pushScene(new LevelScene(boss));
        }
    },

    goRank: function () {
        //console.log("selector scene: go rank");
        cc.director.pushScene(new RankScene);
    },

    left: function () {
        //console.log("selector scene: left");
        this.selector.moveLeft();

        // update start button
        this._updateButton();

        // update best score
        this._updateLabel();
    },

    right: function () {
        //console.log("selector scene: right");
        this.selector.moveRight();

        // update start button
        this._updateButton();

        // update best score
        this._updateLabel();
    }
});