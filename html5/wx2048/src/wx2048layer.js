var GAME_STATE_GUIDE = 0;
var GAME_STATE_RUNNING = 1;
var GAME_STATE_OVER = 2;
var GAME_STATE_SHARE = 3;

var wx2048Layer = cc.LayerColor.extend({
    score: 0,
    bestScore: 0,
    scoreLabel: null,
    bestScoreLabel: null,

    ctor: function () {
        this._super();

        var self = this;
        var winSize = cc.director.getWinSize();
        console.log(winSize.width + ", " + winSize.height);

        // read in best score
        var bestScore;
        bestScore = cc.sys.localStorage.getItem("bestScore");
        if (bestScore) {
            self.bestScore = parseInt(bestScore);
        }

        // game sheet
        cc.spriteFrameCache.addSpriteFrames(res.game_sheet_plist);

        // bg
        var bg = self._bgLayer = cc.Sprite.create(res.main_bg_png);
        bg.setAnchorPoint(0, 0);
        bg.setPosition(0, 0);
        self.addChild(bg, 0);

        // score label
        self.scoreLabel = new cc.LabelTTF("" + self.score, "Arial", 25,
            cc.size(168, 30), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP);
        self.scoreLabel.setAnchorPoint(0, 0);
        self.scoreLabel.attr({
            x: 45,
            y: 1136 - 325
        });
        self.scoreLabel.setColor(cc.color.WHITE);
        self.addChild(self.scoreLabel, 2);

        // best score label
        self.bestScoreLabel = new cc.LabelTTF("" + self.bestScore, "Arial", 25,
            cc.size(168, 30), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP);
        self.bestScoreLabel.setAnchorPoint(0, 0);
        self.bestScoreLabel.attr({
            x: 244,
            y: 1136 - 325
        });
        self.bestScoreLabel.setColor(cc.color.WHITE);
        self.addChild(self.bestScoreLabel, 2);

        // button3
        var button3 = cc.Sprite.create(res.main_restart_png);
        var restartMenuItem = new cc.MenuItemSprite(button3, null, this.restart, this);
        restartMenuItem.setAnchorPoint(0, 0);
        restartMenuItem.setPosition(438, 1136 - 332);

        this.menu = new cc.Menu(restartMenuItem);
        this.menu.setPosition(0, 0);
        this.addChild(this.menu, 1);

        // grid
        self.grid = Grid.create();
        self.grid.setPosition(16, 1136 - 1010);
        self.addChild(self.grid, 1);

        // set state
        self.state = GAME_STATE_RUNNING;
    },

    onEnter: function () {
        this._super();

        // enter guide
        this.state = GAME_STATE_GUIDE;

        this.guide = new Guide();
        this.addChild(this.guide, 6);
    },

    updateScore: function (score) {
        var self = this;
        self.score = score;
        self.scoreLabel.setString("" + score);

        if (self.score > self.bestScore) {
            self.updateBestScore(self.score);
        }

        if (this.gameOverLayer) {
            this.gameOverLayer.scoreLabel.setString("" + score);
        }

        // wechat share
        if (cc.sys.browserType == cc.sys.BROWSER_TYPE_WECHAT) {
            wxUpdateData(self.bestScore);
        }
    },

    updateBestScore: function (bestScore) {
        var self = this;
        self.bestScore = bestScore;
        self.bestScoreLabel.setString("" + bestScore);

        // save best score
        cc.sys.localStorage.setItem("bestScore", "" + self.bestScore);
    },

    restart: function () {
        this.updateScore(0);

        if (this.guide) {
            this.removeChild(this.guide);
            this.guide = null;
        }

        if (this.gameOverLayer) {
            this.removeChild(this.gameOverLayer);
        }

        if (this.shareLayer) {
            this.removeChild(this.shareLayer);
        }

        this.grid.restart();

        // set game to running.
        this.state = GAME_STATE_RUNNING;
    },

    gameOver: function () {
        console.log("game over");
        if (!this.gameOverLayer) {
            this.gameOverLayer = new GameOver();
            this.gameOverLayer.setPosition(16, 1136 - 1010);
        }
        this.addChild(this.gameOverLayer, 2);

        this.state = GAME_STATE_OVER;
    },

    share: function () {
        console.log("share");

        if (this.state != GAME_STATE_OVER)
            return;

        if (!this.shareLayer) {
            this.shareLayer = new Share();
        }
        this.addChild(this.shareLayer, 3);

        this.state = GAME_STATE_SHARE;
    }
});
