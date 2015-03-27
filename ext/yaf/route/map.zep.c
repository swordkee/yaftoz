
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Yaf Route Map for hash based ajax URL
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Map) {

	ZEPHIR_REGISTER_CLASS(Yaf\\Route, Map, yaf, route_map, yaf_route_map_method_entry, 0);

	zend_declare_property_bool(yaf_route_map_ce, SL("_ctlPrefer"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_route_map_ce, SL("_delimiter"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_route_map_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Class constructor
 * @param string $module
 * @param string $controller
 * @param string $action
 */
PHP_METHOD(Yaf_Route_Map, __construct) {

	zend_bool _0;
	zval *controller_prefer = NULL, *delimiter = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &controller_prefer, &delimiter);

	if (!controller_prefer) {
		controller_prefer = ZEPHIR_GLOBAL(global_false);
	}
	if (!delimiter) {
		ZEPHIR_INIT_VAR(delimiter);
		ZVAL_STRING(delimiter, "#!", 1);
	}


	if (Z_TYPE_P(controller_prefer) == IS_BOOL) {
		zephir_update_property_this(this_ptr, SL("_ctlPrefer"), controller_prefer TSRMLS_CC);
	}
	_0 = Z_TYPE_P(delimiter) == IS_STRING;
	if (_0) {
		_0 = !ZEPHIR_IS_STRING(delimiter, "");
	}
	if (_0) {
		zephir_update_property_this(this_ptr, SL("_delimiter"), delimiter TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Processes a request and sets its controller and action.  If
 * no route was possible, default route is set.
 *
 * @param  Yaf_Request_Abstract
 * @return Yaf_Request_Abstract|boolean
 */
PHP_METHOD(Yaf_Route_Map, route) {

	zval *_23 = NULL, *_24 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_6 = NULL;
	zend_bool _0, _1, _8, _16, _17;
	int i, ZEPHIR_LAST_CALL_STATUS;
	zval *request, *requestUri = NULL, *baseuri = NULL, *path = NULL, *rest = NULL, *queryStringPos, *route = NULL, *params, *numSegs, *key = NULL, *val = NULL, *_2 = NULL, _4 = zval_used_for_init, *_5 = NULL, *_7, *_9, *_10, *_11, _12 = zval_used_for_init, _13 = zval_used_for_init, _14, *_15 = NULL, *_18, *_19, *_20, *_21 = NULL, *_22 = NULL;

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
	ZEPHIR_INIT_NVAR(path);
	ZEPHIR_CALL_FUNCTION(&_5, "urldecode", &_6, path);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_4);
	ZVAL_STRING(&_4, "/", 0);
	zephir_fast_trim(path, _5, &_4, ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_INIT_VAR(rest);
	ZVAL_STRING(rest, "", 1);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_delimiter"), PH_NOISY_CC);
	_8 = Z_TYPE_P(_7) == IS_STRING;
	if (_8) {
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("_delimiter"), PH_NOISY_CC);
		_8 = !ZEPHIR_IS_STRING(_9, "");
	}
	if (_8) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_delimiter"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(queryStringPos);
		zephir_fast_strpos(queryStringPos, path, _10, 0 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(queryStringPos)) {
			_11 = zephir_fetch_nproperty_this(this_ptr, SL("_delimiter"), PH_NOISY_CC);
			ZEPHIR_SINIT_VAR(_12);
			ZVAL_LONG(&_12, (zephir_get_numberval(queryStringPos) + zephir_fast_strlen_ev(_11)));
			ZEPHIR_SINIT_VAR(_13);
			ZVAL_LONG(&_13, (zephir_fast_strlen_ev(path) - 1));
			ZEPHIR_INIT_NVAR(rest);
			zephir_substr(rest, path, zephir_get_intval(&_12), zephir_get_intval(&_13), 0);
			ZEPHIR_SINIT_VAR(_14);
			ZVAL_LONG(&_14, 0);
			ZEPHIR_INIT_VAR(_15);
			zephir_substr(_15, path, 0 , zephir_get_intval(queryStringPos), 0);
			ZEPHIR_CPY_WRT(path, _15);
		}
	}
	ZEPHIR_INIT_VAR(route);
	ZVAL_STRING(route, "", 1);
	_16 = !ZEPHIR_IS_STRING(path, "");
	if (_16) {
		_16 = !ZEPHIR_IS_STRING(path, "/");
	}
	if (_16) {
		ZEPHIR_INIT_NVAR(route);
		ZEPHIR_INIT_NVAR(_15);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_STRING(&_4, "/", 0);
		zephir_fast_trim(_15, path, &_4, ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_12);
		ZVAL_STRING(&_12, "/", 0);
		ZEPHIR_SINIT_NVAR(_13);
		ZVAL_STRING(&_13, "_", 0);
		zephir_fast_str_replace(route, &_12, &_13, _15 TSRMLS_CC);
	}
	if (!ZEPHIR_IS_STRING(route, "")) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_ctlPrefer"), PH_NOISY_CC);
		if (ZEPHIR_IS_TRUE(_10)) {
			ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, route);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, route);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_VAR(params);
	array_init(params);
	_17 = Z_TYPE_P(rest) != IS_NULL;
	if (_17) {
		ZEPHIR_INIT_NVAR(_15);
		zephir_fast_trim(_15, rest, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		_17 = !ZEPHIR_IS_STRING(_15, "");
	}
	if (_17) {
		ZEPHIR_INIT_NVAR(path);
		ZEPHIR_INIT_VAR(_18);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_STRING(&_4, "/", 0);
		zephir_fast_trim(_18, rest, &_4, ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_12);
		ZVAL_STRING(&_12, "/", 0);
		zephir_fast_explode(path, &_12, _18, LONG_MAX TSRMLS_CC);
		ZEPHIR_INIT_VAR(numSegs);
		ZVAL_LONG(numSegs, zephir_fast_count_int(path TSRMLS_CC));
		if (!ZEPHIR_IS_LONG(numSegs, 0)) {
			i = 0;
			while (1) {
				if (!(ZEPHIR_GT_LONG(numSegs, i))) {
					break;
				}
				zephir_array_fetch_long(&_19, path, i, PH_NOISY | PH_READONLY, "yaf/Route/map.zep", 84 TSRMLS_CC);
				ZEPHIR_CALL_FUNCTION(&key, "urldecode", &_6, _19);
				zephir_check_call_status();
				if (zephir_array_isset_long(path, (i + 1))) {
					zephir_array_fetch_long(&_20, path, (i + 1), PH_NOISY | PH_READONLY, "yaf/Route/map.zep", 85 TSRMLS_CC);
					ZEPHIR_CALL_FUNCTION(&val, "urldecode", &_6, _20);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(val);
					ZVAL_NULL(val);
				}
				ZEPHIR_INIT_LNVAR(_21);
				if (zephir_array_isset(params, key)) {
					ZEPHIR_INIT_NVAR(_21);
					ZEPHIR_OBS_NVAR(_22);
					zephir_array_fetch(&_22, params, key, PH_NOISY, "yaf/Route/map.zep", 86 TSRMLS_CC);
					zephir_get_arrval(_23, _22);
					ZEPHIR_INIT_NVAR(_24);
					array_init_size(_24, 2);
					zephir_array_fast_append(_24, val);
					zephir_fast_array_merge(_21, &(_23), &(_24) TSRMLS_CC);
				} else {
					ZEPHIR_CPY_WRT(_21, val);
				}
				zephir_array_update_zval(&params, key, &_21, PH_COPY | PH_SEPARATE);
				i = (i + 2);
			}
		}
		ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, params);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);

}

/**
 * used to create routes on the fly from config
 *
 * @param array $config
 */
PHP_METHOD(Yaf_Route_Map, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *config_param = NULL, *controllerPrefer = NULL, *delimiter = NULL, *_1;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	ZEPHIR_INIT_VAR(controllerPrefer);
	ZVAL_BOOL(controllerPrefer, 0);
	_0 = zephir_array_isset_string(config, SS("controllerPrefer"));
	if (_0) {
		zephir_array_fetch_string(&_1, config, SL("controllerPrefer"), PH_NOISY | PH_READONLY, "yaf/Route/map.zep", 107 TSRMLS_CC);
		_0 = Z_TYPE_P(_1) == IS_BOOL;
	}
	if (_0) {
		ZEPHIR_OBS_NVAR(controllerPrefer);
		zephir_array_fetch_string(&controllerPrefer, config, SL("controllerPrefer"), PH_NOISY, "yaf/Route/map.zep", 108 TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(delimiter);
	ZVAL_STRING(delimiter, "#!", 1);
	if (zephir_array_isset_string(config, SS("delimiter"))) {
		ZEPHIR_OBS_NVAR(delimiter);
		zephir_array_fetch_string(&delimiter, config, SL("delimiter"), PH_NOISY, "yaf/Route/map.zep", 113 TSRMLS_CC);
	}
	object_init_ex(return_value, yaf_route_map_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, controllerPrefer, delimiter);
	zephir_check_call_status();
	RETURN_MM();

}

