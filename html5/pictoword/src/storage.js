/**
 * Created by Administrator on 2014/8/25.
 */
var storage = {
    topLevelKey: "topLevel",
    currentLevelKey: "currentLevel",
    levelScoreKey: "levelScore",
    chanceKey: "chance",
    dateKey: "date",
    justWonKey: "justWon", // for fade in key on level scene
    bonusKey: "bonus",

    _getValue: function (key, defaultValue) {
        var value = cc.sys.localStorage.getItem(key);
        if (value) {
            var number = parseInt(value);
            if (isNaN(number)) {
                return 0;
            } else {
                return number;
            }
        } else {
            if (defaultValue == undefined)
                return 0;
            else
                return defaultValue;
        }
    },

    clear: function () {
        cc.sys.localStorage.clear();
    },

    getCurrentBoss: function () {
        var currentBoss = (storage.getCurrentLevel() / 3) | 0;
        return currentBoss;
    },

    setCurrentLevel: function (level) {
        cc.sys.localStorage.setItem(storage.currentLevelKey, "" + level);
    },

    getCurrentLevel: function () {
        return storage._getValue(storage.currentLevelKey);
    },

    setTopLevel: function (level) {
        if (storage.getTopLevel() < level) {
            cc.sys.localStorage.setItem(storage.topLevelKey, "" + level);
        }
    },

    getTopLevel: function () {
        return storage._getValue(storage.topLevelKey);
    },

    setLevelScore: function (level, score, isPass, forced) {
        console.log("setLevelScore(level = " + level + ", score = " + score + ", isPass = " + isPass + ");");

        var needUpload = false;

        // save score
        var oldScore = storage.getLevelScore(level);
        if (score > oldScore) {
            cc.sys.localStorage.setItem(storage.levelScoreKey + level, "" + score);
            needUpload = true;
        }

        // save pass
        var topLevel = storage.getTopLevel();
        if (isPass && topLevel < level + 1) {
            storage.setTopLevel(level + 1);
            needUpload = true;
        }

        if (needUpload && !forced) {
            user.uploadLevelScore(score, level, isPass);
        }
    },

    getLevelScore: function (level) {
        return storage._getValue(storage.levelScoreKey + level);
    },

    setChance: function (chance) {
        cc.sys.localStorage.setItem(storage.chanceKey, "" + chance);
    },

    getChance: function () {
        return storage._getValue(storage.chanceKey, config.MaxChance);
    },

    setDate: function (date) {
        cc.sys.localStorage.setItem(storage.dateKey, "" + date);
    },

    getDate: function () {
        return storage._getValue(storage.dateKey, 100);
    },

    setJustWon: function (won) {
        cc.sys.localStorage.setItem(storage.justWonKey, "" + won);
    },

    getJustWon: function () {
        return storage._getValue(storage.justWonKey, 1);
    },

    setBonus: function (bonus) {
        cc.sys.localStorage.setItem(storage.bonusKey, "" + bonus);
    },

    getBonus: function () {
        return storage._getValue(storage.bonusKey, 0);
    },

    getBoss: function () {
        var boss = (storage.getTopLevel() / 3) | 0;
        return boss;
    },

    getTotalScore: function () {
        var totalScore = 0;
        for (var i = 0; i < 9; i++) {
            totalScore += storage.getLevelScore(i);
        }
        return totalScore;
    }
};