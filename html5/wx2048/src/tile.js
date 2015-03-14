/**
 * Created by Yu on 2014/8/15.
 */
var icons = new Array(17);

var Tile = cc.Layer.extend({
    offsetX: 18,
    offsetY: 18,
    gap: 16,
    icon: null,
    icons: [
        null,
        res.game_2_png,
        res.game_4_png,
        res.game_8_png,
        res.game_16_png,
        res.game_32_png,
        res.game_64_png,
        res.game_128_png,
        res.game_256_png,
        res.game_512_png,
        res.game_1024_png,
        res.game_2048_png,
        res.game_4096_png,
        res.game_8192_png,
        res.game_16384_png,
        res.game_32768_png,
        res.game_65536_png
    ],
    level: 0,
    size: 132,
    position: {
        x: 0,
        y: 0
    },
    previousPosition: null,
    mergedFrom: null,

    ctor: function (position, level, merged) {
        this._super();

        this.position = position;

        if (level == null)
            level = 0;
        this.level = level;
        if (this.level == 0) {
            alert("create tile with level 0");
        }

        if (merged == null)
            merged = false;
        this.merged = merged;

        // Tracks tiles that merged together
        this.previousPosition = null;
        this.mergedFrom = null;

        // icon
        this.icon = cc.Sprite.create("#" + this.icons[this.level]);
        this.icon.setAnchorPoint(0.5, 0.5);
        this.addChild(this.icon);

        // update position
        this.updatePosition(this.position);

        // create animation
        this.actCreateAnimation();
    },

    savePosition: function () {
        this.previousPosition = this.position;
    },

    updatePosition: function (position) {
        console.log("updatePosition, (" + this.position.x + ", " + this.position.y + ") -> ("
            + position.x + ", " + position.y + ")");

        this.position = position;

        position = this.getIconPosition(this.position);
        this.icon.setPosition(position.x, position.y);
    },

    getIconPosition: function (position) {
        return {
            x: this.offsetX + position.x * (this.size + this.gap) + this.size / 2,
            y: this.offsetY + (GridSize - 1 - position.y) * (this.size + this.gap) + this.size / 2
        };
    },

    moveToPosition: function (position) {
        var iconPosition = this.getIconPosition(position);
        var moveTo = cc.MoveTo.create(0.2, iconPosition.x, iconPosition.y);
        this.icon.runAction(cc.EaseSineIn.create(moveTo));

        this.position = position;
    },

    actCreateAnimation: function () {
        if (this.merged) {
            this.icon.runAction(cc.Sequence.create(cc.ScaleTo.create(0.1, 1.2, 1.1), cc.ScaleTo.create(0.2, 1, 1)));
        } else {
            this.icon.setScale(0.1, 0.1);
            this.icon.runAction(cc.ScaleTo.create(0.2, 1, 1));
        }
    }
});