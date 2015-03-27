
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

ZEPHIR_INIT_CLASS(Yaf_Route_Regex) {

	ZEPHIR_REGISTER_CLASS(Yaf\\Route, Regex, yaf, route_regex, yaf_route_regex_method_entry, 0);

	zend_declare_property_string(yaf_route_regex_ce, SL("_route"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_regex_ce, SL("_default"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_regex_ce, SL("_maps"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_regex_ce, SL("_verify"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_route_regex_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Instantiates route based on passed Yaf_Config_Abstract structure
 *
 * @param array $config Configuration object
 */
PHP_METHOD(Yaf_Route_Regex, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _2, _4;
	zval *config_param = NULL, *_1, *_3, *_5, *_6, *_7, *_8;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	_0 = !(zephir_array_isset_string(config, SS("match")));
	if (!(_0)) {
		zephir_array_fetch_string(&_1, config, SL("match"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 24 TSRMLS_CC);
		_0 = !(Z_TYPE_P(_1) == IS_STRING);
	}
	_2 = !(zephir_array_isset_string(config, SS("route")));
	if (!(_2)) {
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch_string(&_3, config, SL("route"), PH_NOISY, "yaf/Route/regex.zep", 26 TSRMLS_CC);
		_2 = ZEPHIR_IS_EMPTY(_3);
	}
	_4 = !(zephir_array_isset_string(config, SS("map")));
	if (!(_4)) {
		ZEPHIR_OBS_VAR(_5);
		zephir_array_fetch_string(&_5, config, SL("map"), PH_NOISY, "yaf/Route/regex.zep", 28 TSRMLS_CC);
		_4 = ZEPHIR_IS_EMPTY(_5);
	}
	if (_0) {
		RETURN_MM_NULL();
	} else if (_2) {
		RETURN_MM_NULL();
	} else if (_4) {
		RETURN_MM_NULL();
	} else {
		object_init_ex(return_value, yaf_route_regex_ce);
		zephir_array_fetch_string(&_6, config, SL("match"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 31 TSRMLS_CC);
		zephir_array_fetch_string(&_7, config, SL("route"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 31 TSRMLS_CC);
		zephir_array_fetch_string(&_8, config, SL("map"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 31 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _6, _7, _8);
		zephir_check_call_status();
		RETURN_MM();
	}

}

PHP_METHOD(Yaf_Route_Regex, __construct) {

	zval *_4 = NULL, *_5 = NULL;
	zend_bool _2, _3;
	zval *match, *route, *map, *verify = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &match, &route, &map, &verify);

	if (!verify) {
		verify = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_maps"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("_default"), _1 TSRMLS_CC);
	_2 = !(Z_TYPE_P(match) == IS_STRING);
	if (!(_2)) {
		_2 = ZEPHIR_IS_STRING(match, "");
	}
	if (_2) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_routerfailed_ce, "Expects a string as the first parameter", "yaf/Route/regex.zep", 38);
		return;
	}
	if (!(Z_TYPE_P(route) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_routerfailed_ce, "Expects a array as the second parameter", "yaf/Route/regex.zep", 42);
		return;
	}
	if (!(Z_TYPE_P(map) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_routerfailed_ce, "Expects a array as the third parameter", "yaf/Route/regex.zep", 46);
		return;
	}
	_3 = Z_TYPE_P(verify) != IS_NULL;
	if (_3) {
		_3 = !(Z_TYPE_P(verify) == IS_ARRAY);
	}
	if (_3) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_routerfailed_ce, "Expects an array as verify parameter", "yaf/Route/regex.zep", 50);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_route"), match TSRMLS_CC);
	zephir_get_arrval(_4, route);
	zephir_update_property_this(this_ptr, SL("_default"), _4 TSRMLS_CC);
	zephir_get_arrval(_5, map);
	zephir_update_property_this(this_ptr, SL("_maps"), _5 TSRMLS_CC);
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
PHP_METHOD(Yaf_Route_Regex, route) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_6 = NULL, *_8 = NULL;
	zend_bool _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *requestUri = NULL, *baseuri = NULL, *path = NULL, *res = NULL, *values = NULL, *_2 = NULL, _4, *_5 = NULL, *_7, *_9, *_10, *_11, *_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_INIT_VAR(values);
	array_init(values);
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
	ZEPHIR_CALL_FUNCTION(&_5, "urldecode", &_6, path);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(path, _5);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_route"), PH_NOISY_CC);
	Z_SET_ISREF_P(values);
	ZEPHIR_CALL_FUNCTION(&res, "preg_match", &_8, _7, path, values);
	Z_UNSET_ISREF_P(values);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG_IDENTICAL(res, 0)) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "_getmappedvalues", NULL, values);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(values, _5);
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_9, SS("module"))) {
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_11, _10, SL("module"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 87 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, _11);
		zephir_check_call_status();
	}
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_10, SS("controller"))) {
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_11, _12, SL("controller"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 91 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _11);
		zephir_check_call_status();
	}
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
	if (zephir_array_isset_string(_10, SS("action"))) {
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("_default"), PH_NOISY_CC);
		zephir_array_fetch_string(&_11, _12, SL("action"), PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 95 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _11);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, values);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

/**
 * Uses user provided map array which consists
 * of index => name parameter mapping. If map is not found,
 * it returns nothing.
 *
 * @param  array   $values Indexed or associative array of values to map
 * @return array   An array of mapped values
 */
PHP_METHOD(Yaf_Route_Regex, _getMappedValues) {

	HashTable *_1;
	HashPosition _0;
	zval *values_param = NULL, *tempReturn, *key = NULL, *value = NULL, *index, **_2, *_3, *_4;
	zval *values = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &values_param);

	zephir_get_arrval(values, values_param);


	ZEPHIR_INIT_VAR(tempReturn);
	array_init(tempReturn);
	zephir_is_iterable(values, &_1, &_0, 0, 0, "yaf/Route/regex.zep", 124);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if (Z_TYPE_P(key) == IS_LONG) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("_maps"), PH_NOISY_CC);
			if (zephir_array_key_exists(_3, key TSRMLS_CC)) {
				_4 = zephir_fetch_nproperty_this(this_ptr, SL("_maps"), PH_NOISY_CC);
				zephir_array_fetch(&index, _4, key, PH_NOISY | PH_READONLY, "yaf/Route/regex.zep", 117 TSRMLS_CC);
				zephir_array_update_zval(&tempReturn, index, &value, PH_COPY | PH_SEPARATE);
			}
		} else {
			zephir_array_update_zval(&tempReturn, key, &value, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(tempReturn);

}

