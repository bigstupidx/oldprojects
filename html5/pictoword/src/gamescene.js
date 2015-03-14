/**
 * Created by Administrator on 2014/8/29.
 */
GameScene = cc.Scene.extend({
    hp: null,
    boss: null,
    level: null,
    timer: null,
    score: null,
    currentQuestion: 0,
    rightStars: 0,
    lastestScore: null,
    lastestResult: null,
    dynamicScore: null,

    ctor: function () {
        this._super();

        this.boss = storage.getCurrentBoss();
        this.level = storage.getCurrentLevel() % 3;

        this.hp = config.MaxHp;
        if (storage.getBonus() != 0) {
            this.hp += config.BonusHp;
            storage.setBonus(0);
        }
        this.timer = this.getMaxTimer();

        this.score = 0;

        // bg
        this.bg = new Decorate(false, true, true, false);
        this.addChild(this.bg);

        // back button
        var backButtonSprite = cc.Sprite.create(res.game_back_button_png);
        var backButton = new cc.MenuItemSprite(backButtonSprite, null, null, this.back, this);
        backButton.setPosition(68, 1136 - 144);

        // submit button
        this.submitButtonSprite = cc.Sprite.create(res.game_submit_png);
        this.submitButtonDisableSprite = cc.Sprite.create(res.game_submit_disabled_png);
        this.submitButton = new cc.MenuItemSprite(this.submitButtonSprite, null, null, this.submit, this);
        this.submitButton.setPosition(320, 1136 - 983);

        // menu
        this.menu = cc.Menu.create(backButton, this.submitButton);
        this.menu.setAnchorPoint(0, 0);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu);

        // score bg
        var scoreSprite = cc.Sprite.create(res.game_score_bg_png);
        scoreSprite.setPosition(530, 1136 - 144);
        this.addChild(scoreSprite);

        // score label
        this.scoreLabel = new cc.LabelTTF("" + this.score, "Arial", 30,
            cc.size(116, 30), cc.TEXT_ALIGNMENT_RIGHT, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        this.scoreLabel.attr({
            x: 545,
            y: 1136 - 140
        });
        this.scoreLabel.setColor(new cc.color(255, 255, 255, 255));
        this.addChild(this.scoreLabel);

        // multiple icon
        this.multipleIcon = cc.Sprite.create(res.game_multiple_icon_png);
        this.multipleIcon.setPosition(559, 1136 - 263);
        this.addChild(this.multipleIcon, 1);

        // single icon
        this.singleIcon = cc.Sprite.create(res.game_single_icon_png);
        this.singleIcon.setPosition(559, 1136 - 263);
        this.addChild(this.singleIcon, 1);

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

        // timer bg
        var timerSprite = cc.Sprite.create(res.game_timer_bg_png);
        timerSprite.setPosition(320, 1136 - 243);
        this.addChild(timerSprite);

        // timer label
        this.timerLabel = new cc.LabelAtlas("", res.game_info_number_png, 22, 35, "0");
        this.timerLabel.attr({
            x: 346,
            y: 1136 - 243
        });
        this.timerLabel.setAnchorPoint(0.5, 0.5);
        this.addChild(this.timerLabel);
        this.schedule(this.updateTimer, 1, cc.REPEAT_FOREVER);

        // hp
        this.hpSprite = cc.Sprite.create(res.game_hp_png);
        this.hpSprite.setPosition(154, 1136 - 144);
        this.addChild(this.hpSprite, 3);

        // hp level
        this.hpLabel = new cc.LabelAtlas(":" + this.hp, res.game_info_number_png, 22, 35, "0");
        this.hpLabel.attr({
            x: 220,
            y: 1136 - 144
        });
        this.hpLabel.setAnchorPoint(0.5, 0.5);
        this.addChild(this.hpLabel);

        // options
        this.option = new Options();
        this.addChild(this.option);

        // level
        var levelBg = cc.Sprite.create(res.game_level_bg_png);
        levelBg.setPosition(540, 1136 - 650);
        this.addChild(levelBg);

        // level label
        this.levelLabel = new cc.LabelAtlas("1;" + config.OverQuestions, res.game_info_number_png, 22, 35, "0");
        this.levelLabel.attr({
            x: 540,
            y: 1136 - 650
        });
        this.levelLabel.setAnchorPoint(0.5, 0.5);
        this.addChild(this.levelLabel);

        // dynamic score
        this.dynamicScoreLabel = new cc.LabelTTF("+100", "Arial", 40,
            cc.size(116, 40), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        this.dynamicScoreLabel.setOpacity(0);
        this.addChild(this.dynamicScoreLabel);

        // notice: the HTML audio element has bug, we should play it after load a while.
        // play music
        if (!cc.audioEngine.isMusicPlaying())
            cc.audioEngine.playMusic(res.background_mp3, true);
    },

    back: function () {
        console.log("game scene: back");
        cc.director.popScene();
        cc.director.popScene();
    },

    _submit: function (answer) {
        var rightAnswer = questions.getQuestion().answer;
        var isRight = (answer == rightAnswer) || false;
        this.lastestResult = isRight;
        if (!isRight) {
            this.lastestScore = config.ScorePunish;
            this.hp--;
        } else {
            // 100 score per question and 20 score per second.
            this.lastestScore = config.ScorePerQuestion + this.timer * config.ScorePerSecond;
            this.rightStars++;
        }

        // add score
        this.score += this.lastestScore;
        if (this.score < 0) {
            this.score = 0;
        }

        // handle hp
        if (this.hp == 0) {
            this.over();
            return;
        }

        // next question
        this.currentQuestion++;
        questions.next();

        // run a new result scene after questions.next
        if (this.currentQuestion >= config.OverQuestions) {
            cc.director.pushScene(new ResultScene(
                isRight,
                this.score,
                !!(this.rightStars >= config.PassStars),
                false));
            if (this.rightStars == config.OverQuestions) {
                storage.setBonus(1);
            }
        } else {
            cc.director.pushScene(new ResultScene(
                isRight,
                this.score,
                false,
                false));
        }
    },

    submit: function () {
        // no option is chosen.
        if (this.option.answer == "") {
            return;
        }

        var answer = "";
        if (questions.getQuestionType() == "binary") {
            answer = this.option.answer;
        } else {
            // sort this.option.answer
            for (var i = 0; i < 6; i++) {
                var char = String.fromCharCode(65 + i);
                if (this.option.answer.indexOf(char) >= 0) {
                    answer += char;
                }
            }
        }

        this._submit(answer);
    },

    updateTimer: function () {
        if (this.isRunning()) {
            this.timer--;
            if (this.timer >= 0) {
                this.timerLabel.setString("" + this.timer);
            } else {
                // time over
                console.log("time over");
                this.timeOver();
            }
        }
    },

    updateQuestion: function () {
        var questionStr = questions.getQuestion().question;
        this.questionLabel.setString(questionStr);

        this.questionLabel.setDimensions(cc.size(this.questionSize.width, 0));
        var height = this.questionLabel.getContentSize().height;
        if (height < this.questionSize.height) {
            height = this.questionSize.height;
        }
        this.questionLabel.attr({
            x: this.questionSize.width / 2,
            y: height / 2
        });
        this.questionLabel.setDimensions(cc.size(this.questionSize.width, height));
        this.scrollView.setInnerContainerSize(cc.size(this.questionSize.width, height));

        if (questions.getQuestionType() == "binary") {
            // binaray
            this.option.setCount(2);
            this.option.setString(["对", "错"]);
            this.option.updateOptions();

            // hide multiple icon
            this.multipleIcon.setVisible(false);
            this.singleIcon.setVisible(false);
        } else {
            // multiple
            var options = questions.getQuestion().options.split("\t");
            this.option.setCount(options.length);
            this.option.setString(options);
            this.option.updateOptions();

            // show multiple icon
            if (questions.getQuestion().answer.length == 1) {
                this.multipleIcon.setVisible(false);
                this.singleIcon.setVisible(true);
            } else {
                this.multipleIcon.setVisible(true);
                this.singleIcon.setVisible(false);
            }
        }

        this.submitButton.setNormalImage(this.submitButtonDisableSprite);

        // update level label
        var index = this.currentQuestion + 1;
        this.levelLabel.setString(index + ";" + config.OverQuestions);
    },

    getMaxTimer: function () {
        return config.MaxTimer[this.level];
    },

    onEnter: function () {
        this._super();

        console.log("game scene: onEnter");

        // reset timer
        this.timer = this.getMaxTimer();
        this.timerLabel.setString("" + this.timer);

        // update question
        this.updateQuestion();

        // update score
        this.updateScore();

        // update hp
        this.updateHP();
    },

    updateHP: function () {
        // when hp = 1, show as 0
        var hp = this.hp - 1;
        this.hpLabel.setString(":" + hp);

        if (this.lastestScore != null) {
            if (this.lastestScore < 0) {
                // run animation
                var target = cc.Sprite.create(res.game_hp_png);
                target.setPosition(154, 1136 - 144);
                this.addChild(target, 3);

                var bezier = [
                    cc.p(640 / 2, -1136 / 2),
                    cc.p(-640 / 2, -1136 / 2),
                    cc.p(-640 / 2, -1136 / 2)
                ];
                target.runAction(cc.spawn(cc.fadeOut(2.3), cc.bezierBy(2, bezier)));
            }
        }
    },

    updateScore: function () {
        this.scoreLabel.setString("" + this.score);

        if (this.lastestScore != null) {
            var target = this.dynamicScoreLabel;
            if (this.lastestScore > 0) {
                target.setString("+" + this.lastestScore);
                target.setColor(cc.color(102, 163, 65, 255));
            } else {
                target.setString("" + this.lastestScore);
                target.setColor(cc.color(255, 0, 0, 255));
            }
            target.setPosition(560, 1136 - 205);
            target.setOpacity(255);
            target.runAction(cc.spawn(cc.fadeOut(3),
                cc.moveTo(2, 560, 1136 - 140)));
        }
    },

    over: function () {
        console.log("game scene: over");
        var resultScene = new ResultScene(false, this.score, false, true);
        cc.director.pushScene(resultScene);
    },

    timeOver: function () {
        console.log("game scene: time over");

        this._submit("");
    }
});