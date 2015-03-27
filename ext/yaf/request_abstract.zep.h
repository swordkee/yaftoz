
extern zend_class_entry *yaf_request_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Request_Abstract);

PHP_METHOD(Yaf_Request_Abstract, getActionName);
PHP_METHOD(Yaf_Request_Abstract, getBaseUri);
PHP_METHOD(Yaf_Request_Abstract, getControllerName);
PHP_METHOD(Yaf_Request_Abstract, getEnv);
PHP_METHOD(Yaf_Request_Abstract, getQuery);
PHP_METHOD(Yaf_Request_Abstract, setException);
PHP_METHOD(Yaf_Request_Abstract, getException);
PHP_METHOD(Yaf_Request_Abstract, getLanguage);
PHP_METHOD(Yaf_Request_Abstract, getMethod);
PHP_METHOD(Yaf_Request_Abstract, getModuleName);
PHP_METHOD(Yaf_Request_Abstract, getParam);
PHP_METHOD(Yaf_Request_Abstract, getParams);
PHP_METHOD(Yaf_Request_Abstract, getRequestUri);
PHP_METHOD(Yaf_Request_Abstract, getServer);
PHP_METHOD(Yaf_Request_Abstract, isCli);
PHP_METHOD(Yaf_Request_Abstract, isDispatched);
PHP_METHOD(Yaf_Request_Abstract, isGet);
PHP_METHOD(Yaf_Request_Abstract, isHead);
PHP_METHOD(Yaf_Request_Abstract, isOptions);
PHP_METHOD(Yaf_Request_Abstract, isPost);
PHP_METHOD(Yaf_Request_Abstract, isPut);
PHP_METHOD(Yaf_Request_Abstract, isDelete);
PHP_METHOD(Yaf_Request_Abstract, isXmlHttpRequest);
PHP_METHOD(Yaf_Request_Abstract, isRouted);
PHP_METHOD(Yaf_Request_Abstract, setActionName);
PHP_METHOD(Yaf_Request_Abstract, setBaseUri);
PHP_METHOD(Yaf_Request_Abstract, setControllerName);
PHP_METHOD(Yaf_Request_Abstract, setDispatched);
PHP_METHOD(Yaf_Request_Abstract, setModuleName);
PHP_METHOD(Yaf_Request_Abstract, setParam);
PHP_METHOD(Yaf_Request_Abstract, clearParams);
PHP_METHOD(Yaf_Request_Abstract, setRequestUri);
PHP_METHOD(Yaf_Request_Abstract, setRouted);
PHP_METHOD(Yaf_Request_Abstract, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_getenv, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_getquery, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setexception, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, exception, Exception, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_getparam, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_getserver, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, tmpDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setactionname, 0, 0, 1)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setbaseuri, 0, 0, 0)
	ZEND_ARG_INFO(0, baseUri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setcontrollername, 0, 0, 1)
	ZEND_ARG_INFO(0, controller)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setdispatched, 0, 0, 0)
	ZEND_ARG_INFO(0, dispatched)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setmodulename, 0, 0, 1)
	ZEND_ARG_INFO(0, module)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setparam, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setrequesturi, 0, 0, 0)
	ZEND_ARG_INFO(0, requestUri)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_request_abstract_setrouted, 0, 0, 0)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_request_abstract_method_entry) {
	PHP_ME(Yaf_Request_Abstract, getActionName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getBaseUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getControllerName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getEnv, arginfo_yaf_request_abstract_getenv, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getQuery, arginfo_yaf_request_abstract_getquery, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setException, arginfo_yaf_request_abstract_setexception, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getException, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getLanguage, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getMethod, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getModuleName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getParam, arginfo_yaf_request_abstract_getparam, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getParams, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getRequestUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, getServer, arginfo_yaf_request_abstract_getserver, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isCli, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isDispatched, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isGet, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isHead, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isOptions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isPost, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isPut, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isDelete, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isXmlHttpRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, isRouted, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setActionName, arginfo_yaf_request_abstract_setactionname, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setBaseUri, arginfo_yaf_request_abstract_setbaseuri, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setControllerName, arginfo_yaf_request_abstract_setcontrollername, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setDispatched, arginfo_yaf_request_abstract_setdispatched, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setModuleName, arginfo_yaf_request_abstract_setmodulename, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setParam, arginfo_yaf_request_abstract_setparam, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, clearParams, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setRequestUri, arginfo_yaf_request_abstract_setrequesturi, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, setRouted, arginfo_yaf_request_abstract_setrouted, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Request_Abstract, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
  PHP_FE_END
};
