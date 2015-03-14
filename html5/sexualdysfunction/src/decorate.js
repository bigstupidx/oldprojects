/**
 * Created by Yu on 2014/9/12.
 */
Decorate = cc.Layer.extend({
    ctor: function (light, cloud, rainbow, car) {
        this._super();

        if (!light && !cloud && !rainbow && !car) {
            // has no animation
            var bg = cc.Sprite.create(res.rank_bg_png);
            bg.setAnchorPoint(0, 0);
            bg.setPosition(0, 0);
            this.addChild(bg);
        } else {
            this.bird = cc.Sprite.create(res.common_bird_png);
            this.bird.setPosition(640 / 2, 1136 / 2);
            this.addChild(this.bird);

            this.light = cc.Sprite.create(res.common_light_png);
            this.light.setPosition(320, 1136 - 485);
            this.light.setAnchorPoint(620 / 1389, 1000 / 1963);
            this.light.setScale(1.5);
            this.addChild(this.light);
            if (light) {
                var rotate = cc.rotateBy(12, 360).repeatForever();
                this.light.runAction(rotate);
            }

            this.cloud = cc.Sprite.create(res.common_cloud_png);
            this.cloud.setPosition(320, 0);
            this.cloud.setAnchorPoint(350 / 730, 39 / 439);
            this.cloud.setScale(1.15);
            this.addChild(this.cloud);
            if (cloud) {
                var scale = cc.sequence(cc.scaleTo(2, 1), cc.scaleTo(2, 1.15)).repeatForever();
                this.cloud.runAction(scale);
            }

            this.rainbow = cc.Sprite.create(res.common_rainbow_png);
            this.rainbow.setAnchorPoint(0.5, 0);
            this.rainbow.setPosition(472, 0);
            this.rainbow.setOpacity(0);
            this.addChild(this.rainbow);
            if (rainbow) {
                var sequence = cc.sequence(cc.fadeIn(1.5), cc.callFunc(function (target) {
                    target.runAction(cc.sequence(cc.scaleTo(1.8, 0.8), cc.scaleTo(1.8, 1)).repeatForever());
                }, this.rainbow));
                this.rainbow.runAction(sequence);
            }

            this.car = cc.Sprite.create(res.common_car_png);
            this.car.setPosition(320, 1136 - 985);
            this.car.setScale(1.0);
            this.addChild(this.car);
            if (car) {
                this.car.setPosition(660, 1136 - 779);
                this.car.setScale(0.5);
                this.car.runAction(cc.sequence(cc.spawn(cc.scaleTo(2, 1.0), cc.moveTo(2.0, 320, 1136 - 985)),
                    cc.callFunc(function (target) {
                        target.runAction(cc.sequence(cc.delayTime(0.2), cc.scaleTo(1.7, 0.9), cc.scaleTo(1.7, 1)).repeatForever());
                    })));
            }
        }

        this.setPosition(0, 0);
        this.setAnchorPoint(0, 0);
    }
});