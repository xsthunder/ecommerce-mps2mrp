/**
 *   For
 *   Created by xs at 2018/1/12
 */
"use strict";
(function () {
    //fix this, add util
    var enableLocalServer = true;
    var enableHttps = false;

    var serverPort =20184;
    var server='l.lovecust.com';
    if(enableLocalServer){
        server = 'localhost';
    }
    var tmp = {
        enableHttps:enableHttps,
        server:server,
        serverPort:serverPort,
        base_url:("http" + (enableHttps?"s":"") +"://"+server + ':' + serverPort)
    };
    console.log(tmp.base_url);
    angular.module('app')
        .constant('appConfigure',tmp);
})();