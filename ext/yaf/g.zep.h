
extern zend_class_entry *yaf_g_ce;

ZEPHIR_INIT_CLASS(Yaf_g);

PHP_METHOD(Yaf_g, __construct);
PHP_METHOD(Yaf_g, getGlobals);
PHP_METHOD(Yaf_g, getIni);
PHP_METHOD(Yaf_g, iniSet);
PHP_METHOD(Yaf_g, iniGet);
PHP_METHOD(Yaf_g, set);
PHP_METHOD(Yaf_g, get);
PHP_METHOD(Yaf_g, isAbsolutePath);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_g_iniset, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_g_iniget, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_g_set, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_g_get, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_g_isabsolutepath, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_g_method_entry) {
	PHP_ME(Yaf_g, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_g, getGlobals, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_g, getIni, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_g, iniSet, arginfo_yaf_g_iniset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_g, iniGet, arginfo_yaf_g_iniget, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_g, set, arginfo_yaf_g_set, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_g, get, arginfo_yaf_g_get, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_g, isAbsolutePath, arginfo_yaf_g_isabsolutepath, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
