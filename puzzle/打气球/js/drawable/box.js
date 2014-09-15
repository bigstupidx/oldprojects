MS.Box = function(){
	
};

MS.Box.prototype = {
	self : this,
	h : 0,
	w : 0,
	x : 0,
	y : 0,
	getX : function(){
		return this.x;
	},
	getY : function(){
		return this.y;
	},
	getW : function(){
		return this.w;
	},
	getH : function(){
		return this.h;
	},
	setPos : function(x,y){
		this.x = x;
		this.y = y;
	},
	setW : function(w){
		this.w = w;
	},
	setH : function(h){
		this.h = h;
	},
	collisionPoint : function(x,y){
		if( x > this.x && x < this.x + this.w && y > this.y && y < this.y + this.h){
			return true;
		}else{
			return false;
		}
	},
	collisionBox : function(box){
		if(box.x - this.x < this.w && box.y - this.y < this.h){
			return true;
		}else if(this.x - box.x < box.w && this.y - box.y < box.h){
			return true;
		}else{
			return false;
		}
	}
};