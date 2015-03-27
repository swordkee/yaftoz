
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
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/string.h"

ZEPHIR_INIT_CLASS(Yaf_Router) {

	ZEPHIR_REGISTER_CLASS(Yaf, Router, yaf, router, yaf_router_method_entry, 0);

	/**
	 * Array of routes to match against
	 *
	 * @var array
	 */
	zend_declare_property_null(yaf_router_ce, SL("_routes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Currently matched route
	 *
	 * @var string
	 */
	zend_declare_property_null(yaf_router_ce, SL("_current"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("URI_DELIMITER"), "/" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("URI_VARIABLE"), ":" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("YAF_DEFAULT_EXT"), "php" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("YAF_ROUTER_DEFAULT_ACTION"), "index" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("YAF_ROUTER_DEFAULT_CONTROLLER"), "Index" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_router_ce, SL("YAF_ROUTER_DEFAULT_MODULE"), "Index" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Router, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0, *defaultRoute = NULL, *_2 = NULL, *_3 = NULL, *_4;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_routes"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "default_route", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&defaultRoute, yaf_g_ce, "get", &_1, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	if (Z_TYPE_P(defaultRoute) != IS_NULL) {
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "_getroutefromarray", NULL, defaultRoute);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "_default", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", NULL, _2, _3);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_2);
		object_init_ex(_2, yaf_route_static_ce);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_4);
		ZVAL_STRING(_4, "_default", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", NULL, _4, _2);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Add route to the route chain
 *
 * @param  string $name Name of the route
 * @param  Yaf_Route_Interface $route Instance of the route
 * @return Yaf_Router
 */
PHP_METHOD(Yaf_Router, addRoute) {

	zval *name_param = NULL, *route;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &route);

	zephir_get_strval(name, name_param);


	zephir_update_property_array(this_ptr, SL("_routes"), name, route TSRMLS_CC);
	RETURN_THIS();

}

/**
 *
 * Example INI:
 * routes.archive.type = "simple"
 * routes.archive.module = Index
 * routes.archive.controller = archive
 * routes.archive.action = show
 *
 * routes.news.type = "static"
 * routes.news.route = "news"
 *
 * And finally after you have created a Yaf_Config with above ini:
 * $router = new Yaf_Router();
 * $router->addConfig($config);
 *
 * @param  array|Yaf_Config $config  Configuration object
 * @throws Yaf_Router_Exception
 * @return Yaf_Router
 */
PHP_METHOD(Yaf_Router, addConfig) {

	zephir_fcall_cache_entry *_4 = NULL, *_5 = NULL, *_8 = NULL;
	HashTable *_2;
	HashPosition _1;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_9 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *config = NULL, *name = NULL, *entry = NULL, *route = NULL, **_3, *_6 = NULL, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config);

	ZEPHIR_SEPARATE_PARAM(config);


	if (Z_TYPE_P(config) == IS_ARRAY) {
		php_printf("%s", "not allowed");
	} else {
		if (zephir_instance_of_ev(config, yaf_config_abstract_ce TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&config, config, "toarray", NULL);
			zephir_check_call_status();
		} else {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_routerfailed_ce, "Expecting Array or Yaf_Config_Abstract instance", "yaf/router.zep", 87);
			return;
		}
	}
	Z_SET_ISREF_P(config);
	ZEPHIR_CALL_FUNCTION(&name, "key", &_0, config);
	Z_UNSET_ISREF_P(config);
	zephir_check_call_status();
	zephir_is_iterable(config, &_2, &_1, 0, 0, "yaf/router.zep", 112);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(entry, _3);
		ZEPHIR_CALL_METHOD(&route, this_ptr, "_getroutefromarray", &_4, entry);
		zephir_check_call_status();
		if (Z_TYPE_P(route) != IS_NULL) {
			if (zephir_instance_of_ev(route, yaf_route_interface_ce TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", &_5, name, route);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", &_5, name, route);
				zephir_check_call_status();
			}
		} else {
			if (Z_TYPE_P(name) == IS_STRING) {
				ZEPHIR_INIT_NVAR(_6);
				object_init_ex(_6, yaf_exception_routerfailed_ce);
				ZEPHIR_INIT_LNVAR(_7);
				ZEPHIR_CONCAT_SV(_7, "Unable to initialize route named ", name);
				ZEPHIR_CALL_METHOD(NULL, _6, "__construct", &_8, _7);
				zephir_check_call_status();
				zephir_throw_exception_debug(_6, "yaf/router.zep", 104 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			} else {
				ZEPHIR_INIT_NVAR(_6);
				object_init_ex(_6, yaf_exception_routerfailed_ce);
				ZEPHIR_INIT_LNVAR(_7);
				ZEPHIR_CONCAT_SV(_7, "Unable to initialize route at index ", name);
				ZEPHIR_CALL_METHOD(NULL, _6, "__construct", &_8, _7);
				zephir_check_call_status();
				zephir_throw_exception_debug(_6, "yaf/router.zep", 106 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		Z_SET_ISREF_P(config);
		ZEPHIR_CALL_FUNCTION(NULL, "next", &_9, config);
		Z_UNSET_ISREF_P(config);
		zephir_check_call_status();
		Z_SET_ISREF_P(config);
		ZEPHIR_CALL_FUNCTION(&name, "key", &_0, config);
		Z_UNSET_ISREF_P(config);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * Get a route from a config instance
 *
 * @param  Yaf_Config_Abstract $info
 * @return Yaf_Route_Interface
 */
PHP_METHOD(Yaf_Router, _getRouteFromConfig) {

	zval *_4;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_5 = NULL;
	zval *info, *useNamespace = NULL, *tmpClass = NULL, *route = NULL, *e = NULL, *_1 = NULL, *_2, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &info);



	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yaf.use_namespace", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&useNamespace, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(tmpClass);
	if (zephir_is_true(useNamespace)) {
		if (zephir_array_isset_string(info, SS("type"))) {
			ZEPHIR_INIT_NVAR(_1);
			zephir_array_fetch_string(&_2, info, SL("type"), PH_NOISY | PH_READONLY, "yaf/router.zep", 128 TSRMLS_CC);
			zephir_ucfirst(_1, _2);
			ZEPHIR_CONCAT_SV(tmpClass, "\\Yaf\\Route\\", _1);
		} else {
			ZVAL_STRING(tmpClass, "\\Yaf\\Route\\Static", 1);
		}
	} else {
		if (zephir_array_isset_string(info, SS("type"))) {
			ZEPHIR_INIT_VAR(_3);
			zephir_array_fetch_string(&_2, info, SL("type"), PH_NOISY | PH_READONLY, "yaf/router.zep", 130 TSRMLS_CC);
			zephir_ucfirst(_3, _2);
			ZEPHIR_INIT_NVAR(tmpClass);
			ZEPHIR_CONCAT_SV(tmpClass, "Yaf_Route_", _3);
		} else {
			ZEPHIR_INIT_NVAR(tmpClass);
			ZVAL_STRING(tmpClass, "Yaf_Route_Static", 1);
		}
	}

	/* try_start_1: */

		ZEPHIR_INIT_VAR(_4);
		array_init_size(_4, 3);
		zephir_array_fast_append(_4, tmpClass);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "getInstance", 1);
		zephir_array_fast_append(_4, _3);
		ZEPHIR_CALL_FUNCTION(&route, "call_user_func", &_5, _4, info);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			RETURN_MM_NULL();
		}
	}
	RETURN_CCTOR(route);

}

/**
 * Get a route from an array
 *
 * @param  array $info
 * @return Yaf_Route_Interface
 */
PHP_METHOD(Yaf_Router, _getRouteFromArray) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_5 = NULL;
	zval *info_param = NULL, *useNamespace = NULL, *tmpClass = NULL, *route = NULL, *e = NULL, *_1 = NULL, *_2, *_3 = NULL;
	zval *info = NULL, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &info_param);

	zephir_get_arrval(info, info_param);


	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yaf.use_namespace", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&useNamespace, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(tmpClass);
	if (zephir_is_true(useNamespace)) {
		if (zephir_array_isset_string(info, SS("type"))) {
			ZEPHIR_INIT_NVAR(_1);
			zephir_array_fetch_string(&_2, info, SL("type"), PH_NOISY | PH_READONLY, "yaf/router.zep", 153 TSRMLS_CC);
			zephir_ucfirst(_1, _2);
			ZEPHIR_CONCAT_SV(tmpClass, "\\Yaf\\Route\\", _1);
		} else {
			ZVAL_STRING(tmpClass, "\\Yaf\\Route\\Static", 1);
		}
	} else {
		if (zephir_array_isset_string(info, SS("type"))) {
			ZEPHIR_INIT_VAR(_3);
			zephir_array_fetch_string(&_2, info, SL("type"), PH_NOISY | PH_READONLY, "yaf/router.zep", 155 TSRMLS_CC);
			zephir_ucfirst(_3, _2);
			ZEPHIR_INIT_NVAR(tmpClass);
			ZEPHIR_CONCAT_SV(tmpClass, "Yaf_Route_", _3);
		} else {
			ZEPHIR_INIT_NVAR(tmpClass);
			ZVAL_STRING(tmpClass, "Yaf_Route_Static", 1);
		}
	}

	/* try_start_1: */

		ZEPHIR_INIT_VAR(_4);
		array_init_size(_4, 3);
		zephir_array_fast_append(_4, tmpClass);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "getInstance", 1);
		zephir_array_fast_append(_4, _3);
		ZEPHIR_CALL_FUNCTION(&route, "call_user_func", &_5, _4, info);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			RETURN_MM_NULL();
		}
	}
	RETURN_CCTOR(route);

}

/**
 * Retrieve a currently matched route
 *
 * @throws Yaf_Exception_RouterFailed
 * @return Yaf_Route_Interface Route object
 */
PHP_METHOD(Yaf_Router, getCurrentRoute) {


	RETURN_MEMBER(this_ptr, "_current");

}

/**
 * Retrieve a named route
 *
 * @param string $name Name of the route
 * @throws Yaf_Exception_RouterFailed
 * @return Yaf_Route_Interface Route object
 */
PHP_METHOD(Yaf_Router, getRoute) {

	zval *name_param = NULL, *_0, *_1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_routes"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, name))) {
		RETURN_MM_NULL();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_routes"), PH_NOISY_CC);
	zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "yaf/router.zep", 193 TSRMLS_CC);
	RETURN_CTOR(_2);

}

/**
 * Retrieve an array of routes added to the route chain
 *
 * @return array All of the defined routes
 */
PHP_METHOD(Yaf_Router, getRoutes) {


	RETURN_MEMBER(this_ptr, "_routes");

}

/**
 * Find a matching route to the current Request and inject
 * returning values to the Request object.
 *
 * @return bool if there is a valid route
 */
PHP_METHOD(Yaf_Router, route) {

	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zend_bool routeMatched;
	zval *request, *name = NULL, *route = NULL, *ret = NULL, *_0, *_1 = NULL, **_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	routeMatched = 0;
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_routes"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(&_1, "array_reverse", &_2, _0, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	zephir_is_iterable(_1, &_4, &_3, 0, 0, "yaf/router.zep", 228);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HMKEY(name, _4, _3);
		ZEPHIR_GET_HVALUE(route, _5);
		ZEPHIR_CALL_METHOD(&ret, route, "route", NULL, request);
		zephir_check_call_status();
		if (!ZEPHIR_IS_FALSE(ret)) {
			zephir_update_property_this(this_ptr, SL("_current"), name TSRMLS_CC);
			routeMatched = 1;
			break;
		}
	}
	if (!(routeMatched)) {
		RETURN_MM_BOOL(0);
	} else {
		ZEPHIR_INIT_VAR(_6);
		ZVAL_BOOL(_6, 1);
		ZEPHIR_CALL_METHOD(NULL, request, "setrouted", NULL, _6);
		zephir_check_call_status();
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

