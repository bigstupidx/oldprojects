MS.Balloon = function(){
	MS.DrawAble.call(this);
	this.initEl();
};
WGame.extend(MS.Balloon,MS.DrawAble);

WGame.apply(MS.Balloon.prototype,
	{
		img: null,
		a_img:null,
		isImg : false,
		name: 'balloon',
		index: 1,
		content:'',
		type:'text',
		circle : null,
		answer:null,
		boom: false,
		boomCount : 0,
		boomBlock : 8,
		initEl : function(){
			var imgR = MS.config.ball_radius;
			
			this.circle = new MS.Circle();
			this.circle.setR(imgR);
		},
		setAnswer:function(a){
			this.answer = a;
			this.a_img = new Image();
			this.a_img.src = this.answer.src;
			self = this;
			this.a_img.onload = function(){
				self.isImg = true;
			};
		},
		setPos:function(x,y){
			this.x = x;
			this.y = y;
			var imgOffx = 117;
			this.circle.setPos(this.x + imgOffx,this.y + this.circle.r + 1);
		},
		getPos:function(degree,r){
			var pos = {};
			
			pos.x = this.x + r*Math.cos(degree);
			pos.y = this.y + r*Math.sin(degree);
			return pos;
		},
		draw : function(context){
			
			this.drawBalloon(context);
            if(this.boom){
            	this.boomCount ++;
            	
            	if(this.boomCount < 40){
            		//这里处理爆炸效果
//            		for(var i=0 ; i<this.boomBlock ; i++ ){
//                		var pos = this.getPos(Math.PI*2 *i /this.boomBlock,this.boomCount);
//                		
//                		context.beginPath();
////            			context.arc(pos.x,pos.y,this.r, Math.PI/2*this.boomBlock + Math.PI*2 *i /this.boomBlock,Math.PI/2*this.boomBlock + Math.PI*2 *(i+1) /this.boomBlock);
//            			context.arc(pos.x,pos.y,this.r, Math.PI*2 *i /this.boomBlock, Math.PI*2 *(i+1) /this.boomBlock);
////            			context.lineTo(pos.x,pos.y);
//                        context.closePath();
//                        context.fillStyle = 'rgba(0, 255, 0, 0.5)';
//                        context.fill();
//                	}
            	}
            }else{
            	this.move();
            }
		},
		drawBalloon : function(context){
        	context.drawImage(this.img,this.x,this.y,this.img.width,this.img.height);
        	
        	context.textBaseline="baseline";
			context.font =14 +"px Microsoft Yahei";
			
			context.lineWidth = 4;
			
//			var txt ='A' + (this.index + 1),
//				tx = this.circle.x-12,
//				ty = this.circle.y;
//			
//			context.strokeStyle = '#fff';
//			context.strokeText(txt,tx,ty);
//			
//			context.fillStyle = '#e71f19';
//			
//			context.save();
//			
//			MS.TOOL.setShadow(context,"rgba(0,100,100,0.5)",3,3,3);
//			
//			context.fillText(txt,tx,ty);
//			
//			context.restore();
			
			if(this.isImg){
				context.drawImage(this.a_img,this.x + 19,this.y + 69,this.a_img.width,this.a_img.height);
			}
//			else{
//				var str = this.answer.title;
//				
//				if(MS.config.showAnswer){
//					str +=  ('--'+ this.answer.id);
//				}
//				
//				context.font ="blod " + 14*MS.scale +"px Microsoft Yahei";
//				
//				context.strokeStyle = '#fff';
//				context.strokeText(str,tx-40,ty+45);
//				
//				context.fillStyle = '#313131';
//				context.fillText(str,tx-40,ty+45);
//			}
			
			if(MS.config.debug){
				context.beginPath();
				context.arc(this.circle.x,this.circle.y,this.circle.r,0,Math.PI*2);
				context.closePath();
				context.fillStyle = 'rgba(0, 255, 0, 0.5)';
				context.fill();
			}
		},
		move:function(){
			if(!this.boom){
				this.y -= MS.config.ball_spd;
				this.circle.y -= MS.config.ball_spd;
			}
		},
		broken:function(){
			this.boom = true;
//			MS.playSoundDelayed('broken',100);
		},
		outScreen:function(){
			if(this.y + this.h < 0){
				return true;
			}
			return false;
		},
		setIndex : function(index){
			this.index = index;
			
			this.img = new Image(); 
			this.img.src="image/balloon_"+(this.index + 1)+".png";
			
			var self = this;
			
			this.img.onload = function(){
				self.setW(self.img.width);
				self.setH(self.img.height);
			};
		},
		setType:function(type){
			this.type = type;
		},
		getAnswerId:function(){
			return this.answer.id;
		}
	},
	new MS.Box()
);
