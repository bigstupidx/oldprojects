MS.Shooter = function(){
	MS.DrawAble.call(this);
	this.initEl();
};
WGame.extend(MS.Shooter,MS.DrawAble);

WGame.apply(MS.Shooter.prototype,
	{
		toY : -1,
		canShoot : true,
		shootCount:0,
		bullets : [],
		platform_img: null,
		rope_img:null,
		r_count:0,
		rope_i:0,
		
		shooter_sprite:null,
		gear_top_sprite:null,
		gear_bottom_sprite:null,
		
		moving:false,
		moveDir: 1,

		arr_top_img:null,
		arr_bot_img:null,
		
		initEl : function(){
			this.chair_img = new Image(); 
			this.chair_img.src="image/platform.png";
			
			this.rope_img = new Image(); 
			this.rope_img.src="image/rope_0.png";
			
			this.setW(MS.config.s_w);
			this.setH(MS.config.s_h);
			
			this.shooter_sprite = new MS.Sprite('shooter');
			this.gear_top_sprite = new MS.Sprite('gear_top');
			this.gear_bottom_sprite = new MS.Sprite('gear_bottom');
			
			this.arr_top_img = new Image();
			this.arr_top_img.src = "image/arr_top.png";
			
			this.arr_bot_img = new Image();
			this.arr_bot_img.src = "image/arr_bot.png";
		},
		control:function(x,y){
			var arr_x = this.x + 47,
				arr_top_y = 18,
				arr_w = this.arr_top_img.width,
				arr_bot_y = MS.rh-arr_w - 5;
			
			if( x > arr_x && x < arr_x + arr_w && y > arr_top_y && y < arr_top_y + arr_w){
				this.move(1);
			}else if( x > arr_x && x < arr_x + arr_w && y > arr_bot_y && y < arr_bot_y + arr_w){
				this.move(2);
			}else{
				this.shoot();
			}
		},
		draw : function(context){
			
			this.x=MS.rw - (this.w + MS.config.s_offset_w);
			
			if(!this.canShoot){
				this.shootCount ++ ;
				
				if(this.shootCount > MS.config.bullet_interval_t / MS.config.rt){
					this.canShoot = true;
				}
			}
			
			if(this.toY != -1 && this.toY != this.y){
				if(this.toY > this.y){
					this.y += MS.config.s_spd;
					if(this.y > this.toY){
						this.y = this.toY;
						this.moving = false;
					}
				}else{
					this.y -= MS.config.s_spd;
					if(this.y < this.toY){
						this.y = this.toY;
						this.moving = false;
					}
				}
			}
			
			this.drawRope(context);
			
			//绘制齿轮
			this.gear_top_sprite.draw(context,this.x,0);
			this.gear_bottom_sprite.draw(context,this.x + 42,MS.rh-this.gear_bottom_sprite.h);
			
			this.drawArr(context);
			
			//绘制椅子
			context.drawImage(this.chair_img,this.x+6,this.y+50,this.chair_img.width,this.chair_img.height);
			
			//绘制射手人物
			this.shooter_sprite.draw(context,this.x,this.y);
			if(MS.config.debug){
				context.strokeStyle = '#f0f000';
				context.strokeRect(this.x,this.y,this.w,this.h);
			}
			this.drawArr(context);
		},
		drawBullet:function(context){
			for(var i = this.bullets.length - 1 ; i >= 0 ; i--){
				
				var bullet = this.bullets[i];
				if(bullet.x < 0 || bullet.y > MS.rh){
					this.bullets.remove(i);
				}else{
					this.bullets[i].draw(context);
				}
			}
		},
		drawRope:function(context){
			this.r_count ++ ;
			var rope_x = this.x + 46,
				rope_y = 46,
				rope_w = this.rope_img.width,
				rope_h = MS.rh-this.gear_bottom_sprite.h;
			
			var ptrn = context.createPattern(this.rope_img,"repeat");
			context.fillStyle = ptrn;
			
			context.save();
			context.translate(rope_x,rope_y);
			context.fillRect(0, 0, rope_w, rope_h);
			
			context.translate(92 - rope_w*2,0);
			context.fillRect(0, 0, rope_w, rope_h);
			
			context.restore();
		},
		getRopeX : function(){
			return this.x + 46;
		},
		drawArr:function(context){
			var arr_x = this.x + 47,
				arr_top_y = 18,
				arr_w = this.arr_top_img.width,
				arr_bot_y = MS.rh-arr_w - 5;
			
//			context.save();
			
//			context.globalAlpha= (Math.sin(this.r_count/7) + 1) / 2;
			
			context.drawImage(this.arr_top_img,arr_x,arr_top_y,arr_w,arr_w);
			context.drawImage(this.arr_bot_img,arr_x,arr_bot_y,arr_w,arr_w);
			
//			context.restore();
		},
		getTopArrBox:function(){
			
		},
		move:function(dir){
			if(dir == 1){
				this.moveTo(MS.config.s_offset_t);
			}else if(dir == 2){
				this.moveTo(MS.rh - MS.config.s_offset_b - this.h);
			}
		},
		stopMove:function(){
			this.moving = false;
			this.toY = this.y;
		},
		moveTo: function(y){
			
			if(y < MS.config.s_offset_t){
				y = MS.config.s_offset_t;
			}
			if(y > MS.rh - MS.config.s_offset_b - this.h){
				y = MS.rh - MS.config.s_offset_b - this.h;
			}
			this.toY = y;
			this.gear_top_sprite.restart();
			this.gear_bottom_sprite.restart();
			this.moving = true;
		},
		shoot:function(){
			if(this.canShoot){
				this.canShoot = false;
				this.shootCount = 0;
				
				var bullet = new MS.Bullet();
				bullet.setR(MS.config.bullet_radius);
				bullet.setPos(this.x - bullet.r/2 - 3 , this.y + this.h/2);
				
				this.bullets.push(bullet);
				
				this.shooter_sprite.restart();
				
				MS.playSound('shoot');
			}
		},
		clearBullet : function(){
			this.bullets = [];
		}
	},
	new MS.Box()
);
