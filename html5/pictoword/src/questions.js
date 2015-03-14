/**
 * Created by Yu on 2014/8/31.
 */
var questions = {
    binaryCount: 9,
    multipleCount: 9,
    count: null, // binary count plus multiple count
    list: new Array(),
    current: null,

    /**
     * init 15 questions
     */
    build: function () {
        questions.count = questions.binaryCount + questions.multipleCount;

        if (questions.list.length > 0)
            return;

        var i = 0;
        do {
            var index = Math.floor(Math.random() * database.binaries.length);
            if (questions._isAvailableQuestion(database.binaries[index])) {
                questions.list.push({
                    data: database.binaries[index],
                    used: false});
                i++;
            }
        }
        while (i < questions.binaryCount);

        i = 0;
        do {
            var index = Math.floor(Math.random() * database.multiples.length);
            if (questions._isAvailableQuestion(database.multiples[index])) {
                questions.list.push({
                    data: database.multiples[index],
                    used: false});
                i++;
            }
        }
        while (i < questions.multipleCount);

        // next
        questions.next();
    },

    clear: function () {
        questions.list = [];

        questions.current = 0;
    },

    rebuild: function () {
        questions.clear();

        questions.build();
    },

    getQuestion: function () {
        return questions.list[questions.current].data;
    },

    getQuestionType: function () {
        if (questions.list[questions.current].data.options != undefined) {
            return "multiple";
        } else {
            return "binary"
        }
    },

    next: function () {
        var list = questions._availableList();

        if (list.length) {
            var i = Math.floor(Math.random() * list.length);
            questions.current = list[i].index;
            questions.list[questions.current].used = true;
        }
    },

    _availableList: function () {
        var list = [];
        for (var i = 0; i < questions.list.length; i++) {
            if (!questions.list[i].used) {
                list.push({
                    data: questions.list[i],
                    index: i
                });
            }
        }
        return list;
    },

    _isAvailableQuestion: function (question) {
        // remove repeated
        for (var i = 0; i < questions.list.length; i++) {
            if (questions.list[i].data.index == question.index) {
                return false;
            }
        }

        // only single multiple question on first boss
        if (storage.getCurrentBoss() == 0) {
            if (question.options) {
                if (question.answer.length > 1) {
                    return false;
                }
            }
        }
        return true;
    }
};