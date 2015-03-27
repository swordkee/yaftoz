
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"

ZEPHIR_INIT_CLASS(Yaf_Config_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Config_Abstract, yaf, config_abstract, yaf_config_abstract_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * holds the config array
	 * @var array
	 */
	zend_declare_property_null(yaf_config_abstract_ce, SL("_config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Whether the config is  readonly and cannot be changed/modified
	 * true means canmot be changed
	 * false means can be changed
	 * @var boolean
	 */
	zend_declare_property_bool(yaf_config_abstract_ce, SL("_readonly"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Config_Abstract, get) {

}

PHP_METHOD(Yaf_Config_Abstract, set) {

}

PHP_METHOD(Yaf_Config_Abstract, readonly) {


	RETURN_MEMBER(this_ptr, "_readonly");

}

PHP_METHOD(Yaf_Config_Abstract, toArray) {

}

PHP_METHOD(Yaf_Config_Abstract, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_config"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

