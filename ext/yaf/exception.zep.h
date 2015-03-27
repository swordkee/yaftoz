
extern zend_class_entry *yaf_exception_ce;

ZEPHIR_INIT_CLASS(Yaf_Exception);

PHP_METHOD(Yaf_Exception, trigger_error);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_exception_trigger_error, 0, 0, 0)
	ZEND_ARG_INFO(0, errmsg)
	ZEND_ARG_INFO(0, errtype)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_exception_method_entry) {
	PHP_ME(Yaf_Exception, trigger_error, arginfo_yaf_exception_trigger_error, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
