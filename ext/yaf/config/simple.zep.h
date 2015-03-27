
extern zend_class_entry *yaf_config_simple_ce;

ZEPHIR_INIT_CLASS(Yaf_Config_Simple);

PHP_METHOD(Yaf_Config_Simple, __construct);
PHP_METHOD(Yaf_Config_Simple, count);
PHP_METHOD(Yaf_Config_Simple, current);
PHP_METHOD(Yaf_Config_Simple, __get);
PHP_METHOD(Yaf_Config_Simple, __isset);
PHP_METHOD(Yaf_Config_Simple, offsetExists);
PHP_METHOD(Yaf_Config_Simple, offsetGet);
PHP_METHOD(Yaf_Config_Simple, offsetSet);
PHP_METHOD(Yaf_Config_Simple, offsetUnset);
PHP_METHOD(Yaf_Config_Simple, key);
PHP_METHOD(Yaf_Config_Simple, next);
PHP_METHOD(Yaf_Config_Simple, rewind);
PHP_METHOD(Yaf_Config_Simple, __set);
PHP_METHOD(Yaf_Config_Simple, toArray);
PHP_METHOD(Yaf_Config_Simple, valid);
PHP_METHOD(Yaf_Config_Simple, __unset);
PHP_METHOD(Yaf_Config_Simple, get);
PHP_METHOD(Yaf_Config_Simple, set);
PHP_METHOD(Yaf_Config_Simple, _arrayMergeRecursive);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
	ZEND_ARG_INFO(0, readonly)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple_set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_simple__arraymergerecursive, 0, 0, 2)
	ZEND_ARG_INFO(0, firstArray)
	ZEND_ARG_INFO(0, secondArray)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_config_simple_method_entry) {
	PHP_ME(Yaf_Config_Simple, __construct, arginfo_yaf_config_simple___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Config_Simple, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, __get, arginfo_yaf_config_simple___get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, __isset, arginfo_yaf_config_simple___isset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, offsetExists, arginfo_yaf_config_simple_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, offsetGet, arginfo_yaf_config_simple_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, offsetSet, arginfo_yaf_config_simple_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, offsetUnset, arginfo_yaf_config_simple_offsetunset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, __set, arginfo_yaf_config_simple___set, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, __unset, arginfo_yaf_config_simple___unset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, get, arginfo_yaf_config_simple_get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, set, arginfo_yaf_config_simple_set, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Simple, _arrayMergeRecursive, arginfo_yaf_config_simple__arraymergerecursive, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
