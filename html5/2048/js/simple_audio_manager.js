function SimpleAudioManager() {
	// number of channels
	var channel_max = 10;

	this.audiochannels = new Array();

	for ( a = 0; a < channel_max; a++) {// prepare the channels
		this.audiochannels[a] = new Array();
		this.audiochannels[a]['channel'] = new Audio();
		// create a new audio object
		this.audiochannels[a]['finished'] = -1;
		// expected end time for this channel
	}

	// load audio.
	var move = $id('move-audio');
	move.addEventListener("ended", function() {
		console.log("move-audio play ended");
		move.load();
	}, false);

	var backgroud = $id('background-audio');
	backgroud.addEventListener("ended", function() {
		console.log("backgroud-audio play ended");
		backgroud.play();
	}, false);
}

SimpleAudioManager.prototype.play = function(s) {
	if (!ENABLE_AUDIO) {
		return;
	}

	// Use channles will cause lag.
	if (false) {
		for ( a = 0; a < this.audiochannels.length; a++) {
			thistime = new Date();
			if (this.audiochannels[a]['finished'] < thistime.getTime()) {// is this channel finished?
				this.audiochannels[a]['finished'] = thistime.getTime() + document.getElementById(s).duration * 1000;
				this.audiochannels[a]['channel'].src = document.getElementById(s).src;
				this.audiochannels[a]['channel'].load();
				this.audiochannels[a]['channel'].play();
				break;
			}
		}
	} else {
		var audio = $id(s);
		console.log("play audio: " + s);
		if (!ENABLE_EFFECT_AUDIO && s == 'move-audio') {
			return;
		}

		console.log(audio + ": " + audio.ended + ", " + audio.currentTime);
		if (audio && (audio.ended || audio.currentTime == 0)) {
			audio.play();
		}
	}
};
