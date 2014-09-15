MS.Game = function(level){
	MS.DrawAble.call(this);
	this.initEl(level);
};

WGame.extend(MS.Game,MS.DrawAble);

WGame.apply(MS.Game.prototype,
	{
		sw : 0,
		lw : 0,
		status : -1,
		_status : -1,
		shooter : null,
		balloons : null,
		q_index : 0,
		a_index : 0,
		ballCount : 0,
		answerPos : null,

		level:0, //下标从0开始
		st_time:0,
		_st_time:0,
		time : 180,
		combo : 0,
		score:0,
		question_list:null,
		now_question:null,
		current_num:0,
		
		bg_img:null,
		q_person_img:null,
		q_bg_img:null,
		cloud_img:null,
		score_p_img:null,
		score_num_img:null,
		score_combo_img:null,
		wall_img:null,
		wall_t_img : null,
		q_count:0,
		q_show:true,
		
		r_count:0,
		showScore : 0,
		r_show : false,
		result_img:null,
		r_x:0,
		r_y:0,
		cd_img:null,
		
		cd_count:0,
		cd_bg_img:null,
		cd_head_img:null,
		cd_top_img:null,
		cd_light_img:null,
		cd_medal_img:null,
		cd_main_img:null,
		cd_number_img:null,
		
		initEl : function(level){
			this.level = level;
			
			this.shooter = new MS.Shooter();
			
			this.sw = this.shooter.w + MS.rw*7/100 ;
			
			this.lw = MS.rw*4/100;

			this.shooter.setPos(MS.rw - this.sw ,MS.config.s_offset_t);
			
			this.balloons = new Array(MS.config.ball_number);
			
			this.loadQuestion();
			
			this.bg_img = new Image(); 
			this.bg_img.src="image/game_bg.jpg";
			
			this.q_person_img = new Image(); 
			this.q_person_img.src="image/q_person.png";
			
			this.q_bg_img = new Image(); 
			this.q_bg_img.src="image/q_bg.png";
			
			this.cloud_img = new Image(); 
			this.cloud_img.src="image/game_cloud.png";
			
			this.score_p_img = new Image(); 
			this.score_p_img.src="image/score_p.png";
			
			this.cd_bg_img = new Image(); 
			this.cd_bg_img.src = "image/cd_bg.png";
			
			this.cd_head_img = new Image();
			this.cd_head_img.src = "image/cd_head.png";
			
			this.cd_top_img = new Image();
			this.cd_top_img.src = "image/cd_top.png";
			
			this.cd_light_img = new Image();
			this.cd_light_img.src = "image/cd_light.png";
			
			this.cd_medal_img = new Image();
			this.cd_medal_img.src = "image/cd_medal.png";
			
			this.cd_main_img = new Image();
			this.cd_main_img.src = "image/cd_main.png";
			
			this.result_img = new Image();
			this.result_img.src = "image/result.png";

			this.cd_number_img = new Image();
			this.cd_number_img.src = "image/number_cd.png";
			
			this.score_num_img = new Image();
			this.score_num_img.src = "image/number_score.png";
			
			this.score_combo_img = new Image();
			this.score_combo_img.src = "image/combo.png";
			
			this.wall_img = new Image();
			this.wall_img.src = "image/wall.png";

			this.wall_t_img = new Image();
			this.wall_t_img.src = "image/wall_t.png";
			
			MS.playBgm();
		},
		resize: function(){
			
		},
		start : function(){
			this.q_index = 0;
			this.initQuestion();
			this.setStatus(MS.CONST.GAME_PLAY);
		},
		loadQuestion:function(){
			this.question_list = [];
			
			clone(this.question_list,MS.questions[this.level]);
			
			this.question_list.sort(randomsort);//问题数组随机排序
			
			for(var i=0 ; i< this.question_list.length ; i++){
				var answers = [],
					question = this.question_list[i];
				for(var j = 0; j < question.answers.length ; j++){
					answers.push({
						src:'image/answer/' + question.id + '_' + j + '.png',
						id: j,
						title : question.answers[j]
					});
				}
				
				answers.sort(randomsort);

				question.answers = answers;
			}
			
			this.preLoadAnswer(this.question_list[0]);
		},
		preLoadAnswer:function(question){
			var answer_src = [];
			
			for(var i = 0 ; i< question.answers.length ; i++){
				answer_src.push(question.answers[i].src);
			}
			
			preload(answer_src,'');
		},
		setControl : function(canvas){
			
//			this.shooter.setControl();
			
			var self = this;
			
			$('#game').on(MS.mousedown,function(e){

				if(self.status == MS.CONST.GAME_PAUSE){
					self.setStatus(self._status);
				}else if(self.status == MS.CONST.GAME_RESULT){
					
				}else if(self.status == MS.CONST.GAME_PLAY){
					var ex = 0,ey = 0;
					if(MS.touchAble){
						var et = e.originalEvent.touches;
			            for(var i = 0 ; i < et.length ; i++){
			            	ex = et[i].clientX / MS.scale;
			            	ey = et[i].clientY / MS.scale;    
			            }
			        }else{
			        	ex=e.offsetX / MS.scale;
			        	ey=e.offsetY / MS.scale;
			        }	
					
					var	arr_top_y = 0,
						arr_w = self.shooter.arr_top_img.width * 2,
						arr_x = self.shooter.x + 47 - arr_w/4,
						arr_bot_y = MS.rh-arr_w;
					
					if( ex > arr_x && ex < arr_x + arr_w && ey > arr_top_y && ey < arr_top_y + arr_w){
						self.shooter.move(1);
					}else if( ex > arr_x && ex < arr_x + arr_w && ey > arr_bot_y && ey < arr_bot_y + arr_w){
						self.shooter.move(2);
					}else{
						self.shooter.shoot();
					}
				}
			}).on(MS.mousemove,function(e){
				if(!MS.touchAble){
					return;
				}
			}).on(MS.mouseup,function(e){
				if(self.shooter.moving){
					self.shooter.stopMove();
				}
			});
		},
		removeControl:function(){
			$(canvas).off(MS.mousedown+MS.mousemove+MS.mouseup);
		},
		draw : function(context){
			this.sw = MS.config.s_w + MS.config.s_offset_w ;
			this.lw = MS.rw*4/100;
			
			this.drawBg(context);
			
			if(this.status == MS.CONST.GAME_PAUSE){
				
			}else{
				
				this.drawCloud(context);
				
				if(this.status == MS.CONST.GAME_PLAY){
					this.drawBalloon(context);
				}else if(this.status == MS.CONST.GAME_RESULT){
					this.drawResult(context);
				}
				
//				this.drawResult(context);
				
				this.drawScore(context);
				
				this.drawCountDown(context);
				
				this.drawCurrentNum(context);
				
				this.shooter.drawBullet(context);
				
				this.drawWall(context);
				
				this.drawQuestionTitle(context);
				
				this.shooter.draw(context);
			}
			
			if(MS.config.debug){
				var	arr_top_y = 0,
					arr_w = this.shooter.arr_top_img.width * 2,
					arr_x = this.shooter.x + 47 - arr_w/4,
					arr_bot_y = MS.rh-arr_w;
				
				context.strokeStyle = '#f0f000';
				context.strokeRect(arr_x,arr_top_y,arr_w,arr_w);
				context.strokeRect(arr_x,arr_bot_y,arr_w,arr_w);
			}
		},
		drawBalloon:function(context){
			this.ballCount ++ ;
			
			if(this.ballCount > MS.config.ball_interval_t / MS.config.rt){
				this.nextAnswer();
				this.ballCount = 0;
			}
			for(var i = this.balloons.length - 1 ; i >= 0 ; i--){
				var balloon = this.balloons[i];
				
				if(balloon){
					if(!balloon.boom){
						for(var j = this.shooter.bullets.length - 1 ; j >= 0 ; j--){
							var bullet = this.shooter.bullets[j];
							
							if(bullet && bullet.collisionCircle(balloon.circle)){
								this.r_x = balloon.getX() + 105 + balloon.circle.r/2 - 50/2;
								this.r_y = balloon.getY();
								balloon.broken();
								this.shooter.clearBullet();
								if(this.isCurrent(balloon,this.question_list[this.q_index])){
									var sc = MS.config.current_score + this.combo *MS.config.combo_score + this.time * MS.config.time_score;
									this.showScore = sc;
									this.score += sc;
									this.combo += 1;
									this.r_show = true;
									this.current_num ++;
								}else{
									this.combo = 0;
								}
								this.setStatus(MS.CONST.GAME_RESULT);
							}
						}
					}
					balloon.draw(context);
					
					if( i == MS.config.ball_number-1 && balloon.outScreen()){
						this.nextQuestion();
					}
				}
			}
		},
		drawBg:function(context){
			var w = 46,
				num = MS.rw / w + 1;
			
			context.fillStyle = '#4b81ad';
			for(var i = 0; i < num ; i++){
				if(i % 2 == 0){
					context.fillRect(i*w,0,w+1,MS.rw);
				}
			}
			context.fillStyle = '#5388b2';
			for(var i = 0; i < num ; i++){
				if(i % 2 != 0){
					context.fillRect(i*w,0,w+1,MS.rh);
				}
			}
//			var ptrn = context.createPattern(this.bg_img,"repeat");
//			context.fillStyle = ptrn;
//			context.fillRect(0, 0, MS.rw, MS.rh);
		},
		drawWall : function(context){
			var ptrn = context.createPattern(this.wall_img,"repeat");
			context.fillStyle = ptrn;
			
			context.save();
			context.translate(0,MS.rh - this.wall_img.height);
			context.fillRect(0, 0, MS.rw, this.wall_img.height);
			context.restore();
			
			var w = this.wall_t_img.width,
				h = this.wall_t_img.height;
			context.drawImage(this.wall_t_img,(MS.rw - w)/2,MS.rh - this.wall_img.height,w,h);
		},
		drawCloud : function(context){
			var c_w = this.cloud_img.width,
				c_h = this.cloud_img.height;
			
			context.drawImage(this.cloud_img,(MS.rw - c_w)/2,0,c_w,c_h);
		},
		drawResult:function(context){
			
			this.r_count ++ ;
			
			if(this.r_count > 30){
				this.r_show = false;
				this.r_count = 0;
				this.nextQuestion();
				this.setStatus(MS.CONST.GAME_PLAY);
				return;
			}
			
			var r_off_x = 0;
			
			if(!this.r_show){
				r_off_x = 50;
			}
			
			context.drawImage(this.result_img,r_off_x,0,50,50,this.r_x,this.r_y,50,50);
			
			if(this.r_show){
				
				context.textBaseline="top";
				context.font ="bold "+30+"px Microsoft Yahei";
				
				//绘制分数
				
				MS.TOOL.drawNumber(context,this.score_num_img,this.showScore,20,28,MS.rw - this.sw - 90,this.score_p_img.height + 60 - this.r_count,true);
				
				//绘制连击数				
				if(this.combo > 1){
					var combo_w = this.score_combo_img.width,
						combo_x = MS.rw*2/5,
						combo_y = MS.rh/2- this.r_count*2;
					context.drawImage(this.score_combo_img,combo_x,combo_y,this.score_combo_img.width,this.score_combo_img.height);
					MS.TOOL.drawNumber(context,this.score_num_img,this.combo - 1,20,28,combo_x + combo_w,combo_y,true);
				}
			}
		},
		drawScore:function(context){
			var s_p_w = this.score_p_img.width,
				s_p_h = this.score_p_img.height,
				x_off = 30,
				top = 33;
			
			context.drawImage(this.score_p_img,MS.rw - this.sw - s_p_w + x_off,top,s_p_w,s_p_h);
			
			context.textAlign="left";
			context.textBaseline="middle";
			context.font ="bold "+20+"px Microsoft Yahei";
			
			var str = '第'+this.getLevelName(this.level)+'关:'+this.score;
			
			var width = context.measureText(str).width;
			context.fillStyle = '#fff';
			context.fillText(str,MS.rw - this.sw - s_p_w/2 - width * 2/3 + 15 + x_off,top + s_p_h/2);
		},
		getLevelName:function(level){
			if(level > MS.config.total_level - 1 || level < 0){
				return '';
			}
			return MS.config.levelName[level];
		},
		drawCountDown:function(context){
			this.cd_count ++ ;
			
			if(this.cd_count >= MS.config.FPS){
				this.cd_count = 0;
				this.time -= 1;
				
				if(this.time < 0){
					this.nextQuestion();
				}
			}
			
			var cd_x = this.lw + 85, 
				cd_h = this.cd_top_img.height,
				top = 33;
			
			//绘制倒计时
			
			MS.TOOL.drawNumberCD(context,this.cd_number_img,this.time,36,49,cd_x,top,24);
		},
		drawCurrentNum:function(context){
			
			var cd_x = this.lw + 170, 
				cd_bg_w = this.cd_bg_img.width,
				cd_bg_h = this.cd_bg_img.height,
				cd_off_x = 6,
				cd_off_y = 3,
				cd_left_w = 16,
				cd_w = (this.cd_bg_img.width) - cd_off_x * 2 - cd_left_w,
				cd_h = this.cd_top_img.height,
				top = 33;
			
			//绘制背景
			context.drawImage(this.cd_bg_img,cd_x,top,cd_bg_w,cd_bg_h);
			
			//绘制进度条左侧部分
			context.drawImage(this.cd_top_img,0,0,16,41,cd_x+cd_off_x,top + cd_off_y,cd_left_w,cd_h);
			
			//绘制进度条
			
			var cd_main_w = cd_w * this.current_num/this.question_list.length;
			
			context.drawImage(this.cd_main_img,0,0,cd_main_w,41,cd_x+cd_off_x + cd_left_w,top + cd_off_y,cd_main_w,cd_h);
			
			//绘制奖牌
			context.drawImage(this.cd_medal_img,cd_x + cd_bg_w - (this.cd_medal_img.width+15),top + 10,this.cd_medal_img.width,this.cd_medal_img.height);
			
			//绘制头像
			context.drawImage(this.cd_head_img,cd_x+cd_off_x+cd_left_w + cd_main_w - this.cd_head_img.width/2,top - (this.cd_head_img.height - cd_bg_h)/2 ,this.cd_head_img.width,this.cd_head_img.height);
		},
		drawQuestionTitle:function(context){
			
			if(this.q_show){
				this.q_count ++;
				
				if(this.q_count > 30){
					this.q_show = false;
					this.q_count = 0;
				}
			}
			
			var p_h = this.q_person_img.height,
				p_w = this.q_person_img.width,
				bg_w = this.q_bg_img.width,
				bg_h = this.q_bg_img.height,
				bg_x = (MS.rw - bg_w)/2,
				bg_y = MS.rh -  bg_h;
				
			
			context.drawImage(this.q_bg_img,bg_x,bg_y,bg_w,bg_h);
			context.drawImage(this.q_person_img,bg_x - p_w + 26,MS.rh - p_h,p_w,p_h);
			
			
			var q_x = bg_x + 26,
				q_y = bg_y + bg_h/2 - 4;
			
			if(this.q_show){
				q_y += (120 - this.q_count*4);
			}
			var title = this.question_list[this.q_index].title;
			
			if(MS.config.showAnswer){
				title += '  答案：'+this.now_question.c_answer;
			}
			
			context.textBaseline="middle";
			context.font ="bold "+36+"px Microsoft Yahei";
			context.lineWidth = 4;
			context.strokeStyle = '#fff';
			
			var txtW = bg_w - (q_x - (MS.rw - bg_w)/2);
			
			if(txtW + q_x > this.shooter.getRopeX()){
				txtW = this.shooter.getRopeX() - q_x -5;
			}
			
			if(q_y < bg_y + bg_h){
				MS.TOOL.drawTextByWidth(context,title,q_x,q_y,txtW, bg_h , 'strokeText');
//				context.strokeText(title,q_x,q_y);
				
				context.fillStyle = '#000000';
				MS.TOOL.drawTextByWidth(context,title,q_x,q_y,txtW, bg_h , 'fillText');
//				context.fillText(title,q_x,q_y);
			}
			
//			context.clearRect(q_x-2,bg_y + bg_h,MS.rw - q_x,bg_h);
		},
		nextQuestion: function(){
			if(this.q_index < MS.config.level_q_num - 1){
				this.q_index ++ ;
				this.initQuestion();
			}else{
				this.showRank();
			}
		},
		nextAnswer : function(){
			if(this.a_index < MS.config.ball_number){
				var balloon = new MS.Balloon();
				balloon.setPos(this.answerPos[this.a_index],MS.rh*0.831);
				balloon.setIndex(this.a_index);
				balloon.setAnswer(this.now_question.answers[this.a_index]);
				this.balloons[this.a_index] = balloon;
				
				this.a_index ++ ;
			}
		},
		initQuestion : function(){
			this.q_show = true;
			this.a_index = 0;
			this.ballCount = 0;
			this.time = MS.config.level_time;
			this.now_question = this.question_list[this.q_index];
			this.initAnswer();
			this.nextAnswer();
			
			if(this.q_index  < MS.config.level_q_num - 2){
				this.preLoadAnswer(this.question_list[this.q_index + 1]);
			}
		},
		initAnswer : function(){
			this.balloons = new Array(MS.config.ball_number);
			this.answerPos = new Array(MS.config.ball_number);
			
			if(MS.config.ball_appear == 1){
				for(var i = 0 ; i< MS.config.ball_number ; i++){
					this.answerPos[i] = (MS.config.ball_area_offset + MS.TOOL.getRandomNum(5,MS.config.ball_area)) * MS.rw/100 + MS.config.ball_radius;
				}
			}else if(MS.config.ball_appear == 2){
				for(var i = 0 ; i< MS.config.ball_number ; i++){
					this.answerPos[i] = (MS.config.ball_area_offset + MS.config.ball_area / 4 ) * MS.rw/100 + MS.config.ball_radius;
				}
			}
		},
		isCurrent:function(balloon,question){
			return balloon.getAnswerId() == 0;
		},
		setStatus:function(status){
			if(this.status != status){
				this._status = this.status;
			}
			this.status = status;
		},
		pause:function(){
			MS.stopBgm();
		},
		resume:function(){
			MS.playBgm();
		},
		showRank : function(){
			this.gameEnd();
		},
		gameEnd:function(){
			
			this.isPass = this.current_num == this.question_list.length ? 1 : 0;
			
			MS.saveLevelScore(this.score,this.level + 1,this.isPass);
			
			MS.stopGame();
			
		}
	}
);
