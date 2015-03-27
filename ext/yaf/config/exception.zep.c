
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


/**
 * Yaf Config Exception
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Config_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Config, Exception, yaf, config_exception, yaf_exception_ce, NULL, 0);

	return SUCCESS;

}

