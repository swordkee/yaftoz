
extern zend_class_entry *yaf_request_http_ce;

ZEPHIR_INIT_CLASS(Yaf_Request_Http);

PHP_METHOD(Yaf_Request_Http, __construct);
PHP_METHOD(Yaf_Request_Http, __clone);
PHP_METHOD(Yaf_Request_Http, __get);
PHP_METHOD(Yaf_Request_Http, get);
PHP_METHOD(Yaf_Request_Http, __set);
PHP_METHOD(Yaf_Request_Http, __isset);
PHP_METHOD(Yaf_Request_Http, getQuery);
PHP_METHOD(Yaf_Request_Http, getPost);
PHP_METHOD(Yaf_Request_Http, getCookie);
PHP_METHOD(Yaf_Request_Http, getFiles);
PHP_METHOD(Yaf_Request_Http, getRequest);
PHP_METHOD(Yaf_Request_Http, getRequestUri);
PHP_METHOD(Yaf_Request_Http, getPathInfo);
PHP_METHOD(Yaf_Request_Http, getBaseUri);
PHP_METHOD(Yaf_Request_Http, setBaseUri);
PHP_METHOD(Yaf_Request_Http, setRequestUri);
PHP_METHOD(Yaf_Request_Http, getScheme);
PHP_METHOD(Yaf_Request_Http, getHttpHost);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, requestUri)
	ZEND_ARG_INFO(0, baseUri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_getquery, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_getpost, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_getcookie, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_getfiles, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_getrequest, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_setbaseuri, 0, 0, 0)
	ZEND_ARG_INFO(0, baseUri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_http_setrequesturi, 0, 0, 0)
	ZEND_ARG_INFO(0, requestUri)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_request_http_method_entry) {
	PHP_ME(Yaf_Request_Http, __construct, arginfo_yaf_request_http___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Request_Http, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Request_Http, __get, arginfo_yaf_request_http___get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, get, arginfo_yaf_request_http_get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, __set, arginfo_yaf_request_http___set, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, __isset, arginfo_yaf_request_http___isset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getQuery, arginfo_yaf_request_http_getquery, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getPost, arginfo_yaf_request_http_getpost, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getCookie, arginfo_yaf_request_http_getcookie, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getFiles, arginfo_yaf_request_http_getfiles, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getRequest, arginfo_yaf_request_http_getrequest, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getRequestUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getPathInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getBaseUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, setBaseUri, arginfo_yaf_request_http_setbaseuri, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, setRequestUri, arginfo_yaf_request_http_setrequesturi, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getScheme, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Http, getHttpHost, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
