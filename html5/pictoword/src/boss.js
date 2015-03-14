/**
 * Created by Administrator on 2014/8/25.
 */
Boss = cc.Layer.extend({
    boss: 0,
    locked: false,

    boss_png: [
        res.selector_boss1_png,
        res.selector_boss2_png,
        res.selector_boss3_png
    ],

    ctor: function (boss, locked) {
        this._super();

        this.boss = boss;

        if (typeof locked == undefined) {
            locked = false;
        }
        this.locked = locked;

        this.bossSprite = cc.Sprite.create(this.boss_png[this.boss]);
        this.addChild(this.bossSprite);

        if (this.locked) {
            this.lockSprite = cc.Sprite.create(res.selector_lock_png);
            this.lockSprite.setScale(1.5);
            this.addChild(this.lockSprite);
        }

        this.setAnchorPoint(0, 0);

        this.cascadeColor = true;
        this.cascadeOpacity = true;
    },

    setScale: function(scale) {
        this._super(scale);
    }
});