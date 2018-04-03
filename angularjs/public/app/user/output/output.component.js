/**
 *   For
 *   Created by xs at 2018/4/3
 */
"use strict";
(function () {
    angular.module('app')
        .component('xxOutput',{
            templateUrl:'./app/user/output/output.html',
            controller:ctrl
        });
    function ctrl($scope,UserFactory,urlConstant) {
        $scope.output = 'now loading';
        function cb(err,res) {
            if(err)return urlConstant.notice('err');
            $scope.output = res['res'];
        }
        UserFactory.get('output',cb);
    }
})();
