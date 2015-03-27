
extern zend_class_entry *yaf_plugin_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Plugin_Abstract);

PHP_METHOD(Yaf_Plugin_Abstract, dispatchLoopShutdown);
PHP_METHOD(Yaf_Plugin_Abstract, dispatchLoopStartup);
PHP_METHOD(Yaf_Plugin_Abstract, postDispatch);
PHP_METHOD(Yaf_Plugin_Abstract, preDispatch);
PHP_METHOD(Yaf_Plugin_Abstract, routerShutdown);
PHP_METHOD(Yaf_Plugin_Abstract, routerStartup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_dispatchloopshutdown, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_dispatchloopstartup, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_postdispatch, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_predispatch, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_routershutdown, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_plugin_abstract_routerstartup, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_plugin_abstract_method_entry) {
	PHP_ME(Yaf_Plugin_Abstract, dispatchLoopShutdown, arginfo_yaf_plugin_abstract_dispatchloopshutdown, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Plugin_Abstract, dispatchLoopStartup, arginfo_yaf_plugin_abstract_dispatchloopstartup, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Plugin_Abstract, postDispatch, arginfo_yaf_plugin_abstract_postdispatch, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Plugin_Abstract, preDispatch, arginfo_yaf_plugin_abstract_predispatch, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Plugin_Abstract, routerShutdown, arginfo_yaf_plugin_abstract_routershutdown, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Plugin_Abstract, routerStartup, arginfo_yaf_plugin_abstract_routerstartup, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
