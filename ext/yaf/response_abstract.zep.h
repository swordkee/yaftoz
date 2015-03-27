
extern zend_class_entry *yaf_response_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Response_Abstract);

PHP_METHOD(Yaf_Response_Abstract, appendBody);
PHP_METHOD(Yaf_Response_Abstract, clearBody);
PHP_METHOD(Yaf_Response_Abstract, clearHeaders);
PHP_METHOD(Yaf_Response_Abstract, __clone);
PHP_METHOD(Yaf_Response_Abstract, __construct);
PHP_METHOD(Yaf_Response_Abstract, __destruct);
PHP_METHOD(Yaf_Response_Abstract, getBody);
PHP_METHOD(Yaf_Response_Abstract, getHeader);
PHP_METHOD(Yaf_Response_Abstract, prependBody);
PHP_METHOD(Yaf_Response_Abstract, response);
PHP_METHOD(Yaf_Response_Abstract, setAllHeaders);
PHP_METHOD(Yaf_Response_Abstract, setBody);
PHP_METHOD(Yaf_Response_Abstract, setHeader);
PHP_METHOD(Yaf_Response_Abstract, setRedirect);
PHP_METHOD(Yaf_Response_Abstract, __toString);
PHP_METHOD(Yaf_Response_Abstract, _normalizeHeader);
PHP_METHOD(Yaf_Response_Abstract, sendHeaders);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_appendbody, 0, 0, 1)
	ZEND_ARG_INFO(0, body)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_clearbody, 0, 0, 0)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_getbody, 0, 0, 0)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_prependbody, 0, 0, 1)
	ZEND_ARG_INFO(0, body)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_setbody, 0, 0, 1)
	ZEND_ARG_INFO(0, body)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_setheader, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, replace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract_setredirect, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_response_abstract__normalizeheader, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_response_abstract_method_entry) {
	PHP_ME(Yaf_Response_Abstract, appendBody, arginfo_yaf_response_abstract_appendbody, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, clearBody, arginfo_yaf_response_abstract_clearbody, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, clearHeaders, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Response_Abstract, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Response_Abstract, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Yaf_Response_Abstract, getBody, arginfo_yaf_response_abstract_getbody, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, getHeader, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, prependBody, arginfo_yaf_response_abstract_prependbody, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, response, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, setAllHeaders, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, setBody, arginfo_yaf_response_abstract_setbody, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, setHeader, arginfo_yaf_response_abstract_setheader, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, setRedirect, arginfo_yaf_response_abstract_setredirect, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Response_Abstract, _normalizeHeader, arginfo_yaf_response_abstract__normalizeheader, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Response_Abstract, sendHeaders, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
