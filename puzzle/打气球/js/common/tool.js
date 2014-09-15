MS.TOOL = {
	//绘制最高4位的数字
	drawNumber : function(ctx,img,num,w,h,x,y,add){
		var str = ''+num,
			len = str.length,
			n = 0,
			index = 0,
			dw = w,
			dh = h;
		
		if(add){
			index = 1;
			ctx.drawImage(img,10*w,0,w,h,x ,y,dw,dh);
		}
		while( len-- > 0){
			var p = (Math.pow(10,len)),
				_p = p * 10;
			n = Math.floor(num % _p / p);
			
			ctx.drawImage(img,n*w,0,w,h,x + dw * index ,y,dw,dh);
			index ++ ;
		}
	},
	//绘制最高4位的数字，绘制0，增加间距
	drawNumberCD : function(ctx,img,num,w,h,x,y,distance){
		var len = 2,
			n = 0,
			index = 0,
			dw = w,
			dh = h;
		
		while( len-- > 0){
			var p = (Math.pow(10,len)),
				_p = p * 10;
			n = Math.floor(num % _p / p);
			
			ctx.drawImage(img,n*w,0,w,h,x + distance * index ,y,dw,dh);
			index ++ ;
		}
	},
	strBuffer:{
		str:'',
		split_index:0,
		change:false
	},
	//绘制文字，根据宽度自动换行
	drawTextByWidth:function(ctx,str,x,y,w,h,func1,func2){
		
		var len,
			split_index = 0,
			change = false;
		
		if(MS.TOOL.strBuffer.str != str){
			//初始化缓存
			MS.TOOL.strBuffer.str = str;
			MS.TOOL.strBuffer.str_width = ctx.measureText(str).width;
			MS.TOOL.strBuffer.len = str.length;
			
			if(MS.TOOL.strBuffer.str_width > w){
				for(var i=0 ; i< str.length ; i++){
					var width = ctx.measureText(str.slice(0,i)).width;
					
					if(width > w){
						MS.TOOL.strBuffer.split_index = i - 1;
						MS.TOOL.strBuffer.change = true;
						break;
					}
				}
			}else{
				MS.TOOL.strBuffer.split_index = 0;
				MS.TOOL.strBuffer.change = false;
			}
		}
		
		split_index = MS.TOOL.strBuffer.split_index;
		change = MS.TOOL.strBuffer.change ;
		len = MS.TOOL.strBuffer.len;
		
		if(func1 && ctx[func1]){
			
			if(change){//单行
				ctx[func1](str.slice(0,split_index),x,y-h/4,w);
				ctx[func1](str.slice(split_index,len),x,y + h/4,w);
			}else{//两行
				ctx[func1](str,x,y);
			}
		}
		
//		if(func && ctx[func]){
//			
//			if(len * width < w){//单行
//				ctx[func](str,x,y);
//			}else{//两行
//				var l1 = parseInt(w / width);
//				ctx[func](str.slice(0,l1),x,y-h/4,w);
//				ctx[func](str.slice(l1,len),x,y + h/4,w);
//			}
//		}
	},
	setShadow : function(context,color,x,y,offset){
		context.shadowColor = color;  
        //在X轴上偏移5(左)  
		context.shadowOffsetX = x;  
        //在Y轴上偏移5(左)  
		context.shadowOffsetY = y;  
        //高斯模糊  
		context.shadowBlur = offset; 
	},
	getRandomNum : function (Min,Max)
	{   
		var Range = Max - Min;   
		var Rand = Math.random();   
		return(Min + Math.round(Rand * Range));   
	},
	collision : function(x,y,box){
		if( x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h){
			return true;
		}else{
			return false;
		}
	},
};

function $id(id) {
	return document.getElementById(id);
};

function preload(list, path, fileloaded, callback){
	var loaded = 0;
	var total = list.length;
	
	var loadImg = function (src){
		var img = new Image();
		img.onload = img.onerror = function(){
			loaded++;
			fileloaded && fileloaded(loaded/total);
			if(loaded == total) {
				callback && callback();
			} else {
				setTimeout(function(){
					loadImg(list.shift());
				},10);
//				,100);
				
			};
		};
		img.src = path + src;
	};
	
	loadImg(list.shift());
	
};

function getURLParameter(name) {
	return decodeURIComponent(
		(RegExp("[?|&]" + name + "=(.+?)(&|$)").exec(location.search)||[,null])[1]
	);
};

function isArray(obj) {
	return Object.prototype.toString.call( obj ) === "[object Array]";
};

Array.prototype.shuffle = function() {
    var i = this.length,
        j, temp;
    if (i == 0) return this;
    while (--i) {
        j = Math.floor(Math.random() * (i + 1));
        temp = this[i];
        this[i] = this[j];
        this[j] = temp;
    };
    return this;
};

function randomsort(a, b) {
	return Math.random()>0.5 ? -1 : 1;//用Math.random()函数生成0~1之间的随机数与0.5比较，返回-1或1
}

function getType(o)
{
    var _t;
    return ((_t = typeof(o)) == "object" ? o==null && "null" || Object.prototype.toString.call(o).slice(8,-1):_t).toLowerCase();
}

function clone(destination,source)
{
    for(var p in source)
    {
        if(getType(source[p])=="array"||getType(source[p])=="object")
        {
            destination[p]=getType(source[p])=="array"?[]:{};
            arguments.callee(destination[p],source[p]);
        }
        else
        {
            destination[p]=source[p];
        }
    }
}