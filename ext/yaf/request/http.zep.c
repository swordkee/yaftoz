
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
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * Yaf Request Http
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Request_Http) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Request, Http, yaf, request_http, yaf_request_abstract_ce, yaf_request_http_method_entry, 0);

	/**
	 * REQUEST_URI
	 * @var string;
	 */
	zend_declare_property_null(yaf_request_http_ce, SL("_requestUri"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_request_http_ce, SL("_params"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Scheme for http
	 *
	 */
	zend_declare_class_constant_string(yaf_request_http_ce, SL("SCHEME_HTTP"), "http" TSRMLS_CC);

	/**
	 * Scheme for https
	 *
	 */
	zend_declare_class_constant_string(yaf_request_http_ce, SL("SCHEME_HTTPS"), "https" TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor
 *
 * @param string $requestUri
 * @param string $baseUri
 * @return void
 */
PHP_METHOD(Yaf_Request_Http, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *requestUri_param = NULL, *baseUri_param = NULL;
	zval *requestUri = NULL, *baseUri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &requestUri_param, &baseUri_param);

	if (!requestUri_param) {
		ZEPHIR_INIT_VAR(requestUri);
		ZVAL_EMPTY_STRING(requestUri);
	} else {
		zephir_get_strval(requestUri, requestUri_param);
	}
	if (!baseUri_param) {
		ZEPHIR_INIT_VAR(baseUri);
		ZVAL_EMPTY_STRING(baseUri);
	} else {
		zephir_get_strval(baseUri, baseUri_param);
	}


	if (!ZEPHIR_IS_STRING_IDENTICAL(requestUri, "")) {
		zephir_update_property_this(this_ptr, SL("_requestUri"), requestUri TSRMLS_CC);
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrequesturi", NULL);
		zephir_check_call_status();
	}
	if (!ZEPHIR_IS_STRING_IDENTICAL(baseUri, "")) {
		zephir_update_property_this(this_ptr, SL("_baseUri"), baseUri TSRMLS_CC);
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setbaseuri", NULL);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Request_Http, __clone) {



}

/**
 * Magic method get
 * @param string $key
 * @return mixed
 */
PHP_METHOD(Yaf_Request_Http, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "get", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Access values contained in the superglobals as public members
 * Order of precedence: 1. GET, 2. POST, 3. COOKIE, 4. SERVER, 5. ENV
 *
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Yaf_Request_Http, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *tmpDefault_param = NULL, *_0, *_GET, *_POST, *_COOKIE, *_SERVER, *_1, *_2;
	zval *name = NULL, *tmpDefault = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &tmpDefault_param);

	zephir_get_strval(name, name_param);
	if (!tmpDefault_param) {
		ZEPHIR_INIT_VAR(tmpDefault);
		ZVAL_EMPTY_STRING(tmpDefault);
	} else {
		zephir_get_strval(tmpDefault, tmpDefault_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
	zephir_get_global(&_GET, SS("_GET") TSRMLS_CC);
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_get_global(&_COOKIE, SS("_COOKIE") TSRMLS_CC);
	zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
	if (zephir_array_isset(_0, name)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 76 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else if (zephir_array_isset(_GET, name)) {
		zephir_array_fetch(&_2, _GET, name, PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 78 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else if (zephir_array_isset(_POST, name)) {
		zephir_array_fetch(&_2, _POST, name, PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 80 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else if (zephir_array_isset(_COOKIE, name)) {
		zephir_array_fetch(&_2, _COOKIE, name, PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 82 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else if (ZEPHIR_IS_STRING(name, "REQUEST_URI")) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getrequesturi", NULL);
		zephir_check_call_status();
		RETURN_MM();
	} else if (ZEPHIR_IS_STRING(name, "PATH_INFO")) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getpathinfo", NULL);
		zephir_check_call_status();
		RETURN_MM();
	} else if (zephir_array_isset(_SERVER, name)) {
		zephir_array_fetch(&_2, _SERVER, name, PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 88 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else {
		RETURN_CTOR(tmpDefault);
	}

}

PHP_METHOD(Yaf_Request_Http, __set) {

	zval *name, *value;

	zephir_fetch_params(0, 2, 0, &name, &value);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(yaf_request_exception_ce, "Use setParam to set a parameter of request", "yaf/Request/http.zep", 99);
	return;

}

/**
 * Check to see if a property is set
 *
 * @param string $key
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Http, __isset) {

	zval *key_param = NULL, *_0, *_GET, *_POST, *_COOKIE, *_SERVER;
	zval *key = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(key, key_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
	zephir_get_global(&_GET, SS("_GET") TSRMLS_CC);
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_get_global(&_COOKIE, SS("_COOKIE") TSRMLS_CC);
	zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
	if (zephir_array_isset(_0, key)) {
		RETURN_MM_BOOL(1);
	} else if (zephir_array_isset(_GET, key)) {
		RETURN_MM_BOOL(1);
	} else if (zephir_array_isset(_POST, key)) {
		RETURN_MM_BOOL(1);
	} else if (zephir_array_isset(_COOKIE, key)) {
		RETURN_MM_BOOL(1);
	} else if (zephir_array_isset(_SERVER, key)) {
		RETURN_MM_BOOL(1);
	} else {
		RETURN_MM_BOOL(0);
	}

}

/**
 * Retrieve a member of the $_GET superglobal
 *
 * If no $name is passed, returns the entire $_GET array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Http, getQuery) {

	zval *name_param = NULL, *tmpDefault = NULL, *get = NULL, *_GET, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name_param, &tmpDefault);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
		zephir_get_strval(name, name_param);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_GET, SS("_GET") TSRMLS_CC);
	ZEPHIR_CPY_WRT(get, _GET);
	if (ZEPHIR_IS_STRING_IDENTICAL(name, "")) {
		RETVAL_ZVAL(_GET, 1, 0);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(get, name)) {
		zephir_array_fetch(&_0, get, name, PH_NOISY, "yaf/Request/http.zep", 145 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Retrieve a member of the $_POST superglobal
 *
 * If no $name is passed, returns the entire $_POST array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Http, getPost) {

	zval *name_param = NULL, *tmpDefault = NULL, *post = NULL, *_POST, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name_param, &tmpDefault);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
		zephir_get_strval(name, name_param);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	ZEPHIR_CPY_WRT(post, _POST);
	if (ZEPHIR_IS_STRING_IDENTICAL(name, "")) {
		RETURN_CCTOR(post);
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(post, name)) {
		zephir_array_fetch(&_0, post, name, PH_NOISY, "yaf/Request/http.zep", 166 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Retrieve a member of the $_COOKIE superglobal
 *
 * If no $name is passed, returns the entire $_COOKIE array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Http, getCookie) {

	zval *name_param = NULL, *tmpDefault = NULL, *cookie = NULL, *_COOKIE, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name_param, &tmpDefault);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
		zephir_get_strval(name, name_param);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_COOKIE, SS("_COOKIE") TSRMLS_CC);
	ZEPHIR_CPY_WRT(cookie, _COOKIE);
	if (ZEPHIR_IS_STRING_IDENTICAL(name, "")) {
		RETURN_CCTOR(cookie);
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(cookie, name)) {
		zephir_array_fetch(&_0, cookie, name, PH_NOISY, "yaf/Request/http.zep", 187 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Retrieve a member of the $_FILES superglobal
 *
 * If no $name is passed, returns the entire $_FILES array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Http, getFiles) {

	zval *name_param = NULL, *tmpDefault = NULL, *files = NULL, *_FILES, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name_param, &tmpDefault);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
		zephir_get_strval(name, name_param);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_FILES, SS("_FILES") TSRMLS_CC);
	ZEPHIR_CPY_WRT(files, _FILES);
	if (ZEPHIR_IS_STRING_IDENTICAL(name, "")) {
		RETURN_CCTOR(files);
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(files, name)) {
		zephir_array_fetch(&_0, files, name, PH_NOISY, "yaf/Request/http.zep", 208 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Retrieve a member of the $_REQUEST superglobal
 *
 * If no $name is passed, returns the entire $_REQUEST array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Http, getRequest) {

	zval *name_param = NULL, *tmpDefault = NULL, *request = NULL, *_REQUEST, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name_param, &tmpDefault);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
		zephir_get_strval(name, name_param);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_REQUEST, SS("_REQUEST") TSRMLS_CC);
	ZEPHIR_CPY_WRT(request, _REQUEST);
	if (ZEPHIR_IS_STRING_IDENTICAL(name, "")) {
		RETURN_CCTOR(request);
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(request, name)) {
		zephir_array_fetch(&_0, request, name, PH_NOISY, "yaf/Request/http.zep", 228 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Returns the REQUEST_URI taking into account
 * platform differences between Apache and IIS
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Http, getRequestUri) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("_requestUri"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(_0)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrequesturi", NULL);
		zephir_check_call_status();
	}
	RETURN_MM_MEMBER(this_ptr, "_requestUri");

}

PHP_METHOD(Yaf_Request_Http, getPathInfo) {



}

/**
 * Everything in REQUEST_URI before PATH_INFO
 * <form action="<?=$baseUrl?>/news/submit" method="POST"/>
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Http, getBaseUri) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_baseUri"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setbaseuri", NULL);
		zephir_check_call_status();
	}
	RETURN_MM_MEMBER(this_ptr, "_baseUri");

}

/**
 * Set the base URL of the request; i.e.,
 * the segment leading to the script name
 *
 * E.g.:
 * - /admin
 * - /myapp
 * - /subdir/index.php
 *
 * Do not use the full URI when providing the base. The following are
 * examples of what not to use:
 * - http://example.com/admin (should be just /admin)
 * - http://example.com/subdir/index.php (should be just /subdir/index.php)
 *
 * If no $baseUrl is provided, attempts to determine the base URL from the
 * environment, using SCRIPT_FILENAME, SCRIPT_NAME, PHP_SELF, and
 * ORIG_SCRIPT_NAME in its determination.
 *
 * @param mixed $baseUrl
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Http, setBaseUri) {

	zephir_nts_static zephir_fcall_cache_entry *_14 = NULL, *_18 = NULL;
	zend_bool _0, _2, _5, _8, _16, _17;
	int index, ZEPHIR_LAST_CALL_STATUS;
	zval *baseUri = NULL, *filename = NULL, *path = NULL, *file = NULL, *segs = NULL, *last, *pos = NULL, *seg = NULL, *requestUri = NULL, *truncatedRequestUri = NULL, *basename, *_SERVER, *_1, *_3, *_4, *_6, *_7, *_9, *_10, *_11 = NULL, _12 = zval_used_for_init, *_13 = NULL, *_15 = NULL, *_19 = NULL, _20 = zval_used_for_init, *_21;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &baseUri);

	if (!baseUri) {
		ZEPHIR_CPY_WRT(baseUri, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(baseUri);
	}


	_0 = Z_TYPE_P(baseUri) != IS_NULL;
	if (_0) {
		_0 = !(Z_TYPE_P(baseUri) == IS_STRING);
	}
	if (_0) {
		RETURN_THIS();
	}
	if (Z_TYPE_P(baseUri) == IS_NULL) {
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		if (zephir_array_isset_string(_SERVER, SS("SCRIPT_FILENAME"))) {
			ZEPHIR_INIT_VAR(filename);
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_1, _SERVER, SL("SCRIPT_FILENAME"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 296 TSRMLS_CC);
			zephir_basename(filename, _1 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(filename);
			ZVAL_STRING(filename, "", 1);
		}
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		_2 = zephir_array_isset_string(_SERVER, SS("SCRIPT_NAME"));
		if (_2) {
			ZEPHIR_INIT_VAR(_3);
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_4, _SERVER, SL("SCRIPT_NAME"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 298 TSRMLS_CC);
			zephir_basename(_3, _4 TSRMLS_CC);
			_2 = ZEPHIR_IS_IDENTICAL(_3, filename);
		}
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		_5 = zephir_array_isset_string(_SERVER, SS("PHP_SELF"));
		if (_5) {
			ZEPHIR_INIT_VAR(_6);
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_7, _SERVER, SL("PHP_SELF"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 300 TSRMLS_CC);
			zephir_basename(_6, _7 TSRMLS_CC);
			_5 = ZEPHIR_IS_IDENTICAL(_6, filename);
		}
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		_8 = zephir_array_isset_string(_SERVER, SS("ORIG_SCRIPT_NAME"));
		if (_8) {
			ZEPHIR_INIT_VAR(_9);
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_10, _SERVER, SL("ORIG_SCRIPT_NAME"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 302 TSRMLS_CC);
			zephir_basename(_9, _10 TSRMLS_CC);
			_8 = ZEPHIR_IS_IDENTICAL(_9, filename);
		}
		if (_2) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			ZEPHIR_OBS_NVAR(baseUri);
			zephir_array_fetch_string(&baseUri, _SERVER, SL("SCRIPT_NAME"), PH_NOISY, "yaf/Request/http.zep", 299 TSRMLS_CC);
		} else if (_5) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			ZEPHIR_OBS_NVAR(baseUri);
			zephir_array_fetch_string(&baseUri, _SERVER, SL("PHP_SELF"), PH_NOISY, "yaf/Request/http.zep", 301 TSRMLS_CC);
		} else if (_8) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			ZEPHIR_OBS_NVAR(baseUri);
			zephir_array_fetch_string(&baseUri, _SERVER, SL("ORIG_SCRIPT_NAME"), PH_NOISY, "yaf/Request/http.zep", 303 TSRMLS_CC);
		} else {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			if (zephir_array_isset_string(_SERVER, SS("PHP_SELF"))) {
				zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
				ZEPHIR_OBS_VAR(path);
				zephir_array_fetch_string(&path, _SERVER, SL("PHP_SELF"), PH_NOISY, "yaf/Request/http.zep", 308 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(path);
				ZVAL_STRING(path, "", 1);
			}
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			if (zephir_array_isset_string(_SERVER, SS("SCRIPT_FILENAME"))) {
				zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
				ZEPHIR_OBS_VAR(file);
				zephir_array_fetch_string(&file, _SERVER, SL("SCRIPT_FILENAME"), PH_NOISY, "yaf/Request/http.zep", 310 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(file);
				ZVAL_STRING(file, "", 1);
			}
			ZEPHIR_INIT_VAR(segs);
			ZEPHIR_INIT_VAR(_11);
			ZEPHIR_SINIT_VAR(_12);
			ZVAL_STRING(&_12, "/", 0);
			zephir_fast_trim(_11, file, &_12, ZEPHIR_TRIM_BOTH TSRMLS_CC);
			zephir_fast_explode_str(segs, SL("/"), _11, LONG_MAX TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_13, "array_reverse", &_14, segs);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(segs, _13);
			index = 0;
			ZEPHIR_INIT_VAR(last);
			ZVAL_LONG(last, zephir_fast_count_int(segs TSRMLS_CC));
			ZEPHIR_INIT_NVAR(baseUri);
			ZVAL_STRING(baseUri, "", 1);
			do {
				ZEPHIR_OBS_NVAR(seg);
				zephir_array_fetch_long(&seg, segs, index, PH_NOISY, "yaf/Request/http.zep", 317 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_15);
				ZEPHIR_CONCAT_SVV(_15, "/", seg, baseUri);
				ZEPHIR_CPY_WRT(baseUri, _15);
				index++;
				ZEPHIR_INIT_NVAR(pos);
				zephir_fast_strpos(pos, path, baseUri, 0 );
				_16 = ZEPHIR_GT_LONG(last, index);
				if (_16) {
					_16 = !ZEPHIR_IS_FALSE_IDENTICAL(pos);
				}
				_17 = _16;
				if (_17) {
					_17 = !ZEPHIR_IS_LONG(pos, 0);
				}
			} while (_17);
		}
		ZEPHIR_CALL_METHOD(&requestUri, this_ptr, "getrequesturi", NULL);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		zephir_fast_strpos(_11, requestUri, baseUri, 0 );
		if (ZEPHIR_IS_LONG_IDENTICAL(_11, 0)) {
			zephir_update_property_this(this_ptr, SL("_baseUri"), baseUri TSRMLS_CC);
			RETURN_THIS();
		}
		ZEPHIR_CALL_FUNCTION(&_13, "dirname", &_18, baseUri);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		zephir_fast_strpos(_11, requestUri, _13, 0 );
		if (ZEPHIR_IS_LONG_IDENTICAL(_11, 0)) {
			ZEPHIR_CALL_FUNCTION(&_19, "dirname", &_18, baseUri);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("_baseUri"), _19 TSRMLS_CC);
			RETURN_THIS();
		}
		ZEPHIR_CPY_WRT(truncatedRequestUri, requestUri);
		ZEPHIR_SINIT_NVAR(_12);
		ZVAL_STRING(&_12, "?", 0);
		ZEPHIR_INIT_NVAR(pos);
		zephir_fast_strpos(pos, requestUri, &_12, 0 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
			ZEPHIR_SINIT_VAR(_20);
			ZVAL_LONG(&_20, 0);
			ZEPHIR_INIT_NVAR(truncatedRequestUri);
			zephir_substr(truncatedRequestUri, requestUri, 0 , zephir_get_intval(pos), 0);
		}
		ZEPHIR_INIT_VAR(basename);
		zephir_basename(basename, baseUri TSRMLS_CC);
		_16 = ZEPHIR_IS_EMPTY(basename);
		if (!(_16)) {
			ZEPHIR_INIT_NVAR(_11);
			zephir_fast_strpos(_11, truncatedRequestUri, basename, 0 );
			_16 = !zephir_is_true(_11);
		}
		if (_16) {
			ZEPHIR_INIT_ZVAL_NREF(_21);
			ZVAL_STRING(_21, "", 1);
			zephir_update_property_this(this_ptr, SL("_baseUri"), _21 TSRMLS_CC);
			RETURN_THIS();
		}
		ZEPHIR_INIT_NVAR(pos);
		zephir_fast_strpos(pos, requestUri, baseUri, 0 );
		_16 = zephir_fast_strlen_ev(requestUri) >= zephir_fast_strlen_ev(baseUri);
		if (_16) {
			_17 = !ZEPHIR_IS_FALSE_IDENTICAL(pos);
			if (_17) {
				_17 = !ZEPHIR_IS_LONG_IDENTICAL(pos, 0);
			}
			_16 = _17;
		}
		if (_16) {
			ZEPHIR_SINIT_NVAR(_12);
			ZVAL_LONG(&_12, 0);
			ZEPHIR_SINIT_NVAR(_20);
			ZVAL_LONG(&_20, (zephir_get_numberval(pos) + zephir_fast_strlen_ev(baseUri)));
			ZEPHIR_INIT_NVAR(baseUri);
			zephir_substr(baseUri, requestUri, 0 , zephir_get_intval(&_20), 0);
		}
	}
	zephir_update_property_this(this_ptr, SL("_baseUri"), baseUri TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set the REQUEST_URI on which the instance operates
 *
 * If no request URI is passed, uses the value in $_SERVER['REQUEST_URI'],
 * $_SERVER['HTTP_X_REWRITE_URL'],
 * or $_SERVER['ORIG_PATH_INFO'] + $_SERVER['QUERY_STRING'].
 *
 * @param string $requestUri
 * @return Yaf_Request_Http
 */
PHP_METHOD(Yaf_Request_Http, setRequestUri) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _2, _3;
	zval *requestUri = NULL, *schemeAndHttpHost = NULL, *_SERVER, *_1, *_4, *_5, *_6 = NULL, *_7 = NULL, *_8, _9, *_10, *_11, *_12, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &requestUri);

	if (!requestUri) {
		ZEPHIR_CPY_WRT(requestUri, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(requestUri);
	}
	ZEPHIR_INIT_VAR(schemeAndHttpHost);
	ZVAL_STRING(schemeAndHttpHost, "", 1);


	if (Z_TYPE_P(requestUri) == IS_NULL) {
		ZEPHIR_OBS_NVAR(requestUri);
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		_0 = zephir_array_isset_string(_SERVER, SS("IIS_WasUrlRewritten"));
		if (_0) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_1, _SERVER, SL("IIS_WasUrlRewritten"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 384 TSRMLS_CC);
			_0 = ZEPHIR_IS_LONG(_1, 1);
		}
		_2 = _0;
		if (_2) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			_2 = zephir_array_isset_string(_SERVER, SS("UNENCODED_URL"));
		}
		_3 = _2;
		if (_3) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_4, _SERVER, SL("UNENCODED_URL"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 384 TSRMLS_CC);
			_3 = !ZEPHIR_IS_STRING(_4, "");
		}
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		if (zephir_array_isset_string_fetch(&requestUri, _SERVER, SS("HTTP_X_REWRITE_URL"), 0 TSRMLS_CC)) {
			zephir_update_property_this(this_ptr, SL("_requestUri"), requestUri TSRMLS_CC);
		} else if (_3) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_5, _SERVER, SL("UNENCODED_URL"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 385 TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_requestUri"), _5 TSRMLS_CC);
		} else if (zephir_array_isset_string(_SERVER, SS("REQUEST_URI"))) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_5, _SERVER, SL("REQUEST_URI"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 387 TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_requestUri"), _5 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_6, this_ptr, "getscheme", NULL);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "gethttphost", NULL);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(schemeAndHttpHost);
			ZEPHIR_CONCAT_VSV(schemeAndHttpHost, _6, "://", _7);
			ZEPHIR_INIT_VAR(_8);
			zephir_fast_strpos(_8, requestUri, schemeAndHttpHost, 0 );
			if (ZEPHIR_IS_LONG_IDENTICAL(_8, 0)) {
				ZEPHIR_SINIT_VAR(_9);
				ZVAL_LONG(&_9, zephir_fast_strlen_ev(schemeAndHttpHost));
				ZEPHIR_INIT_VAR(_10);
				zephir_substr(_10, requestUri, zephir_get_intval(&_9), 0, ZEPHIR_SUBSTR_NO_LENGTH);
				zephir_update_property_this(this_ptr, SL("_requestUri"), _10 TSRMLS_CC);
			}
		} else if (zephir_array_isset_string(_SERVER, SS("ORIG_PATH_INFO"))) {
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			zephir_array_fetch_string(&_5, _SERVER, SL("ORIG_PATH_INFO"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 397 TSRMLS_CC);
			zephir_update_property_this(this_ptr, SL("_requestUri"), _5 TSRMLS_CC);
			zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
			ZEPHIR_OBS_VAR(_11);
			zephir_array_fetch_string(&_11, _SERVER, SL("QUERY_STRING"), PH_NOISY, "yaf/Request/http.zep", 399 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_11))) {
				zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
				zephir_array_fetch_string(&_12, _SERVER, SL("QUERY_STRING"), PH_NOISY | PH_READONLY, "yaf/Request/http.zep", 400 TSRMLS_CC);
				ZEPHIR_INIT_VAR(_13);
				ZEPHIR_CONCAT_SV(_13, "?", _12);
				zephir_update_property_this(this_ptr, SL("_requestUri"), _13 TSRMLS_CC);
			}
		} else {
			RETURN_THIS();
		}
	} else if (!(Z_TYPE_P(requestUri) == IS_STRING)) {
		RETURN_THIS();
	}
	zephir_update_property_this(this_ptr, SL("_requestUri"), requestUri TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Get the request URI scheme
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Http, getScheme) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "HTTPS", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getserver", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_1, "on")) {
		ZVAL_STRING(_0, "https", 1);
	} else {
		ZVAL_STRING(_0, "http", 1);
	}
	RETURN_CCTOR(_0);

}

/**
 * Get the HTTP host.
 *
 * "Host" ":" host [ ":" port ] ; Section 3.2.2
 * Note the HTTP Host header is not the same as the URI host.
 * It includes the port while the URI host doesn't.
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Http, getHttpHost) {

	zend_bool _1, _2, _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *host = NULL, *scheme = NULL, *name = NULL, *port = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "HTTP_HOST", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&host, this_ptr, "getserver", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(host))) {
		RETURN_CCTOR(host);
	}
	ZEPHIR_CALL_METHOD(&scheme, this_ptr, "getscheme", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "SERVER_NAME", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&name, this_ptr, "getserver", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "SERVER_PORT", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&port, this_ptr, "getserver", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	_1 = ZEPHIR_IS_STRING(scheme, "http");
	if (_1) {
		_1 = ZEPHIR_IS_LONG(port, 80);
	}
	_2 = _1;
	if (!(_2)) {
		_3 = ZEPHIR_IS_STRING(scheme, "https");
		if (_3) {
			_3 = ZEPHIR_IS_LONG(port, 443);
		}
		_2 = _3;
	}
	if (Z_TYPE_P(name) == IS_NULL) {
		RETURN_MM_STRING("", 1);
	} else if (_2) {
		RETURN_CCTOR(name);
	} else {
		ZEPHIR_CONCAT_VSV(return_value, name, ":", port);
		RETURN_MM();
	}

}

