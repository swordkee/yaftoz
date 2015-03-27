
extern zend_class_entry *yaf_route_static_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Static);

PHP_METHOD(Yaf_Route_Static, __construct);
PHP_METHOD(Yaf_Route_Static, match);
PHP_METHOD(Yaf_Route_Static, route);
PHP_METHOD(Yaf_Route_Static, getInstance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_static_match, 0, 0, 1)
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_static_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_static_getinstance, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_static_method_entry) {
	PHP_ME(Yaf_Route_Static, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Route_Static, match, arginfo_yaf_route_static_match, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Static, route, arginfo_yaf_route_static_route, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Static, getInstance, arginfo_yaf_route_static_getinstance, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
