/**
 * Created by Yu on 2014/8/31.
 */
Options = cc.Layer.extend({
    options: new Array(),
    optionSprite: [],
    optionSelectedSprite: [],
    optionsLabel: new Array(),
    count: 4,
    answer: "",

    ctor: function () {
        this._super();

        for (var i = 0; i < 6; i++) {
            this.optionSprite[i] = cc.Sprite.create(res.game_option_bg_png);
            this.optionSelectedSprite[i] = cc.Sprite.create(res.game_option_selected_png);
            this.options[i] = cc.MenuItemSprite.create(this.optionSprite[i], null, null, this.select, this);

            this.optionsLabel[i] = new cc.LabelTTF("Option " + i, "Arial", 25,
                cc.size(198 - 23 * 2, 101 - 15 * 2), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
            this.optionsLabel[i].setColor(new cc.color(0, 0, 0, 255));
            this.addChild(this.optionsLabel[i], 2);
        }

        this.menu = cc.Menu.create(this.options);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // update options at first time
        this.updateOptions();
    },

    select: function (target) {
        for (var i = 0; i < 6; i++) {
            if (this.options[i] == target) {
                break;
            }
        }

        if (questions.getQuestionType() == "binary") {
            if (i == 0) {
                this.answer = "true";
            }
            else {
                this.answer = "false";
            }
            // select target and unselect another
            this.selectedOption(i);
            this.unselectedOption(1 - i);
        } else {
            var t = String.fromCharCode(65 + i);
            var index = this.answer.indexOf(t);
            if (index >= 0) {
                if (this.answer.length > 1) {
                    this.unselectedOption(i);
                    this.answer = this.answer.substring(0, index) + this.answer.substring(index + 1, this.answer.length);
                }
            } else {
                this.answer += t;
                this.selectedOption(i);
            }
        }

        var gamescene = this.getParent();
        gamescene.submitButton.setNormalImage(gamescene.submitButtonSprite);
    },

    setCount: function (count) {
        if (this.count != count) {
            this.count = count;
            this.updateOptions();
        }
    },

    updateOptions: function () {
        // calculate position
        if (this.count <= 4) {
            // init 4 options
            var fixY = -70;

            this.options[0].setPosition(205, 1136 - 683 + fixY);
            this.options[1].setPosition(428, 1136 - 683 + fixY);
            this.options[2].setPosition(205, 1136 - 809 + fixY);
            this.options[3].setPosition(428, 1136 - 809 + fixY);

            this.optionsLabel[0].setPosition(205, 1136 - 683 + fixY);
            this.optionsLabel[1].setPosition(428, 1136 - 683 + fixY);
            this.optionsLabel[2].setPosition(205, 1136 - 809 + fixY);
            this.optionsLabel[3].setPosition(428, 1136 - 809 + fixY);

            // enable used options
            for (var i = 0; i < this.count; i++) {
                this.options[i].setVisible(true);
                this.optionsLabel[i].setVisible(true);
            }

            // disable useless options
            for (var i = this.count; i < 6; i++) {
                this.options[i].setVisible(false);
                this.optionsLabel[i].setVisible(false);
            }
        }

        // reset answer
        this.answer = "";
    },

    setString: function (options) {
        if (options instanceof Array) {
            for (var i = 0; i < options.length; i++) {
                this.optionsLabel[i].setString(options[i]);

                this.unselectedOption(i);
            }
        }
    },

    selectedOption: function (index) {
        this.options[index].setNormalImage(this.optionSelectedSprite[index]);
    },

    unselectedOption: function (index) {
        this.options[index].setNormalImage(this.optionSprite[index]);
    }
});