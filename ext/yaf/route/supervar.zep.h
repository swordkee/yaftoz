
extern zend_class_entry *yaf_route_supervar_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Supervar);

PHP_METHOD(Yaf_Route_Supervar, __construct);
PHP_METHOD(Yaf_Route_Supervar, route);
PHP_METHOD(Yaf_Route_Supervar, getInstance);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_supervar___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, varName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_supervar_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_supervar_getinstance, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_supervar_method_entry) {
	PHP_ME(Yaf_Route_Supervar, __construct, arginfo_yaf_route_supervar___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Route_Supervar, route, arginfo_yaf_route_supervar_route, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Route_Supervar, getInstance, arginfo_yaf_route_supervar_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
