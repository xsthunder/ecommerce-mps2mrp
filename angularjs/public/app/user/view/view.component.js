/**
 *   For
 *   Created by xs at 2018/4/4
 */
"use strict";
(function () {
    angular.module('app')
        .component('xxView', {
            templateUrl: '/app/user/view/view.html',
            controller: ctrl
        });

    function ctrl($scope,$state,urlConstant) {
        var loading = "now loading";
        var inputField = [
            'mps',
            'bom',
            'stock',
            'consist',
            'output'
        ];
        $scope.inputField = inputField;
        $scope.input = { };
        inputField.forEach(function (value) { $scope.input[value] = loading });
        var setField = function (s) {
            var cb = function (err,res) {
                if(err||res['err'])return urlConstant.notice(err);
                $scope.input[s] = res['res'];
            };
            urlConstant.get(s,cb);
        };
        inputField.forEach(function (value) { setField(value) });
        $scope.post =function (s,ans) {
            var body = {};
            body[s] = ans;
            var cb = function (err,res) {
                if(err||res['err'])return urlConstant.notice(err);
                $scope.input[s] = res['res'];
                urlConstant.notice(s+' updated');
            };
            urlConstant.post(s,body,cb);
        }
    }
})();
