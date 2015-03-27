
extern zend_class_entry *yaf_response_cli_ce;

ZEPHIR_INIT_CLASS(Yaf_Response_Cli);

PHP_METHOD(Yaf_Response_Cli, __toString);

ZEPHIR_INIT_FUNCS(yaf_response_cli_method_entry) {
	PHP_ME(Yaf_Response_Cli, __toString, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
