
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/hash.h"

ZEPHIR_INIT_CLASS(Yaf_Application) {

	ZEPHIR_REGISTER_CLASS(Yaf, Application, yaf, application, yaf_application_method_entry, 0);

	/**
	 * @var Yaf_Config_Abstract
	 */
	zend_declare_property_null(yaf_application_ce, SL("_config"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 *
	 * @var Yaf_Dispatcher
	 */
	zend_declare_property_null(yaf_application_ce, SL("_dispatcher"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 *
	 * @var Yaf_Application
	 */
	zend_declare_property_null(yaf_application_ce, SL("_app"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(yaf_application_ce, SL("_modules"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(yaf_application_ce, SL("_running"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_application_ce, SL("_environ"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_application_ce, SL("_options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(yaf_application_ce, SL("_errno"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_application_ce, SL("_errmsg"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Application, __construct) {

	zval *_23 = NULL, *_24;
	zend_bool _6, _7, _11, _18, _20;
	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_9 = NULL, *_14 = NULL, *_27 = NULL, *_28 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *config = NULL, *env = NULL, *_0, *_1, *app = NULL, *request, *loader = NULL, *tmpNamespace, *_2, *_3 = NULL, *_5 = NULL, *_8 = NULL, *_10, *_12, *_13, *_15 = NULL, *_16, *_17, *_19, *_21, *_22, *_25, *_26;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &config, &env);

	ZEPHIR_SEPARATE_PARAM(config);
	if (!env) {
		env = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_options"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("_modules"), _1 TSRMLS_CC);
	ZEPHIR_CALL_SELF(&app, "app", NULL);
	zephir_check_call_status();
	if (!(Z_TYPE_P(app) == IS_NULL)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Only one application can be initialized", "yaf/application.zep", 38);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_environ"), env TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_environ"), PH_NOISY_CC);
	if (Z_TYPE_P(_2) == IS_NULL) {
		ZEPHIR_INIT_VAR(_5);
		ZVAL_STRING(_5, "yaf.environ", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "iniget", &_4, _5);
		zephir_check_temp_parameter(_5);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_environ"), _3 TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "_loadconfig", NULL, config);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(config, _3);
	_6 = Z_TYPE_P(config) == IS_NULL;
	if (!(_6)) {
		_6 = !((zephir_instance_of_ev(config, yaf_config_abstract_ce TSRMLS_CC)));
	}
	_7 = _6;
	if (!(_7)) {
		ZEPHIR_CALL_METHOD(&_8, config, "toarray", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "parseoptions", NULL, _8);
		zephir_check_call_status();
		_7 = !ZEPHIR_IS_TRUE(_3);
	}
	if (_7) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Initialization of application config failed", "yaf/application.zep", 52);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_config"), config TSRMLS_CC);
	ZEPHIR_INIT_VAR(request);
	object_init_ex(request, yaf_request_http_ce);
	ZEPHIR_CALL_METHOD(NULL, request, "__construct", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(request) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Initialization of request failed", "yaf/application.zep", 60);
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_dispatcher_ce, "getinstance", &_9);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_dispatcher"), _3 TSRMLS_CC);
	_10 = zephir_fetch_nproperty_this(this_ptr, SL("_dispatcher"), PH_NOISY_CC);
	_11 = Z_TYPE_P(_10) == IS_NULL;
	if (!(_11)) {
		ZEPHIR_OBS_VAR(_12);
		zephir_read_property_this(&_12, this_ptr, SL("_dispatcher"), PH_NOISY_CC);
		_11 = !(zephir_instance_of_ev(_12, yaf_dispatcher_ce TSRMLS_CC));
	}
	if (_11) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Instantiation of dispatcher failed", "yaf/application.zep", 66);
		return;
	}
	_13 = zephir_fetch_nproperty_this(this_ptr, SL("_dispatcher"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _13, "setrequest", NULL, request);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_15);
	_16 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
	if (zephir_array_isset_string(_16, SS("local_library"))) {
		_17 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(_15);
		zephir_array_fetch_string(&_15, _17, SL("local_library"), PH_NOISY, "yaf/application.zep", 71 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_15);
		ZVAL_STRING(_15, "", 1);
	}
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "yaf.library", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "iniget", &_4, _5);
	zephir_check_temp_parameter(_5);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&loader, yaf_loader_ce, "getinstance", &_14, _15, _3);
	zephir_check_call_status();
	_18 = Z_TYPE_P(loader) == IS_NULL;
	if (!(_18)) {
		_18 = !((zephir_instance_of_ev(loader, yaf_loader_ce TSRMLS_CC)));
	}
	if (_18) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Initialization of application auto loader failed", "yaf/application.zep", 74);
		return;
	}
	_19 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
	_20 = zephir_array_isset_string(_19, SS("local_namespace"));
	if (_20) {
		_21 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
		zephir_array_fetch_string(&_22, _21, SL("local_namespace"), PH_NOISY | PH_READONLY, "yaf/application.zep", 77 TSRMLS_CC);
		_20 = !ZEPHIR_IS_STRING(_22, "");
	}
	if (_20) {
		ZEPHIR_INIT_VAR(tmpNamespace);
		ZEPHIR_INIT_VAR(_23);
		array_init_size(_23, 3);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, ",", 1);
		zephir_array_fast_append(_23, _5);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, " ", 1);
		zephir_array_fast_append(_23, _5);
		ZEPHIR_INIT_VAR(_24);
		array_init_size(_24, 3);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, ":", 1);
		zephir_array_fast_append(_24, _5);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, ":", 1);
		zephir_array_fast_append(_24, _5);
		_25 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
		zephir_array_fetch_string(&_26, _25, SL("local_namespace"), PH_NOISY | PH_READONLY, "yaf/application.zep", 78 TSRMLS_CC);
		zephir_fast_str_replace(tmpNamespace, _23, _24, _26 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, loader, "registerlocalnamespace", NULL, tmpNamespace);
		zephir_check_call_status();
	}
	zephir_update_static_property_ce(yaf_application_ce, SL("_app"), &this_ptr TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "throwException", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "get", &_27, _5);
	zephir_check_temp_parameter(_5);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE(_3)) {
		ZEPHIR_INIT_NVAR(_23);
		array_init_size(_23, 3);
		zephir_array_fast_append(_23, this_ptr);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, "exceptionHandler", 1);
		zephir_array_fast_append(_23, _5);
		ZEPHIR_CALL_FUNCTION(NULL, "set_exception_handler", &_28, _23);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Application, __destruct) {



}

PHP_METHOD(Yaf_Application, bootstrap) {

	zend_bool _22;
	HashTable *_15, *_20;
	HashPosition _14, _19;
	zend_class_entry *_10;
	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_7 = NULL, *_13 = NULL, *_18 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *bootstrapClass, *bootstrap = NULL, *loader = NULL, *tmpClass, *classMethods = NULL, *methodNames = NULL, *initMethodLength, *method = NULL, *_0, *_1, *_2 = NULL, *_3 = NULL, *_5 = NULL, *_8 = NULL, *_9 = NULL, *_11 = NULL, _12 = zval_used_for_init, **_16, *_17 = NULL, **_21, _23 = zval_used_for_init, _24 = zval_used_for_init;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(bootstrapClass);
	ZVAL_STRING(bootstrapClass, "Bootstrap", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
	if (zephir_array_isset_string(_0, SS("bootstrap"))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_options"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(bootstrap);
		zephir_array_fetch_string(&bootstrap, _1, SL("bootstrap"), PH_NOISY, "yaf/application.zep", 98 TSRMLS_CC);
	} else {
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "getappdirectory", NULL);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_5);
		ZVAL_STRING(_5, "ext", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "get", &_4, _5);
		zephir_check_temp_parameter(_5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(bootstrap);
		ZEPHIR_CONCAT_VSVSV(bootstrap, _2, "/", bootstrapClass, ".", _3);
	}
	ZEPHIR_CALL_CE_STATIC(&loader, yaf_loader_ce, "getinstance", &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_2, yaf_loader_ce, "import", &_7, bootstrap);
	zephir_check_call_status();
	if (zephir_is_true(_2)) {
		if (!(zephir_class_exists(bootstrapClass, 1 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_5);
			object_init_ex(_5, yaf_exception_ce);
			ZEPHIR_INIT_VAR(_8);
			ZEPHIR_CONCAT_SV(_8, "Couldn't find class Bootstrap in ", bootstrap);
			ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, _8);
			zephir_check_call_status();
			zephir_throw_exception_debug(_5, "yaf/application.zep", 106 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			ZEPHIR_INIT_NVAR(bootstrap);
			zephir_fetch_safe_class(_9, bootstrapClass);
			_10 = zend_fetch_class(Z_STRVAL_P(_9), Z_STRLEN_P(_9), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
			object_init_ex(bootstrap, _10);
			if (zephir_has_constructor(bootstrap TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, bootstrap, "__construct", NULL);
				zephir_check_call_status();
			}
			if (!(zephir_instance_of_ev(bootstrap, yaf_bootstrap_abstract_ce TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_5);
				object_init_ex(_5, yaf_exception_ce);
				ZEPHIR_INIT_VAR(_11);
				zephir_get_class(_11, bootstrap, 0 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_8);
				ZEPHIR_CONCAT_SVS(_8, "Expect a Yaf_Bootstrap_Abstract instance, ", _11, " give ");
				ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, _8);
				zephir_check_call_status();
				zephir_throw_exception_debug(_5, "yaf/application.zep", 111 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_NVAR(_5);
			ZEPHIR_GET_CONSTANT(_5, "PHP_VERSION");
			ZEPHIR_SINIT_VAR(_12);
			ZVAL_STRING(&_12, "5.2.6", 0);
			ZEPHIR_CALL_FUNCTION(&_3, "version_compare", &_13, _5, &_12);
			zephir_check_call_status();
			if (ZEPHIR_IS_LONG_IDENTICAL(_3, -1)) {
				ZEPHIR_INIT_VAR(tmpClass);
				object_init_ex(tmpClass, zephir_get_internal_ce(SS("reflectionobject") TSRMLS_CC));
				ZEPHIR_CALL_METHOD(NULL, tmpClass, "__construct", NULL, bootstrap);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&classMethods, tmpClass, "getmethods", NULL);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(methodNames);
				array_init(methodNames);
				zephir_is_iterable(classMethods, &_15, &_14, 0, 0, "yaf/application.zep", 122);
				for (
				  ; zephir_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
				  ; zephir_hash_move_forward_ex(_15, &_14)
				) {
					ZEPHIR_GET_HVALUE(method, _16);
					ZEPHIR_CALL_METHOD(&_17, method, "getname", NULL);
					zephir_check_call_status();
					zephir_array_append(&methodNames, _17, PH_SEPARATE, "yaf/application.zep", 120);
				}
			} else {
				ZEPHIR_CALL_FUNCTION(&methodNames, "get_class_methods", &_18, bootstrap);
				zephir_check_call_status();
			}
			ZEPHIR_SINIT_NVAR(_12);
			ZVAL_STRING(&_12, "_init", 0);
			ZEPHIR_INIT_VAR(initMethodLength);
			ZVAL_LONG(initMethodLength, zephir_fast_strlen_ev(&_12));
			zephir_is_iterable(methodNames, &_20, &_19, 0, 0, "yaf/application.zep", 132);
			for (
			  ; zephir_hash_get_current_data_ex(_20, (void**) &_21, &_19) == SUCCESS
			  ; zephir_hash_move_forward_ex(_20, &_19)
			) {
				ZEPHIR_GET_HVALUE(method, _21);
				_22 = ZEPHIR_LT_LONG(initMethodLength, zephir_fast_strlen_ev(method));
				if (_22) {
					ZEPHIR_SINIT_NVAR(_23);
					ZVAL_LONG(&_23, 0);
					ZEPHIR_INIT_NVAR(_11);
					zephir_substr(_11, method, 0 , zephir_get_intval(initMethodLength), 0);
					ZEPHIR_SINIT_NVAR(_24);
					ZVAL_STRING(&_24, "_init", 0);
					_22 = ZEPHIR_IS_IDENTICAL(&_24, _11);
				}
				if (_22) {
					_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dispatcher"), PH_NOISY_CC);
					ZEPHIR_CALL_METHOD(NULL, bootstrap, Z_STRVAL_P(method), NULL, _1);
					zephir_check_call_status();
				}
			}
		}
	} else {
		ZEPHIR_INIT_NVAR(_5);
		object_init_ex(_5, yaf_exception_ce);
		ZEPHIR_INIT_LNVAR(_8);
		ZEPHIR_CONCAT_SV(_8, "Couldn't find bootstrap file ", bootstrap);
		ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, _8);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5, "yaf/application.zep", 134 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * Start Yaf_Application
 */
PHP_METHOD(Yaf_Application, run) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_running"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE(_0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "An application instance already run", "yaf/application.zep", 147);
		return;
	} else {
		zephir_update_property_this(this_ptr, SL("_running"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dispatcher"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_METHOD(_1, "dispatch", NULL);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Retrieve application instance
 * @return Yaf_Application
 */
PHP_METHOD(Yaf_Application, app) {

	zval *_0;


	_0 = zephir_fetch_static_property_ce(yaf_application_ce, SL("_app") TSRMLS_CC);
	RETURN_CTORW(_0);

}

/**
 * Retrieve the config instance
 */
PHP_METHOD(Yaf_Application, getConfig) {


	RETURN_MEMBER(this_ptr, "_config");

}

/**
 * Get Yaf_Dispatcher instance
 * @return Yaf_Dispatcher
 */
PHP_METHOD(Yaf_Application, getDispatcher) {


	RETURN_MEMBER(this_ptr, "_dispatcher");

}

/**
 * Get defined module names
 */
PHP_METHOD(Yaf_Application, getModules) {


	RETURN_MEMBER(this_ptr, "_modules");

}

/**
 * Retrieve environment
 */
PHP_METHOD(Yaf_Application, environ) {


	RETURN_MEMBER(this_ptr, "_environ");

}

PHP_METHOD(Yaf_Application, execute) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_1 = NULL, *_4 = NULL;
	zval *args, *arguments = NULL, *callback, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &args);



	ZEPHIR_CALL_FUNCTION(&arguments, "func_get_args", &_0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(callback);
	zephir_array_fetch_long(&callback, arguments, 0, PH_NOISY, "yaf/application.zep", 221 TSRMLS_CC);
	if (!(zephir_is_callable(callback TSRMLS_CC))) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "First argument is expected to be a valid callback", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, 512);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_1, _2, _3);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
	}
	Z_SET_ISREF_P(arguments);
	ZEPHIR_CALL_FUNCTION(NULL, "array_shift", &_4, arguments);
	Z_UNSET_ISREF_P(arguments);
	zephir_check_call_status();
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callback, arguments);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Yaf_Application can not be cloned
 */
PHP_METHOD(Yaf_Application, __clone) {



}

/**
 * Yaf_Application can not be serialized
 */
PHP_METHOD(Yaf_Application, __sleep) {



}

/**
 * Yaf_Application can not be deserialized
 */
PHP_METHOD(Yaf_Application, __wakeup) {



}

PHP_METHOD(Yaf_Application, getAppDirectory) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_1;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "directory", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(yaf_g_ce, "get", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Yaf_Application, setAppDirectory) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL, *_4 = NULL, *_5 = NULL;
	zval *directory, *_0 = NULL, *_3 = NULL, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &directory);



	ZEPHIR_CALL_FUNCTION(&_0, "is_dir", &_1, directory);
	zephir_check_call_status();
	_2 = !zephir_is_true(_0);
	if (!(_2)) {
		ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "isabsolutepath", &_4, directory);
		zephir_check_call_status();
		_2 = !zephir_is_true(_3);
	}
	if (_2) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(_6);
	ZVAL_STRING(_6, "directory", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _6, directory);
	zephir_check_temp_parameter(_6);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * this was added internally
 * @param string $module
 * @return boolean
 */
PHP_METHOD(Yaf_Application, isModuleName) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *module_param = NULL, *app = NULL, *modules = NULL, *_0, _1, *_2 = NULL, *_4 = NULL;
	zval *module = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &module_param);

	zephir_get_strval(module, module_param);


	ZEPHIR_CALL_SELF(&app, "app", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(app) == IS_NULL) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&modules, app, "getmodules", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtolower(_0, module);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "strtolower", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "array_map", &_3, &_1, modules);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_4, "array_search", &_5, _0, _2);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(_4)) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

PHP_METHOD(Yaf_Application, setErrorNo) {

	zval *err;

	zephir_fetch_params(0, 1, 0, &err);



	zephir_update_property_this(this_ptr, SL("_errno"), err TSRMLS_CC);

}

PHP_METHOD(Yaf_Application, setErrorMsg) {

	zval *msg;

	zephir_fetch_params(0, 1, 0, &msg);



	zephir_update_property_this(this_ptr, SL("_errmsg"), msg TSRMLS_CC);

}

PHP_METHOD(Yaf_Application, clearLastError) {

	zval *_0;


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, 0);
	zephir_update_property_this(this_ptr, SL("_errno"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_STRING(_0, "", 1);
	zephir_update_property_this(this_ptr, SL("_errmsg"), _0 TSRMLS_CC);

}

PHP_METHOD(Yaf_Application, getLastErrorMsg) {


	RETURN_MEMBER(this_ptr, "_errmsg");

}

PHP_METHOD(Yaf_Application, getLastErrorNo) {


	RETURN_MEMBER(this_ptr, "_errno");

}

/**
 * Load configuration file of options
 *
 * @param  string $file
 * @throws Yaf_Exception when invalid configuration file is provided
 * @return array
 */
PHP_METHOD(Yaf_Application, _loadConfig) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *file_param = NULL, *environment = NULL, *config = NULL, *_0;
	zval *file = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &file_param);

	zephir_get_strval(file, file_param);


	ZEPHIR_CALL_METHOD(&environment, this_ptr, "environ", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(file) == IS_STRING) {
		ZEPHIR_INIT_VAR(config);
		object_init_ex(config, yaf_config_ini_ce);
		ZEPHIR_CALL_METHOD(NULL, config, "__construct", NULL, file, environment);
		zephir_check_call_status();
	} else if (Z_TYPE_P(file) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(config);
		object_init_ex(config, yaf_config_simple_ce);
		ZEPHIR_CALL_METHOD(NULL, config, "__construct", NULL, file);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, yaf_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SS(_1, "Invalid options provided; must be location of config file, ", "a config object, or an array");
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "yaf/application.zep", 343 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(config);

}

/**
 * Parse application options
 *
 * @param  array $options
 * @throws Yaf_Exception When no bootstrap path is provided
 * @throws Yaf_Exception When invalid bootstrap information are provided
 * @return Yaf_Application
 */
PHP_METHOD(Yaf_Application, parseOptions) {

	HashTable *_57;
	HashPosition _56;
	zend_bool _16, _21, _28, _33, _35, _37, _39, _42, _48, _53;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_5 = NULL, *_8 = NULL, *_13 = NULL, *_32 = NULL, *_55 = NULL;
	zval *options_param = NULL, *modules = NULL, *module = NULL, _0 = zval_used_for_init, *_1 = NULL, *_3, *_4, _6, *_7 = NULL, *_9 = NULL, *_10, *_11 = NULL, *_12 = NULL, *_14, *_15, *_17, *_18, *_19, *_20 = NULL, *_22, *_23, *_24, *_25, *_26 = NULL, *_27 = NULL, *_29, *_30, *_31, *_34, *_SERVER, *_36, *_38 = NULL, *_40, *_41, *_43, *_44, *_45, *_46, *_47, *_49, *_50, *_51, *_52 = NULL, *_54, **_58;
	zval *options = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &options_param);

	zephir_get_arrval(options, options_param);


	if (!(Z_TYPE_P(options) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expected an array of application configure", "yaf/application.zep", 362);
		return;
	}
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_FUNCTION(&_1, "array_change_key_case", &_2, options, &_0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(options, _1);
	if (!(zephir_array_isset_string(options, SS("application")))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expected an array of application configure", "yaf/application.zep", 367);
		return;
	}
	zephir_array_fetch_string(&_3, options, SL("application"), PH_NOISY | PH_READONLY, "yaf/application.zep", 369 TSRMLS_CC);
	ZEPHIR_CPY_WRT(options, _3);
	ZEPHIR_OBS_VAR(_4);
	zephir_array_fetch_string(&_4, options, SL("directory"), PH_NOISY, "yaf/application.zep", 371 TSRMLS_CC);
	if (!(ZEPHIR_IS_EMPTY(_4))) {
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "/", 0);
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "/", 0);
		ZEPHIR_CALL_FUNCTION(&_7, "preg_quote", &_8, &_0, &_6);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_9);
		ZEPHIR_CONCAT_SVS(_9, "/", _7, "$/");
		zephir_array_fetch_string(&_10, options, SL("directory"), PH_NOISY | PH_READONLY, "yaf/application.zep", 372 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_11);
		ZVAL_STRING(_11, "", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&_12, "preg_replace", &_13, _9, _11, _10);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "directory", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _12);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_startuperror_ce, "Expected a directory entry in application configures", "yaf/application.zep", 374);
		return;
	}
	ZEPHIR_OBS_VAR(_14);
	zephir_array_fetch_string(&_14, options, SL("ext"), PH_NOISY, "yaf/application.zep", 377 TSRMLS_CC);
	if (!(ZEPHIR_IS_EMPTY(_14))) {
		zephir_array_fetch_string(&_10, options, SL("ext"), PH_NOISY | PH_READONLY, "yaf/application.zep", 378 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "ext", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _10);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_VAR(_15);
	zephir_array_fetch_string(&_15, options, SL("bootstrap"), PH_NOISY, "yaf/application.zep", 381 TSRMLS_CC);
	_16 = !(ZEPHIR_IS_EMPTY(_15));
	if (_16) {
		zephir_array_fetch_string(&_10, options, SL("bootstrap"), PH_NOISY | PH_READONLY, "yaf/application.zep", 381 TSRMLS_CC);
		_16 = Z_TYPE_P(_10) == IS_STRING;
	}
	if (_16) {
		zephir_array_fetch_string(&_17, options, SL("bootstrap"), PH_NOISY | PH_READONLY, "yaf/application.zep", 382 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "bootstrap", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _11, _17 TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(_18);
	zephir_array_fetch_string(&_18, options, SL("library"), PH_NOISY, "yaf/application.zep", 385 TSRMLS_CC);
	if (!(ZEPHIR_IS_EMPTY(_18))) {
		zephir_array_fetch_string(&_10, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 387 TSRMLS_CC);
		if (Z_TYPE_P(_10) == IS_STRING) {
			zephir_array_fetch_string(&_17, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 388 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "local_library", 1);
			zephir_update_property_array(this_ptr, SL("_options"), _11, _17 TSRMLS_CC);
		} else {
			zephir_array_fetch_string(&_17, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 391 TSRMLS_CC);
			if (Z_TYPE_P(_17) == IS_ARRAY) {
				zephir_array_fetch_string(&_19, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 393 TSRMLS_CC);
				ZEPHIR_OBS_VAR(_20);
				zephir_array_fetch_string(&_20, _19, SL("directory"), PH_NOISY, "yaf/application.zep", 393 TSRMLS_CC);
				_21 = !(ZEPHIR_IS_EMPTY(_20));
				if (_21) {
					zephir_array_fetch_string(&_22, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 393 TSRMLS_CC);
					zephir_array_fetch_string(&_23, _22, SL("directory"), PH_NOISY | PH_READONLY, "yaf/application.zep", 393 TSRMLS_CC);
					_21 = Z_TYPE_P(_23) == IS_STRING;
				}
				if (_21) {
					zephir_array_fetch_string(&_24, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 394 TSRMLS_CC);
					zephir_array_fetch_string(&_25, _24, SL("directory"), PH_NOISY | PH_READONLY, "yaf/application.zep", 394 TSRMLS_CC);
					ZEPHIR_INIT_VAR(_26);
					ZVAL_STRING(_26, "local_library", 1);
					zephir_update_property_array(this_ptr, SL("_options"), _26, _25 TSRMLS_CC);
				}
				zephir_array_fetch_string(&_24, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 397 TSRMLS_CC);
				ZEPHIR_OBS_VAR(_27);
				zephir_array_fetch_string(&_27, _24, SL("namespace"), PH_NOISY, "yaf/application.zep", 397 TSRMLS_CC);
				_28 = !(ZEPHIR_IS_EMPTY(_27));
				if (_28) {
					zephir_array_fetch_string(&_25, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 397 TSRMLS_CC);
					zephir_array_fetch_string(&_29, _25, SL("namespace"), PH_NOISY | PH_READONLY, "yaf/application.zep", 397 TSRMLS_CC);
					_28 = Z_TYPE_P(_29) == IS_STRING;
				}
				if (_28) {
					zephir_array_fetch_string(&_30, options, SL("library"), PH_NOISY | PH_READONLY, "yaf/application.zep", 398 TSRMLS_CC);
					zephir_array_fetch_string(&_31, _30, SL("namespace"), PH_NOISY | PH_READONLY, "yaf/application.zep", 398 TSRMLS_CC);
					ZEPHIR_INIT_NVAR(_26);
					ZVAL_STRING(_26, "local_namespace", 1);
					zephir_update_property_array(this_ptr, SL("_options"), _26, _31 TSRMLS_CC);
				}
			}
		}
	} else {
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "directory", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "get", &_32, _11);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_9);
		ZEPHIR_CONCAT_VSS(_9, _7, "/", "library");
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "local_library", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _11, _9 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_20);
	zephir_array_fetch_string(&_20, options, SL("view"), PH_NOISY, "yaf/application.zep", 406 TSRMLS_CC);
	_21 = !(ZEPHIR_IS_EMPTY(_20));
	if (_21) {
		zephir_array_fetch_string(&_10, options, SL("view"), PH_NOISY | PH_READONLY, "yaf/application.zep", 406 TSRMLS_CC);
		_21 = Z_TYPE_P(_10) == IS_ARRAY;
	}
	_28 = _21;
	if (_28) {
		zephir_array_fetch_string(&_17, options, SL("view"), PH_NOISY | PH_READONLY, "yaf/application.zep", 406 TSRMLS_CC);
		ZEPHIR_OBS_NVAR(_27);
		zephir_array_fetch_string(&_27, _17, SL("ext"), PH_NOISY, "yaf/application.zep", 406 TSRMLS_CC);
		_28 = !(ZEPHIR_IS_EMPTY(_27));
	}
	_33 = _28;
	if (_33) {
		zephir_array_fetch_string(&_19, options, SL("view"), PH_NOISY | PH_READONLY, "yaf/application.zep", 406 TSRMLS_CC);
		zephir_array_fetch_string(&_22, _19, SL("ext"), PH_NOISY | PH_READONLY, "yaf/application.zep", 406 TSRMLS_CC);
		_33 = Z_TYPE_P(_22) == IS_STRING;
	}
	if (_33) {
		zephir_array_fetch_string(&_23, options, SL("view"), PH_NOISY | PH_READONLY, "yaf/application.zep", 407 TSRMLS_CC);
		zephir_array_fetch_string(&_24, _23, SL("ext"), PH_NOISY | PH_READONLY, "yaf/application.zep", 407 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "view_ext", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _24);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_VAR(_34);
	zephir_array_fetch_string(&_34, options, SL("baseUri"), PH_NOISY, "yaf/application.zep", 410 TSRMLS_CC);
	_35 = !(ZEPHIR_IS_EMPTY(_34));
	if (_35) {
		zephir_array_fetch_string(&_10, options, SL("baseUri"), PH_NOISY | PH_READONLY, "yaf/application.zep", 410 TSRMLS_CC);
		_35 = Z_TYPE_P(_10) == IS_STRING;
	}
	if (_35) {
		zephir_array_fetch_string(&_17, options, SL("baseUri"), PH_NOISY | PH_READONLY, "yaf/application.zep", 411 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "baseUri", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _11, _17 TSRMLS_CC);
	} else {
		zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);
		zephir_array_fetch_string(&_10, _SERVER, SL("PHP_SELF"), PH_NOISY | PH_READONLY, "yaf/application.zep", 413 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "baseUri", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _11, _10 TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(_36);
	zephir_array_fetch_string(&_36, options, SL("dispatcher"), PH_NOISY, "yaf/application.zep", 416 TSRMLS_CC);
	_37 = !(ZEPHIR_IS_EMPTY(_36));
	if (_37) {
		zephir_array_fetch_string(&_10, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 416 TSRMLS_CC);
		_37 = Z_TYPE_P(_10) == IS_ARRAY;
	}
	if (_37) {
		zephir_array_fetch_string(&_17, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 418 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_38);
		zephir_array_fetch_string(&_38, _17, SL("defaultModule"), PH_NOISY, "yaf/application.zep", 418 TSRMLS_CC);
		_39 = !(ZEPHIR_IS_EMPTY(_38));
		if (_39) {
			zephir_array_fetch_string(&_25, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 418 TSRMLS_CC);
			zephir_array_fetch_string(&_29, _25, SL("defaultModule"), PH_NOISY | PH_READONLY, "yaf/application.zep", 418 TSRMLS_CC);
			_39 = Z_TYPE_P(_29) == IS_STRING;
		}
		if (_39) {
			zephir_array_fetch_string(&_30, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 419 TSRMLS_CC);
			zephir_array_fetch_string(&_31, _30, SL("defaultModule"), PH_NOISY | PH_READONLY, "yaf/application.zep", 419 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_module", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _31);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_module", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_26);
			ZVAL_STRING(_26, "Index", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
			zephir_check_temp_parameter(_11);
			zephir_check_temp_parameter(_26);
			zephir_check_call_status();
		}
		zephir_array_fetch_string(&_40, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 424 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_41);
		zephir_array_fetch_string(&_41, _40, SL("defaultController"), PH_NOISY, "yaf/application.zep", 424 TSRMLS_CC);
		_42 = !(ZEPHIR_IS_EMPTY(_41));
		if (_42) {
			zephir_array_fetch_string(&_43, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 424 TSRMLS_CC);
			zephir_array_fetch_string(&_44, _43, SL("defaultController"), PH_NOISY | PH_READONLY, "yaf/application.zep", 424 TSRMLS_CC);
			_42 = Z_TYPE_P(_44) == IS_STRING;
		}
		if (_42) {
			zephir_array_fetch_string(&_45, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 425 TSRMLS_CC);
			zephir_array_fetch_string(&_46, _45, SL("defaultController"), PH_NOISY | PH_READONLY, "yaf/application.zep", 425 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_controller", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _46);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_controller", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_26);
			ZVAL_STRING(_26, "Index", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
			zephir_check_temp_parameter(_11);
			zephir_check_temp_parameter(_26);
			zephir_check_call_status();
		}
		zephir_array_fetch_string(&_45, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 430 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_47);
		zephir_array_fetch_string(&_47, _45, SL("defaultAction"), PH_NOISY, "yaf/application.zep", 430 TSRMLS_CC);
		_48 = !(ZEPHIR_IS_EMPTY(_47));
		if (_48) {
			zephir_array_fetch_string(&_46, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 430 TSRMLS_CC);
			zephir_array_fetch_string(&_49, _46, SL("defaultAction"), PH_NOISY | PH_READONLY, "yaf/application.zep", 430 TSRMLS_CC);
			_48 = Z_TYPE_P(_49) == IS_STRING;
		}
		if (_48) {
			zephir_array_fetch_string(&_50, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 431 TSRMLS_CC);
			zephir_array_fetch_string(&_51, _50, SL("defaultAction"), PH_NOISY | PH_READONLY, "yaf/application.zep", 431 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_action", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _51);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_action", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_26);
			ZVAL_STRING(_26, "index", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
			zephir_check_temp_parameter(_11);
			zephir_check_temp_parameter(_26);
			zephir_check_call_status();
		}
		zephir_array_fetch_string(&_45, options, SL("dispatcher"), PH_READONLY, "yaf/application.zep", 436 TSRMLS_CC);
		if (zephir_array_isset_string(_45, SS("throwException"))) {
			zephir_array_fetch_string(&_46, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 437 TSRMLS_CC);
			ZEPHIR_OBS_VAR(_52);
			zephir_array_fetch_string(&_52, _46, SL("throwException"), PH_NOISY, "yaf/application.zep", 437 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "throwException", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_26);
			ZVAL_BOOL(_26, zephir_get_boolval(_52));
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		}
		zephir_array_fetch_string(&_45, options, SL("dispatcher"), PH_READONLY, "yaf/application.zep", 440 TSRMLS_CC);
		if (zephir_array_isset_string(_45, SS("catchException"))) {
			zephir_array_fetch_string(&_46, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 441 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(_52);
			zephir_array_fetch_string(&_52, _46, SL("catchException"), PH_NOISY, "yaf/application.zep", 441 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "catchException", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_INIT_NVAR(_26);
			ZVAL_BOOL(_26, zephir_get_boolval(_52));
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		}
		zephir_array_fetch_string(&_45, options, SL("dispatcher"), PH_READONLY, "yaf/application.zep", 444 TSRMLS_CC);
		_53 = zephir_array_isset_string(_45, SS("defaultRoute"));
		if (_53) {
			zephir_array_fetch_string(&_46, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 444 TSRMLS_CC);
			zephir_array_fetch_string(&_50, _46, SL("defaultRoute"), PH_NOISY | PH_READONLY, "yaf/application.zep", 444 TSRMLS_CC);
			_53 = Z_TYPE_P(_50) == IS_ARRAY;
		}
		if (_53) {
			zephir_array_fetch_string(&_51, options, SL("dispatcher"), PH_NOISY | PH_READONLY, "yaf/application.zep", 445 TSRMLS_CC);
			zephir_array_fetch_string(&_54, _51, SL("defaultRoute"), PH_NOISY | PH_READONLY, "yaf/application.zep", 445 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_11);
			ZVAL_STRING(_11, "default_route", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _54);
			zephir_check_temp_parameter(_11);
			zephir_check_call_status();
		}
	} else {
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "default_module", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_NVAR(_26);
		ZVAL_STRING(_26, "Index", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
		zephir_check_temp_parameter(_11);
		zephir_check_temp_parameter(_26);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "default_controller", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_NVAR(_26);
		ZVAL_STRING(_26, "Index", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
		zephir_check_temp_parameter(_11);
		zephir_check_temp_parameter(_26);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "default_action", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_NVAR(_26);
		ZVAL_STRING(_26, "index", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_g_ce, "set", &_5, _11, _26);
		zephir_check_temp_parameter(_11);
		zephir_check_temp_parameter(_26);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "throwException", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _11, ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_26);
		ZVAL_STRING(_26, "catchException", 1);
		zephir_update_property_array(this_ptr, SL("_options"), _26, ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_38);
	zephir_array_fetch_string(&_38, options, SL("modules"), PH_NOISY, "yaf/application.zep", 455 TSRMLS_CC);
	_39 = !(ZEPHIR_IS_EMPTY(_38));
	if (_39) {
		zephir_array_fetch_string(&_10, options, SL("modules"), PH_NOISY | PH_READONLY, "yaf/application.zep", 455 TSRMLS_CC);
		_39 = Z_TYPE_P(_10) == IS_STRING;
	}
	if (_39) {
		zephir_array_fetch_string(&_17, options, SL("modules"), PH_NOISY | PH_READONLY, "yaf/application.zep", 456 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "/,/", 0);
		ZEPHIR_CALL_FUNCTION(&modules, "preg_split", &_55, &_0, _17);
		zephir_check_call_status();
		zephir_is_iterable(modules, &_57, &_56, 0, 0, "yaf/application.zep", 460);
		for (
		  ; zephir_hash_get_current_data_ex(_57, (void**) &_58, &_56) == SUCCESS
		  ; zephir_hash_move_forward_ex(_57, &_56)
		) {
			ZEPHIR_GET_HVALUE(module, _58);
			ZEPHIR_INIT_NVAR(_11);
			zephir_fast_trim(_11, module, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			zephir_update_property_array_append(this_ptr, SL("_modules"), _11 TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_NVAR(_38);
	zephir_read_property_this(&_38, this_ptr, SL("_modules"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(_38)) {
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_STRING(_11, "default_module", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "get", &_32, _11);
		zephir_check_temp_parameter(_11);
		zephir_check_call_status();
		zephir_update_property_array_append(this_ptr, SL("_modules"), _7 TSRMLS_CC);
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(Yaf_Application, exceptionHandler) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *e, *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &e);



	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_GET_CONSTANT(_0, "PHP_EOL");
	ZEPHIR_CALL_METHOD(&_1, e, "getmessage", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VSV(_2, _0, "Exception throught App - ", _1);
	zend_print_zval(_2, 0);
	ZEPHIR_MM_RESTORE();

}

