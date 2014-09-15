MS.config = {
		//基本参数
		
		//是否开启调试
		debug:false,
		showAnswer:false,
				
		//API地址
		//APIURL: "http://sgmels.wizlong.com:10032/app/game/games.jsp",
		APIURL: "http://sgmels.wizlong.com/app/game/games.jsp",
		
		//API请求超时时间（单位：秒）
		TIMEOUT: 90,
		//游戏ID
		GAMEID: 3,
		//GAMEID: 1,
		
		//总关卡数
		total_level: 10 ,
		//每关问题数
		level_q_num: 25,
		
		//关卡时间 //修改为每题时间
		level_time:20,
		//解锁关卡需要答对问题数
		level_q_current: 25,
		
		current_score : 100,
		combo_score:50,
		time_score:10,
		
		//帧数
		FPS : 30,
		rt : 33 ,
		
		//气球上升速度
		ball_spd : 1.5,
		//气球出现间隔时间
		ball_interval_t : 4000,
		ball_radius : 30,
		//气球出现区域-百分比
		ball_area : 50,
		//气球出现区域偏移-百分比 
		ball_area_offset : 5,
		//气球出现方式-   1：随机，2：固定区域
		ball_appear: 1,
		ball_number : 4,
		
		//平台移动速度
		s_spd : 20,
		//平台区域宽度-百分比
		s_area_width: 14,
		s_w:163,
		s_h:210,
		s_offset_w : 60,
		s_offset_t : 20,
		s_offset_b : 40,
		s_height : 100,
		
		//子弹移动速度
		bullet_spd : 10,
		//子弹射击间隔
		bullet_interval_t : 500,
		bullet_radius : 25, //子弹半径
		bullet_g : 0.8, //下坠加速度
		
		//关卡名称
		levelName:['一','二','三','四','五','六','七','八','九','十'],
		end:null
};

jQuery.ajaxSetup({
    timeout: MS.config.TIMEOUT * 1e3,
    async: false,
    cache: false,
    type: "GET",
    dataType: "jsonp",
    jsonpCallback: "jsonResult",
    error: function (jqXHR, textStatus, errorThrown) {
        if (this.url.indexOf("action=setScore") == -1) {
        	MS.error("获取数据失败，请检查您的网络。", errorThrown);
        } else {
			alert("分数提交失败。");
		};
    }
});

MS.map_pos = [
    [147,175],
    [236,206],
    [273,282],
    [329,356],
    [394,398],
    [486,394],
    [515,316],
    [576,278],
    [652,329],
    [707,275]
];
