
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/exception.h"

ZEPHIR_INIT_CLASS(Yaf_Request_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Request_Abstract, yaf, request_abstract, yaf_request_abstract_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Has the action been dispatched?
	 * @var boolean
	 */
	zend_declare_property_bool(yaf_request_abstract_ce, SL("dispatched"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Module
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("module"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Controller
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("controller"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Action
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("action"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Method
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("method"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Request parameters
	 * @var array
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("params"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * request_uri
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("language"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * routed
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("routed"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * base_uri
	 * @var string
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("_baseUri"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * exception
	 * @var \Exception
	 */
	zend_declare_property_null(yaf_request_abstract_ce, SL("_exception"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Retrieve the action name
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Abstract, getActionName) {


	RETURN_MEMBER(this_ptr, "action");

}

PHP_METHOD(Yaf_Request_Abstract, getBaseUri) {



}

/**
 * Retrieve the controller name
 *
 * @return string
 */
PHP_METHOD(Yaf_Request_Abstract, getControllerName) {


	RETURN_MEMBER(this_ptr, "controller");

}

/**
 * Retrieve a member of the $_ENV superglobal
 *
 * If no $key is passed, returns the entire $_ENV array.
 *
 * @param string $name
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Abstract, getEnv) {

	zval *name_param = NULL, *tmpDefault = NULL;
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


	RETVAL_ZVAL(tmpDefault, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Yaf_Request_Abstract, getQuery) {

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
		zephir_array_fetch(&_0, get, name, PH_NOISY, "yaf/request_abstract.zep", 115 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

/**
 * Set the exception
 * @todo check if this is OK
 */
PHP_METHOD(Yaf_Request_Abstract, setException) {

	zval *exception;

	zephir_fetch_params(0, 1, 0, &exception);



	zephir_update_property_this(this_ptr, SL("_exception"), exception TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Retrieve the exception
 * @todo check if this is OK
 * @return \Exception
 */
PHP_METHOD(Yaf_Request_Abstract, getException) {


	RETURN_MEMBER(this_ptr, "_exception");

}

/**
 * Retrieve the language
 * @return string
 */
PHP_METHOD(Yaf_Request_Abstract, getLanguage) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("language"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "HTTP_ACCEPT_LANGUAGE", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "getenv", NULL, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("language"), _1 TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "language");

}

/**
 * Retrieve the method
 * @return string
 */
PHP_METHOD(Yaf_Request_Abstract, getMethod) {

	zend_bool _3;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *method = NULL, *sapiType = NULL, *_0, *_1 = NULL, _4, _5, *_6, *_7;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("method"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "REQUEST_METHOD", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&method, this_ptr, "getserver", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		if (zephir_is_true(method)) {
			zephir_update_property_this(this_ptr, SL("method"), method TSRMLS_CC);
		} else {
			ZEPHIR_CALL_FUNCTION(&sapiType, "php_sapi_name", &_2);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_1);
			zephir_fast_strtolower(_1, sapiType);
			_3 = ZEPHIR_IS_STRING(_1, "cli");
			if (!(_3)) {
				ZEPHIR_SINIT_VAR(_4);
				ZVAL_LONG(&_4, 0);
				ZEPHIR_SINIT_VAR(_5);
				ZVAL_LONG(&_5, 3);
				ZEPHIR_INIT_VAR(_6);
				zephir_substr(_6, sapiType, 0 , 3 , 0);
				_3 = ZEPHIR_IS_STRING(_6, "cgi");
			}
			if (_3) {
				ZEPHIR_INIT_ZVAL_NREF(_7);
				ZVAL_STRING(_7, "CLI", 1);
				zephir_update_property_this(this_ptr, SL("method"), _7 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_ZVAL_NREF(_7);
				ZVAL_STRING(_7, "Unknown", 1);
				zephir_update_property_this(this_ptr, SL("method"), _7 TSRMLS_CC);
			}
		}
	}
	RETURN_MM_MEMBER(this_ptr, "method");

}

PHP_METHOD(Yaf_Request_Abstract, getModuleName) {


	RETURN_MEMBER(this_ptr, "module");

}

/**
 * Get an action parameter
 *
 * @param string $key
 * @param mixed $default Default value to use if key not found
 * @return mixed
 */
PHP_METHOD(Yaf_Request_Abstract, getParam) {

	zval *_0 = NULL;
	zval *name = NULL, *tmpDefault = NULL, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &tmpDefault);

	ZEPHIR_SEPARATE_PARAM(name);
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_strval(_0, name);
	ZEPHIR_CPY_WRT(name, _0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("params"), PH_NOISY_CC);
	if (zephir_array_isset(_1, name)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("params"), PH_NOISY_CC);
		zephir_array_fetch(&_3, _2, name, PH_NOISY | PH_READONLY, "yaf/request_abstract.zep", 196 TSRMLS_CC);
		RETURN_CTOR(_3);
	}
	RETVAL_ZVAL(tmpDefault, 1, 0);
	RETURN_MM();

}

/**
 * Get all action parameters
 *
 * @return array
 */
PHP_METHOD(Yaf_Request_Abstract, getParams) {


	RETURN_MEMBER(this_ptr, "params");

}

PHP_METHOD(Yaf_Request_Abstract, getRequestUri) {



}

/**
 * Retrieve a member of the $_SERVER superglobal
 *
 * If no $key is passed, returns the entire $_SERVER array.
 *
 * @param string $key
 * @param mixed $default Default value to use if key not found
 * @return mixed Returns null if key does not exist
 */
PHP_METHOD(Yaf_Request_Abstract, getServer) {

	zval *name = NULL, *tmpDefault = NULL, *server = NULL, *_SERVER, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &name, &tmpDefault);

	if (!name) {
		name = ZEPHIR_GLOBAL(global_null);
	}
	if (!tmpDefault) {
		tmpDefault = ZEPHIR_GLOBAL(global_null);
	}


	zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
	ZEPHIR_CPY_WRT(server, _SERVER);
	if (Z_TYPE_P(name) == IS_NULL) {
		RETURN_CCTOR(server);
	}
	ZEPHIR_INIT_VAR(_0);
	if (zephir_array_isset(server, name)) {
		zephir_array_fetch(&_0, server, name, PH_NOISY, "yaf/request_abstract.zep", 235 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(_0, tmpDefault);
	}
	RETURN_CCTOR(_0);

}

PHP_METHOD(Yaf_Request_Abstract, isCli) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "CLI")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Determine if the request has been dispatched
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isDispatched) {


	RETURN_MEMBER(this_ptr, "dispatched");

}

/**
 * Was the request made by GET?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "GET")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Was the request made by HEAD?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isHead) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "HEAD")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Was the request made by OPTIONS?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isOptions) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "OPTIONS")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Was the request made by POST?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isPost) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "POST")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Was the request made by PUT?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isPut) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "PUT")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Was the request made by DELETE?
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isDelete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "DELETE")) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Is the request a Javascript XMLHttpRequest?
 *
 * Should work with Prototype/Script.aculo.us, possibly others.
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isXmlHttpRequest) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_2, _3, *_4 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "HTTP_X_REQUESTED_WITH", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getserver", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, "XMLHttpRequest", 0);
	ZEPHIR_CALL_FUNCTION(&_4, "strcasecmp", &_5, _1, &_3);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_4, 0)) {
		ZVAL_BOOL(_0, 1);
	} else {
		ZVAL_BOOL(_0, 0);
	}
	RETURN_CCTOR(_0);

}

/**
 * Determine if the request has been routed
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Request_Abstract, isRouted) {


	RETURN_MEMBER(this_ptr, "routed");

}

/**
 * Set the action name
 *
 * @param string $value
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, setActionName) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *action, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &action);



	if (!(Z_TYPE_P(action) == IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_request_exception_ce, "Expect a string action name", "yaf/request_abstract.zep", 389);
		return;
	}
	zephir_update_property_this(this_ptr, SL("action"), action TSRMLS_CC);
	if (Z_TYPE_P(action) == IS_NULL) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "action", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setparam", NULL, _0, action);
		zephir_check_temp_parameter(_0);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Yaf_Request_Abstract, setBaseUri) {

	zval *baseUri = NULL;

	zephir_fetch_params(0, 0, 1, &baseUri);

	if (!baseUri) {
		baseUri = ZEPHIR_GLOBAL(global_null);
	}



}

/**
 * Set the controller name to use
 *
 * @param string $value
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, setControllerName) {

	zval *controller;

	zephir_fetch_params(0, 1, 0, &controller);



	if (!(Z_TYPE_P(controller) == IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(yaf_request_exception_ce, "Expect a string controller name", "yaf/request_abstract.zep", 414);
		return;
	}
	zephir_update_property_this(this_ptr, SL("controller"), controller TSRMLS_CC);
	RETURN_THISW();

}

PHP_METHOD(Yaf_Request_Abstract, setDispatched) {

	zval *dispatched = NULL;

	zephir_fetch_params(0, 0, 1, &dispatched);

	if (!dispatched) {
		dispatched = ZEPHIR_GLOBAL(global_true);
	}


	zephir_update_property_this(this_ptr, SL("dispatched"), dispatched TSRMLS_CC);

}

/**
 * Set the module name to use
 *
 * @param string $value
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, setModuleName) {

	zval *module;

	zephir_fetch_params(0, 1, 0, &module);



	if (!(Z_TYPE_P(module) == IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(yaf_request_exception_ce, "Expect a string module name", "yaf/request_abstract.zep", 436);
		return;
	}
	zephir_update_property_this(this_ptr, SL("module"), module TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Set an action parameter
 *
 * A $value of null will unset the $key if it exists
 *
 * @param string $key
 * @param mixed $value
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, setParam) {

	zval *_2 = NULL;
	zval *name = NULL, *value = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &value);

	ZEPHIR_SEPARATE_PARAM(name);
	if (!value) {
		value = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(name) == IS_ARRAY) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("params"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_1);
		zephir_add_function_ex(_1, _0, name TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("params"), _1 TSRMLS_CC);
	} else {
		zephir_get_strval(_2, name);
		ZEPHIR_CPY_WRT(name, _2);
		zephir_update_property_array(this_ptr, SL("params"), name, value TSRMLS_CC);
	}
	RETURN_THIS();

}

/**
 * Unset all user parameters
 *
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, clearParams) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("params"), _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Yaf_Request_Abstract, setRequestUri) {

	zval *requestUri = NULL;

	zephir_fetch_params(0, 0, 1, &requestUri);

	if (!requestUri) {
		requestUri = ZEPHIR_GLOBAL(global_null);
	}



}

/**
 * Set flag indicating whether or not request has been dispatched
 *
 * @param boolean $flag
 * @return Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Request_Abstract, setRouted) {

	zval *flag_param = NULL, *_0 = NULL;
	zend_bool flag;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &flag_param);

	if (!flag_param) {
		flag = 1;
	} else {
		flag = zephir_get_boolval(flag_param);
	}


	ZEPHIR_INIT_VAR(_0);
	if (flag) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_BOOL(_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_BOOL(_0, 0);
	}
	zephir_update_property_this(this_ptr, SL("routed"), _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Yaf_Request_Abstract, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("params"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

