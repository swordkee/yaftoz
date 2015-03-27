
extern zend_class_entry *yaf_router_ce;

ZEPHIR_INIT_CLASS(Yaf_Router);

PHP_METHOD(Yaf_Router, __construct);
PHP_METHOD(Yaf_Router, addRoute);
PHP_METHOD(Yaf_Router, addConfig);
PHP_METHOD(Yaf_Router, _getRouteFromConfig);
PHP_METHOD(Yaf_Router, _getRouteFromArray);
PHP_METHOD(Yaf_Router, getCurrentRoute);
PHP_METHOD(Yaf_Router, getRoute);
PHP_METHOD(Yaf_Router, getRoutes);
PHP_METHOD(Yaf_Router, route);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router_addroute, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_OBJ_INFO(0, route, Yaf\\Route_Interface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router_addconfig, 0, 0, 1)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router__getroutefromconfig, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, info, Yaf\\Config_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router__getroutefromarray, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, info, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router_getroute, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_router_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_router_method_entry) {
	PHP_ME(Yaf_Router, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Router, addRoute, arginfo_yaf_router_addroute, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Router, addConfig, arginfo_yaf_router_addconfig, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Router, _getRouteFromConfig, arginfo_yaf_router__getroutefromconfig, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Router, _getRouteFromArray, arginfo_yaf_router__getroutefromarray, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Router, getCurrentRoute, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Router, getRoute, arginfo_yaf_router_getroute, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Router, getRoutes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Router, route, arginfo_yaf_router_route, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
