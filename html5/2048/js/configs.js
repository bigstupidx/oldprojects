// The max value
var MAX_VALUE = 65536;

// The won value
var WON_VALUE = 2048;

// SGM stuff
var TEST_USER_NAME = 'd232123d10684d89ab875e079df8952d';
var API_URL = "http://sgmels.wizlong.com:10032/app/game/games.jsp";
var TIMEOUT = 90;
var GAME_ID = 1;

// user type
var USER_TYPE_ENUM = {"sgm": 0, "debug": 1, "anonymous": 2};
var USER_TYPE = USER_TYPE_ENUM.anonymous;

// audio settings
var ENABLE_AUDIO = false;
var ENABLE_EFFECT_AUDIO = false;

jQuery.ajaxSetup({
    timeout: TIMEOUT * 1e3,
    async: false,
    cache: false,
    type: "GET",
    dataType: "jsonp",
    jsonpCallback: "jsonResult",
    error: function (jqXHR, textStatus, errorThrown) {
        if (this.url.indexOf("action=setScore") == -1) {
        	window.app.error("获取数据失败，请检查您的网络。", errorThrown);
        } else {
			alert("分数提交失败。");
		};
    }
});

var RES = [
	// loading images.
	"loading.png",
	"loading_progressbar_bg.png",
	"loading_progressbar_content.png",
	"loading-text-1.png",
	"loading-text-2.png",
	"loading-text-3.png",
	"loading-text-4.png",
	"loading-text-5.png",
	
	// tile image.
	"2.png",
	"4.png",
	"8.png",
	"16.png",
	"32.png",
	"64.png",
	"128.png",
	"256.png",
	"512.png",
	"1024.png",
	"2048.png",
	"4096.png",
	"8192.png",
	"16384.png",
	"32768.png",
	"65536.png",

	// button images.
	"best-bg.png",
	"score-bg.png",
	"restart-bg.png",
	"rank-button-bg.png",

	// rank images.	
	"rank-bg.png",
	"rank-01.png",
	"rank-02.png",
	"rank-03.png",
	"rank-04.png",
	"rank-05.png",
	"rank-01-selected.png",
	"rank-02-selected.png",
	"rank-03-selected.png",
	"rank-04-selected.png",
	"rank-05-selected.png",
	"rank-back.png",

	// prompt images.
	"prompt-finger.png",
	"prompt-text.png",

	// other images.
	"logo.png",
	"bottom-car.png",
	"above-game.png",
	"game-won.png",
	"keey-playing-button-img.png",

    // weixin images.
    "share.png"
];