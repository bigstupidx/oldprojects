/**
 * Created by Yu on 2014/8/24.
 */
Selector = cc.Layer.extend({
    BossCount: 3,
    focus: 0,

    ctor: function () {
        this._super();

        // focus the current boss
        this.focus = storage.getCurrentBoss();

        // add boss
        this.boss = new Array();

        for (var i = 0; i < this.BossCount; i++) {
            this.boss[i] = new Boss(i, this.getLocked(i));
            this.addChild(this.boss[i]);
        }

        this._updateSprite();
    },

    getLocked: function (boss) {
        if (boss == undefined)
            boss = this.focus;

        return (storage.getBoss() < boss) | false;
    },

    _updateSprite: function () {
        this.boss[this.focus].setPosition(320, 1136 - 470);
        this.boss[this.focus].setScale(1.0);
        this.boss[this.focus].setLocalZOrder(1);
        this.boss[this.focus].setOpacity(255);

        var right = this.boss[(this.focus + 1) % this.BossCount];
        right.setPosition(520, 1136 - 424);
        right.setScale(0.6);
        right.setOpacity(128);

        var left = this.boss[(this.focus + 2) % this.BossCount];
        left.setPosition(125, 1136 - 424);
        left.setScale(0.6);
        left.setOpacity(128);
    },

    _runAction: function () {
        {
            var target = this.boss[this.focus];
            var oldAction = target.getActionByTag(0);
            var duration = 0.2;
            var moveTo = cc.moveTo(duration, cc.p(320, 1136 - 470));
            var scaleTo = cc.scaleTo(duration, 1.0);
            var fadeTo = cc.fadeTo(duration, 255);
            var newAction = cc.spawn(moveTo, scaleTo, fadeTo);
            newAction.setTag(0);
            var action;
            if (oldAction == null) {
                action = newAction;
            } else {
                action = cc.sequence(oldAction, newAction);
                action.setTag(0);
            }
            target.stopAllActions();
            target.runAction(action);
            target.setLocalZOrder(1);
        }

        {
            var target = this.boss[(this.focus + 1) % this.BossCount];
            var oldAction = target.getActionByTag(0);
            var moveTo = cc.moveTo(duration, cc.p(520, 1136 - 424));
            var scaleTo = cc.scaleTo(duration, 0.6);
            var fadeTo = cc.fadeTo(duration, 128);
            var newAction = cc.spawn(moveTo, scaleTo, fadeTo);
            newAction.setTag(0);
            var action;
            if (oldAction == null) {
                action = newAction;
            } else {
                action = cc.sequence(oldAction, newAction);
                action.setTag(0);
            }
            target.stopAllActions();
            target.runAction(action);
        }

        {
            var target = this.boss[(this.focus + 2) % this.BossCount];
            var oldAction = target.getActionByTag(0);
            var moveTo = cc.moveTo(duration, cc.p(125, 1136 - 424));
            var scaleTo = cc.scaleTo(duration, 0.6);
            var fadeTo = cc.fadeTo(duration, 128);
            var newAction = cc.spawn(moveTo, scaleTo, fadeTo);
            newAction.setTag(0);
            var action;
            if (oldAction == null) {
                action = newAction;
            } else {
                action = cc.sequence(oldAction, newAction);
                action.setTag(0);
            }
            target.stopAllActions();
            target.runAction(action);
        }
    },

    moveLeft: function () {
        this.focus--;
        if (this.focus < 0) {
            this.focus = this.BossCount - 1;
        }
        //console.log("selector move left, focus = " + this.focus);

        this._runAction();
    },

    moveRight: function () {
        this.focus++;
        if (this.focus >= this.BossCount) {
            this.focus = 0;
        }
        //console.log("selector move right, focus = " + this.focus);

        this._runAction();
    },

    getFocus: function () {
        return this.focus;
    }
});