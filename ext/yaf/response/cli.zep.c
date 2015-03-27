
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"


/**
 * Yaf_Response_Cli
 *
 * CLI response for controllers
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Response_Cli) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Response, Cli, yaf, response_cli, yaf_response_abstract_ce, yaf_response_cli_method_entry, 0);

	return SUCCESS;

}

/**
 * Magic __toString functionality
 *
 * @return string
 */
PHP_METHOD(Yaf_Response_Cli, __toString) {


	RETURN_MEMBER(this_ptr, "_body");

}

