
extern zend_class_entry *yaf_request_simple_ce;

ZEPHIR_INIT_CLASS(Yaf_Request_Simple);

PHP_METHOD(Yaf_Request_Simple, __construct);
PHP_METHOD(Yaf_Request_Simple, __clone);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_simple___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, method)
	ZEND_ARG_INFO(0, module)
	ZEND_ARG_INFO(0, controller)
	ZEND_ARG_INFO(0, action)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_request_simple_method_entry) {
	PHP_ME(Yaf_Request_Simple, __construct, arginfo_yaf_request_simple___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Request_Simple, __clone, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
