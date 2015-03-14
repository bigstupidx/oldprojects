// 微信分享的数据
window.wxData = {
    "appId": "", // 服务号可以填写appId
    "imgUrl": "",
    "link": "",
    "desc": "看看你能过几关",
    "title": "科鲁兹大赢家"
};

// set dynamic url
window.wxData["link"] = location.protocol+'//'+location.host+location.pathname;
window.wxData["imgUrl"] = window.wxData["link"] + "/res/share/logo.png";
//alert(window.wxData["imgUrl"] + "\n" + window.wxData["link"]);

function wxUpdateData(m) {
    window.wxData["desc"] = "我拼了" + m + "分，看看你能拼多少？";
}

WeixinApi.ready(function (Api) {

    // 分享的回调
    var wxCallbacks = {
        ready: function () {
        },

        cancel: function (resp) {
        },

        fail: function (resp) {
        },

        confirm: function (resp) {
        },

        all: function (resp) {
        }
    };

    Api.shareToFriend(window.wxData, wxCallbacks);

    Api.shareToTimeline(window.wxData, wxCallbacks);

    Api.shareToWeibo(window.wxData, wxCallbacks);
});