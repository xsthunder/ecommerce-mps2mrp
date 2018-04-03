(function () {
    var States = [
        {
            name: 'show',
            url: '/show',
            component: 'xxShow'
        },{                       //user
            name: 'show.home',
            url: '/home',
            component: 'xxHome'
        },{
            name:'show.output',
            url:'output',
            component:'xxOutput'
        },
        {
            name: "otherwise",
            url: "*path",
            controller: function ($state) {
                $state.go('show.home');
            }
        }
    ];
    angular.module('app')
        .constant('ROUTER_CONSTANT', States);
})();