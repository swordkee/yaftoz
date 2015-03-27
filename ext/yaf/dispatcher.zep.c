
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/string.h"

ZEPHIR_INIT_CLASS(Yaf_Dispatcher) {

	ZEPHIR_REGISTER_CLASS(Yaf, Dispatcher, yaf, dispatcher, yaf_dispatcher_method_entry, 0);

	/**
	 * Instance of Yaf_Router_Interface
	 * @var Yaf_Router
	 */
	zend_declare_property_null(yaf_dispatcher_ce, SL("_router"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * View object
	 * @var Yaf_View_Interface
	 */
	zend_declare_property_null(yaf_dispatcher_ce, SL("_view"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Instance of Yaf_Request_Abstract
	 * @var Yaf_Request_Abstract
	 */
	zend_declare_property_null(yaf_dispatcher_ce, SL("_request"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * holds the references to the plugins
	 * @var array
	 */
	zend_declare_property_null(yaf_dispatcher_ce, SL("_plugins"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Singleton instance
	 * @var Yaf_Dispatcher
	 */
	zend_declare_property_null(yaf_dispatcher_ce, SL("_instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * Whether or not to enable view.
	 * @var boolean
	 */
	zend_declare_property_bool(yaf_dispatcher_ce, SL("_auto_render"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Whether or not to return the response prior to rendering output while in
	 * {@link dispatch()}; default is to send headers and render output.
	 * @var boolean
	 */
	zend_declare_property_bool(yaf_dispatcher_ce, SL("_returnResponse"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(yaf_dispatcher_ce, SL("_instantly_flush"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_dispatcher_ce, SL("_default_module"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_dispatcher_ce, SL("_default_controller"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_dispatcher_ce, SL("_default_action"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Dispatcher, autoRender) {

	zval *flag;

	zephir_fetch_params(0, 1, 0, &flag);



	if (!(Z_TYPE_P(flag) == IS_BOOL)) {
		RETURN_MEMBER(this_ptr, "_auto_render");
	} else {
		zephir_update_property_this(this_ptr, SL("_auto_render"), flag TSRMLS_CC);
	}

}

/**
 * Set the throwExceptions flag and retrieve current status
 *
 * Set whether exceptions encounted in the dispatch loop should be thrown
 * or caught and trapped in the response object.
 *
 * Default behaviour is to trap them in the response object; call this
 * method to have them thrown.
 *
 * Passing no value will return the current value of the flag; passing a
 * boolean true or false value will set the flag and return the current
 * object instance.
 *
 * @param boolean $flag Defaults to null (return flag state)
 * @return boolean|Yaf_Dispatcher when used as a setter,
 * returns object; as a getter, returns boolean
 */
PHP_METHOD(Yaf_Dispatcher, catchException) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_2 = NULL;
	zval *flag_param = NULL, *_1 = NULL;
	zend_bool flag;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &flag_param);

	if (!flag_param) {
		flag = 0;
	} else {
		flag = zephir_get_boolval(flag_param);
	}


	if (flag != 0) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "catchException", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_0, _1, (flag ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		RETURN_THIS();
	}
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "catchException", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(yaf_g_ce, "get", &_2, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Enforce singleton; disallow cloning
 *
 * @return void
 */
PHP_METHOD(Yaf_Dispatcher, __clone) {



}

/**
 * Constructor
 *
 * Instantiate using {@link getInstance()}; dispatcher is a singleton
 * object.
 *
 * @return void
 */
PHP_METHOD(Yaf_Dispatcher, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_plugins"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Dispatcher, disableView) {


	zephir_update_property_this(this_ptr, SL("_auto_render"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

/**
 * Dispatch an HTTP request to a controller/action.
 *
 * @param Yaf_Request_Abstract|null $request
 * @return void|Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Dispatcher, dispatch) {

	zend_bool _24;
	zephir_fcall_cache_entry *_17 = NULL, *_18 = NULL, *_23 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_12 = NULL, *_30 = NULL;
	HashTable *_3, *_7, *_10, *_15, *_20, *_27;
	HashPosition _2, _6, _9, _14, _19, _26;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request = NULL, *response = NULL, *router = NULL, *plugin = NULL, *e = NULL, *view = NULL, *nested = NULL, *_0 = NULL, *_1, **_4, *_5, **_8, **_11, *_13 = NULL, **_16, **_21, *_22 = NULL, *_25, **_28, *_29 = NULL, *_31 = NULL, *_32, *_33;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &request);

	if (!request) {
		ZEPHIR_CPY_WRT(request, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(request);
	}


	if (Z_TYPE_P(request) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&request, this_ptr, "getrequest", NULL);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrequest", NULL, request);
		zephir_check_call_status();
	}
	if (!(zephir_instance_of_ev(request, yaf_request_abstract_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expect a Yaf_Request_Abstract instance", "yaf/dispatcher.zep", 134);
		return;
	}
	if (zephir_instance_of_ev(request, yaf_request_http_ce TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(response);
		object_init_ex(response, yaf_response_http_ce);
		ZEPHIR_CALL_METHOD(NULL, response, "__construct", NULL);
		zephir_check_call_status();
	} else {
		if (zephir_instance_of_ev(request, yaf_request_simple_ce TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(response);
			object_init_ex(response, yaf_response_cli_ce);
			ZEPHIR_CALL_METHOD(NULL, response, "__construct", NULL);
			zephir_check_call_status();
		}
	}
	ZEPHIR_CALL_METHOD(&router, this_ptr, "getrouter", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, request, "isrouted", NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
		zephir_is_iterable(_1, &_3, &_2, 0, 0, "yaf/dispatcher.zep", 166);
		for (
		  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(plugin, _4);
			ZEPHIR_CALL_METHOD(NULL, plugin, "routerstartup", NULL, request, response);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(NULL, router, "route", NULL, request);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "_fixdefault", NULL, request);
		zephir_check_call_status();
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
		zephir_is_iterable(_5, &_7, &_6, 0, 0, "yaf/dispatcher.zep", 174);
		for (
		  ; zephir_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
		  ; zephir_hash_move_forward_ex(_7, &_6)
		) {
			ZEPHIR_GET_HVALUE(plugin, _8);
			ZEPHIR_CALL_METHOD(NULL, plugin, "routershutdown", NULL, request, response);
			zephir_check_call_status();
		}
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "_fixdefault", NULL, request);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&view, this_ptr, "initview", NULL);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
	zephir_is_iterable(_1, &_10, &_9, 0, 0, "yaf/dispatcher.zep", 184);
	for (
	  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
	  ; zephir_hash_move_forward_ex(_10, &_9)
	) {
		ZEPHIR_GET_HVALUE(plugin, _11);
		ZEPHIR_CALL_METHOD(NULL, plugin, "dispatchloopstartup", NULL, request, response);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_13);
	ZVAL_STRING(_13, "yaf.forward_limit", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&nested, yaf_g_ce, "iniget", &_12, _13);
	zephir_check_temp_parameter(_13);
	zephir_check_call_status();

	/* try_start_1: */

		do {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
			zephir_is_iterable(_1, &_15, &_14, 0, 0, "yaf/dispatcher.zep", 200);
			for (
			  ; zephir_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
			  ; zephir_hash_move_forward_ex(_15, &_14)
			) {
				ZEPHIR_GET_HVALUE(plugin, _16);
				ZEPHIR_CALL_METHOD(NULL, plugin, "predispatch", NULL, request, response);
				zephir_check_call_status_or_jump(try_end_1);
			}
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "handle", &_17, request, response, view);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "_fixdefault", &_18, request);
			zephir_check_call_status_or_jump(try_end_1);
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
			zephir_is_iterable(_5, &_20, &_19, 0, 0, "yaf/dispatcher.zep", 208);
			for (
			  ; zephir_hash_get_current_data_ex(_20, (void**) &_21, &_19) == SUCCESS
			  ; zephir_hash_move_forward_ex(_20, &_19)
			) {
				ZEPHIR_GET_HVALUE(plugin, _21);
				ZEPHIR_CALL_METHOD(NULL, plugin, "postdispatch", NULL, request, response);
				zephir_check_call_status_or_jump(try_end_1);
			}
			ZEPHIR_SEPARATE(nested);
			zephir_decrement(nested);
			ZEPHIR_CALL_METHOD(&_22, request, "isdispatched", &_23);
			zephir_check_call_status_or_jump(try_end_1);
			_24 = !zephir_is_true(_22);
			if (_24) {
				_24 = ZEPHIR_GT_LONG(nested, 0);
			}
		} while (_24);
		_25 = zephir_fetch_nproperty_this(this_ptr, SL("_plugins"), PH_NOISY_CC);
		zephir_is_iterable(_25, &_27, &_26, 0, 0, "yaf/dispatcher.zep", 216);
		for (
		  ; zephir_hash_get_current_data_ex(_27, (void**) &_28, &_26) == SUCCESS
		  ; zephir_hash_move_forward_ex(_27, &_26)
		) {
			ZEPHIR_GET_HVALUE(plugin, _28);
			ZEPHIR_CALL_METHOD(NULL, plugin, "dispatchloopshutdown", NULL, request, response);
			zephir_check_call_status_or_jump(try_end_1);
		}

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_22, this_ptr, "catchexception", NULL);
			zephir_check_call_status();
			if (zephir_is_true(_22)) {
				ZEPHIR_CALL_METHOD(&_29, request, "getmodulename", NULL);
				zephir_check_call_status();
				_1 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
				if (!ZEPHIR_IS_EQUAL(_29, _1)) {
					ZEPHIR_INIT_NVAR(_13);
					ZVAL_STRING(_13, "Error", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _13);
					zephir_check_temp_parameter(_13);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_13);
					ZVAL_STRING(_13, "error", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _13);
					zephir_check_temp_parameter(_13);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_13);
					ZVAL_STRING(_13, "exception", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, _13, e);
					zephir_check_temp_parameter(_13);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, request, "setexception", NULL, e);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "handle", &_17, request, response, view);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, response, "response", NULL);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, response, "clearbody", NULL);
					zephir_check_call_status();
					RETURN_MM_BOOL(0);
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
				ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, _5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_13);
				ZVAL_STRING(_13, "Error", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _13);
				zephir_check_temp_parameter(_13);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_13);
				ZVAL_STRING(_13, "error", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _13);
				zephir_check_temp_parameter(_13);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_13);
				ZVAL_STRING(_13, "exception", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_METHOD(NULL, request, "setparam", NULL, _13, e);
				zephir_check_temp_parameter(_13);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, request, "setexception", NULL, e);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "handle", &_17, request, response, view);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, response, "response", NULL);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, response, "clearbody", NULL);
				zephir_check_call_status();
				RETURN_MM_BOOL(0);
			} else {
				ZEPHIR_CALL_METHOD(&_29, this_ptr, "throwexception", NULL);
				zephir_check_call_status();
				if (zephir_is_true(_29)) {
					zephir_throw_exception_debug(e, "yaf/dispatcher.zep", 260 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				} else {
					ZEPHIR_CALL_METHOD(&_31, e, "getmessage", NULL);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_13);
					ZVAL_LONG(_13, 256);
					ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_30, _31, _13);
					zephir_check_call_status();
				}
			}
		}
	}
	_24 = ZEPHIR_IS_LONG(nested, 0);
	if (_24) {
		ZEPHIR_CALL_METHOD(&_22, request, "isdispatched", &_23);
		zephir_check_call_status();
		_24 = !zephir_is_true(_22);
	}
	if (_24) {
		ZEPHIR_INIT_NVAR(_13);
		object_init_ex(_13, yaf_exception_dispatchfailed_ce);
		ZEPHIR_INIT_VAR(_32);
		ZVAL_STRING(_32, "yaf.forward_limit", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_29, yaf_g_ce, "iniget", &_12, _32);
		zephir_check_temp_parameter(_32);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_33);
		ZEPHIR_CONCAT_SVS(_33, "The max dispatch nesting ", _29, " was reached");
		ZEPHIR_CALL_METHOD(NULL, _13, "__construct", NULL, _33);
		zephir_check_call_status();
		zephir_throw_exception_debug(_13, "yaf/dispatcher.zep", 268 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_22, this_ptr, "returnresponse", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE(_22)) {
		ZEPHIR_CALL_METHOD(NULL, response, "response", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, response, "clearbody", NULL);
		zephir_check_call_status();
	}
	RETURN_CCTOR(response);

}

PHP_METHOD(Yaf_Dispatcher, handle) {

	zend_bool _10;
	zval *_8 = NULL, *_13;
	zend_class_entry *_6, *_12;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	zval *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *response, *view, *app = NULL, *appDir = NULL, *module = NULL, *controllerName = NULL, *className = NULL, *controller, *viewDir = NULL, *templateDir = NULL, *action = NULL, *actionMethod = NULL, *methodParams = NULL, *ret = NULL, *actionName = NULL, *actionController, *_0 = NULL, *_2 = NULL, *_4 = NULL, *_5 = NULL, *_7, *_9 = NULL, *_11 = NULL, *_14, *_15, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &request, &response, &view);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_BOOL(_0, 1);
	ZEPHIR_CALL_METHOD(NULL, request, "setdispatched", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&app, this_ptr, "getapplication", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&appDir, app, "getappdirectory", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(appDir, "")) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, yaf_exception_startuperror_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SSS(_1, "Yaf_Dispatcher requires ", "Yaf_Application(which set the application.directory) ", "to be initialized first.");
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "yaf/dispatcher.zep", 291 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&module, request, "getmodulename", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(module)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_dispatchfailed_ce, "Unexcepted an empty module name", "yaf/dispatcher.zep", 296);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_2, yaf_application_ce, "ismodulename", &_3, module);
	zephir_check_call_status();
	if (!(zephir_is_true(_2))) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, yaf_exception_loadfailed_module_ce);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_SV(_4, "There is no module ", module);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "yaf/dispatcher.zep", 300 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&controllerName, request, "getcontrollername", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(controllerName)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_dispatchfailed_ce, "Unexcepted an empty controller name", "yaf/dispatcher.zep", 305);
		return;
	}
	ZEPHIR_CALL_METHOD(&className, this_ptr, "getcontroller", NULL, appDir, module, controllerName);
	zephir_check_call_status();
	if (!(zephir_is_true(className))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(controller);
	zephir_fetch_safe_class(_5, className);
	_6 = zend_fetch_class(Z_STRVAL_P(_5), Z_STRLEN_P(_5), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(controller, _6);
	if (zephir_has_constructor(controller TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, controller, "__construct", NULL, request, response, view);
		zephir_check_call_status();
	}
	if (!(zephir_instance_of_ev(controller, yaf_controller_abstract_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Controller must be an instance of Yaf_Controller_Abstract", "yaf/dispatcher.zep", 316);
		return;
	}
	ZEPHIR_CALL_METHOD(&viewDir, view, "getscriptpath", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(viewDir)) {
		ZEPHIR_INIT_VAR(templateDir);
		ZVAL_STRING(templateDir, "", 1);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(templateDir);
		if (ZEPHIR_IS_EQUAL(_7, module)) {
			ZEPHIR_CONCAT_VSS(templateDir, appDir, "/", "views");
		} else {
			ZEPHIR_CONCAT_VSSSVSS(templateDir, appDir, "/", "modules", "/", module, "/", "views");
		}
		ZEPHIR_CALL_METHOD(NULL, view, "setscriptpath", NULL, templateDir);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&action, request, "getactionname", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(actionMethod);
	ZEPHIR_CONCAT_VS(actionMethod, action, "Action");
	if ((zephir_method_exists(controller, actionMethod TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD(&methodParams, this_ptr, "getactionparams", NULL, className, actionMethod);
		zephir_check_call_status();
		if (Z_TYPE_P(methodParams) == IS_NULL) {
			ZEPHIR_INIT_VAR(ret);
			ZEPHIR_INIT_VAR(_8);
			array_init_size(_8, 3);
			zephir_array_fast_append(_8, controller);
			zephir_array_fast_append(_8, actionMethod);
			ZEPHIR_CALL_USER_FUNC(ret, _8);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(ret);
			ZEPHIR_INIT_NVAR(_8);
			array_init_size(_8, 3);
			zephir_array_fast_append(_8, controller);
			zephir_array_fast_append(_8, actionMethod);
			ZEPHIR_CALL_METHOD(&_9, this_ptr, "prepareactionparams", NULL, request, methodParams);
			zephir_check_call_status();
			ZEPHIR_CALL_USER_FUNC_ARRAY(ret, _8, _9);
			zephir_check_call_status();
		}
		_10 = Z_TYPE_P(ret) == IS_BOOL;
		if (_10) {
			_10 = ZEPHIR_IS_FALSE(ret);
		}
		if (_10) {
			RETURN_MM_BOOL(1);
		}
	} else {
		ZEPHIR_CALL_METHOD(&actionName, this_ptr, "getaction", NULL, appDir, controller, action, module);
		zephir_check_call_status();
		if (Z_TYPE_P(actionName) != IS_NULL) {
			ZEPHIR_INIT_VAR(actionController);
			zephir_fetch_safe_class(_11, actionName);
			_12 = zend_fetch_class(Z_STRVAL_P(_11), Z_STRLEN_P(_11), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
			object_init_ex(actionController, _12);
			if (zephir_has_constructor(actionController TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, actionController, "__construct", NULL, request, response, view);
				zephir_check_call_status();
			}
			if (!(zephir_instance_of_ev(actionController, yaf_action_abstract_ce TSRMLS_CC))) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Action must be an instance of Yaf_Action_Abstract", "yaf/dispatcher.zep", 356);
				return;
			}
			ZEPHIR_CALL_METHOD(NULL, actionController, "setcontroller", NULL, controller);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(actionMethod);
			ZVAL_STRING(actionMethod, "execute", 1);
			if ((zephir_method_exists(actionController, actionMethod TSRMLS_CC)  == SUCCESS)) {
				ZEPHIR_INIT_NVAR(_0);
				zephir_get_class(_0, actionController, 0 TSRMLS_CC);
				ZEPHIR_CALL_METHOD(&methodParams, this_ptr, "getactionparams", NULL, _0, actionMethod);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(ret);
				ZVAL_NULL(ret);
				if (Z_TYPE_P(methodParams) == IS_NULL) {
					ZEPHIR_INIT_NVAR(ret);
					ZEPHIR_INIT_NVAR(_8);
					array_init_size(_8, 3);
					zephir_array_fast_append(_8, actionController);
					zephir_array_fast_append(_8, actionMethod);
					ZEPHIR_CALL_USER_FUNC(ret, _8);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(ret);
					ZEPHIR_INIT_VAR(_13);
					array_init_size(_13, 3);
					zephir_array_fast_append(_13, actionController);
					zephir_array_fast_append(_13, actionMethod);
					ZEPHIR_CALL_METHOD(&_9, this_ptr, "prepareactionparams", NULL, request, methodParams);
					zephir_check_call_status();
					ZEPHIR_CALL_USER_FUNC_ARRAY(ret, _13, _9);
					zephir_check_call_status();
				}
				_10 = Z_TYPE_P(ret) == IS_BOOL;
				if (_10) {
					_10 = ZEPHIR_IS_FALSE(ret);
				}
				if (_10) {
					RETURN_MM_BOOL(1);
				}
			} else {
				ZEPHIR_INIT_VAR(_14);
				object_init_ex(_14, yaf_exception_loadfailed_action_ce);
				ZEPHIR_INIT_VAR(_15);
				zephir_get_class(_15, controller, 0 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_SVSVS(_4, "There is no method ", actionMethod, " in ", _15, "::actions");
				ZEPHIR_CALL_METHOD(NULL, _14, "__construct", NULL, _4);
				zephir_check_call_status();
				zephir_throw_exception_debug(_14, "yaf/dispatcher.zep", 378 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			RETURN_MM_BOOL(0);
		}
	}
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_auto_render"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE(_7)) {
		_16 = zephir_fetch_nproperty_this(this_ptr, SL("_instantly_flush"), PH_NOISY_CC);
		if (ZEPHIR_IS_TRUE(_16)) {
			ZEPHIR_CALL_METHOD(NULL, controller, "display", NULL, action);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&ret, controller, "render", NULL, action);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, response, "appendbody", NULL, ret);
			zephir_check_call_status();
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Dispatcher, getAction) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_7 = NULL, *_13 = NULL;
	zval *appDir, *controller, *action, *module, *nameSeparator = NULL, *actionPath, *actionUpper = NULL, *tmpClassname = NULL, *actionDir = NULL, *_1 = NULL, *_2, *_3, *_4, *_5, *_6 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_12, *_14 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &appDir, &controller, &action, &module);



	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yaf.name_separator", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&nameSeparator, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, controller, SL("actions"), PH_NOISY_CC);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEPHIR_OBS_VAR(_3);
		zephir_read_property(&_3, controller, SL("actions"), PH_NOISY_CC);
		if (zephir_array_isset(_3, action)) {
			ZEPHIR_OBS_VAR(_4);
			zephir_read_property(&_4, controller, SL("actions"), PH_NOISY_CC);
			zephir_array_fetch(&_5, _4, action, PH_NOISY | PH_READONLY, "yaf/dispatcher.zep", 406 TSRMLS_CC);
			ZEPHIR_INIT_VAR(actionPath);
			ZEPHIR_CONCAT_VSV(actionPath, appDir, "/", _5);
			ZEPHIR_CALL_CE_STATIC(&_6, yaf_loader_ce, "import", &_7, actionPath);
			zephir_check_call_status();
			if (zephir_is_true(_6)) {
				ZEPHIR_CALL_METHOD(&actionUpper, this_ptr, "_formatname", NULL, action);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_1);
				ZVAL_STRING(_1, "yaf.name_suffix", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_CE_STATIC(&_8, yaf_g_ce, "iniget", &_0, _1);
				zephir_check_temp_parameter(_1);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(tmpClassname);
				if (ZEPHIR_IS_TRUE(_8)) {
					ZEPHIR_CONCAT_VVS(tmpClassname, actionUpper, nameSeparator, "Action");
				} else {
					ZEPHIR_CONCAT_SVV(tmpClassname, "Action", nameSeparator, actionUpper);
				}
				if (!(zephir_class_exists(tmpClassname, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_1);
					object_init_ex(_1, yaf_exception_loadfailed_action_ce);
					ZEPHIR_INIT_VAR(_9);
					ZEPHIR_CONCAT_SVSV(_9, "Could not find action ", tmpClassname, " in ", actionPath);
					ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _9);
					zephir_check_call_status();
					zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 418 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				RETURN_CCTOR(tmpClassname);
			} else {
				ZEPHIR_INIT_NVAR(_1);
				object_init_ex(_1, yaf_exception_loadfailed_action_ce);
				ZEPHIR_INIT_LNVAR(_9);
				ZEPHIR_CONCAT_SV(_9, "Could not find action script ", actionPath);
				ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _9);
				zephir_check_call_status();
				zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 423 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_NVAR(_1);
			object_init_ex(_1, yaf_exception_loadfailed_action_ce);
			ZEPHIR_INIT_VAR(_10);
			zephir_get_class(_10, controller, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_11);
			ZEPHIR_CONCAT_SVSVS(_11, "There is no method ", action, "Action in ", _10, "::actions");
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _11);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 426 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "yaf.st_compatible", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_6, yaf_g_ce, "iniget", &_0, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		if (zephir_is_true(_6)) {
			ZEPHIR_INIT_VAR(actionDir);
			ZVAL_STRING(actionDir, "", 1);
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(actionDir);
			if (ZEPHIR_IS_EQUAL(_12, module)) {
				ZEPHIR_CONCAT_VSS(actionDir, appDir, "/", "actions");
			} else {
				ZEPHIR_CONCAT_VSSSVSS(actionDir, appDir, "/", "modules", "/", module, "/", "actions");
			}
			ZEPHIR_CALL_METHOD(&actionUpper, this_ptr, "_formatname", NULL, action);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "yaf.name_suffix", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_8, yaf_g_ce, "iniget", &_0, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(tmpClassname);
			if (ZEPHIR_IS_TRUE(_8)) {
				ZEPHIR_CONCAT_VVS(tmpClassname, actionUpper, nameSeparator, "Action");
			} else {
				ZEPHIR_CONCAT_SVV(tmpClassname, "Action", nameSeparator, actionUpper);
			}
			if (!(zephir_class_exists(tmpClassname, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC))) {
				ZEPHIR_CALL_CE_STATIC(&_8, yaf_loader_ce, "getinstance", &_13);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_14, _8, "internal_autoload", NULL, actionUpper, actionDir);
				zephir_check_call_status();
				if (!(zephir_is_true(_14))) {
					ZEPHIR_INIT_NVAR(_1);
					object_init_ex(_1, yaf_exception_loadfailed_action_ce);
					ZEPHIR_INIT_LNVAR(_11);
					ZEPHIR_CONCAT_SV(_11, "Could not find action script ", actionDir);
					ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _11);
					zephir_check_call_status();
					zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 449 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			if (!(zephir_class_exists(tmpClassname, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_1);
				object_init_ex(_1, yaf_exception_loadfailed_loadfailed_ce);
				ZEPHIR_INIT_LNVAR(_9);
				ZEPHIR_CONCAT_SVSV(_9, "Could not find class ", tmpClassname, " in action script ", actionDir);
				ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _9);
				zephir_check_call_status();
				zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 454 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_CCTOR(tmpClassname);
		} else {
			ZEPHIR_INIT_NVAR(_1);
			object_init_ex(_1, yaf_exception_loadfailed_action_ce);
			ZEPHIR_INIT_NVAR(_10);
			zephir_get_class(_10, controller, 0 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_11);
			ZEPHIR_CONCAT_SVSV(_11, "There is no method ", action, "Action in ", _10);
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _11);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1, "yaf/dispatcher.zep", 459 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_MM_NULL();

}

PHP_METHOD(Yaf_Dispatcher, prepareActionParams) {

	zephir_fcall_cache_entry *_8 = NULL;
	HashTable *_1;
	HashPosition _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *methodParams, *data, *params = NULL, *param = NULL, *name = NULL, **_2, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &request, &methodParams);



	ZEPHIR_INIT_VAR(data);
	array_init(data);
	ZEPHIR_CALL_METHOD(&params, request, "getparams", NULL);
	zephir_check_call_status();
	zephir_is_iterable(methodParams, &_1, &_0, 0, 0, "yaf/dispatcher.zep", 489);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(param, _2);
		ZEPHIR_CALL_METHOD(&name, param, "getname", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_3, param, "isoptional", NULL);
		zephir_check_call_status();
		ZEPHIR_OBS_NVAR(_4);
		zephir_array_fetch(&_4, params, name, PH_NOISY, "yaf/dispatcher.zep", 481 TSRMLS_CC);
		if (zephir_is_true(_3)) {
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_OBS_NVAR(_6);
			zephir_array_fetch(&_6, params, name, PH_NOISY, "yaf/dispatcher.zep", 480 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_6))) {
				ZEPHIR_OBS_NVAR(_5);
				zephir_array_fetch(&_5, params, name, PH_NOISY, "yaf/dispatcher.zep", 480 TSRMLS_CC);
			} else {
				ZEPHIR_CALL_METHOD(&_5, param, "getdefaultvalue", NULL);
				zephir_check_call_status();
			}
			zephir_array_update_zval(&data, name, &_5, PH_COPY | PH_SEPARATE);
		} else if (ZEPHIR_IS_EMPTY(_4)) {
			ZEPHIR_INIT_NVAR(_7);
			object_init_ex(_7, yaf_exception_ce);
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_CONCAT_SVS(_5, "Parameter: ", name, " cannot be empty");
			ZEPHIR_CALL_METHOD(NULL, _7, "__construct", &_8, _5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_7, "yaf/dispatcher.zep", 483 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			zephir_array_fetch(&_9, params, name, PH_NOISY | PH_READONLY, "yaf/dispatcher.zep", 485 TSRMLS_CC);
			zephir_array_update_zval(&data, name, &_9, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(data);

}

PHP_METHOD(Yaf_Dispatcher, getActionParams) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *className, *action, *funcRef, *paramsRef = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &className, &action);



	ZEPHIR_INIT_VAR(funcRef);
	object_init_ex(funcRef, zephir_get_internal_ce(SS("reflectionmethod") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, funcRef, "__construct", NULL, className, action);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&paramsRef, funcRef, "getparameters", NULL);
	zephir_check_call_status();
	RETURN_CCTOR(paramsRef);

}

PHP_METHOD(Yaf_Dispatcher, getController) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL, *_11 = NULL;
	zval *appDir, *module, *controller, *controllerDir = NULL, *nameSeparator = NULL, *classname, *_0, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_6 = NULL, *_7, _8, _9, *_10 = NULL, *_12, *_13 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &appDir, &module, &controller);



	ZEPHIR_INIT_VAR(controllerDir);
	ZVAL_STRING(controllerDir, "", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(controllerDir);
	if (ZEPHIR_IS_EQUAL(_0, module)) {
		ZEPHIR_CONCAT_VSS(controllerDir, appDir, "/", "controllers");
	} else {
		ZEPHIR_CONCAT_VSSSVSS(controllerDir, appDir, "/", "modules", "/", module, "/", "controllers");
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "yaf.name_separator", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&nameSeparator, yaf_g_ce, "iniget", &_1, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "yaf.name_suffix", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "iniget", &_1, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(classname);
	if (ZEPHIR_IS_TRUE(_3)) {
		ZEPHIR_CONCAT_VVS(classname, controller, nameSeparator, "Controller");
	} else {
		ZEPHIR_CONCAT_SVV(classname, "Controller", nameSeparator, controller);
	}
	if (!(zephir_class_exists(classname, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC))) {
		ZEPHIR_CALL_CE_STATIC(&_4, yaf_loader_ce, "getinstance", &_5);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_6, _4, "internal_autoload", NULL, controller, controllerDir);
		zephir_check_call_status();
		if (!(zephir_is_true(_6))) {
			ZEPHIR_INIT_NVAR(_2);
			object_init_ex(_2, yaf_exception_loadfailed_controller_ce);
			ZEPHIR_INIT_VAR(_7);
			ZEPHIR_SINIT_VAR(_8);
			ZVAL_STRING(&_8, "_", 0);
			ZEPHIR_SINIT_VAR(_9);
			ZVAL_STRING(&_9, "/", 0);
			zephir_fast_str_replace(_7, &_8, &_9, controller TSRMLS_CC);
			ZEPHIR_INIT_VAR(_12);
			ZVAL_STRING(_12, "ext", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_10, yaf_g_ce, "get", &_11, _12);
			zephir_check_temp_parameter(_12);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_13);
			ZEPHIR_CONCAT_SVSVSV(_13, "Could not find controller script ", controllerDir, "/", _7, ".", _10);
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, _13);
			zephir_check_call_status();
			zephir_throw_exception_debug(_2, "yaf/dispatcher.zep", 524 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (!(zephir_class_exists(classname, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(_2);
		object_init_ex(_2, yaf_exception_loadfailed_loadfailed_ce);
		ZEPHIR_INIT_LNVAR(_13);
		ZEPHIR_CONCAT_SVSV(_13, "Could not find class ", classname, " in controller script ", controllerDir);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, _13);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "yaf/dispatcher.zep", 529 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(classname);

}

PHP_METHOD(Yaf_Dispatcher, _fixDefault) {

	zend_bool _0, _3, _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *module = NULL, *controller = NULL, *action = NULL, *_1, *_2 = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_CALL_METHOD(&module, request, "getmodulename", NULL);
	zephir_check_call_status();
	_0 = ZEPHIR_IS_EMPTY(module);
	if (!(_0)) {
		_0 = !(Z_TYPE_P(module) == IS_STRING);
	}
	if (_0) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_default_module"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, _1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(_2);
		zephir_ucfirst(_2, module);
		ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, _2);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&controller, request, "getcontrollername", NULL);
	zephir_check_call_status();
	_3 = ZEPHIR_IS_EMPTY(controller);
	if (!(_3)) {
		_3 = !(Z_TYPE_P(controller) == IS_STRING);
	}
	if (_3) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_default_controller"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _1);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "_formatname", NULL, controller);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, _4);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&action, request, "getactionname", NULL);
	zephir_check_call_status();
	_5 = ZEPHIR_IS_EMPTY(action);
	if (!(_5)) {
		_5 = !(Z_TYPE_P(action) == IS_STRING);
	}
	if (_5) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_default_action"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_2);
		zephir_fast_strtolower(_2, action);
		ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, _2);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Dispatcher, _formatName) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL;
	HashTable *_2, *_13;
	HashPosition _1, _12;
	zend_bool _0;
	zval *unformatted, *segments = NULL, *segment = NULL, *key = NULL, **_3, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_8 = NULL, _10 = zval_used_for_init, _11 = zval_used_for_init, **_14;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &unformatted);



	ZEPHIR_INIT_VAR(segments);
	zephir_fast_explode_str(segments, SL("\\"), unformatted, LONG_MAX TSRMLS_CC);
	_0 = zephir_is_true(segments);
	if (_0) {
		_0 = zephir_fast_count_int(segments TSRMLS_CC) > 1;
	}
	if (_0) {
		zephir_is_iterable(segments, &_2, &_1, 1, 0, "yaf/dispatcher.zep", 575);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HMKEY(key, _2, _1);
			ZEPHIR_GET_HVALUE(segment, _3);
			ZEPHIR_INIT_NVAR(_4);
			zephir_fast_strtolower(_4, segment);
			ZEPHIR_INIT_NVAR(_5);
			ZVAL_STRING(_5, "/[^a-z0-9 ]/", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_6);
			ZVAL_STRING(_6, "", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_FUNCTION(&segment, "preg_replace", &_7, _5, _6, _4);
			zephir_check_temp_parameter(_5);
			zephir_check_temp_parameter(_6);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_5);
			ZEPHIR_CALL_FUNCTION(&_8, "ucwords", &_9, segment);
			zephir_check_call_status();
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_STRING(&_10, " ", 0);
			ZEPHIR_SINIT_NVAR(_11);
			ZVAL_STRING(&_11, "", 0);
			zephir_fast_str_replace(_5, &_10, &_11, _8 TSRMLS_CC);
			zephir_array_update_zval(&segments, key, &_5, PH_COPY | PH_SEPARATE);
		}
		zephir_fast_join_str(return_value, SL("\\"), segments TSRMLS_CC);
		RETURN_MM();
	}
	ZEPHIR_INIT_NVAR(segments);
	zephir_fast_explode_str(segments, SL("_"), unformatted, LONG_MAX TSRMLS_CC);
	if (zephir_is_true(segments)) {
		zephir_is_iterable(segments, &_13, &_12, 1, 0, "yaf/dispatcher.zep", 586);
		for (
		  ; zephir_hash_get_current_data_ex(_13, (void**) &_14, &_12) == SUCCESS
		  ; zephir_hash_move_forward_ex(_13, &_12)
		) {
			ZEPHIR_GET_HMKEY(key, _13, _12);
			ZEPHIR_GET_HVALUE(segment, _14);
			ZEPHIR_INIT_NVAR(_4);
			zephir_fast_strtolower(_4, segment);
			ZEPHIR_INIT_NVAR(_5);
			ZVAL_STRING(_5, "/[^a-z0-9 ]/", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_6);
			ZVAL_STRING(_6, "", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_FUNCTION(&segment, "preg_replace", &_7, _5, _6, _4);
			zephir_check_temp_parameter(_5);
			zephir_check_temp_parameter(_6);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_5);
			ZEPHIR_CALL_FUNCTION(&_8, "ucwords", &_9, segment);
			zephir_check_call_status();
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_STRING(&_10, " ", 0);
			ZEPHIR_SINIT_NVAR(_11);
			ZVAL_STRING(&_11, "", 0);
			zephir_fast_str_replace(_5, &_10, &_11, _8 TSRMLS_CC);
			zephir_array_update_zval(&segments, key, &_5, PH_COPY | PH_SEPARATE);
		}
		zephir_fast_join_str(return_value, SL("_"), segments TSRMLS_CC);
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Dispatcher, enableView) {


	zephir_update_property_this(this_ptr, SL("_auto_render"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

PHP_METHOD(Yaf_Dispatcher, flushInstantly) {

	zval *flag;

	zephir_fetch_params(0, 1, 0, &flag);



	if (!(Z_TYPE_P(flag) == IS_BOOL)) {
		RETURN_MEMBER(this_ptr, "_instantly_flush");
	} else {
		zephir_update_property_this(this_ptr, SL("_instantly_flush"), flag TSRMLS_CC);
	}
	RETURN_THISW();

}

/**
 * returns the application
 *
 * @return Yaf_Application
 */
PHP_METHOD(Yaf_Dispatcher, getApplication) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(yaf_application_ce, "app", &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Singleton instance
 *
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, getInstance) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_2, *_3 = NULL, *_5, *_6 = NULL, *_7, *_8 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(yaf_dispatcher_ce, SL("_instance") TSRMLS_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, yaf_dispatcher_ce);
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
		zephir_check_call_status();
		zephir_update_static_property_ce(yaf_dispatcher_ce, SL("_instance"), &_1 TSRMLS_CC);
		_2 = zephir_fetch_static_property_ce(yaf_dispatcher_ce, SL("_instance") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "default_action", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "get", &_4, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _2, "setdefaultaction", NULL, _3);
		zephir_check_call_status();
		_5 = zephir_fetch_static_property_ce(yaf_dispatcher_ce, SL("_instance") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "default_controller", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_6, yaf_g_ce, "get", &_4, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _5, "setdefaultcontroller", NULL, _6);
		zephir_check_call_status();
		_7 = zephir_fetch_static_property_ce(yaf_dispatcher_ce, SL("_instance") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "default_module", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_8, yaf_g_ce, "get", &_4, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _7, "setdefaultmodule", NULL, _8);
		zephir_check_call_status();
	}
	_2 = zephir_fetch_static_property_ce(yaf_dispatcher_ce, SL("_instance") TSRMLS_CC);
	RETURN_CTOR(_2);

}

/**
 * Return the request object.
 *
 * @return null|Yaf_Request_Abstract
 */
PHP_METHOD(Yaf_Dispatcher, getRequest) {


	RETURN_MEMBER(this_ptr, "_request");

}

/**
 * Return the router object.
 * @return Yaf_Router
 */
PHP_METHOD(Yaf_Dispatcher, getRouter) {


	RETURN_MEMBER(this_ptr, "_router");

}

PHP_METHOD(Yaf_Dispatcher, initView) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *templates_dir = NULL, *options = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &templates_dir, &options);

	if (!templates_dir) {
		templates_dir = ZEPHIR_GLOBAL(global_null);
	}
	if (!options) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_view"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, yaf_view_simple_ce);
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, templates_dir, options);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_view"), _1 TSRMLS_CC);
	}
	RETURN_MM_MEMBER(this_ptr, "_view");

}

/**
 * Register a plugin.
 *
 * @param  Yaf_Plugin_Abstract $plugin
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, registerPlugin) {

	zval *plugin;

	zephir_fetch_params(0, 1, 0, &plugin);



	zephir_update_property_array_append(this_ptr, SL("_plugins"), plugin TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Set whether {@link dispatch()} should return the response without first
 * rendering output. By default, output is rendered and dispatch() returns
 * nothing.
 *
 * @param boolean $flag
 * @return boolean|Yaf_Dispatcher Used as a setter,
 * returns object; as a getter, returns boolean
 */
PHP_METHOD(Yaf_Dispatcher, returnResponse) {

	zval *flag_param = NULL;
	zend_bool flag;

	zephir_fetch_params(0, 0, 1, &flag_param);

	if (!flag_param) {
		flag = 0;
	} else {
		flag = zephir_get_boolval(flag_param);
	}


	if (flag == 1) {
		zephir_update_property_this(this_ptr, SL("_returnResponse"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		RETURN_THISW();
	} else if (flag == 0) {
		zephir_update_property_this(this_ptr, SL("_returnResponse"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		RETURN_THISW();
	}
	RETURN_MEMBER(this_ptr, "_returnResponse");

}

/**
 * Set the default action
 *
 * @param string $action
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, setDefaultAction) {

	zval *action_param = NULL;
	zval *action = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &action_param);

	zephir_get_strval(action, action_param);


	zephir_get_strval(_0, action);
	zephir_update_property_this(this_ptr, SL("_default_action"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set the default controller
 *
 * @param string $controller
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, setDefaultController) {

	zval *controller_param = NULL, *_0;
	zval *controller = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &controller_param);

	zephir_get_strval(controller, controller_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_get_strval(_1, controller);
	zephir_ucfirst(_0, _1);
	zephir_update_property_this(this_ptr, SL("_default_controller"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set the default module name
 *
 * @param string $module
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, setDefaultModule) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *module_param = NULL, *_0 = NULL, *_3, *_4;
	zval *module = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &module_param);

	zephir_get_strval(module, module_param);


	ZEPHIR_CALL_CE_STATIC(&_0, yaf_application_ce, "ismodulename", &_1, module);
	zephir_check_call_status();
	_2 = zephir_is_true(_0);
	if (!(_2)) {
		ZEPHIR_INIT_VAR(_3);
		zephir_fast_strtolower(_3, module);
		_2 = ZEPHIR_IS_STRING(_3, "index");
	}
	if (_2) {
		ZEPHIR_INIT_VAR(_4);
		zephir_get_strval(_5, module);
		zephir_ucfirst(_4, _5);
		zephir_update_property_this(this_ptr, SL("_default_module"), _4 TSRMLS_CC);
	}
	RETURN_THIS();

}

PHP_METHOD(Yaf_Dispatcher, setErrorHandler) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *callback, *error_types = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &callback, &error_types);

	if (!error_types) {
		ZEPHIR_INIT_VAR(error_types);
		ZVAL_STRING(error_types, "E_ALL", 1);
	}


	ZEPHIR_CALL_FUNCTION(NULL, "set_error_handler", &_0, callback, error_types);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the request object.
 * @param Yaf_Request_Abstract $request
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, setRequest) {

	zval *request;

	zephir_fetch_params(0, 1, 0, &request);



	zephir_update_property_this(this_ptr, SL("_request"), request TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Set the view object.
 *
 * @param Yaf_View_Interface $view
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Dispatcher, setView) {

	zval *view;

	zephir_fetch_params(0, 1, 0, &view);



	zephir_update_property_this(this_ptr, SL("_view"), view TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Enforce singleton; disallow serialization
 *
 * @return void
 */
PHP_METHOD(Yaf_Dispatcher, __sleep) {



}

/**
 * Set the throwExceptions flag and retrieve current status
 *
 * Set whether exceptions encounted in the dispatch loop should be thrown
 * or caught and trapped in the response object.
 *
 * Default behaviour is to trap them in the response object; call this
 * method to have them thrown.
 *
 * Passing no value will return the current value of the flag; passing a
 * boolean true or false value will set the flag and return the current
 * object instance.
 *
 * @param boolean $flag Defaults to null (return flag state)
 * @return boolean|Yaf_Dispatcher Used as a setter,
 *     returns object; as a getter, returns boolean
 */
PHP_METHOD(Yaf_Dispatcher, throwException) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_2 = NULL;
	zval *flag_param = NULL, *_1 = NULL;
	zend_bool flag;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &flag_param);

	if (!flag_param) {
		flag = 0;
	} else {
		flag = zephir_get_boolval(flag_param);
	}


	if (flag != 0) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "throwException", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_0, _1, (flag ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		RETURN_THIS();
	}
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "throwException", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(yaf_g_ce, "get", &_2, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Enforce singleton; disallow serialization
 *
 * @return void
 */
PHP_METHOD(Yaf_Dispatcher, __wakeup) {



}

