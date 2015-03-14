GameScene = cc.Scene.extend({

    ctor: function () {
        this._super();

        // bg
        this.bg = new Decorate(false, true, true, false);
        this.addChild(this.bg);

        // submit button
        this.submitButtonSprite = cc.Sprite.create(res.game_submit_png);
        this.submitButtonDisableSprite = cc.Sprite.create(res.game_submit_disabled_png);
        this.submitButton = new cc.MenuItemSprite(this.submitButtonSprite, null, null, this.submit, this);
        this.submitButton.setPosition(320, 1136 - 983);

        // menu
        this.menu = cc.Menu.create(this.submitButton);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // question bg
        var questionBg = cc.Sprite.create(res.game_question_bg_png);
        questionBg.setPosition(320, 1136 - 460);
        this.addChild(questionBg);

        // question scroll view
        this.questionSize = cc.size(586 - 66 * 2, 464 - 53 * 2);
        this.scrollView = new ccui.ScrollView();
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.scrollView.setPosition(320, 1136 - 460);
        this.scrollView.setContentSize(this.questionSize);
        this.scrollView.setAnchorPoint(0.5, 0.5);
        this.scrollView.setInnerContainerSize(cc.size(this.questionSize.width, this.questionSize.height * 2));
        this.addChild(this.scrollView, 2);

        // question label
        this.questionLabel = new cc.LabelTTF("", "Arial", 35,
            cc.size(this.questionSize.width, this.questionSize.height), cc.TEXT_ALIGNMENT_LEFT, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        this.questionLabel.attr({
            x: this.questionSize.width / 2,
            y: this.questionSize.height
        });
        this.questionLabel.setAnchorPoint(0.5, 0.5);
        this.questionLabel.setColor(cc.color(0, 0, 0, 255));
        this.scrollView.addChild(this.questionLabel);

        // options
        this.option = new Options();
        this.addChild(this.option);
    },

    submit: function () {

    }
});