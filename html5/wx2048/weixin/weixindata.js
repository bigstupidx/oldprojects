// 微信分享的数据
window.wxData = {
    "appId": "", // 服务号可以填写appId
    "imgUrl": "http://kivvi.mobi/wx2048/res/share/logo.png",
    "link": "http://kivvi.mobi/wx2048",
    "desc": "看看你能拼多少？",
    "title": "拼出你的ATS-L"
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