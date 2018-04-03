/**
 *   For
 *   Created by xs at 2018/1/12
 */
"use strict";
(function () {
    angular.module('app')
        .factory('urlConstant', fn);
    function fn($http,$mdToast,appConfigure) {
        var self = {};
        var base_url = appConfigure.base_url;
        self.notice = function (msg) {
            msg = msg || "something wrong";
            $mdToast.show(
                $mdToast.simple()
                    .textContent(msg)
                    .hideDelay(3000)
            );
        };
        self.post = function (url, obj, cb) {
            var pl = new FormData();
            for (var i in obj) {
                pl.append(i, obj[i]);
            }
            $http({
                url: base_url + '/' + url,
                method: 'POST',
                data: pl,
                headers: {'Content-Type': undefined}
            }).then(function (res) {
                cb(null, res.data);
            }, function (res) {
                cb(res);
            });
        };
        self.__wrap = function (method,url, cb) {
            $http({
                url: base_url + '/' + url,
                method: method
            }).then(function (res) {
                cb(null, res.data);
            }, function (reason) {
                cb(reason);
            })
        };
        self.get = function (url,cb) {
            self.__wrap('GET',url,cb);
        };
        self.delete= function (url,cb) {
            self.__wrap('DELETE',url,cb);
        };
        return self;
    }
})();