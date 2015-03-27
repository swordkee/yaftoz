
extern zend_class_entry *yaf_view_simple_ce;

ZEPHIR_INIT_CLASS(Yaf_View_Simple);

PHP_METHOD(Yaf_View_Simple, assign);
PHP_METHOD(Yaf_View_Simple, assignRef);
PHP_METHOD(Yaf_View_Simple, setScriptPath);
PHP_METHOD(Yaf_View_Simple, getScriptPath);
PHP_METHOD(Yaf_View_Simple, clear);
PHP_METHOD(Yaf_View_Simple, __construct);
PHP_METHOD(Yaf_View_Simple, display);
PHP_METHOD(Yaf_View_Simple, evaluate);
PHP_METHOD(Yaf_View_Simple, __call);
PHP_METHOD(Yaf_View_Simple, get);
PHP_METHOD(Yaf_View_Simple, __get);
PHP_METHOD(Yaf_View_Simple, __isset);
PHP_METHOD(Yaf_View_Simple, __set);
PHP_METHOD(Yaf_View_Simple, __unset);
PHP_METHOD(Yaf_View_Simple, render);
PHP_METHOD(Yaf_View_Simple, _script);
PHP_METHOD(Yaf_View_Simple, _run);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_assign, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_assignref, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_setscriptpath, 0, 0, 1)
	ZEND_ARG_INFO(0, templateDir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_clear, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, templateDir)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_display, 0, 0, 1)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_INFO(0, tplVars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_evaluate, 0, 0, 1)
	ZEND_ARG_INFO(0, tpl_content)
	ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___call, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, arguments)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_get, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple_render, 0, 0, 1)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_INFO(0, tplVars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple__script, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_simple__run, 0, 0, 2)
	ZEND_ARG_INFO(0, template)
	ZEND_ARG_INFO(0, vars)
	ZEND_ARG_INFO(0, useEval)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_view_simple_method_entry) {
	PHP_ME(Yaf_View_Simple, assign, arginfo_yaf_view_simple_assign, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, assignRef, arginfo_yaf_view_simple_assignref, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, setScriptPath, arginfo_yaf_view_simple_setscriptpath, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, getScriptPath, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, clear, arginfo_yaf_view_simple_clear, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __construct, arginfo_yaf_view_simple___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_View_Simple, display, arginfo_yaf_view_simple_display, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, evaluate, arginfo_yaf_view_simple_evaluate, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __call, arginfo_yaf_view_simple___call, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, get, arginfo_yaf_view_simple_get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __get, arginfo_yaf_view_simple___get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __isset, arginfo_yaf_view_simple___isset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __set, arginfo_yaf_view_simple___set, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, __unset, arginfo_yaf_view_simple___unset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, render, arginfo_yaf_view_simple_render, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_View_Simple, _script, arginfo_yaf_view_simple__script, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_View_Simple, _run, arginfo_yaf_view_simple__run, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
