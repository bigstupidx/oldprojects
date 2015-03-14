var STATE_STANDBY = 0;
var STATE_RUNNING = 1;
var STATE_OVER = 2;

var RbgyLayer = cc.Layer.extend({
    _actionSprite: null,

    _redBlock: null,
    _blueBlock: null,
    _greenBlock: null,
    _yellowBlock: null,

    _prompt: null,

    /** yellow text */
    _redText: null,
    _blueText: null,
    _greenText: null,
    _yellowText: null,

    _texts: [
        this._redText,
        this._blueText,
        this._greenText,
        this._blueText
    ],

    _colors: [
        cc.color.RED,
        cc.color.BLUE,
        cc.color.GREEN,
        cc.color.BLUE
    ],

    _score: 0,
    _textIndex: 0,
    _colorIndex: 0,

    _state: STATE_STANDBY,

    createBlocks: function () {
        // red block
        this._redBlock = cc.Sprite.create(res.Dot_png);
        this._redBlock.attr({
            x: 0,
            y: 0,
            width: 1,
            height: 1,
            scaleX: DESIGN_WIDTH / 2,
            scaleY: DESIGN_HEIGHT / 2
        });
        this._redBlock.setAnchorPoint(0, 0);
        this._redBlock.setColor(cc.color(255, 0, 0, 255));
        this.addChild(this._redBlock, 0);

        // blue block
        this._blueBlock = cc.Sprite.create(res.Dot_png);
        this._blueBlock.attr({
            x: 0,
            y: DESIGN_HEIGHT / 2,
            width: 1,
            height: 1,
            scaleX: DESIGN_WIDTH / 2,
            scaleY: DESIGN_HEIGHT / 2
        });
        this._blueBlock.setAnchorPoint(0, 0);
        this._blueBlock.setColor(cc.color(0, 255, 0, 255));
        this.addChild(this._blueBlock, 0);

        // green block
        this._greenBlock = cc.Sprite.create(res.Dot_png);
        this._greenBlock.attr({
            x: DESIGN_WIDTH / 2,
            y: 0,
            width: 1,
            height: 1,
            scaleX: DESIGN_WIDTH / 2,
            scaleY: DESIGN_HEIGHT / 2
        });
        this._greenBlock.setAnchorPoint(0, 0);
        this._greenBlock.setColor(cc.color(0, 0, 255, 255));
        this.addChild(this._greenBlock, 0);

        // yellow block
        this._yellowBlock = cc.Sprite.create(res.Dot_png);
        this._yellowBlock.attr({
            x: DESIGN_WIDTH / 2,
            y: DESIGN_HEIGHT / 2,
            width: 1,
            height: 1,
            scaleX: DESIGN_WIDTH / 2,
            scaleY: DESIGN_HEIGHT / 2
        });
        this._yellowBlock.setAnchorPoint(0, 0);
        this._yellowBlock.setColor(cc.color(255, 255, 0, 255));
        this.addChild(this._yellowBlock, 0);

        // score
        var fontDefRedStrokeShadow = new cc.FontDefinition();
        fontDefRedStrokeShadow.fontName = "Arial";
        fontDefRedStrokeShadow.fontSize = 72;
        fontDefRedStrokeShadow.textAlign = cc.TEXT_ALIGNMENT_CENTER;
        fontDefRedStrokeShadow.verticalAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        fontDefRedStrokeShadow.fillStyle = cc.color.WHITE;
        //fontDefRedStrokeShadow.boundingWidth = blockSize.width;
        //fontDefRedStrokeShadow.boundingHeight = blockSize.height;
        // stroke
        fontDefRedStrokeShadow.strokeEnabled = true;
        fontDefRedStrokeShadow.strokeStyle = cc.color.BLACK;
        // shadow
        fontDefRedStrokeShadow.shadowEnabled = true;
        fontDefRedStrokeShadow.shadowOffsetX = 2;
        fontDefRedStrokeShadow.shadowOffsetY = 2;   //shadowOffset;

        this._scoreLabel = cc.LabelTTF.create(this._score, fontDefRedStrokeShadow);
        this._scoreLabel.setColor(cc.color.WHITE);
        this._scoreLabel.attr({
            x: DESIGN_WIDTH / 2,
            y: DESIGN_HEIGHT - 40
        });
        this.addChild(this._scoreLabel, 2);
    },

    createTextures: function () {
        this._texts[0] = this._redText = cc.textureCache.addImage(res.Red_png);
        this._texts[1] = this._blueText = cc.textureCache.addImage(res.Blue_png);
        this._texts[2] = this._greenText = cc.textureCache.addImage(res.Green_png);
        this._texts[3] = this._yellowText = cc.textureCache.addImage(res.Yellow_png);
    },

    createActionSprite: function () {
        this._actionSprite = cc.Sprite.create(this._texts[this._textIndex]);
        this._actionSprite.attr({
            x: DESIGN_WIDTH / 2,
            y: DESIGN_HEIGHT / 2
        });
        this._actionSprite.setColor(this._colors[this._colorIndex]);
        this.addChild(this._actionSprite, 2);
    },

    changeActionSprite: function () {
        // get text
        this._textIndex = 0 | Math.random() * 4;
        this._actionSprite.setTexture(this._texts[this._textIndex]);

        // get color
        this._colorIndex = 0 | Math.random() * 4;
        this._actionSprite.setColor(this._colors[this._colorIndex]);
    },

    acceptTouch: function () {
        // accept touch now!
        if (cc.sys.capabilities.hasOwnProperty('keyboard'))
            cc.eventManager.addListener({
                event: cc.EventListener.KEYBOARD,
                onKeyPressed: function (key, event) {
                    MW.KEYS[key] = true;
                },
                onKeyReleased: function (key, event) {
                    MW.KEYS[key] = false;
                }
            }, this);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan: this.onTouchBegan
        }, this);
},

    onTouchBegan:function (touch, event) {
        var target = event.getCurrentTarget();
        var getPoint = touch.getLocation();

        var index;
        var x = 0 | getPoint.x / (DESIGN_WIDTH / 2);
        var y = 0 | getPoint.y / (DESIGN_HEIGHT / 2);
        index = x + 2 * y;
        console.log(index, x, y);

        if (target._state == STATE_STANDBY) {
            target._state = STATE_RUNNING;
            target.removeChild(target._prompt);

            if (index == target._textIndex) {
                target.updateScore(target._score + 1);
                target.changeActionSprite();
            }
        } else if (target._state == STATE_RUNNING) {
            if (index == target._textIndex) {
                target.updateScore(target._score + 1);
                target.changeActionSprite();
            }
        }

        return true;
    },

    updateScore: function(score) {
        this._score = score;
        this._scoreLabel.setString(this._score);
    },

    ctor: function () {
        // 1. super init first
        this._super();

        // ask director the window size
        var size = cc.director.getWinSize();

        // create blocks
        this.createBlocks();

        // create textures
        this.createTextures();

        // create action sprite
        this.createActionSprite();

        // change action sprite at first
        this.changeActionSprite();

        // create and add prompt text
        this._prompt = cc.Sprite.create(res.Prompt_png);
        this._prompt.attr({
            x: size.width / 2,
            y: 100
        });
        this.addChild(this._prompt, 1);

        // accept touch
        this.acceptTouch();

        // end with a return true
        return true;
    }
});

