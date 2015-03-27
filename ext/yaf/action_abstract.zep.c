
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


/**
 * @todo check an example to see how does it work
 * Yaf Action Abstract
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Action_Abstract) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf, Action_Abstract, yaf, action_abstract, yaf_controller_abstract_ce, yaf_action_abstract_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(yaf_action_abstract_ce, SL("_controller"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Action_Abstract, execute) {



}

PHP_METHOD(Yaf_Action_Abstract, setController) {

	zval *controller;

	zephir_fetch_params(0, 1, 0, &controller);



	zephir_update_property_this(this_ptr, SL("_controller"), controller TSRMLS_CC);

}

PHP_METHOD(Yaf_Action_Abstract, getController) {


	RETURN_MEMBER(this_ptr, "_controller");

}

