
extern zend_class_entry *yaf_route_map_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Map);

PHP_METHOD(Yaf_Route_Map, __construct);
PHP_METHOD(Yaf_Route_Map, route);
PHP_METHOD(Yaf_Route_Map, getInstance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_map___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, controller_prefer)
	ZEND_ARG_INFO(0, delimiter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_map_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_map_getinstance, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_map_method_entry) {
	PHP_ME(Yaf_Route_Map, __construct, arginfo_yaf_route_map___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Route_Map, route, arginfo_yaf_route_map_route, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Map, getInstance, arginfo_yaf_route_map_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
