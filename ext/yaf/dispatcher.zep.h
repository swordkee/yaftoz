
extern zend_class_entry *yaf_dispatcher_ce;

ZEPHIR_INIT_CLASS(Yaf_Dispatcher);

PHP_METHOD(Yaf_Dispatcher, autoRender);
PHP_METHOD(Yaf_Dispatcher, catchException);
PHP_METHOD(Yaf_Dispatcher, __clone);
PHP_METHOD(Yaf_Dispatcher, __construct);
PHP_METHOD(Yaf_Dispatcher, disableView);
PHP_METHOD(Yaf_Dispatcher, dispatch);
PHP_METHOD(Yaf_Dispatcher, handle);
PHP_METHOD(Yaf_Dispatcher, getAction);
PHP_METHOD(Yaf_Dispatcher, prepareActionParams);
PHP_METHOD(Yaf_Dispatcher, getActionParams);
PHP_METHOD(Yaf_Dispatcher, getController);
PHP_METHOD(Yaf_Dispatcher, _fixDefault);
PHP_METHOD(Yaf_Dispatcher, _formatName);
PHP_METHOD(Yaf_Dispatcher, enableView);
PHP_METHOD(Yaf_Dispatcher, flushInstantly);
PHP_METHOD(Yaf_Dispatcher, getApplication);
PHP_METHOD(Yaf_Dispatcher, getInstance);
PHP_METHOD(Yaf_Dispatcher, getRequest);
PHP_METHOD(Yaf_Dispatcher, getRouter);
PHP_METHOD(Yaf_Dispatcher, initView);
PHP_METHOD(Yaf_Dispatcher, registerPlugin);
PHP_METHOD(Yaf_Dispatcher, returnResponse);
PHP_METHOD(Yaf_Dispatcher, setDefaultAction);
PHP_METHOD(Yaf_Dispatcher, setDefaultController);
PHP_METHOD(Yaf_Dispatcher, setDefaultModule);
PHP_METHOD(Yaf_Dispatcher, setErrorHandler);
PHP_METHOD(Yaf_Dispatcher, setRequest);
PHP_METHOD(Yaf_Dispatcher, setView);
PHP_METHOD(Yaf_Dispatcher, __sleep);
PHP_METHOD(Yaf_Dispatcher, throwException);
PHP_METHOD(Yaf_Dispatcher, __wakeup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_autorender, 0, 0, 1)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_catchexception, 0, 0, 0)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_dispatch, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_handle, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, view, Yaf\\View_Interface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_getaction, 0, 0, 4)
	ZEND_ARG_INFO(0, appDir)
	ZEND_ARG_OBJ_INFO(0, controller, Yaf\\Controller_Abstract, 0)
	ZEND_ARG_INFO(0, action)
	ZEND_ARG_INFO(0, module)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_prepareactionparams, 0, 0, 2)
	ZEND_ARG_INFO(0, request)
	ZEND_ARG_INFO(0, methodParams)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_getactionparams, 0, 0, 2)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_getcontroller, 0, 0, 3)
	ZEND_ARG_INFO(0, appDir)
	ZEND_ARG_INFO(0, module)
	ZEND_ARG_INFO(0, controller)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher__fixdefault, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher__formatname, 0, 0, 1)
	ZEND_ARG_INFO(0, unformatted)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_flushinstantly, 0, 0, 1)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_initview, 0, 0, 0)
	ZEND_ARG_INFO(0, templates_dir)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_registerplugin, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, plugin, Yaf\\Plugin_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_returnresponse, 0, 0, 0)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_setdefaultaction, 0, 0, 1)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_setdefaultcontroller, 0, 0, 1)
	ZEND_ARG_INFO(0, controller)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_setdefaultmodule, 0, 0, 1)
	ZEND_ARG_INFO(0, module)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_seterrorhandler, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, error_types)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_setrequest, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_setview, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, view, Yaf\\View_Interface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_dispatcher_throwexception, 0, 0, 0)
	ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_dispatcher_method_entry) {
	PHP_ME(Yaf_Dispatcher, autoRender, arginfo_yaf_dispatcher_autorender, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, catchException, arginfo_yaf_dispatcher_catchexception, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, __construct, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Dispatcher, disableView, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, dispatch, arginfo_yaf_dispatcher_dispatch, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, handle, arginfo_yaf_dispatcher_handle, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, getAction, arginfo_yaf_dispatcher_getaction, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, prepareActionParams, arginfo_yaf_dispatcher_prepareactionparams, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, getActionParams, arginfo_yaf_dispatcher_getactionparams, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, getController, arginfo_yaf_dispatcher_getcontroller, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, _fixDefault, arginfo_yaf_dispatcher__fixdefault, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, _formatName, arginfo_yaf_dispatcher__formatname, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, enableView, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, flushInstantly, arginfo_yaf_dispatcher_flushinstantly, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, getApplication, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, getInstance, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Dispatcher, getRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, getRouter, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, initView, arginfo_yaf_dispatcher_initview, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, registerPlugin, arginfo_yaf_dispatcher_registerplugin, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, returnResponse, arginfo_yaf_dispatcher_returnresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setDefaultAction, arginfo_yaf_dispatcher_setdefaultaction, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setDefaultController, arginfo_yaf_dispatcher_setdefaultcontroller, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setDefaultModule, arginfo_yaf_dispatcher_setdefaultmodule, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setErrorHandler, arginfo_yaf_dispatcher_seterrorhandler, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setRequest, arginfo_yaf_dispatcher_setrequest, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, setView, arginfo_yaf_dispatcher_setview, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, __sleep, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Dispatcher, throwException, arginfo_yaf_dispatcher_throwexception, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Dispatcher, __wakeup, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
