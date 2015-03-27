
extern zend_class_entry *yaf_route_rewrite_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Rewrite);

PHP_METHOD(Yaf_Route_Rewrite, getInstance);
PHP_METHOD(Yaf_Route_Rewrite, __construct);
PHP_METHOD(Yaf_Route_Rewrite, route);
PHP_METHOD(Yaf_Route_Rewrite, _match);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_rewrite_getinstance, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_rewrite___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, match)
	ZEND_ARG_INFO(0, route)
	ZEND_ARG_INFO(0, verify)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_rewrite_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_rewrite__match, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_rewrite_method_entry) {
	PHP_ME(Yaf_Route_Rewrite, getInstance, arginfo_yaf_route_rewrite_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Route_Rewrite, __construct, arginfo_yaf_route_rewrite___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Route_Rewrite, route, arginfo_yaf_route_rewrite_route, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Rewrite, _match, arginfo_yaf_route_rewrite__match, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
