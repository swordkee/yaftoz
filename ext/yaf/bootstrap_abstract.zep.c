
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


/**
 * Bootstrap is a mechanism used to do some intial config
 * before a Application run.
 * User may define their own Bootstrap class by inheriting
 * Yaf_Bootstrap_Abstract
 * Any method declared in Bootstrap class with leading "_init",
 * will be called by Yaf_Application::bootstrap()
 * one by one according to their defined order.
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Bootstrap_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Bootstrap_Abstract, yaf, bootstrap_abstract, NULL, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_class_constant_string(yaf_bootstrap_abstract_ce, SL("YAF_DEFAULT_BOOTSTRAP"), "Bootstrap" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_bootstrap_abstract_ce, SL("YAF_BOOTSTRAP_INITFUNC_PREFIX"), "_init" TSRMLS_CC);

	return SUCCESS;

}

