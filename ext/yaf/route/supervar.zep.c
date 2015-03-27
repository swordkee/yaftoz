
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
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Yaf router supervar
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Supervar) {

	ZEPHIR_REGISTER_CLASS(Yaf\\Route, Supervar, yaf, route_supervar, yaf_route_supervar_method_entry, 0);

	zend_declare_property_string(yaf_route_supervar_ce, SL("_varName"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_route_supervar_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Class constructor
 *
 */
PHP_METHOD(Yaf_Route_Supervar, __construct) {

	zend_bool _0;
	zval *varName;

	zephir_fetch_params(0, 1, 0, &varName);



	_0 = !(Z_TYPE_P(varName) == IS_STRING);
	if (!(_0)) {
		_0 = ZEPHIR_IS_STRING(varName, "");
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(yaf_exception_typeerror_ce, "Expects a string super var name", "yaf/Route/supervar.zep", 22);
		return;
	} else {
		zephir_update_property_this(this_ptr, SL("_varName"), varName TSRMLS_CC);
	}

}

/**
 * Processes a request and sets its controller and action based on a
 * supervar value.
 *
 * @param  Yaf_Request_Abstract
 * @return Yaf_Request_Abstract|boolean
 */
PHP_METHOD(Yaf_Route_Supervar, route) {

	zval *_31 = NULL, *_32 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL, *_15 = NULL, *_27 = NULL;
	zend_bool _1, _3, _10, _12, _16, _17, _18, _19, _20, _21, _22, _23, _24;
	int i, ZEPHIR_LAST_CALL_STATUS;
	zval *request, *requestUri = NULL, *module = NULL, *controller = NULL, *action = NULL, *rest = NULL, *path = NULL, *actionPrefer = NULL, *params, *numSegs, *key = NULL, *val = NULL, *_0, _2, *_4 = NULL, _5, *_6 = NULL, *_8, *_11, *_13, _14, _25, *_26, *_28, *_29 = NULL, *_30 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_varName"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&requestUri, request, "getquery", NULL, _0);
	zephir_check_call_status();
	_1 = Z_TYPE_P(requestUri) == IS_NULL;
	if (!(_1)) {
		_1 = ZEPHIR_IS_STRING(requestUri, "");
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(module);
	ZVAL_NULL(module);
	ZEPHIR_INIT_VAR(controller);
	ZVAL_NULL(controller);
	ZEPHIR_INIT_VAR(action);
	ZVAL_NULL(action);
	ZEPHIR_INIT_VAR(rest);
	ZVAL_NULL(rest);
	ZEPHIR_INIT_VAR(path);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "/", 0);
	zephir_fast_trim(path, requestUri, &_2, ZEPHIR_TRIM_BOTH TSRMLS_CC);
	_3 = !ZEPHIR_IS_STRING(path, "");
	if (_3) {
		_3 = !ZEPHIR_IS_STRING(path, "/");
	}
	if (_3) {
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_SINIT_VAR(_5);
		ZVAL_STRING(&_5, "/", 0);
		zephir_fast_explode(_4, &_5, path, LONG_MAX TSRMLS_CC);
		ZEPHIR_CPY_WRT(path, _4);
		zephir_array_fetch_long(&_8, path, 0, PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 54 TSRMLS_CC);
		ZEPHIR_CALL_CE_STATIC(&_6, yaf_application_ce, "ismodulename", &_7, _8);
		zephir_check_call_status();
		if (zephir_is_true(_6)) {
			ZEPHIR_OBS_NVAR(module);
			zephir_array_fetch_long(&module, path, 0, PH_NOISY, "yaf/Route/supervar.zep", 55 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_9, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		_10 = (zephir_fast_count_int(path TSRMLS_CC)) ? 1 : 0;
		if (_10) {
			ZEPHIR_OBS_VAR(_11);
			zephir_array_fetch_long(&_11, path, 0, PH_NOISY, "yaf/Route/supervar.zep", 59 TSRMLS_CC);
			_10 = !(ZEPHIR_IS_EMPTY(_11));
		}
		if (_10) {
			ZEPHIR_OBS_NVAR(controller);
			zephir_array_fetch_long(&controller, path, 0, PH_NOISY, "yaf/Route/supervar.zep", 60 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_9, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		_12 = (zephir_fast_count_int(path TSRMLS_CC)) ? 1 : 0;
		if (_12) {
			ZEPHIR_OBS_VAR(_13);
			zephir_array_fetch_long(&_13, path, 0, PH_NOISY, "yaf/Route/supervar.zep", 64 TSRMLS_CC);
			_12 = !(ZEPHIR_IS_EMPTY(_13));
		}
		if (_12) {
			ZEPHIR_OBS_NVAR(action);
			zephir_array_fetch_long(&action, path, 0, PH_NOISY, "yaf/Route/supervar.zep", 65 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_9, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(rest);
		ZEPHIR_SINIT_VAR(_14);
		ZVAL_STRING(&_14, "/", 0);
		zephir_fast_join(rest, &_14, path TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "yaf.action_prefer", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&actionPrefer, yaf_g_ce, "iniget", &_15, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
		_16 = Z_TYPE_P(module) == IS_NULL;
		if (_16) {
			_16 = Z_TYPE_P(controller) == IS_NULL;
		}
		_17 = _16;
		if (_17) {
			_17 = Z_TYPE_P(action) == IS_NULL;
		}
		_18 = Z_TYPE_P(module) == IS_NULL;
		if (_18) {
			_18 = Z_TYPE_P(action) == IS_NULL;
		}
		_19 = _18;
		if (_19) {
			_19 = Z_TYPE_P(rest) == IS_NULL;
		}
		_20 = Z_TYPE_P(controller) == IS_NULL;
		if (_20) {
			_20 = Z_TYPE_P(action) == IS_NULL;
		}
		_21 = _20;
		if (_21) {
			_21 = Z_TYPE_P(rest) != IS_NULL;
		}
		_22 = Z_TYPE_P(action) == IS_NULL;
		if (_22) {
			_22 = Z_TYPE_P(rest) == IS_NULL;
		}
		_23 = Z_TYPE_P(controller) == IS_NULL;
		if (_23) {
			_23 = Z_TYPE_P(action) == IS_NULL;
		}
		if (_17) {
			if (ZEPHIR_IS_TRUE(actionPrefer)) {
				ZEPHIR_CPY_WRT(action, rest);
			} else {
				ZEPHIR_CPY_WRT(controller, rest);
			}
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		} else if (_19) {
			if (ZEPHIR_IS_TRUE(actionPrefer)) {
				ZEPHIR_CPY_WRT(action, controller);
				ZEPHIR_INIT_NVAR(controller);
				ZVAL_NULL(controller);
			}
		} else if (_21) {
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_CPY_WRT(action, rest);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_NULL(module);
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		} else if (_22) {
			ZEPHIR_CPY_WRT(action, controller);
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_NULL(module);
		} else if (_23) {
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_CPY_WRT(action, rest);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_NULL(module);
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		} else if (Z_TYPE_P(action) == IS_NULL) {
			ZEPHIR_CPY_WRT(action, rest);
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		}
		if (Z_TYPE_P(module) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, module);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(controller) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, controller);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(action) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, action);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(params);
		array_init(params);
		_24 = Z_TYPE_P(rest) != IS_NULL;
		if (_24) {
			ZEPHIR_INIT_NVAR(_4);
			zephir_fast_trim(_4, rest, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			_24 = !ZEPHIR_IS_STRING(_4, "");
		}
		if (_24) {
			ZEPHIR_INIT_NVAR(path);
			ZEPHIR_SINIT_VAR(_25);
			ZVAL_STRING(&_25, "/", 0);
			zephir_fast_explode(path, &_25, rest, LONG_MAX TSRMLS_CC);
			ZEPHIR_INIT_VAR(numSegs);
			ZVAL_LONG(numSegs, zephir_fast_count_int(path TSRMLS_CC));
			if (!ZEPHIR_IS_LONG(numSegs, 0)) {
				i = 0;
				while (1) {
					if (!(ZEPHIR_GT_LONG(numSegs, i))) {
						break;
					}
					zephir_array_fetch_long(&_26, path, i, PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 124 TSRMLS_CC);
					ZEPHIR_CALL_FUNCTION(&key, "urldecode", &_27, _26);
					zephir_check_call_status();
					if (zephir_array_isset_long(path, (i + 1))) {
						zephir_array_fetch_long(&_28, path, (i + 1), PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 125 TSRMLS_CC);
						ZEPHIR_CALL_FUNCTION(&val, "urldecode", &_27, _28);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(val);
						ZVAL_NULL(val);
					}
					ZEPHIR_INIT_LNVAR(_29);
					if (zephir_array_isset(params, key)) {
						ZEPHIR_INIT_NVAR(_29);
						ZEPHIR_OBS_NVAR(_30);
						zephir_array_fetch(&_30, params, key, PH_NOISY, "yaf/Route/supervar.zep", 126 TSRMLS_CC);
						zephir_get_arrval(_31, _30);
						ZEPHIR_INIT_NVAR(_32);
						array_init_size(_32, 2);
						zephir_array_fast_append(_32, val);
						zephir_fast_array_merge(_29, &(_31), &(_32) TSRMLS_CC);
					} else {
						ZEPHIR_CPY_WRT(_29, val);
					}
					zephir_array_update_zval(&params, key, &_29, PH_COPY | PH_SEPARATE);
					i = (i + 2);
				}
			}
			ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, params);
			zephir_check_call_status();
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * used to create routes on the fly from config
 *
 * @param array $config
 */
PHP_METHOD(Yaf_Route_Supervar, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *config_param = NULL, *_0, *_2, *_3;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	zephir_array_fetch_string(&_0, config, SL("varname"), PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 145 TSRMLS_CC);
	_1 = !(Z_TYPE_P(_0) == IS_STRING);
	if (!(_1)) {
		zephir_array_fetch_string(&_2, config, SL("varname"), PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 145 TSRMLS_CC);
		_1 = ZEPHIR_IS_STRING(_2, "");
	}
	if (_1) {
		RETURN_MM_NULL();
	}
	object_init_ex(return_value, yaf_route_supervar_ce);
	zephir_array_fetch_string(&_3, config, SL("varname"), PH_NOISY | PH_READONLY, "yaf/Route/supervar.zep", 150 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _3);
	zephir_check_call_status();
	RETURN_MM();

}

