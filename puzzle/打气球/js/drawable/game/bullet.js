MS.Bullet = function(){
	MS.DrawAble.call(this);
	this.initEl();
};
WGame.extend(MS.Bullet,MS.DrawAble);

WGame.apply(MS.Bullet.prototype,
	{
		count : 0,
		bullet_sprite:null,
		initEl : function(){
			this.bullet_sprite = new MS.Sprite('bullet');
		},
		draw : function(context){
			this.count ++;
			
			if(MS.config.debug){
				context.beginPath();
				context.arc(this.x,this.y,this.r,0,Math.PI*2);
	            context.closePath();
	            context.fillStyle = 'rgba(255, 0, 0, 1)';
	            context.fill();
			}
            
            this.bullet_sprite.draw(context,this.x-this.r,this.y-this.r);
            
            this.move();
		},
		move:function(){
			this.x -= MS.config.bullet_spd;
			this.y += Math.pow(this.count/(MS.config.FPS),2) * MS.config.bullet_g;
		}
	},
	new MS.Circle()
);
