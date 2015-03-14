var WeixinApi = (function () {

    "use strict";

    function weixinShareTimeline(data, callbacks) {
        callbacks = callbacks || {};
        var shareTimeline = function (theData) {
            window["WeixinJSBridge"]["invoke"]('shareTimeline', {
                "appid": theData["appId"] ? theData["appId"] : '',
                "img_url": theData["imgUrl"],
                "link": theData["link"],
                "desc": theData["title"],
                "title": theData["desc"], // 注意这里要分享出去的内容是desc
                "img_width": "120",
                "img_height": "120"
            }, function (resp) {
                switch (resp["err_msg"]) {
                    // share_timeline:cancel 用户取消
                    case 'share_timeline:cancel':
                        callbacks.cancel && callbacks.cancel(resp);
                        break;
                    // share_timeline:fail　发送失败
                    case 'share_timeline:fail':
                        callbacks.fail && callbacks.fail(resp);
                        break;
                    // share_timeline:confirm 发送成功
                    case 'share_timeline:confirm':
                    case 'share_timeline:ok':
                        callbacks.confirm && callbacks.confirm(resp);
                        break;
                }
                // 无论成功失败都会执行的回调
                callbacks.all && callbacks.all(resp);
            });
        };
        window["WeixinJSBridge"]["on"]('menu:share:timeline', function (argv) {
            if (callbacks.async && callbacks.ready) {
                window["_wx_loadedCb_"] = callbacks.dataLoaded || new Function();
                if (window["_wx_loadedCb_"].toString().indexOf("_wx_loadedCb_") > 0) {
                    window["_wx_loadedCb_"] = new Function();
                }
                callbacks.dataLoaded = function (newData) {
                    window["_wx_loadedCb_"](newData);
                    shareTimeline(newData);
                };
                // 然后就绪
                callbacks.ready && callbacks.ready(argv);
            } else {
                // 就绪状态
                callbacks.ready && callbacks.ready(argv);
                shareTimeline(data);
            }
        });
    }

    function weixinSendAppMessage(data, callbacks) {
        callbacks = callbacks || {};
        var sendAppMessage = function (theData) {
            window["WeixinJSBridge"]["invoke"]('sendAppMessage', {
                "appid": theData["appId"] ? theData["appId"] : '',
                "img_url": theData["imgUrl"],
                "link": theData["link"],
                "desc": theData["desc"],
                "title": theData["title"],
                "img_width": "120",
                "img_height": "120"
            }, function (resp) {
                switch (resp["err_msg"]) {
                    // send_app_msg:cancel 用户取消
                    case 'send_app_msg:cancel':
                        callbacks.cancel && callbacks.cancel(resp);
                        break;
                    // send_app_msg:fail　发送失败
                    case 'send_app_msg:fail':
                        callbacks.fail && callbacks.fail(resp);
                        break;
                    // send_app_msg:confirm 发送成功
                    case 'send_app_msg:confirm':
                    case 'send_app_msg:ok':
                        callbacks.confirm && callbacks.confirm(resp);
                        break;
                }

                callbacks.all && callbacks.all(resp);
            });
        };
        window["WeixinJSBridge"]["on"]('menu:share:appmessage', function (argv) {
            if (callbacks.async && callbacks.ready) {
                window["_wx_loadedCb_"] = callbacks.dataLoaded || new Function();
                if (window["_wx_loadedCb_"].toString().indexOf("_wx_loadedCb_") > 0) {
                    window["_wx_loadedCb_"] = new Function();
                }
                callbacks.dataLoaded = function (newData) {
                    window["_wx_loadedCb_"](newData);
                    sendAppMessage(newData);
                };
                // 然后就绪
                callbacks.ready && callbacks.ready(argv);
            } else {
                // 就绪状态
                callbacks.ready && callbacks.ready(argv);
                sendAppMessage(data);
            }
        });
    }

    function weixinShareWeibo(data, callbacks) {
        callbacks = callbacks || {};
        var shareWeibo = function (theData) {
            window["WeixinJSBridge"]["invoke"]('shareWeibo', {
                "content": theData["desc"],
                "url": theData["link"]
            }, function (resp) {
                switch (resp["err_msg"]) {
                    case 'share_weibo:cancel':
                        callbacks.cancel && callbacks.cancel(resp);
                        break;

                    case 'share_weibo:fail':
                        callbacks.fail && callbacks.fail(resp);
                        break;

                    case 'share_weibo:confirm':
                    case 'share_weibo:ok':
                        callbacks.confirm && callbacks.confirm(resp);
                        break;
                }

                callbacks.all && callbacks.all(resp);
            });
        };
        window["WeixinJSBridge"]["on"]('menu:share:weibo', function (argv) {
            if (callbacks.async && callbacks.ready) {
                window["_wx_loadedCb_"] = callbacks.dataLoaded || new Function();
                if (window["_wx_loadedCb_"].toString().indexOf("_wx_loadedCb_") > 0) {
                    window["_wx_loadedCb_"] = new Function();
                }
                callbacks.dataLoaded = function (newData) {
                    window["_wx_loadedCb_"](newData);
                    shareWeibo(newData);
                };

                callbacks.ready && callbacks.ready(argv);
            } else {

                callbacks.ready && callbacks.ready(argv);
                shareWeibo(data);
            }
        });
    }


    function imagePreview(curSrc, srcList) {
        if (!curSrc || !srcList || srcList.length == 0) {
            return;
        }
        window["WeixinJSBridge"]["invoke"]('imagePreview', {
            'current': curSrc,
            'urls': srcList
        });
    }

    function showOptionMenu() {
        window["WeixinJSBridge"]["call"]('showOptionMenu');
    }


    function hideOptionMenu() {
        window["WeixinJSBridge"]["call"]('hideOptionMenu');
    }

    function showToolbar() {
        window["WeixinJSBridge"]["call"]('showToolbar');
    }

    function hideToolbar() {
        window["WeixinJSBridge"]["call"]('hideToolbar');
    }

    function getNetworkType(callback) {
        if (callback && typeof callback == 'function') {
            window["WeixinJSBridge"]["invoke"]('getNetworkType', {}, function (e) {
                callback(e["err_msg"]);
            });
        }
    }

    function closeWindow() {
        window["WeixinJSBridge"]["call"]("closeWindow");
    }

    function wxJsBridgeReady(readyCallback) {
        if (readyCallback && typeof readyCallback == 'function') {
            var Api = this;
            var wxReadyFunc = function () {
                readyCallback(Api);
            };
            if (typeof window["WeixinJSBridge"] == "undefined") {
                if (document.addEventListener) {
                    document.addEventListener('WeixinJSBridgeReady', wxReadyFunc, false);
                } else if (document.attachEvent) {
                    document.attachEvent('WeixinJSBridgeReady', wxReadyFunc);
                    document.attachEvent('onWeixinJSBridgeReady', wxReadyFunc);
                }
            } else {
                wxReadyFunc();
            }
        }
    }

    return {
        version: "1.8",
        ready: wxJsBridgeReady,
        shareToTimeline: weixinShareTimeline,
        shareToWeibo: weixinShareWeibo,
        shareToFriend: weixinSendAppMessage,
        showOptionMenu: showOptionMenu,
        hideOptionMenu: hideOptionMenu,
        showToolbar: showToolbar,
        hideToolbar: hideToolbar,
        getNetworkType: getNetworkType,
        imagePreview: imagePreview,
        closeWindow: closeWindow
    };
})();
