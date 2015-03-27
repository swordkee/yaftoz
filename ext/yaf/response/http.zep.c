
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
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/fcall.h"


/**
 * Yaf_Response_Http
 *
 * HTTP response for controllers
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Response_Http) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Response, Http, yaf, response_http, yaf_response_abstract_ce, yaf_response_http_method_entry, 0);

	zend_declare_property_bool(yaf_response_http_ce, SL("_sendheader"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(yaf_response_http_ce, SL("_responseCode"), 200, ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Set HTTP response code to use with headers
 *
 * @param int $code
 * @return Yaf_Response_Http
 */
PHP_METHOD(Yaf_Response_Http, setResponseCode) {

	zend_bool _1, _2;
	zval *code_param = NULL, _0, *_3;
	int code;

	zephir_fetch_params(0, 1, 0, &code_param);

	code = zephir_get_intval(code_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, code);
	_1 = !(Z_TYPE_P(&_0) == IS_LONG);
	if (!(_1)) {
		_1 = code > 100;
	}
	_2 = _1;
	if (!(_2)) {
		_2 = code < 599;
	}
	if (_2) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(yaf_response_exception_ce, "Invalid HTTP response code", "yaf/Response/http.zep", 26);
		return;
	}
	ZEPHIR_INIT_ZVAL_NREF(_3);
	ZVAL_LONG(_3, code);
	zephir_update_property_this(this_ptr, SL("_responseCode"), _3 TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Retrieve HTTP response code
 *
 * @return int
 */
PHP_METHOD(Yaf_Response_Http, getResponseCode) {


	RETURN_MEMBER(this_ptr, "_responseCode");

}

/**
 * Send all headers
 *
 * Sends any headers specified.
 * If an {@link setResponseCode() HTTP response code}
 * has been specified, it is sent with the first header.
 *
 * @return Yaf_Response_Http
 */
PHP_METHOD(Yaf_Response_Http, sendHeaders) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_11 = NULL;
	HashTable *_2;
	HashPosition _1;
	zval *header = NULL, *_0, **_3, *_5, *_6, *_7, *_8 = NULL, *_9, *_10;
	zend_bool httpCodeSent, _4;

	ZEPHIR_MM_GROW();

	httpCodeSent = 0;
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_headers"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0, "yaf/Response/http.zep", 72);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(header, _3);
		_4 = !httpCodeSent;
		if (_4) {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_responseCode"), PH_NOISY_CC);
			_4 = zephir_is_true(_5);
		}
		if (_4) {
			zephir_array_fetch_string(&_6, header, SL("name"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 61 TSRMLS_CC);
			zephir_array_fetch_string(&_7, header, SL("value"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 61 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_8);
			ZEPHIR_CONCAT_VSV(_8, _6, ": ", _7);
			zephir_array_fetch_string(&_9, header, SL("replace"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 61 TSRMLS_CC);
			_10 = zephir_fetch_nproperty_this(this_ptr, SL("_responseCode"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "header", &_11, _8, _9, _10);
			zephir_check_call_status();
			httpCodeSent = 1;
		} else {
			zephir_array_fetch_string(&_6, header, SL("name"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 64 TSRMLS_CC);
			zephir_array_fetch_string(&_7, header, SL("value"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 64 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_8);
			ZEPHIR_CONCAT_VSV(_8, _6, ": ", _7);
			zephir_array_fetch_string(&_9, header, SL("replace"), PH_NOISY | PH_READONLY, "yaf/Response/http.zep", 64 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "header", &_11, _8, _9);
			zephir_check_call_status();
		}
	}
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
PHP_METHOD(Yaf_Response_Http, setRedirect) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *_0 = NULL, *_1 = NULL, *_2;
	zval *url = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &url_param);

	zephir_get_strval(url, url_param);


	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "Location", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_BOOL(_2, 1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "setheader", NULL, _1, url, _2);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 302);
	ZEPHIR_CALL_METHOD(NULL, _0, "setresponsecode", NULL, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

