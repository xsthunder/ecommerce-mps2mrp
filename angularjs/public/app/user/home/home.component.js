(function () {
    angular.module('app')
        .component('xxHome', {
            templateUrl: '/app/user/home/home.html',
            controller: ctrl
        });

    function ctrl($scope,UserFactory,userService,$state,urlConstant) {
        var loading = "now loading";
        var inputField = [
            'mps',
            'bom',
            'stock',
            'consist'
        ];
        $scope.inputField = inputField;
        $scope.output = "now output yet";
        $scope.input = { };
        inputField.forEach(function (value) { $scope.input[value] = loading });
        var setField = function (s) {
            var cb = function (err,res) {
                if(err||res['err'])return urlConstant.notice(err);
                $scope.input[s] = res['res'];
            };
           UserFactory.get(s,cb);
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
