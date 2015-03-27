
extern zend_class_entry *yaf_action_abstract_ce;

ZEPHIR_INIT_CLASS(Yaf_Action_Abstract);

PHP_METHOD(Yaf_Action_Abstract, execute);
PHP_METHOD(Yaf_Action_Abstract, setController);
PHP_METHOD(Yaf_Action_Abstract, getController);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_action_abstract_setcontroller, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, controller, Yaf\\Controller_Abstract, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_action_abstract_method_entry) {
	PHP_ME(Yaf_Action_Abstract, execute, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Action_Abstract, setController, arginfo_yaf_action_abstract_setcontroller, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Action_Abstract, getController, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
