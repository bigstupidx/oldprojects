/**
 * Created by Administrator on 2014/9/17.
 */
var user = {
    name: null,
    id: null,
    rank: {
        gnAll: [],
        gzAll: [],
        ugAll: [],
        unAll: [],
        uzAll: []
    },

    init: function () {
        user.id = application.getURLParameter("gspid");
        if (user.id == null || user.id == "null") {
            user.id = config.DebugUserId;
        }
        console.log("user id: " + user.id);

        user._getName();
    },

    _getName: function () {
        user.getName(user._getRank);
    },

    getName: function (callback) {
        if (user.id == null) {
            application.error("获取用户信息失败，请稍后重试。");
        }

        window["$"]["ajax"](config.ApiUrl + "?action=getUser&userName=" + user.id)["done"](function (data) {
            var succeeded = false;

            console.info("get user name: ", data);

            if (data != null && data["dealer"] != "" && data["name"] != "" && data["userName"] != "") {
                // get name succeeded.
                succeeded = true;

                user.dealer = data["dealer"];
                user.zone = data["zone"];
                user.name = data["name"];
                user.id = data["userName"];
            } else {
                application.error("获取用户信息失败，请稍后重试。");
            }

            if (callback != null) {
                callback(succeeded);
            }
        });
    },

    _getLevelScore: function (succeeded) {
        if (succeeded) {
            user.getLevelScore(user._getTotalScore);
        }
    },

    getLevelScore: function (callback) {
        var url = config.ApiUrl;
        url += "?action=getLevelScore";
        url += "&userName=" + user.id;
        url += "&gameId=" + config.GameId;
        window["$"]["ajax"](url)["done"](function (data) {
            var succeeded = false;

            console.info("get level score: ", data);

            if (data != null) {
                // get rank successful.
                succeeded = true;

                var topLevel = parseInt(data["topLevel"]);
                if (!isNaN(topLevel)) {
                    console.log("get top level = " + topLevel);
                    // save top level
                    storage.setTopLevel(topLevel);

                    for (var i = 0; i < 9; i++) {
                        storage.setLevelScore(i, data["scores"][i], false, true);
                    }
                }
            } else {
                application.error("获取分数信息失败，请稍后重试。");
            }
            if (callback != null) {
                callback(succeeded);
            }
        });
    },

    _getRank: function (succeeded) {
        if (succeeded) {
            user.getRank(user._getLevelScore);
        }
    },

    getRank: function (callback) {
        window["$"]["ajax"](config.ApiUrl + "?action=getAllPlaces&userName=" + user.id + "&gameId=" + config.GameId)["done"](function (data) {
            var succeeded = false;

            console.info("get rank: ", data);

            if (data != null) {
                // get rank successful.
                succeeded = true;

                ("gnAll" in data) && application.isArray(data["gnAll"]) && (user.rank.gnAll = data["gnAll"]);
                ("gzAll" in data) && application.isArray(data["gzAll"]) && (user.rank.gzAll = data["gzAll"]);
                ("ugAll" in data) && application.isArray(data["ugAll"]) && (user.rank.ugAll = data["ugAll"]);
                ("unAll" in data) && application.isArray(data["unAll"]) && (user.rank.unAll = data["unAll"]);
                ("uzAll" in data) && application.isArray(data["uzAll"]) && (user.rank.uzAll = data["uzAll"]);
            } else {
                application.error("获取排行榜信息失败，请稍后重试。");
            }

            if (callback != null) {
                callback(succeeded);
            }
        });
    },

    _getTotalScore: function (succeeded) {
        if (succeeded) {
            user.getTotalScore();
        }
    },

    getTotalScore: function (callback) {
        var url = config.ApiUrl;
        url += "?action=getScore";
        url += "&userName=" + user.id;
        url += "&gameId=" + config.GameId;
        window["$"]["ajax"](url)["done"](function (data) {
            var succeeded = false;

            console.info("get total score: ", data);

            if (data != null) {
                // get rank successful.
                succeeded = true;

                var score = parseInt(data["score"]);
                console.log("get total score = " + score);
            } else {
                application.error("获取分数信息失败，请稍后重试。");
            }
            if (callback != null) {
                callback(succeeded);
            }

            // debug test
            // storage.setLevelScore(0, 1, false);
        });
    },

    uploadScore: function () {
        var url = config.ApiUrl;
        url += "?action=setScore";
        url += "&userName=" + user.id;
        url += "&gameId=" + config.GameId;
        url += "&score=" + storage.getTotalScore();

        window["$"]["ajax"](url)["done"](function (data) {
            console.info("user.uploadScore done!" + data);

            // get rank again after upload score
            user.getRank();
        });
    },

    uploadLevelScore: function (score, level, passed) {
        // convert passed to number
        if (passed === true) {
            passed = 1;
        } else if (passed === false) {
            passed = 0;
        }

        // add 1 to level, since level on server is count from 1.
        level = level + 1;

        var url = config.ApiUrl;
        url += "?action=setLevelScore";
        url += "&userName=" + user.id;
        url += "&gameId=" + config.GameId;
        url += "&score=" + score;
        url += "&levelNo=" + level;
        url += "&isPass=" + passed;

        console.log("upload level score: score = " + score + ", level = " + level + ", passed = " + passed);

        window["$"]["ajax"](url)["done"](function (data) {
            console.info("user.uploadBoss done!" + data);

            // get rank after upload new record
            user.getRank();
        });
    }
};