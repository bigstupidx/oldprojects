MS.CONST = {
		TOGGLEEVENT : 'click touch',
		
		//主状态
		MAIN_LOADING : 'loading',
		MAIN_GAME : 'game',
		MAIN_INSTRUCTION : 'instruction',
		MAIN_LEVEL : 'level',
		MAIN_RANK : 'rank',
		MAIN_NO_PLAY : 'no_play',
		MAIN_PAUSE : 'pause',
		MAIN_SCORE : 'score',
		
		//游戏状态
		GAME_PLAY : 1,
		GAME_RESULT : 2,
		GAME_PAUSE : 3
};

(function eventAdapt(){

	MS.touchAble = 'ontouchstart' in window;
	
	MS.mousedown = "mousedown ";
	MS.mousemove = "mousemove ";
	MS.mouseup = "mouseup ";
	MS.mouseout= "mouseout ";
    if ('ontouchstart' in window) {
    	MS.mousedown = "touchstart ";
    	MS.mousemove = "touchmove ";
    	MS.mouseup = "touchend ";
    	MS.mouseout= "touchcancel ";
    }
})();