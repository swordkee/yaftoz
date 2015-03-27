
extern zend_class_entry *yaf_response_http_ce;

ZEPHIR_INIT_CLASS(Yaf_Response_Http);

PHP_METHOD(Yaf_Response_Http, setResponseCode);
PHP_METHOD(Yaf_Response_Http, getResponseCode);
PHP_METHOD(Yaf_Response_Http, sendHeaders);
PHP_METHOD(Yaf_Response_Http, setRedirect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_http_setresponsecode, 0, 0, 1)
	ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_http_setredirect, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_response_http_method_entry) {
	PHP_ME(Yaf_Response_Http, setResponseCode, arginfo_yaf_response_http_setresponsecode, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Http, getResponseCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Http, sendHeaders, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Response_Http, setRedirect, arginfo_yaf_response_http_setredirect, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
