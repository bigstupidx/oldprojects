function Application() {
	this.user = new User();
	this.rank = new Rank();
};

Application.prototype.preload = function(list, path, fileloaded, callback) {
	var loaded = 0;
	var total = list.length;

	var loadImg = function(src) {
		var img = new Image();
		img.onload = img.onerror = function() {
			loaded++;
			fileloaded && fileloaded(loaded / total);
			if (loaded == total) {
				callback && callback();
			} else {
				setTimeout(function() {
					loadImg(list.shift());
				}, 10);
			};
		};
		img.src = path + src;
	};
	loadImg(list.shift());
};

Application.prototype.setStatus = function(status) {
	var oldStatus = this.status;

	if (this.status != status) {
		this.status = status;

		if (status == "loading") {
			$('section#' + status).addClass('show');
		}

		if (status == "prompt") {
			if (oldStatus == "loading") {
				$('section.show').removeClass('show');
				$('section#game').addClass('show');
			}

			if (this.manager == null) {
				this.manager = new GameManager(4, KeyboardInputManager, HTMLActuator, LocalStorageManager, SimpleAudioManager);
			}

			$('.mask2').addClass('show');
			$('.prompt-container').addClass('show');
		} else {
			$('.mask2.show').removeClass('show');
			$('.prompt-container.show').removeClass('show');
		}

		if (status == "game") {
			if (oldStatus == "loading") {
				$('section.show').removeClass('show');
				$('section#' + status).addClass('show');
			}

			if (this.manager == null) {
				this.manager = new GameManager(4, KeyboardInputManager, HTMLActuator, LocalStorageManager, SimpleAudioManager);
			}
		}

		// enable mask layer when show menu or rank.
		if (status == "rank") {
			console.log("setStatus: " + status);
			$('.mask').addClass('show');
			$('.rank-container').addClass('show');
			window.app.rank.show();
		} else {
			$('.mask.show').removeClass('show');
			$('.rank-container.show').removeClass('show');
		}
	}
};

Application.prototype.loading = function(progress) {
	console.log(progress);

	var percent = progress * 100 - 100;
	document.querySelector('.loading-progressbar-content').style.left = percent.toString() + "%";
};

Application.prototype.startGame = function(successed) {
	if (successed) {
		// get successed, load rank.
		window.app.rank.load();

		window.app.setStatus("prompt");
	}
}

Application.prototype.getRank = function(successed) {
	if (successed) {
		window.app.user.getRank(window.app.startGame);
	}
}

Application.prototype.getTopScore = function(successed) {
	if (successed) {
		console.log("application.getTopScore");

		window.app.user.getTopScore(window.app.getRank);
	}
}

Application.prototype.loaded = function() {
	console.log("loaded");

	// login
	window.app.user.getName(window.app.getTopScore);
};

Application.prototype.startLoad = function() {
	this.setStatus("loading");

	this.preload(RES || [], "../images/", this.loading, this.loaded);

	// getInfo();
	// scroll screen up if screen height is not enough.
	var delta = window.screen.availHeight - (471 + 20);
	if (delta < 0) {
		document.querySelector('body').style.marginTop = delta + "px";
		document.querySelector('.footer').style.top = (405 + delta) + "px";
		document.querySelector('.rank-container').style.marginTop = -10 + "px";
	}
};

Application.prototype.error = function(info, error) {
	alert(info);
	if (error) {
		throw new Error(error);
	}
}

Application.prototype.showRank = function() {
	console.log("Application: showRank");
	window.app.setStatus("rank");
}

Application.prototype.backToGame = function() {
	window.app.setStatus("game");
}

// Wait till the browser is ready to render the game (avoids glitches)
window.requestAnimationFrame(function() {
	//new GameManager(4, KeyboardInputManager, HTMLActuator, LocalStorageManager, SimpleAudioManager, User, Rank);
});

window.onload = function() {
	this.app = new Application();
	this.app.startLoad();
};
