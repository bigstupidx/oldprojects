// 微信分享的数据
window.wxData = {
    "appId": "", // 服务号可以填写appId
    "imgUrl": 'http://kivvi.mobi/2048/images/logo.png',
    "link": 'http://kivvi.mobi/2048',
    "desc": "看看你能得几分",
    "title": "凯迪拉克2048"
};

function wxUpdateData(m) {
    window.wxData.desc = "我得了" + m + "分，看看你能得多少分";
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

    Api.shareToFriend(wxData, wxCallbacks);

    Api.shareToTimeline(wxData, wxCallbacks);

    Api.shareToWeibo(wxData, wxCallbacks);
});