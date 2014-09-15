MS.Extend = function(arg1){
	MS.DrawAble.call(this,arg1);
	this.arg1 = arg1;
};
WGame.extend(MS.Extend,MS.DrawAble);

WGame.apply(MS.Extend.prototype,
	{
		initEl : function(){
			
		},
		hover : function(hovered){
		},
		control : function(){
		},
		draw : function(context){
		}
	}
);
