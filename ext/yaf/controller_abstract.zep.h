
extern zend_class_entry *yaf_controller_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Controller_Abstract);

PHP_METHOD(Yaf_Controller_Abstract, __construct);
PHP_METHOD(Yaf_Controller_Abstract, display);
PHP_METHOD(Yaf_Controller_Abstract, forward);
PHP_METHOD(Yaf_Controller_Abstract, getInvokeArg);
PHP_METHOD(Yaf_Controller_Abstract, getInvokeArgs);
PHP_METHOD(Yaf_Controller_Abstract, getModuleName);
PHP_METHOD(Yaf_Controller_Abstract, getRequest);
PHP_METHOD(Yaf_Controller_Abstract, getResponse);
PHP_METHOD(Yaf_Controller_Abstract, getView);
PHP_METHOD(Yaf_Controller_Abstract, getViewpath);
PHP_METHOD(Yaf_Controller_Abstract, init);
PHP_METHOD(Yaf_Controller_Abstract, initView);
PHP_METHOD(Yaf_Controller_Abstract, render);
PHP_METHOD(Yaf_Controller_Abstract, redirect);
PHP_METHOD(Yaf_Controller_Abstract, setViewpath);
PHP_METHOD(Yaf_Controller_Abstract, getViewScript);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract___construct, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
	ZEND_ARG_OBJ_INFO(0, view, Yaf\\View_Interface, 0)
	ZEND_ARG_ARRAY_INFO(0, invokeArgs, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_display, 0, 0, 0)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_ARRAY_INFO(0, parameters, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_forward, 0, 0, 1)
	ZEND_ARG_INFO(0, module)
	ZEND_ARG_INFO(0, controller)
	ZEND_ARG_INFO(0, action)
	ZEND_ARG_ARRAY_INFO(0, args, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_getinvokearg, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_render, 0, 0, 0)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_ARRAY_INFO(0, parameters, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_redirect, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_setviewpath, 0, 0, 1)
	ZEND_ARG_INFO(0, templateDir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_controller_abstract_getviewscript, 0, 0, 0)
	ZEND_ARG_INFO(0, action)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_controller_abstract_method_entry) {
	PHP_ME(Yaf_Controller_Abstract, __construct, arginfo_yaf_controller_abstract___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Controller_Abstract, display, arginfo_yaf_controller_abstract_display, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, forward, arginfo_yaf_controller_abstract_forward, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getInvokeArg, arginfo_yaf_controller_abstract_getinvokearg, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getInvokeArgs, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getModuleName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getResponse, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getView, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getViewpath, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, init, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, initView, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, render, arginfo_yaf_controller_abstract_render, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, redirect, arginfo_yaf_controller_abstract_redirect, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, setViewpath, arginfo_yaf_controller_abstract_setviewpath, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Controller_Abstract, getViewScript, arginfo_yaf_controller_abstract_getviewscript, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
