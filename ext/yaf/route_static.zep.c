
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * StaticRoute is used for managing static URIs.
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Static) {

	ZEPHIR_REGISTER_CLASS(Yaf, Route_Static, yaf, route_static, yaf_route_static_method_entry, 0);

	zend_class_implements(yaf_route_static_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Class constructor
 *
 */
PHP_METHOD(Yaf_Route_Static, __construct) {



}

/**
 * @todo this method is not used anywhere
 *
 * @param string $uri
 * @return bool
 */
PHP_METHOD(Yaf_Route_Static, match) {

	zval *uri_param = NULL;
	zval *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &uri_param);

	zephir_get_strval(uri, uri_param);


	RETURN_MM_BOOL(1);

}

/**
 * Processes a request and sets its controller and action.  If
 * no route was possible, default route is set.
 *
 * @param  Yaf_Request_Abstract
 * @return Yaf_Request_Abstract|boolean
 */
PHP_METHOD(Yaf_Route_Static, route) {

	zval *_33 = NULL, *_34 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_9 = NULL, *_10 = NULL, *_12 = NULL, *_17 = NULL, *_29 = NULL;
	zend_bool _0, _1, _13, _15, _18, _19, _20, _21, _22, _23, _24, _25, _26;
	int i, ZEPHIR_LAST_CALL_STATUS;
	zval *request, *requestUri = NULL, *baseuri = NULL, *path = NULL, *module = NULL, *controller = NULL, *action = NULL, *rest = NULL, *actionPrefer = NULL, *params, *numSegs, *key = NULL, *val = NULL, *_2 = NULL, _4 = zval_used_for_init, *_5 = NULL, _6, _7 = zval_used_for_init, *_8 = NULL, *_11, *_14, *_16, _27, *_28, *_30, *_31 = NULL, *_32 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_CALL_METHOD(&requestUri, request, "getrequesturi", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&baseuri, request, "getbaseuri", NULL);
	zephir_check_call_status();
	_0 = !ZEPHIR_IS_STRING(requestUri, "");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING(baseuri, "");
	}
	_1 = _0;
	if (_1) {
		ZEPHIR_CALL_FUNCTION(&_2, "stripos", &_3, requestUri, baseuri);
		zephir_check_call_status();
		_1 = ZEPHIR_IS_LONG_IDENTICAL(_2, 0);
	}
	if (_1) {
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_LONG(&_4, zephir_fast_strlen_ev(baseuri));
		ZEPHIR_INIT_VAR(path);
		zephir_substr(path, requestUri, zephir_get_intval(&_4), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	} else {
		ZEPHIR_CPY_WRT(path, requestUri);
	}
	ZEPHIR_INIT_VAR(module);
	ZVAL_NULL(module);
	ZEPHIR_INIT_VAR(controller);
	ZVAL_NULL(controller);
	ZEPHIR_INIT_VAR(action);
	ZVAL_NULL(action);
	ZEPHIR_INIT_VAR(rest);
	ZVAL_NULL(rest);
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_SINIT_NVAR(_4);
	ZVAL_STRING(&_4, "/", 0);
	zephir_fast_trim(_5, path, &_4, ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_CPY_WRT(path, _5);
	if (!ZEPHIR_IS_STRING(path, "")) {
		ZEPHIR_INIT_NVAR(_5);
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "/", 0);
		zephir_fast_explode(_5, &_6, path, LONG_MAX TSRMLS_CC);
		ZEPHIR_CPY_WRT(path, _5);
		ZEPHIR_SINIT_VAR(_7);
		ZVAL_STRING(&_7, "strlen", 0);
		ZEPHIR_CALL_FUNCTION(&_8, "array_filter", &_9, path, &_7);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(path, _8);
		zephir_array_fetch_long(&_11, path, 0, PH_NOISY | PH_READONLY, "yaf/route_static.zep", 60 TSRMLS_CC);
		ZEPHIR_CALL_CE_STATIC(&_8, yaf_application_ce, "ismodulename", &_10, _11);
		zephir_check_call_status();
		if (zephir_is_true(_8)) {
			ZEPHIR_OBS_NVAR(module);
			zephir_array_fetch_long(&module, path, 0, PH_NOISY, "yaf/route_static.zep", 61 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_12, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		_13 = (zephir_fast_count_int(path TSRMLS_CC)) ? 1 : 0;
		if (_13) {
			ZEPHIR_OBS_VAR(_14);
			zephir_array_fetch_long(&_14, path, 0, PH_NOISY, "yaf/route_static.zep", 65 TSRMLS_CC);
			_13 = !(ZEPHIR_IS_EMPTY(_14));
		}
		if (_13) {
			ZEPHIR_OBS_NVAR(controller);
			zephir_array_fetch_long(&controller, path, 0, PH_NOISY, "yaf/route_static.zep", 66 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_12, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		_15 = (zephir_fast_count_int(path TSRMLS_CC)) ? 1 : 0;
		if (_15) {
			ZEPHIR_OBS_VAR(_16);
			zephir_array_fetch_long(&_16, path, 0, PH_NOISY, "yaf/route_static.zep", 70 TSRMLS_CC);
			_15 = !(ZEPHIR_IS_EMPTY(_16));
		}
		if (_15) {
			ZEPHIR_OBS_NVAR(action);
			zephir_array_fetch_long(&action, path, 0, PH_NOISY, "yaf/route_static.zep", 71 TSRMLS_CC);
			Z_SET_ISREF_P(path);
			ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_12, path);
			Z_UNSET_ISREF_P(path);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(rest);
		ZEPHIR_SINIT_NVAR(_7);
		ZVAL_STRING(&_7, "/", 0);
		zephir_fast_join(rest, &_7, path TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, "yaf.action_prefer", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&actionPrefer, yaf_g_ce, "iniget", &_17, _5);
		zephir_check_temp_parameter(_5);
		zephir_check_call_status();
		_18 = Z_TYPE_P(module) == IS_NULL;
		if (_18) {
			_18 = Z_TYPE_P(controller) == IS_NULL;
		}
		_19 = _18;
		if (_19) {
			_19 = Z_TYPE_P(action) == IS_NULL;
		}
		_20 = Z_TYPE_P(module) == IS_NULL;
		if (_20) {
			_20 = Z_TYPE_P(action) == IS_NULL;
		}
		_21 = _20;
		if (_21) {
			_21 = Z_TYPE_P(rest) == IS_NULL;
		}
		_22 = Z_TYPE_P(controller) == IS_NULL;
		if (_22) {
			_22 = Z_TYPE_P(action) == IS_NULL;
		}
		_23 = _22;
		if (_23) {
			_23 = Z_TYPE_P(rest) != IS_NULL;
		}
		_24 = Z_TYPE_P(action) == IS_NULL;
		if (_24) {
			_24 = Z_TYPE_P(rest) == IS_NULL;
		}
		_25 = Z_TYPE_P(controller) == IS_NULL;
		if (_25) {
			_25 = Z_TYPE_P(action) == IS_NULL;
		}
		if (_19) {
			if (ZEPHIR_IS_TRUE(actionPrefer)) {
				ZEPHIR_CPY_WRT(action, rest);
			} else {
				ZEPHIR_CPY_WRT(controller, rest);
			}
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		} else if (_21) {
			if (ZEPHIR_IS_TRUE(actionPrefer)) {
				ZEPHIR_CPY_WRT(action, controller);
				ZEPHIR_INIT_NVAR(controller);
				ZVAL_NULL(controller);
			}
		} else if (_23) {
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_CPY_WRT(action, rest);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_NULL(module);
			ZEPHIR_INIT_NVAR(rest);
			ZVAL_NULL(rest);
		} else if (_24) {
			ZEPHIR_CPY_WRT(action, controller);
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_NULL(module);
		} else if (_25) {
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
		_26 = Z_TYPE_P(rest) != IS_NULL;
		if (_26) {
			ZEPHIR_INIT_NVAR(_5);
			zephir_fast_trim(_5, rest, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			_26 = !ZEPHIR_IS_STRING(_5, "");
		}
		if (_26) {
			ZEPHIR_INIT_NVAR(path);
			ZEPHIR_SINIT_VAR(_27);
			ZVAL_STRING(&_27, "/", 0);
			zephir_fast_explode(path, &_27, rest, LONG_MAX TSRMLS_CC);
			ZEPHIR_INIT_VAR(numSegs);
			ZVAL_LONG(numSegs, zephir_fast_count_int(path TSRMLS_CC));
			if (!ZEPHIR_IS_LONG(numSegs, 0)) {
				i = 0;
				while (1) {
					if (!(ZEPHIR_GT_LONG(numSegs, i))) {
						break;
					}
					zephir_array_fetch_long(&_28, path, i, PH_NOISY | PH_READONLY, "yaf/route_static.zep", 128 TSRMLS_CC);
					ZEPHIR_CALL_FUNCTION(&key, "urldecode", &_29, _28);
					zephir_check_call_status();
					if (zephir_array_isset_long(path, (i + 1))) {
						zephir_array_fetch_long(&_30, path, (i + 1), PH_NOISY | PH_READONLY, "yaf/route_static.zep", 129 TSRMLS_CC);
						ZEPHIR_CALL_FUNCTION(&val, "urldecode", &_29, _30);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(val);
						ZVAL_NULL(val);
					}
					ZEPHIR_INIT_LNVAR(_31);
					if (zephir_array_isset(params, key)) {
						ZEPHIR_INIT_NVAR(_31);
						ZEPHIR_OBS_NVAR(_32);
						zephir_array_fetch(&_32, params, key, PH_NOISY, "yaf/route_static.zep", 130 TSRMLS_CC);
						zephir_get_arrval(_33, _32);
						ZEPHIR_INIT_NVAR(_34);
						array_init_size(_34, 2);
						zephir_array_fast_append(_34, val);
						zephir_fast_array_merge(_31, &(_33), &(_34) TSRMLS_CC);
					} else {
						ZEPHIR_CPY_WRT(_31, val);
					}
					zephir_array_update_zval(&params, key, &_31, PH_COPY | PH_SEPARATE);
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
PHP_METHOD(Yaf_Route_Static, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *config_param = NULL;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	object_init_ex(return_value, yaf_route_static_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL);
	zephir_check_call_status();
	RETURN_MM();

}

