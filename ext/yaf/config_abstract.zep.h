
extern zend_class_entry *yaf_config_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Config_Abstract);

PHP_METHOD(Yaf_Config_Abstract, get);
PHP_METHOD(Yaf_Config_Abstract, set);
PHP_METHOD(Yaf_Config_Abstract, readonly);
PHP_METHOD(Yaf_Config_Abstract, toArray);
PHP_METHOD(Yaf_Config_Abstract, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_abstract_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_abstract_set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_config_abstract_method_entry) {
	PHP_ME(Yaf_Config_Abstract, get, arginfo_yaf_config_abstract_get, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	PHP_ME(Yaf_Config_Abstract, set, arginfo_yaf_config_abstract_set, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	PHP_ME(Yaf_Config_Abstract, readonly, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Abstract, toArray, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	PHP_ME(Yaf_Config_Abstract, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
  PHP_FE_END
};
