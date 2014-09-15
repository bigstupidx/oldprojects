MS.Sprite = function(name){
	this.initEl(name);
};

WGame.apply(MS.Sprite.prototype,
	{
		name:'',
		action:null,
		frame:null,
		_action:0,
		_frame:0,
		frames:0,
		img:null,
		
		play:false,
		loop:0,
		
		count:0,
		initEl:function(name){
			this.name = name;
			if(!MS.sprite[name]){
				return;
			}
			
			this.setAction(0);
		},
		setAction:function(action){
			this._action = action;
			this.action = MS.sprite[this.name].actions[this._action];
			
			if(!this.img){
				this.img = new Image();
			}
			
			this.img.src = 'image/action/'+this.name + '_' + this._action +'.png';
			
			this.setW(this.action.w);
			this.setH(this.action.h);
			
			this.play = true;
		},
		draw:function(context,x,y){
			
			context.drawImage(
					this.img,
					this.action.x + this._frame * this.action.w,
					this.action.y,
					this.action.w,
					this.action.h,
					x,
					y,
					this.w,
					this.h);
			
			this.nextFrame();
		},
		nextFrame:function(){
			this.count ++;
			
			if(this.count % this.action.frame_iv == 0 && this.play){
				this._frame ++ ;
				
				if(this._frame > this.action.frames - 1){
					this.resetFrame();
				}
			}
		},
		resetFrame:function(){
			this._frame = 0;
			if(this.action.isloop == false){
				this.play = false;
			}
		},
		pause:function(){
			this.play = false;
		},
		resume:function(){
			this.play = true;
		},
		restart:function(){
			this._frame = 0;
			this.play = true;
		}
	},
	new MS.Box()
);