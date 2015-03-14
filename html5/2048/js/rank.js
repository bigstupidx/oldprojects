function Rank() {
	// set back button's click function.
	this.html = "";
	this.index = 0;

	// disable window scroll.
	document.addEventListener('touchmove', function (e) { e.preventDefault(); }, false);
}

Rank.prototype.createIScroll = function(index) {
	if (this.iscroll != null) {
		this.iscroll.destroy();
	}
	this.iscroll = new IScroll('#wrapper', { mouseWheel: true }, index);
};

Rank.prototype.load = function() {
	console.log("rank data: " + this);

	this.setList(this.uzAll, $id('uzlist'));
	this.setList(this.unAll, $id('unlist'));
	this.setList(this.ugAll, $id('uglist'));
	this.setList(this.gnAll, $id('gnlist'));
	this.setList(this.gzAll, $id('gzlist'));

	console.log($('.rank-btns .tab div'));
	$('.rank-btns .tab div').click(function() {
		var index = $(this).index();
		
		$('#rank-lists .rank-list.current').removeClass('current');
		$('#rank-lists .rank-list').eq(index).addClass('current');

		$('.rank-btns .tab div').removeClass('selected');
		$(this).addClass('selected');

		window.app.rank.index = index;
		window.app.rank.createIScroll(index);
	});	

	this.createIScroll(0);
};

Rank.prototype.show = function() {
	this.createIScroll(this.index);
}

Rank.prototype.addTd = function(item) {
	this.html += "<td>"
	this.html += item;
	this.html += "</td>";
};

Rank.prototype.setList = function(list, dist) {
	if(list && list.length > 0){
		this.html = "";
		for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
			var item = list[i];
			this.html += "<tr>";
			this.addTd("第" + (i + 1) + "名");
			this.addTd(item.zone);
			this.addTd(item.dealer);
			if (item.name) {
				this.addTd(item.name);
			}
			this.addTd(parseInt(Number(item.score)) + "分");
			this.html += "</tr>";
		};
		dist.innerHTML = (list.length > 0) ? "<table>" + this.html + "</table>" : "暂无排名数据";
	}else{
		dist.innerHTML = "暂无排名数据";
	}
};