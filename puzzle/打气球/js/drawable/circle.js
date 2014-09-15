MS.Circle = function(){
	
};
MS.Circle.prototype = {
	self : this,
	r : 0,
	x : 0,
	y : 0,
	name : 'circle',
	getX : function(){
		return this.x;
	},
	getY : function(){
		return this.y;
	},
	getR : function(){
		return this.r;
	},
	setPos : function(x,y){
		this.x = x;
		this.y = y;
	},
	setR : function(r){
		this.r = r;
	},
	collisionPoint : function(x,y){
		if(Math.sqrt(Math.pow(Math.abs(this.x - x) , 2) + Math.pow(Math.abs(this.y - y) , 2)) <= this.r){
			return true;
		}else{
			return false;
		}
	},
	collisionCircle : function(circle){
		if(Math.sqrt(Math.pow(Math.abs(this.x - circle.x) , 2) + Math.pow(Math.abs(this.y - circle.y) , 2)) <= (this.r + circle.r)){
			return true;
		}else{
			return false;
		}
	}
};