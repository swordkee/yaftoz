
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
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/hash.h"
#include "kernel/concat.h"

ZEPHIR_INIT_CLASS(Yaf_Route_Rewrite) {

	ZEPHIR_REGISTER_CLASS(Yaf\\Route, Rewrite, yaf, route_rewrite, yaf_route_rewrite_method_entry, 0);

	zend_declare_property_string(yaf_route_rewrite_ce, SL("_route"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_rewrite_ce, SL("_default"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_rewrite_ce, SL("_verify"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_route_rewrite_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Instantiates route based on passed Yaf_Config_Abstract structure
 *
 * @param array $config Configuration object
 */
PHP_METHOD(Yaf_Route_Rewrite, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _2;
	zval *config_param = NULL, *_1, *_3, *_4, *_5;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	_0 = !(zephir_array_isset_string(config, SS("match")));
	if (!(_0)) {
		zephir_array_fetch_string(&_1, config, SL("match"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 21 TSRMLS_CC);
		_0 = !(Z_TYPE_P(_1) == IS_STRING);
	}
	_2 = !(zephir_array_isset_string(config, SS("route")));
	if (!(_2)) {
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch_string(&_3, config, SL("route"), PH_NOISY, "yaf/Route/rewrite.zep", 23 TSRMLS_CC);
		_2 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_0) {
		RETURN_MM_NULL();
	} else if (_2) {
		RETURN_MM_NULL();
	} else {
		object_init_ex(return_value, yaf_route_rewrite_ce);
		zephir_array_fetch_string(&_4, config, SL("match"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 26 TSRMLS_CC);
		zephir_array_fetch_string(&_5, config, SL("route"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 26 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _4, _5);
		zephir_check_call_status();
		RETURN_MM();
	}

}

PHP_METHOD(Yaf_Route_Rewrite, __construct) {

	zval *_3 = NULL;
	zend_bool _1, _2;
	zval *match, *route, *verify = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &match, &route, &verify);

	if (!verify) {
		verify = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_default"), _0 TSRMLS_CC);
	_1 = !(Z_TYPE_P(match) == IS_STRING);
	if (!(_1)) {
		_1 = ZEPHIR_IS_STRING(match, "");
	}
	if (_1) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expects a string as the first parameter", "yaf/Route/rewrite.zep", 34);
		return;
	}
	if (!(Z_TYPE_P(route) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expects an array as the second parameter", "yaf/Route/rewrite.zep", 38);
		return;
	}
	_2 = Z_TYPE_P(verify) != IS_NULL;
	if (_2) {
		_2 = !(Z_TYPE_P(verify) == IS_ARRAY);
	}
	if (_2) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expects an array as third parameter", "yaf/Route/rewrite.zep", 42);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_route"), match TSRMLS_CC);
	zephir_get_arrval(_3, route);
	zephir_update_property_this(this_ptr, SL("_default"), _3 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_verify"), verify TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Matches a user submitted path with a previously defined route.
 * Assigns and returns an array of defaults on a successful match.
 *
 * @param  string $path Path used to match against this routing map
 * @return array|false  An array of assigned values or a false on a mismatch
 */
PHP_METHOD(Yaf_Route_Rewrite, route) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_6 = NULL;
	zend_bool _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *requestUri = NULL, *baseuri = NULL, *path = NULL, *values = NULL, *_2 = NULL, _4 = zval_used_for_init, *_5 = NULL, *_7, *_8, *_9, *_10;

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
		_1 = !ZEPHIR_IS_FALSE_IDENTICAL(_2);
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
	ZEPHIR_CALL_METHOD(&values, this_ptr, "_match", NULL, path);
	zephir_check_call_status();
	if (Z_TYPE_P(values) == IS_NULL) {
		RETURN_MM_BOOL(0);
	}
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_7, SS("module"))) {
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_9, _8, SL("module"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 77 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, _9);
		zephir_check_call_status();
	}
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_8, SS("controller"))) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_9, _10, SL("controller"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 81 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _9);
		zephir_check_call_status();
	}
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_8, SS("action"))) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_9, _10, SL("action"), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 85 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _9);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, values);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

/**
 * @todo this method can be write differently with (P< style match
 * Matches a user submitted path with parts defined by a map. Assigns and
 * returns an array of variables on a successful match.
 *
 * @param string $path Path used to match against this routing map
 * @return array|false An array of assigned values or a false on a mismatch
 */
PHP_METHOD(Yaf_Route_Rewrite, _match) {

	zephir_nts_static zephir_fcall_cache_entry *_27 = NULL, *_33 = NULL;
	zend_bool _12, _28, _32;
	HashTable *_7, *_22, *_35;
	HashPosition _6, _21, _34;
	int staticCount, pathStaticCount, ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, *values, *matchedPath = NULL, *parts, *variables, *wildcardData, *name = NULL, *part = NULL, *pos = NULL, *pathMatch, *count = NULL, *i = NULL, *varr = NULL, *pathPart = NULL, *tmpReturn = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3, _4 = zval_used_for_init, _5 = zval_used_for_init, **_8, _9 = zval_used_for_init, _10 = zval_used_for_init, *_11 = NULL, _13 = zval_used_for_init, _14 = zval_used_for_init, *_15 = NULL, _16 = zval_used_for_init, _17 = zval_used_for_init, *_18 = NULL, _19 = zval_used_for_init, *_20 = NULL, **_23, *_24 = NULL, *_25, *_26, *_29 = NULL, *_30, *_31 = NULL, **_36;
	zval *path = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path_param);

	zephir_get_strval(path, path_param);


	staticCount = 0;
	pathStaticCount = 0;
	ZEPHIR_INIT_VAR(values);
	array_init(values);
	ZEPHIR_INIT_VAR(matchedPath);
	ZVAL_STRING(matchedPath, "", 1);
	ZEPHIR_INIT_VAR(parts);
	array_init(parts);
	ZEPHIR_INIT_VAR(variables);
	array_init(variables);
	ZEPHIR_INIT_VAR(wildcardData);
	array_init(wildcardData);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_route"), PH_NOISY_CC);
	if (!ZEPHIR_IS_STRING_IDENTICAL(_0, "")) {
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_INIT_VAR(_2);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("_route"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_STRING(&_4, "/", 0);
		zephir_fast_trim(_2, _3, &_4, ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_5);
		ZVAL_STRING(&_5, "/", 0);
		zephir_fast_explode(_1, &_5, _2, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(_1, &_7, &_6, 0, 0, "yaf/Route/rewrite.zep", 135);
		for (
		  ; zephir_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
		  ; zephir_hash_move_forward_ex(_7, &_6)
		) {
			ZEPHIR_GET_HMKEY(pos, _7, _6);
			ZEPHIR_GET_HVALUE(part, _8);
			ZEPHIR_SINIT_NVAR(_9);
			ZVAL_LONG(&_9, 0);
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_LONG(&_10, 1);
			ZEPHIR_INIT_NVAR(_11);
			zephir_substr(_11, part, 0 , 1 , 0);
			_12 = ZEPHIR_IS_STRING(_11, ":");
			if (_12) {
				ZEPHIR_SINIT_NVAR(_13);
				ZVAL_LONG(&_13, 1);
				ZEPHIR_SINIT_NVAR(_14);
				ZVAL_LONG(&_14, 1);
				ZEPHIR_INIT_NVAR(_15);
				zephir_substr(_15, part, 1 , 1 , 0);
				_12 = !ZEPHIR_IS_STRING(_15, ":");
			}
			if (_12) {
				ZEPHIR_SINIT_NVAR(_16);
				ZVAL_LONG(&_16, 1);
				ZEPHIR_INIT_NVAR(name);
				zephir_substr(name, part, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
				zephir_array_update_zval(&parts, pos, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&variables, pos, &name, PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_SINIT_NVAR(_16);
				ZVAL_LONG(&_16, 0);
				ZEPHIR_SINIT_NVAR(_17);
				ZVAL_LONG(&_17, 1);
				ZEPHIR_INIT_NVAR(_18);
				zephir_substr(_18, part, 0 , 1 , 0);
				if (ZEPHIR_IS_STRING(_18, ":")) {
					ZEPHIR_SINIT_NVAR(_19);
					ZVAL_LONG(&_19, 1);
					ZEPHIR_INIT_NVAR(_20);
					zephir_substr(_20, part, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
					ZEPHIR_CPY_WRT(part, _20);
				}
				zephir_array_update_zval(&parts, pos, &part, PH_COPY | PH_SEPARATE);
				if (!ZEPHIR_IS_STRING_IDENTICAL(part, "*")) {
					staticCount++;
				}
			}
		}
	}
	if (!ZEPHIR_IS_STRING_IDENTICAL(path, "")) {
		ZEPHIR_INIT_VAR(pathMatch);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_STRING(&_4, "/", 0);
		zephir_fast_explode(pathMatch, &_4, path, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(pathMatch, &_22, &_21, 0, 0, "yaf/Route/rewrite.zep", 193);
		for (
		  ; zephir_hash_get_current_data_ex(_22, (void**) &_23, &_21) == SUCCESS
		  ; zephir_hash_move_forward_ex(_22, &_21)
		) {
			ZEPHIR_GET_HMKEY(pos, _22, _21);
			ZEPHIR_GET_HVALUE(pathPart, _23);
			if (!(zephir_array_key_exists(parts, pos TSRMLS_CC))) {
				RETURN_MM_BOOL(0);
			}
			ZEPHIR_INIT_LNVAR(_24);
			ZEPHIR_CONCAT_VS(_24, pathPart, "/");
			zephir_concat_self(&matchedPath, _24 TSRMLS_CC);
			zephir_array_fetch(&_25, parts, pos, PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 150 TSRMLS_CC);
			if (ZEPHIR_IS_STRING(_25, "*")) {
				ZEPHIR_INIT_NVAR(count);
				ZVAL_LONG(count, zephir_fast_count_int(pathMatch TSRMLS_CC));
				ZEPHIR_CPY_WRT(i, pos);
				while (1) {
					if (!(ZEPHIR_LT(i, count))) {
						break;
					}
					zephir_array_fetch(&_26, pathMatch, i, PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 154 TSRMLS_CC);
					ZEPHIR_CALL_FUNCTION(&varr, "urldecode", &_27, _26);
					zephir_check_call_status();
					_12 = !(zephir_array_isset(wildcardData, varr));
					if (_12) {
						_3 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
						_12 = !(zephir_array_isset(_3, varr));
					}
					_28 = _12;
					if (_28) {
						_28 = !(zephir_array_isset(values, varr));
					}
					if (_28) {
						ZEPHIR_INIT_LNVAR(_29);
						if (zephir_array_isset_long(pathMatch, (zephir_get_numberval(i) + 1))) {
							zephir_array_fetch_long(&_30, pathMatch, (zephir_get_numberval(i) + 1), PH_NOISY | PH_READONLY, "yaf/Route/rewrite.zep", 157 TSRMLS_CC);
							ZEPHIR_CALL_FUNCTION(&_29, "urldecode", &_27, _30);
							zephir_check_call_status();
						} else {
							ZEPHIR_INIT_NVAR(_29);
							ZVAL_NULL(_29);
						}
						zephir_array_update_zval(&wildcardData, varr, &_29, PH_COPY | PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_1);
					ZVAL_LONG(_1, 2);
					ZEPHIR_ADD_ASSIGN(i, _1);
				}
				ZEPHIR_INIT_NVAR(matchedPath);
				ZEPHIR_SINIT_NVAR(_5);
				ZVAL_STRING(&_5, "/", 0);
				zephir_fast_join(matchedPath, &_5, pathMatch TSRMLS_CC);
				break;
			}
			if (zephir_array_isset(variables, pos)) {
				ZEPHIR_OBS_NVAR(name);
				zephir_array_fetch(&name, variables, pos, PH_NOISY, "yaf/Route/rewrite.zep", 165 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(name);
				ZVAL_NULL(name);
			}
			ZEPHIR_CALL_FUNCTION(&_31, "urldecode", &_27, pathPart);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(pathPart, _31);
			ZEPHIR_OBS_NVAR(part);
			zephir_array_fetch(&part, parts, pos, PH_NOISY, "yaf/Route/rewrite.zep", 167 TSRMLS_CC);
			ZEPHIR_SINIT_NVAR(_9);
			ZVAL_LONG(&_9, 0);
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_LONG(&_10, 2);
			ZEPHIR_INIT_NVAR(_2);
			zephir_substr(_2, part, 0 , 2 , 0);
			if (ZEPHIR_IS_STRING_IDENTICAL(_2, "@@")) {
				ZEPHIR_SINIT_NVAR(_13);
				ZVAL_LONG(&_13, 1);
				ZEPHIR_INIT_NVAR(_11);
				zephir_substr(_11, part, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
				ZEPHIR_CPY_WRT(part, _11);
			}
			_28 = Z_TYPE_P(name) == IS_NULL;
			if (_28) {
				_28 = !ZEPHIR_IS_EQUAL(part, pathPart);
			}
			if (_28) {
				RETURN_MM_BOOL(0);
			}
			_32 = Z_TYPE_P(part) != IS_NULL;
			if (_32) {
				ZEPHIR_INIT_LNVAR(_29);
				ZEPHIR_CONCAT_VSSS(_29, part, "#^", "$#", "iu");
				ZEPHIR_CALL_FUNCTION(&_31, "preg_match", &_33, _29, pathPart);
				zephir_check_call_status();
				_32 = !zephir_is_true(_31);
			}
			if (_32) {
				RETURN_MM_BOOL(0);
			}
			if (Z_TYPE_P(name) != IS_NULL) {
				zephir_array_update_zval(&values, name, &pathPart, PH_COPY | PH_SEPARATE);
			} else {
				pathStaticCount++;
			}
		}
	}
	if (staticCount != pathStaticCount) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(tmpReturn);
	zephir_add_function_ex(tmpReturn, values, wildcardData TSRMLS_CC);
	zephir_is_iterable(variables, &_35, &_34, 0, 0, "yaf/Route/rewrite.zep", 212);
	for (
	  ; zephir_hash_get_current_data_ex(_35, (void**) &_36, &_34) == SUCCESS
	  ; zephir_hash_move_forward_ex(_35, &_34)
	) {
		ZEPHIR_GET_HVALUE(varr, _36);
		if (!(zephir_array_key_exists(tmpReturn, varr TSRMLS_CC))) {
			RETURN_MM_BOOL(0);
		}
	}
	_12 = Z_TYPE_P(values) == IS_NULL;
	if (_12) {
		_12 = Z_TYPE_P(wildcardData) == IS_NULL;
	}
	_32 = _12;
	if (_32) {
		_32 = staticCount != 0;
	}
	if (_32) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_24);
		zephir_add_function_ex(_24, tmpReturn, _3 TSRMLS_CC);
		ZEPHIR_CPY_WRT(tmpReturn, _24);
	}
	RETURN_CCTOR(tmpReturn);

}

