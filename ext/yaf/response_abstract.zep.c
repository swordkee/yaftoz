
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
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"

ZEPHIR_INIT_CLASS(Yaf_Response_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Response_Abstract, yaf, response_abstract, yaf_response_abstract_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Body content
	 * @var array
	 */
	zend_declare_property_null(yaf_response_abstract_ce, SL("_body"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Array of headers. Each header is an array with keys 'name' and 'value'
	 * @var array
	 */
	zend_declare_property_null(yaf_response_abstract_ce, SL("_headers"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Determine to send the headers or not
	 * @var unknown_type
	 */
	zend_declare_property_bool(yaf_response_abstract_ce, SL("_sendheader"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Default body name
	 */
	zend_declare_class_constant_string(yaf_response_abstract_ce, SL("DEFAULT_BODY"), "content" TSRMLS_CC);

	return SUCCESS;

}

/**
 * Append content to the body content
 *
 * @param string $content
 * @param string $key
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, appendBody) {

	zval *key = NULL, *_2 = NULL;
	zval *body, *key_param = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &body, &key_param);

	if (!key_param) {
		ZEPHIR_INIT_VAR(key);
		ZVAL_EMPTY_STRING(key);
	} else {
		zephir_get_strval(key, key_param);
	}


	if (!(zephir_fast_strlen_ev(key))) {
		ZEPHIR_INIT_NVAR(key);
		ZVAL_STRING(key, "content", 1);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, key))) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "", 1);
		zephir_update_property_array(this_ptr, SL("_body"), key, _1 TSRMLS_CC);
	}
	zephir_get_strval(_2, body);
	zephir_update_property_array(this_ptr, SL("_body"), key, _2 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Clear the entire body
 *
 * @param string $key
 * @return boolean
 */
PHP_METHOD(Yaf_Response_Abstract, clearBody) {

	zval *key_param = NULL, *_0, *_1, *_2;
	zval *key = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &key_param);

	if (!key_param) {
		ZEPHIR_INIT_VAR(key);
		ZVAL_EMPTY_STRING(key);
	} else {
		zephir_get_strval(key, key_param);
	}


	if (zephir_fast_strlen_ev(key)) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
		if (zephir_array_key_exists(_0, key TSRMLS_CC)) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
			zephir_array_unset(&_1, key, PH_SEPARATE);
		}
	} else {
		ZEPHIR_INIT_VAR(_2);
		array_init(_2);
		zephir_update_property_this(this_ptr, SL("_body"), _2 TSRMLS_CC);
	}
	RETURN_MM_BOOL(1);

}

/**
 * Clear headers
 *
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, clearHeaders) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_headers"), _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Yaf_Response_Abstract, __clone) {



}

PHP_METHOD(Yaf_Response_Abstract, __construct) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_headers"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("_body"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Response_Abstract, __destruct) {



}

/**
 * Return the body content
 *
 * @param string $key
 * @return string
 */
PHP_METHOD(Yaf_Response_Abstract, getBody) {

	zval *key_param = NULL, *_0, *_1, *_2;
	zval *key = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &key_param);

	if (!key_param) {
		ZEPHIR_INIT_VAR(key);
		ZVAL_EMPTY_STRING(key);
	} else {
		zephir_get_strval(key, key_param);
	}


	if (!(zephir_fast_strlen_ev(key))) {
		ZEPHIR_INIT_NVAR(key);
		ZVAL_STRING(key, "content", 1);
	}
	ZEPHIR_INIT_VAR(_0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
	if (zephir_array_key_exists(_1, key TSRMLS_CC)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
		zephir_array_fetch(&_0, _2, key, PH_NOISY, "yaf/response_abstract.zep", 106 TSRMLS_CC);
	} else {
		ZVAL_NULL(_0);
	}
	RETURN_CCTOR(_0);

}

/**
 * Return array of headers; see {@link $_headers} for format
 *
 * @return array
 */
PHP_METHOD(Yaf_Response_Abstract, getHeader) {


	RETURN_MEMBER(this_ptr, "_headers");

}

/**
 * Prepend content the body
 *
 * @param string $body
 * @param string $key
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, prependBody) {

	zval *body_param = NULL, *key_param = NULL, *_0, *_1, *_2, *_3, *_4;
	zval *body = NULL, *key = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &body_param, &key_param);

	zephir_get_strval(body, body_param);
	if (!key_param) {
		ZEPHIR_INIT_VAR(key);
		ZVAL_EMPTY_STRING(key);
	} else {
		zephir_get_strval(key, key_param);
	}


	if (!(zephir_fast_strlen_ev(key))) {
		ZEPHIR_INIT_NVAR(key);
		ZVAL_STRING(key, "content", 1);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, key))) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "", 1);
		zephir_update_property_array(this_ptr, SL("_body"), key, _1 TSRMLS_CC);
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
	zephir_array_fetch(&_3, _2, key, PH_NOISY | PH_READONLY, "yaf/response_abstract.zep", 135 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_VV(_4, body, _3);
	zephir_update_property_array(this_ptr, SL("_body"), key, _4 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Send the response, including all headers
 *
 * @return void
 */
PHP_METHOD(Yaf_Response_Abstract, response) {

	HashTable *_3;
	HashPosition _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *body = NULL, *_0, *_1, **_4;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_sendheader"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendheaders", NULL);
		zephir_check_call_status();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_body"), PH_NOISY_CC);
	zephir_is_iterable(_1, &_3, &_2, 0, 0, "yaf/response_abstract.zep", 155);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(body, _4);
		zend_print_zval(body, 0);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Response_Abstract, setAllHeaders) {


	RETURN_BOOL(0);

}

/**
 * Set body content
 *
 * @param string $body
 * @param string $key
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, setBody) {

	zval *body_param = NULL, *key_param = NULL;
	zval *body = NULL, *key = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &body_param, &key_param);

	zephir_get_strval(body, body_param);
	if (!key_param) {
		ZEPHIR_INIT_VAR(key);
		ZVAL_EMPTY_STRING(key);
	} else {
		zephir_get_strval(key, key_param);
	}


	if (!(zephir_fast_strlen_ev(key))) {
		ZEPHIR_INIT_NVAR(key);
		ZVAL_STRING(key, "content", 1);
	}
	zephir_get_strval(_0, body);
	zephir_update_property_array(this_ptr, SL("_body"), key, _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set a header
 *
 * If $replace is true, replaces any headers already defined with that
 * $name.
 *
 * @param string $name
 * @param string $value
 * @param boolean $replace
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, setHeader) {

	zval *_8;
	HashTable *_4;
	HashPosition _3;
	zval *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL, *value = NULL, *replace = NULL, *key = NULL, *header = NULL, *_0 = NULL, *_2, **_5, *_6, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &name, &value, &replace);

	ZEPHIR_SEPARATE_PARAM(name);
	ZEPHIR_SEPARATE_PARAM(value);
	if (!replace) {
		replace = ZEPHIR_GLOBAL(global_false);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "_normalizeheader", NULL, name);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(name, _0);
	zephir_get_strval(_1, value);
	ZEPHIR_CPY_WRT(value, _1);
	if (zephir_is_true(replace)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_headers"), PH_NOISY_CC);
		zephir_is_iterable(_2, &_4, &_3, 0, 0, "yaf/response_abstract.zep", 204);
		for (
		  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4, &_3)
		) {
			ZEPHIR_GET_HMKEY(key, _4, _3);
			ZEPHIR_GET_HVALUE(header, _5);
			zephir_array_fetch_string(&_6, header, SL("name"), PH_NOISY | PH_READONLY, "yaf/response_abstract.zep", 199 TSRMLS_CC);
			if (ZEPHIR_IS_EQUAL(name, _6)) {
				_7 = zephir_fetch_nproperty_this(this_ptr, SL("_headers"), PH_NOISY_CC);
				zephir_array_unset(&_7, key, PH_SEPARATE);
			}
		}
	}
	ZEPHIR_INIT_VAR(_8);
	array_init_size(_8, 5);
	zephir_array_update_string(&_8, SL("name"), &name, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_8, SL("value"), &value, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_8, SL("replace"), &replace, PH_COPY | PH_SEPARATE);
	zephir_update_property_array_append(this_ptr, SL("_headers"), _8 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set redirect URL
 *
 * Sets Location header. Forces replacement of any prior redirects.
 *
 * @param string $url
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, setRedirect) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *_0, *_1;
	zval *url = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &url_param);

	zephir_get_strval(url, url_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "Location", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setheader", NULL, _0, url, _1);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Magic __toString functionality
 *
 * Returns response value as string
 * using output buffering.
 *
 * @return string
 */
PHP_METHOD(Yaf_Response_Abstract, __toString) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "response", NULL);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Normalize a header name
 *
 * Normalizes a header name to X-Capitalized-Names
 *
 * @param  string $name
 * @return string
 */
PHP_METHOD(Yaf_Response_Abstract, _normalizeHeader) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	zval *_2 = NULL;
	zval *_0;
	zval *name, *filtered = NULL, *_1 = NULL, _3, *_5, _6, _7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_INIT_VAR(filtered);
	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "-", 1);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "_", 1);
	zephir_array_fast_append(_0, _1);
	zephir_get_strval(_2, name);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, " ", 0);
	zephir_fast_str_replace(filtered, _0, &_3, _2 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_1);
	zephir_fast_strtolower(_1, filtered);
	ZEPHIR_CALL_FUNCTION(&filtered, "ucwords", &_4, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_STRING(&_6, " ", 0);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_STRING(&_7, "-", 0);
	zephir_fast_str_replace(_5, &_6, &_7, filtered TSRMLS_CC);
	ZEPHIR_CPY_WRT(filtered, _5);
	RETURN_CCTOR(filtered);

}

/**
 * Send all headers
 *
 * Sends any headers specified.
 * If an {@link setHttpResponseCode() HTTP response code}
 * has been specified, it is sent with the first header.
 *
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Response_Abstract, sendHeaders) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_8 = NULL;
	HashTable *_2;
	HashPosition _1;
	zval *header = NULL, *_0, **_3, *_4, *_5, *_6 = NULL, *_7;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_headers"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0, "yaf/response_abstract.zep", 277);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(header, _3);
		zephir_array_fetch_string(&_4, header, SL("name"), PH_NOISY | PH_READONLY, "yaf/response_abstract.zep", 274 TSRMLS_CC);
		zephir_array_fetch_string(&_5, header, SL("value"), PH_NOISY | PH_READONLY, "yaf/response_abstract.zep", 274 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_6);
		ZEPHIR_CONCAT_VSV(_6, _4, ": ", _5);
		zephir_array_fetch_string(&_7, header, SL("replace"), PH_NOISY | PH_READONLY, "yaf/response_abstract.zep", 274 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "header", &_8, _6, _7);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

