/**
 * Created by Administrator on 2014/9/17.
 */
var application = {
    error: function (info, error) {
        alert(info);
        if (error) {
            throw new Error(error);
        }
    },

    getURLParameter: function (name) {
        return decodeURIComponent(
            (RegExp("[?|&]" + name + "=(.+?)(&|$)").exec(location.search) || [, null])[1]
        )
    },

    isArray: function (obj) {
        return Object.prototype.toString.call(obj) === "[object Array]";
    }
};

window["jQuery"]["ajaxSetup"]({
    "timeout": config.TimeOut * 1e3,
    "async": false,
    "cache": false,
    "type": "GET",
    "dataType": "jsonp",
    "jsonpCallback": "jsonResult",
    "error": function (jqXHR, textStatus, errorThrown) {
        if (this["url"]["indexOf"]("action=setScore") == -1) {
            application.error("获取数据失败，请检查您的网络。", errorThrown);
        } else {
            application.error("分数提交失败。");
        }
    }
});