WGame.apply(MS,
	{
		user : {
			userName:'d232123d10684d89ab875e079df8952d'			          
//			userName : getURLParameter("gspid")
		},
//		topScore:{
//			topLevel:10,
//			scores: [1000,800,1000,400,0,0,0,0,0,0]
//		},//测试数据
		bestScore:0,
		oldScore:0,
		rank:[],
		selectLevel:0,
		
		game_serial:0,
		game_seed:0,
		showMask:true,
		
		height : 0,
		width : 0,
		rw : 0,
		rh : 0,
		canvas : null,
		canvasBuf : null,
//		qcanvas:null,
		cvsTop : 0,
		cvsLeft : 0,
		status: '',
		_status:'',
		ctx : null,
		ctxBuf : null,
		
		game : null,
		scale : 1,
		playing : false,
		
		startLoad:function(){
			
//			$('body').css('height',document.documentElement.clientHeight);
			
			MS.setStatus(MS.CONST.MAIN_LOADING);
//			MS.initMusic();
			
			var progressStyle = $id("loading_progress").style,
				barStyle = $id("loading_bar").style;
			barStyle.width = $('#loading_bar').height() * 638/56 +'px';
			
			preload( MS.RES || [], "image/", function(progress) {
		        progressStyle.width = progress * 100 + "%";
		    }, function() {
		    	MS.getUserInfo(function(){
		    		MS.setStatus(MS.CONST.MAIN_INSTRUCTION);
		            MS.init();
		            $('#btn_start').click(function(){
		            	MS.setStatus(MS.CONST.MAIN_LEVEL);
		            	//MS.initMusic();
		            });
		    	});
		    });
		},
		loadInstro:function(){
			var instroStyle = $id("intro").style,
				instro_width =  $('#intro').height() * 536/260;
			instroStyle.width = instro_width +'px';
			instroStyle.left = (document.documentElement.clientWidth - instro_width)/2 + 14 * MS.scale +'px';
			
			$("#intro").jScrollPane({
		        verticalDragMaxHeight: 36
		    });
		},
		loadLevel:function(){
			
			var mapStyle = $id("map_area").style,
				map_height = $('#map_area').height(),
				scale =  map_height/512,
	    		map_width =  scale * 807;
	    	mapStyle.width = map_width +'px';
	    	
	    	var level_width = scale*78;
	    	if($('#map_choose .level').length == 0){
	    		for(var i = 0 ; i < MS.map_pos.length ; i ++){
	    			var level = $('<div>').addClass('level');
	    			
	    			level.css({
		    			'height':level_width,
		    			'width':level_width,
		    			'left':MS.map_pos[i][0]*scale - level_width/2,
		    			'top':MS.map_pos[i][1]*scale - level_width/2
		    		});
	    			
	    			if(MS.topScore && i > MS.topScore.topLevel){
	    				level.addClass('lock');
	    			}
	    			
	    			level.click(function(){
	    				
	    				var index = $(this).index();
	    				
	    				if(MS.topScore && index < MS.topScore.topLevel + 1){
		    				$(this).siblings().removeClass('choose');
		    				$(this).addClass('choose');
		    				MS.selectLevel = index;
		    				
		    				$('#level_score').text(MS.topScore.scores[MS.selectLevel]);
	    				}
	    			});
	    			$('#map_choose').append(level);
	    		}
	    		
	    		$('#level_score').text(MS.topScore.scores[MS.selectLevel]);
	    		
	    		$('#level_rank_btn').click(function(){
	    			MS.setStatus(MS.CONST.MAIN_RANK);
    			});
	    		
	    		$('#level_start_btn').click(function(){
	    			MS.startGame(MS.selectLevel);
    			});
	    		
	    	}else{
	    		$('#map_choose .level').each(function(){
	    			var index = $(this).index();
	    			$(this).css({
		    			'height':level_width,
		    			'width':level_width,
		    			'left':MS.map_pos[index][0]*scale - level_width/2,
		    			'top':MS.map_pos[index][1]*scale - level_width/2
		    		});
	    			
	    			if(index <= MS.topScore.topLevel ){
	    				$(this).removeClass('lock');
	    			}
	    		});
	    	}
	    	if($('#map_choose .level.choose').length == 0){
	    		$('#map_choose .level').eq(0).addClass('choose');
	    	}
		},
		loadRank:function(){
			var rank = $("#rank_all_list"),
				rank_width =  rank.height() * 800/253;

			rank.css({
				width:rank_width,
				left:(document.documentElement.clientWidth - rank_width)/2
			});
			$("#rank_all_list").jScrollPane({
			    verticalDragMaxHeight: 36
			});
			MS.rankListApi = $("#rank_all_list").data('jsp'); 
			$('.rank_btns .tab img').click(function(){
				var index = $(this).index();
				
				$('#rank_div .rank_list.current').removeClass('current');
				$('#rank_div .rank_list').eq(index).addClass('current');
				
			});
			$('#rank_btn_ok').click(function(){
				MS.setStatus(MS.CONST.MAIN_LEVEL);
			});
		},
		setList:function(list,dist){
			if(list && list.length > 0){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + parseInt(Number(item.score)) + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		//经销商全国
		setGn:function(list,dist){
			if(list){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + parseInt(Number(item.score)) + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		//经销商区域
		setGz:function(list,dist){
			if(list){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + parseInt(Number(item.score)) + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		//个人展厅/店内
		setUg:function(list,dist){
			if(list){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + item.name + "</td><td>" + item.score + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		//个人区域
		setUn:function(list,dist){
			if(list){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + item.name + "</td><td>" + item.score + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		//个人全国
		setUz:function(list,dist){
			if(list){
				var html = "";
				for (var i = 0, l = Math.min(50, list.length); i < l; i++) {
					var item = list[i];
					html += "<tr><td>第" + (i + 1) + "名</td><td>" + item.zone + "</td><td>" + item.dealer + "</td><td>" + item.name + "</td><td>" + item.score + "分</td></tr>";
				};
				dist.innerHTML = (list.length > 0) ? "<table>" + html + "</table>" : "暂无排名数据";
			}else{
				dist.innerHTML = "暂无排名数据";
			}
		},
		setRankList:function(rank){
			if(!rank){
				return;
			}
			
			this.setGn(rank.gnAll,$id('gnlist'));
			this.setGz(rank.gzAll,$id('gzlist'));
			this.setUg(rank.ugAll,$id('uglist'));
			this.setUn(rank.unAll,$id('unlist'));
			this.setUz(rank.uzAll,$id('uzlist'));
			
			if(MS.rankListApi){
				MS.rankListApi.reinitialise();
			}else{
				$("#rank_all_list").jScrollPane({
				    verticalDragMaxHeight: 36
				});
				MS.rankListApi = $("#rank_all_list").data('jsp'); 
			}
		},
		getTotalScore:function(){
			if(!MS.topScore){
				return 0;
			}
			var score = 0;
			
			for(var i = 0 ; MS.topScore.scores && i < MS.topScore.scores.length ; i++){
				score += MS.topScore.scores[i];
			}
			return score;
		},
		updateToplist : function (){
			$id('unlist').innerText = $id('uzlist').innerText = $id('gnlist').innerText = $id('gzlist').innerText = $id('uglist').innerText = "数据加载中…";
			
			MS.updateGroup(MS.rank.gnAll);
			MS.updateGroup(MS.rank.gzAll);
			MS.updatePersonal(MS.rank.ugAll);
			MS.updatePersonal(MS.rank.unAll);
			MS.updatePersonal(MS.rank.uzAll);
			
			MS.setRankList(MS.rank);
		},
		updatePersonal : function (array){
			var onList = array.some(function(obj){
				return obj.dealer == MS.user.dealer;
			});
			
			if(onList){
				array.forEach(function(obj) {
					if (obj.userName == MS.user.userName) obj.score = MS.bestScore;
					return obj;
				});
				array.sort(function(a, b) {
					return b.score - a.score;
				});
			} else {
				array.push({
					places: 0,
					dealer: MS.user.dealer,
					zone: MS.user.zone,
					name: MS.user.name,
					userName: MS.user.userName,
					score: MS.bestScore
				});
			};
		},
		updateGroup : function (array){
			var onList = array.some(function(obj){
				return obj.dealer == MS.user.dealer;
			});
			
			if(onList){
				array.forEach(function(obj) {
					if (obj.dealer == MS.user.dealer) {
						obj.groupSum = Number(obj.groupSum) + MS.bestScore - MS.oldScore;
						obj.score = Math.round(obj.groupSum / obj.groupSize);
					};
					return obj;
				});
				array.sort(function(a, b) {
					return b.score - a.score;
				});
			} else {
				array.push({
					places: 0,
					dealer: MS.user.dealer,
					zone: MS.user.zone,
					score: MS.bestScore,
					groupSize: 1,
					groupSum: MS.bestScore
				});
			};
		},
		loadScore:function(){
			$('#score_level').text(MS.game.score);
			$('#score_histroy').text(MS.topScore.scores[MS.game.level]);
			$('#score_btn_ok').click(function(){
				MS.nextLevel();
			});
		},
		initGamePos:function(){
			var imgW = 1136,
				imgH = 640;
			
			MS.rh = imgH;
			MS.height = document.documentElement.clientHeight;
			MS.width = document.documentElement.clientWidth;
			MS.rw = MS.rh * MS.width / MS.height;
			
			if(MS.height > MS.width){
				return false;
			}
			
			MS.scale = (MS.height/MS.rh);
			
			if(!MS.canvas){
				return;
			}
			
			MS.canvas.width = MS.rw;
			MS.canvas.height = MS.rh;
			
			MS.canvasBuf.width = MS.rw;
			MS.canvasBuf.height = MS.rh;
			
//			$('.pause').css('left',100*MS.scale);
			$('.pause').css('left',MS.width*4/100);
		},
		initGame : function (){
			
			if(!MS.canvas){
				MS.canvas = document.getElementById("gameCanvas");   
				MS.canvasBuf = document.getElementById("canvasBuf");   
				
				MS.ctx = MS.canvas.getContext("2d");   
				MS.ctxBuf = MS.canvasBuf.getContext("2d"); 
			}
			
			this.initGamePos();
			
			$('section .pause').on(MS.mousedown,function(e){
				if(MS.playing){
					MS.pause();
				}else{
					MS.resume();
				}
				
				e.stopPropagation();
			});
			
			$('section #pause_reusme').click(function(){
				MS.resume();
			});
			
			$('section #pause_rechoose').click(function(){
				MS.setStatus(MS.CONST.MAIN_LEVEL);
			});
			
			$('#notice_mask').click(function(){
				$(this).hide();
				MS.showMask = false;
				MS.resumeGame();
			});
			
			this.gameInited = true;
		},
		loadMusic:function(){
			MS.music = {
				shoot:$id('sound_shoot'),
//				broken:$id('sound_broken'),
				bgm:$id('sound_bgm')
			};
			
			MS.music.shoot.addEventListener("ended", function(){  
				MS.music.shoot.load();
			},false);
//			MS.music.broken.addEventListener("ended", function(){  
////				MS.music.broken.load();
//			},false);
			MS.music.bgm.addEventListener("ended", function(){  
				MS.music.bgm.play();
			},false);
		},
		//initMusic:function(){
		//	for(var i in MS.music){
		//		MS.music[i].load();
		//	}
		//},
		playSoundDelayed : function(name , delay){
			if(delay == null){
				delay = 1;
			}
			setTimeout(function(){
				MS.playSound(name);
			},delay);
		},
		playSound:function(name){
			
			var sound = MS.music[name];
	        if (sound && (sound.ended || sound.currentTime == 0)) sound.play();
		},
		playBgm : function(){
			var sound = MS.music.bgm;
			if (sound.ended || sound.currentTime == 0) sound.play();
		},
		stopBgm : function(){
			var sound = MS.music.bgm;
			if (!(sound.ended || sound.currentTime == 0)) {
				sound.pause();
				sound.load();
			};
		},
		init : function(){

			fixOrientation();
			
			MS.loadMusic();
			
			MS.initGame();
		},
		setStatus : function (status){
			
			if(!status || status == MS.status){
				return;
			}
			MS._status = MS.status;
			MS.status = status;
			$('section.show').removeClass('show');
			$('section#' + status).addClass('show');
			
			if(MS.status == MS.CONST.MAIN_INSTRUCTION){
				MS.loadInstro();
			}else if(MS.status == MS.CONST.MAIN_LEVEL){
				MS.loadLevel();
			}else if(MS.status == MS.CONST.MAIN_RANK){
				MS.loadRank();
			}else if(MS.status == MS.CONST.MAIN_SCORE){
				MS.loadScore();
			}
		},
		
		startGame : function(level){
			
			MS.game = null;
			
			MS.game = new MS.Game(level);

			MS.playing = true;
			
			MS.setStatus(MS.CONST.MAIN_GAME);
			
			MS.game.setControl(MS.canvas);
			MS.game.start();
			
			if(MS.game_seed != 0){
				clearInterval(MS.game_seed);
			}
			
			MS.game_seed = setInterval(function(){
				if(MS.playing){
			    	MS.paint();
			    }
			},MS.config.rt);
			
			if(MS.showMask){
				setTimeout(function(){
					$('#notice_mask').show();
					MS.pauseGame();
				},100);
			}
		},
		stopGame:function(){
			clearInterval(MS.game_seed);
			MS.setStatus(MS.CONST.MAIN_SCORE);
			MS.stopBgm();
		},
		nextLevel:function(){
			
			if(MS.game.isPass == 1){
				
				if(MS.game.level + 1 > MS.topScore.topLevel){
					MS.topScore.topLevel = MS.game.level + 1;
				}
				
				if(MS.game.level < MS.config.total_level - 1 ){
					if(this.selectLevel < MS.config.total_level - 1){
						this.selectLevel = MS.game.level + 1;
						$('#map_choose .level').eq(MS.selectLevel).click();
					}
				}
			}

			MS.bestScore = MS.oldScore = MS.getTotalScore();
			
			if(MS.game.score > MS.topScore.scores[MS.game.level]){
				MS.topScore.scores[MS.game.level] = MS.game.score;
				
				MS.bestScore = MS.getTotalScore();
			}
			
			MS.updateToplist();
			
			MS.setStatus(MS.CONST.MAIN_LEVEL);
		},
		paint : function(){
			
//			MS.ctx.drawImage(MS.canvasBuf,0,0,MS.rw,MS.rh);
			MS.game.draw(MS.ctx);
			
//			MS.ctx.drawImage(MS.canvasBuf, 0, 0, MS.width, MS.height);
			
		},
		pause : function(){
			MS.setStatus(MS.CONST.MAIN_PAUSE);
			MS.pauseGame();
		},
		pauseGame:function(){
			MS.playing = false;
			if(MS.game_seed != 0){
				clearInterval(MS.game_seed);
			}
			
			MS.game.pause();
		},
		resume : function(){
			MS.setStatus(MS.CONST.MAIN_GAME);
			MS.resumeGame();
		},
		resumeGame:function(){
			MS.initGamePos();
			MS.playing = true;
			MS.game_seed = setInterval(function(){
				if(MS.playing){
			    	MS.paint();
			    }
			},MS.config.rt);
			MS.game.resume();
		},
		noplay:function(){
			$('section.show').removeClass('show');
			$('section#no_play').addClass('show');
		},
		canplay:function(){
			$('section.show').removeClass('show');
			$('section#' + MS.status).addClass('show');
		},
		error:function(info,error){
			alert(info);
			if(error) throw new Error(error);
		},
		//数据请求
		getUserInfo : function(callback){
			if(!MS.user.userName){
				 MS.error("获取用户信息失败，请稍后重试。");
			} 
			
			console.info("getUser…");
			$.ajax(MS.config.APIURL + "?action=getUser&userName=" + MS.user.userName).done(function (data) {
				console.info("getUser!", data);
				
				if (data != null && data.dealer != "" && data.name != "" && data.userName != "") {
					MS.user.dealer = data.dealer;
					MS.user.zone = data.zone;
					MS.user.name = data.name;
					MS.user.userName = data.userName;
					
					console.info("getLevelScore…");
					$.ajax(MS.config.APIURL + "?action=getLevelScore&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID).done(function (data) {
						console.info("getLevelScore!", data);
						if (data != null) {
							MS.topScore = data;
							
							console.info("getAllPlaces…");
							$.ajax(MS.config.APIURL + "?action=getAllPlaces&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID).done(function (data) {
								console.info("getAllPlaces!", data);
								if (data != null) {
									("gnAll" in data) && isArray(data.gnAll) && (MS.rank.gnAll = data.gnAll);
									("gzAll" in data) && isArray(data.gzAll) && (MS.rank.gzAll = data.gzAll);
									("ugAll" in data) && isArray(data.ugAll) && (MS.rank.ugAll = data.ugAll);
									("unAll" in data) && isArray(data.unAll) && (MS.rank.unAll = data.unAll);
									("uzAll" in data) && isArray(data.uzAll) && (MS.rank.uzAll = data.uzAll);
									MS.setRankList(MS.rank);
									console.info("Game ready!");
									
									callback && callback();
									
								} else { MS.error("获取排名信息失败，请稍后重试。"); };
							});
						} else { MS.error("获取分数信息失败，请稍后重试。"); };
					});
				} else { MS.error("获取用户信息失败，请稍后重试。"); };
			});
		},
		getUser:function(){
			if(!MS.user.userName){
				 MS.error("获取用户信息失败，请稍后重试。");
			} 
			
			console.info("getUser…");
			$.ajax(MS.config.APIURL + "?action=getUser&userName=" + MS.user.userName).done(function (data) {
				console.info("getUser!", data);
				
				if (data != null && data.dealer != "" && data.name != "" && data.userName != "") {
					MS.user.dealer = data.dealer;
					MS.user.zone = data.zone;
					MS.user.name = data.name;
					MS.user.userName = data.userName;
				} else { 
					MS.error("获取用户信息失败，请稍后重试。"); 
				}
			});
		},
		getAllPlaces:function(){
			console.info("getAllPlaces…");
			$.ajax(MS.config.APIURL + "?action=getAllPlaces&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID).done(function (data) {
				console.info("getAllPlaces!", data);
				if (data != null) {
					("gnAll" in data) && isArray(data.gnAll) && (MS.rank.gnAll = data.gnAll);
					("gzAll" in data) && isArray(data.gzAll) && (MS.rank.gzAll = data.gzAll);
					("ugAll" in data) && isArray(data.ugAll) && (MS.rank.ugAll = data.ugAll);
					("unAll" in data) && isArray(data.unAll) && (MS.rank.unAll = data.unAll);
					("uzAll" in data) && isArray(data.uzAll) && (MS.rank.uzAll = data.uzAll);
					MS.setRankList(MS.rank);
				} else { MS.error("获取排名信息失败，请稍后重试。"); };
			});
		},
		getLevelAllPlaces:function(level){
			console.info("getLevelAllPlaces…");
			$.ajax(MS.config.APIURL + "?action=getLevelAllPlaces&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID + "&level=" + level).done(function (data) {
				console.info("getLevelAllPlaces!", data);
				
				if (data != null) {
					("gnAll" in data) && isArray(data.gnAll) && (MS.gnAll = data.gnAll);
					("gzAll" in data) && isArray(data.gzAll) && (MS.gzAll = data.gzAll);
					("ugAll" in data) && isArray(data.ugAll) && (MS.ugAll = data.ugAll);
					("unAll" in data) && isArray(data.unAll) && (MS.unAll = data.unAll);
					("uzAll" in data) && isArray(data.uzAll) && (MS.uzAll = data.uzAll);
					
				} else { MS.error("获取排名信息失败，请稍后重试。"); };
			});
		},
		getLevelScore:function(){
			console.info("getLevelScore…");
			$.ajax(MS.config.APIURL + "?action=getLevelScore&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID).done(function (data) {
				console.info("getLevelScore!", data);
			});
		},
		saveLevelScore:function(score, level,isPass){
			console.info("setLevelScore…");
			$.ajax(MS.config.APIURL + "?action=setLevelScore&userName=" + MS.user.userName + "&gameId=" + MS.config.GAMEID+ "&levelNo=" + level + "&score=" + score +"&isPass=" + isPass).done(function (data) {
				console.info("setLevelScore!", data);
			});
		}
	}
);

window.onorientationchange = function(){
	fixOrientation();
};

window.onresize = function(){
	fixOrientation();
};

function fixOrientation (){
//	$('body').css('height',document.documentElement.clientHeight);
	
	if(document.documentElement.clientWidth < document.documentElement.clientHeight){
		if(MS.status == MS.CONST.MAIN_GAME){
			MS.pause();
		}
		MS.noplay();
	}else{
		MS.canplay();
	}
	
	//处理说明文字宽度
	MS.loadInstro();
	
	//处理选择关卡地图
	MS.loadLevel();
	
	//处理排行页面
	MS.loadRank();
	
	MS.initGamePos();
	
	$id("css").innerHTML = '#rank_all_list{font-size:'+24*MS.scale+'px}';
}

window.onload = function(){
	MS.startLoad();
};
