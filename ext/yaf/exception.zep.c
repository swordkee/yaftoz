
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


/**
 * Yaf Exception
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf, Exception, yaf, exception, zend_exception_get_default(TSRMLS_C), yaf_exception_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Yaf_Exception, trigger_error) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_1 = NULL;
	zval *errmsg = NULL, *errtype = NULL, *app = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &errmsg, &errtype);

	if (!errmsg) {
		ZEPHIR_INIT_VAR(errmsg);
		ZVAL_STRING(errmsg, "", 1);
	}
	if (!errtype) {
		ZEPHIR_INIT_VAR(errtype);
		ZVAL_LONG(errtype, 0);
	}


	ZEPHIR_CALL_CE_STATIC(&app, yaf_application_ce, "app", &_0);
	zephir_check_call_status();
	if (Z_TYPE_P(app) != IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, app, "seterrorno", NULL, errtype);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, app, "seterrormsg", NULL, errmsg);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_1, errmsg, errtype);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

