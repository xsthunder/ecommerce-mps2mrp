/**
 *   For
 *   Created by xs at 2018/1/12
 */
"use strict";
(function () {
    //fix this, add util
    var enableLocalServer = false;
    var enableHttps = false;
    var serverPort =20184;
    var server='';

    if(enableLocalServer){
        server = 'localhost';
    }
    if(!server){
        server = location.host;
        var index =server.indexOf(':');
        if( index >= 0){
            server = server.substr(0,index);
        }
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