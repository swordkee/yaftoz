
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


/**
 * Yaf Exception LoadFailed
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Exception_LoadFailed_LoadFailed) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Exception\\LoadFailed, LoadFailed, yaf, exception_loadfailed_loadfailed, yaf_exception_ce, NULL, 0);

	return SUCCESS;

}

