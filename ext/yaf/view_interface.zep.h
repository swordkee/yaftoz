
extern zend_class_entry *yaf_view_interface_ce;

ZEPHIR_INIT_CLASS(Yaf_View_Interface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_interface_setscriptpath, 0, 0, 1)
	ZEND_ARG_INFO(0, templateDir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_interface_assign, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_interface_render, 0, 0, 1)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_ARRAY_INFO(0, tplVars, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_view_interface_display, 0, 0, 1)
	ZEND_ARG_INFO(0, tpl)
	ZEND_ARG_ARRAY_INFO(0, tplVars, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_view_interface_method_entry) {
	PHP_ABSTRACT_ME(Yaf_View_Interface, setScriptPath, arginfo_yaf_view_interface_setscriptpath)
	PHP_ABSTRACT_ME(Yaf_View_Interface, getScriptPath, NULL)
	PHP_ABSTRACT_ME(Yaf_View_Interface, assign, arginfo_yaf_view_interface_assign)
	PHP_ABSTRACT_ME(Yaf_View_Interface, render, arginfo_yaf_view_interface_render)
	PHP_ABSTRACT_ME(Yaf_View_Interface, display, arginfo_yaf_view_interface_display)
  PHP_FE_END
};
