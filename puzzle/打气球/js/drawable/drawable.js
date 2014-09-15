MS.DrawAble = function(){
	
};

MS.DrawAble.prototype = {
	self : this,
	initEl: function(){
		
	},
	collision : function(x,y){
		return MS.TOOL.collision(x,y,this);
	},
	draw : function(){
		
	},
	setControl : function(canvas){
		$(canvas).off(MS.CONST.TOGGLEEVENT);
		var self = this;
		
		$(canvas).on(MS.CONST.TOGGLEEVENT,function(e){
			self.control(e);
		});
		
	},
	control : function(e){
		
	}
};
