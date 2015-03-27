
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
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/string.h"


/**
 * Yaf_Request_Simple
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Request_Simple) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Request, Simple, yaf, request_simple, yaf_request_abstract_ce, yaf_request_simple_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Yaf_Request_Simple, __construct) {

	zend_bool _2, _6;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_8 = NULL;
	zval *method = NULL, *module = NULL, *controller = NULL, *action = NULL, *params = NULL, *sapiType = NULL, *_SERVER, *_1 = NULL, _3, _4, *_5, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 5, &method, &module, &controller, &action, &params);

	if (!method) {
		ZEPHIR_CPY_WRT(method, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(method);
	}
	if (!module) {
		module = ZEPHIR_GLOBAL(global_null);
	}
	if (!controller) {
		controller = ZEPHIR_GLOBAL(global_null);
	}
	if (!action) {
		action = ZEPHIR_GLOBAL(global_null);
	}
	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	}


	if (!(Z_TYPE_P(params) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expects the params is an array", "yaf/Request/simple.zep", 18);
		return;
	}
	if (Z_TYPE_P(method) == IS_NULL) {
		ZEPHIR_OBS_NVAR(method);
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		if (zephir_array_isset_string_fetch(&method, _SERVER, SS("REQUEST_METHOD"), 0 TSRMLS_CC)) {
			zephir_update_property_this(this_ptr, SL("method"), method TSRMLS_CC);
		} else {
			ZEPHIR_CALL_FUNCTION(&sapiType, "php_sapi_name", &_0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_1);
			zephir_fast_strtolower(_1, sapiType);
			_2 = ZEPHIR_IS_STRING(_1, "cli");
			if (!(_2)) {
				ZEPHIR_SINIT_VAR(_3);
				ZVAL_LONG(&_3, 0);
				ZEPHIR_SINIT_VAR(_4);
				ZVAL_LONG(&_4, 3);
				ZEPHIR_INIT_VAR(_5);
				zephir_substr(_5, sapiType, 0 , 3 , 0);
				_2 = ZEPHIR_IS_STRING(_5, "cgi");
			}
			ZEPHIR_INIT_NVAR(method);
			if (_2) {
				ZVAL_STRING(method, "CLI", 1);
			} else {
				ZVAL_STRING(method, "unknown", 1);
			}
		}
	}
	_2 = Z_TYPE_P(module) != IS_NULL;
	if (!(_2)) {
		_2 = Z_TYPE_P(action) != IS_NULL;
	}
	_6 = _2;
	if (!(_6)) {
		_6 = Z_TYPE_P(controller) != IS_NULL;
	}
	if (_6) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setactionname", NULL, action);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontrollername", NULL, controller);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setmodulename", NULL, module);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_BOOL(_1, 1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrouted", NULL, _1);
		zephir_check_call_status();
	} else {
		if (Z_TYPE_P(module) == IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "default_module", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "get", &_8, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setmodulename", NULL, _7);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(controller) == IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "default_controller", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "get", &_8, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontrollername", NULL, _7);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(action) == IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "default_action", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "get", &_8, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setactionname", NULL, _7);
			zephir_check_call_status();
		}
	}
	if (zephir_is_true(params)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setparam", NULL, params);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Request_Simple, __clone) {



}

