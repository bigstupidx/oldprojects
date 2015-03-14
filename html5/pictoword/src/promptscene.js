/**
 * Created by Yu on 2014/8/24.
 */
PromptScene = cc.Scene.extend({
    ctor: function () {
        this._super();

        // add bg
        var bg = cc.Sprite.create(res.common_bg_png);
        bg.setAnchorPoint(0, 0);
        this.addChild(bg);

        var decorate = cc.Sprite.create(res.prompt_decorate_png);
        decorate.setAnchorPoint(0, 0);
        this.addChild(decorate);

        var dialog = cc.Sprite.create(res.prompt_dialog_png);
        dialog.setAnchorPoint(0, 0);
        this.addChild(dialog);

        // go on button
        var buttonSprite = cc.Sprite.create(res.common_goon_button_png);
        var button = cc.MenuItemSprite.create(buttonSprite, null, this.goon, this);
        button.setPosition(320, 1136 - 988);

        // menu
        this.menu = cc.Menu.create(button);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // scroll view
        this.scrollView = new ccui.ScrollView();
        this.scrollView.setTouchEnabled(true);
        this.scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        this.scrollView.setPosition(320, 1136 - (885 - 529 / 2));
        this.scrollView.setContentSize(cc.size(467, 529));
        this.scrollView.setAnchorPoint(0.5, 0.5);
        this.addChild(this.scrollView);

        // label
        var txt = "游戏介绍：根据提示依次挑战闯关，并通过答题来获取比分，在更短时间内，正确回答完题目的学员，可以获得更高分值。\n\n难度等级：游戏有3个难度等级，每个难度等级的时间不同，每个等级有3小关。每个小关答对率达到80%，才能解锁下一关。\n\n游戏时间：3小关的每题答题时间分别为20s,19s,18s，超时即算答错。\n\n闯关失败说明：在闯关过程中，每个人有3次答错题目的机会，三次机会使用结束后，闯关失败。\n\n体力值：每人每天有10次闯关的机会（体力值），用完后将无法进行闯关，体力值在第二天零时恢复。\n\n得分规则：答对题的得分（100分/每题）+ 每题剩余时间(n)秒 x 10分，答错不得分。\n\n排名规则：\n    每一关只取最高历史得分，所有已通关的关卡得分总和计入排行榜。\n    您的得分将被系统记录参与排名。同时您的成绩也将影响到您团队的成绩：\n\n团队排名说明：\n    以参与游戏的团队成员得分的加权平均分作为最终得分。\n    团队中参与的人数越多，得分越高，则整个团队的得分越高。\n\n团队得分计算公式：\n    参与游戏用户平均分值 x 参与游戏的人数 / 团队总人数\n    例如：\n    团队A，有50人，其中25人玩了游戏，平均每人得分95分；\n    团队B，有15人，其中5人玩了游戏，平均每人得分98分。\n    团队A：95 x 25/50 = 47.5 分　　\n    团队B：98 x 5/15 = 32.6分\n";
        this.promptLabel = new cc.LabelTTF(txt, "Arial", 30,
            cc.size(467, 0), cc.TEXT_ALIGNMENT_LEFT, cc.VERTICAL_TEXT_ALIGNMENT_TOP);
        this.promptLabel.setColor(new cc.color(75, 75, 75, 255));
        this.scrollView.addChild(this.promptLabel);

        // calculate size and position
        var height = this.promptLabel.getContentSize().height;
        this.promptLabel.setDimensions(cc.size(467, height));
        this.promptLabel.attr({
            x: 467 / 2,
            y: height / 2
        });
        this.scrollView.setInnerContainerSize(cc.size(467, height));
    },

    onEnter: function () {
        this._super();
    },

    goon: function () {
        cc.director.runScene(new SelectorScene());
    }
});