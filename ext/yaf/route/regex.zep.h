
extern zend_class_entry *yaf_route_regex_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Regex);

PHP_METHOD(Yaf_Route_Regex, getInstance);
PHP_METHOD(Yaf_Route_Regex, __construct);
PHP_METHOD(Yaf_Route_Regex, route);
PHP_METHOD(Yaf_Route_Regex, _getMappedValues);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_regex_getinstance, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_regex___construct, 0, 0, 3)
	ZEND_ARG_INFO(0, match)
	ZEND_ARG_INFO(0, route)
	ZEND_ARG_INFO(0, map)
	ZEND_ARG_INFO(0, verify)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_regex_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_regex__getmappedvalues, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, values, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_regex_method_entry) {
	PHP_ME(Yaf_Route_Regex, getInstance, arginfo_yaf_route_regex_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Route_Regex, __construct, arginfo_yaf_route_regex___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Route_Regex, route, arginfo_yaf_route_regex_route, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Regex, _getMappedValues, arginfo_yaf_route_regex__getmappedvalues, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
