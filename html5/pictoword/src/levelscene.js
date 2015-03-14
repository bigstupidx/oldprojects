/**
 * Created by Administrator on 2014/8/28.
 */
LevelScene = cc.Scene.extend({
    titles: [
        res.level_1_png,
        res.level_2_png,
        res.level_3_png
    ],
    focus: 0,
    level: 0, // 0 - 2

    ctor: function (boss) {
        this._super();

        this.boss = boss;

        // add common bg
        var bg = cc.Sprite.create(res.common_bg_png);
        bg.setAnchorPoint(0, 0);
        this.addChild(bg);

        // add level bg
        var levelBg = cc.Sprite.create(res.level_bg_png);
        levelBg.setAnchorPoint(0, 0);
        this.addChild(levelBg);

        // add selecteds
        var selecteds = [
            res.level_key_1_selected_png,
            res.level_key_2_selected_png,
            res.level_key_3_selected_png
        ];
        this.selected = [];
        for (var i = 0; i < 3; i++) {
            var sprite = cc.Sprite.create(selecteds[i]);
            this.selected[i] = new cc.MenuItemSprite(sprite, null, null, this.select, this);
            this.selected[i].setPosition(320 + 5, 1136 - (386 + i * 160 - 2));
        }
        this.selectedMenu = cc.Menu.create(this.selected);
        this.selectedMenu.setAnchorPoint(0, 0);
        this.selectedMenu.setPosition(0, 0);
        this.addChild(this.selectedMenu);

        // add level key bg
        var levelKeyBg = cc.Sprite.create(res.level_key_bg_png);
        levelKeyBg.setAnchorPoint(0, 0);
        this.addChild(levelKeyBg);

        // add keys
        this.key = [];
        var keys = [
            res.level_key_1_png,
            res.level_key_2_png,
            res.level_key_3_png
        ];
        for (var i = 0; i < 3; i++) {
            this.key[i] = cc.Sprite.create(keys[i]);
            this.key[i].setPosition(320 + 50, 1136 - (386 + i * 160));
            this.addChild(this.key[i]);
        }

        // add start button
        var startButtonSprite = cc.Sprite.create(res.level_start_button_png);
        var startButton = new cc.MenuItemSprite(startButtonSprite, null, null, this.start, this);
        startButton.setPosition(320, 1136 - 870);

        // menu
        this.menu = cc.Menu.create(startButton);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);
    },

    start: function () {
        console.log("level scene: start");

        // set current level
        var level = 3 * this.boss;
        storage.setCurrentLevel(level + this.focus);

        // rebuild questions
        questions.rebuild();

        // run game scene
        cc.director.pushScene(new GameScene());
    },

    select: function (target) {
        for (var i = 0; i < 3; i++)
            if (target == this.selected[i])
                break;
        this.setFocus(i);
    },

    onEnter: function () {
        this._super();

        // get level
        if (this.boss < storage.getBoss()) {
            this.level = 2;
        } else {
            this.level = storage.getTopLevel() % 3;
        }

        // add title
        this.title = cc.Sprite.create(this.titles[this.level]);
        this.title.setPosition(320, 1136 - 178);
        this.addChild(this.title);

        // set key visible
        for (var i = 0; i <= this.level; i++) {
            this.key[i].setVisible(true);
        }

        for (var i = this.level + 1; i < 3; i++) {
            this.key[i].setVisible(false);
        }

        // run fade in animation
        if (storage.getJustWon() == 1) {
            // TODO: when do we clear the just won flag?
            var fadeIn = cc.fadeIn(0.8);
            this.key[this.level].setOpacity(0);
            this.key[this.level].runAction(fadeIn);
        }

        // set focus to last level
        this.setFocus(this.level);
    },

    onExit: function () {
        this._super();

        this.removeChild(this.title);
    },

    setFocus: function (focus) {
        if (focus <= this.level) {
            this.focus = focus;

            for (var i = 0; i < 3; i++)
                this.selected[i].setOpacity(0);
            this.selected[this.focus].setOpacity(255);
        }
    }
});