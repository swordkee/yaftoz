
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
 * Yaf Router Exception
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Route, Exception, yaf, route_exception, yaf_exception_ce, NULL, 0);

	return SUCCESS;

}

