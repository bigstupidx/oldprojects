function User() {
    this.topScore = 0;

    if (USER_TYPE == USER_TYPE_ENUM.debug) {
        this.userName = TEST_USER_NAME;
    } else if (USER_TYPE == USER_TYPE_ENUM.sgm) {
        this.userName = getURLParameter("gspid");
    } else if (USER_TYPE == USER_TYPE_ENUM.anonymous) {
        this.userName = "anonymous";

        document.title = "经销商微动课堂";
    }
}

User.prototype.getName = function (callback) {
    if (!window.app.user.userName) {
        window.app.error("获取用户信息失败，请稍后重试。");
    }

    $.ajax(API_URL + "?action=getUser&userName=" + window.app.user.userName).done(function (data) {
        var successed = false;

        console.info("get user name: ", data);

        if (data != null && data.dealer != "" && data.name != "" && data.userName != "") {
            // get name successed.
            successed = true;

            window.app.user.dealer = data.dealer;
            window.app.user.zone = data.zone;
            window.app.user.name = data.name;
            window.app.user.userName = data.userName;
        } else {
            window.app.error("获取用户信息失败，请稍后重试。");
        }

        if (callback != null) {
            callback(successed);
        }
    });
};

User.prototype.getTopScore = function (callback) {
    if (!window.app.user.userName) {
        window.app.error("获取用户信息失败，请稍后重试。");
    }

    $.ajax(API_URL + "?action=getScore&userName=" + window.app.user.userName + "&gameId=" + GAME_ID).done(function (data) {
        var successed = false;

        console.info("get top score: ", data);

        if (data != null) {
            // get top score successful.
            successed = true;

            window.app.user.topScore = data.score;
        } else {
            window.app.error("获取分数信息失败，请稍后重试。");
        }

        if (callback != null) {
            callback(successed);
        }
    });
}

User.prototype.getRank = function (callback) {
    if (!window.app.user.userName) {
        window.app.error("获取用户信息失败，请稍后重试。");
    }

    $.ajax(API_URL + "?action=getAllPlaces&userName=" + window.app.user.userName + "&gameId=" + GAME_ID).done(function (data) {
        var successed = false;

        console.info("get rank: ", data);

        if (data != null) {
            // get rank successful.
            successed = true;

            ("gnAll" in data) && isArray(data.gnAll) && (window.app.rank.gnAll = data.gnAll);
            ("gzAll" in data) && isArray(data.gzAll) && (window.app.rank.gzAll = data.gzAll);
            ("ugAll" in data) && isArray(data.ugAll) && (window.app.rank.ugAll = data.ugAll);
            ("unAll" in data) && isArray(data.unAll) && (window.app.rank.unAll = data.unAll);
            ("uzAll" in data) && isArray(data.uzAll) && (window.app.rank.uzAll = data.uzAll);
        } else {
            window.app.error("获取分数信息失败，请稍后重试。");
        }

        if (callback != null) {
            callback(successed);
        } else {
            window.app.rank.load();
        }
    });
}

User.prototype.setTopScore = function (score) {
    console.info("setTopScore: " + score);

    console.info("topScore = " + parseInt(this.topScore));
    console.info("(parseInt(this.topScore) < score) = " + (parseInt(window.app.user.topScore) < score));
    if (parseInt(this.topScore) < score) {
        this.topScore = score.toString();

        if (USER_TYPE != USER_TYPE_ENUM.anonymous) {
            this.pushTopScore();
        }
    }
}

User.prototype.pushTopScore = function () {
    console.info("pushTopScore...");

    var url = API_URL;
    url += "?action=setScore";
    url += "&userName=" + this.userName;
    url += "&gameId=" + GAME_ID;
    url += "&score=" + this.topScore;

    $.ajax(url).done(function (data) {
        console.info("pushTopScore done!", data);

        // get rank again, after push top score.
        window.app.user.getRank(null);
    });
}