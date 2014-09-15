Array.prototype.remove = function(dx) {
	if(isNaN(dx)||dx>this.length){
		return false;
	}
	this.splice(dx,1);
};

function arr_del(arr,d){
    return arr.slice(0,d-1).concat(arr.slice(d));
}