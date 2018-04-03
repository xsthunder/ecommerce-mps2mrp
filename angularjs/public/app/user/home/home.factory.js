(function(){
	angular.module('app')
		.factory('UserFactory',fn);
	function fn(urlConstant){
		var self = {};
		self.get = function (path ,cb) {
		    urlConstant.get(path,cb);
        };
		return self;
	}
})();
