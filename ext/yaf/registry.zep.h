
extern zend_class_entry *yaf_registry_ce;

ZEPHIR_INIT_CLASS(Yaf_Registry);

PHP_METHOD(Yaf_Registry, set);
PHP_METHOD(Yaf_Registry, get);
PHP_METHOD(Yaf_Registry, has);
PHP_METHOD(Yaf_Registry, del);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_registry_set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_registry_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_registry_has, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_registry_del, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_registry_method_entry) {
	PHP_ME(Yaf_Registry, set, arginfo_yaf_registry_set, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Registry, get, arginfo_yaf_registry_get, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Registry, has, arginfo_yaf_registry_has, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Registry, del, arginfo_yaf_registry_del, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
