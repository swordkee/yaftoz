
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
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/fcall.h"


/**
 * Yaf Route Simple
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Simple) {

	ZEPHIR_REGISTER_CLASS(Yaf\\Route, Simple, yaf, route_simple, yaf_route_simple_method_entry, 0);

	zend_declare_property_null(yaf_route_simple_ce, SL("_module"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_simple_ce, SL("_controller"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_route_simple_ce, SL("_action"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_route_simple_ce TSRMLS_CC, 1, yaf_route_interface_ce);
	return SUCCESS;

}

/**
 * Class constructor
 * @param string $module
 * @param string $controller
 * @param string $action
 */
PHP_METHOD(Yaf_Route_Simple, __construct) {

	zend_bool _0, _1;
	zval *module_param = NULL, *controller_param = NULL, *action_param = NULL;
	zval *module = NULL, *controller = NULL, *action = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &module_param, &controller_param, &action_param);

	zephir_get_strval(module, module_param);
	zephir_get_strval(controller, controller_param);
	zephir_get_strval(action, action_param);


	_0 = !(Z_TYPE_P(module) == IS_STRING);
	if (!(_0)) {
		_0 = !(Z_TYPE_P(controller) == IS_STRING);
	}
	_1 = _0;
	if (!(_1)) {
		_1 = !(Z_TYPE_P(action) == IS_STRING);
	}
	if (_1) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Expect 3 string paramsters", "yaf/Route/simple.zep", 25);
		return;
	} else {
		zephir_update_property_this(this_ptr, SL("_module"), module TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_controller"), controller TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_action"), action TSRMLS_CC);
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
PHP_METHOD(Yaf_Route_Simple, route) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _6, _7;
	zval *request, *module = NULL, *controller = NULL, *action = NULL, *_GET, *_0, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	zephir_get_global(&_GET, SS("_GET") TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_module"), PH_NOISY_CC);
	if (zephir_array_isset(_GET, _0)) {
		ZEPHIR_OBS_VAR(module);
		ZEPHIR_OBS_VAR(_1);
		zephir_read_property_this(&_1, this_ptr, SL("_module"), PH_NOISY_CC);
		zephir_array_fetch(&module, _GET, _1, PH_NOISY, "yaf/Route/simple.zep", 45 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(module);
		ZVAL_NULL(module);
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_controller"), PH_NOISY_CC);
	if (zephir_array_isset(_GET, _2)) {
		ZEPHIR_OBS_VAR(controller);
		ZEPHIR_OBS_VAR(_3);
		zephir_read_property_this(&_3, this_ptr, SL("_controller"), PH_NOISY_CC);
		zephir_array_fetch(&controller, _GET, _3, PH_NOISY, "yaf/Route/simple.zep", 47 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(controller);
		ZVAL_NULL(controller);
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("_action"), PH_NOISY_CC);
	if (zephir_array_isset(_GET, _4)) {
		ZEPHIR_OBS_VAR(action);
		ZEPHIR_OBS_VAR(_5);
		zephir_read_property_this(&_5, this_ptr, SL("_action"), PH_NOISY_CC);
		zephir_array_fetch(&action, _GET, _5, PH_NOISY, "yaf/Route/simple.zep", 49 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(action);
		ZVAL_NULL(action);
	}
	_6 = Z_TYPE_P(module) == IS_NULL;
	if (_6) {
		_6 = Z_TYPE_P(controller) == IS_NULL;
	}
	_7 = _6;
	if (_7) {
		_7 = Z_TYPE_P(action) == IS_NULL;
	}
	if (_7) {
		RETURN_MM_BOOL(0);
	} else {
		if (Z_TYPE_P(module) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, module);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(controller) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, controller);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(action) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, action);
			zephir_check_call_status();
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * used to create routes on the fly from config
 *
 * @param array $config
 */
PHP_METHOD(Yaf_Route_Simple, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _2, _4;
	zval *config_param = NULL, *_1, *_3, *_5, *_6, *_7, *_8;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	_0 = !(zephir_array_isset_string(config, SS("module")));
	if (!(_0)) {
		zephir_array_fetch_string(&_1, config, SL("module"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 79 TSRMLS_CC);
		_0 = !(Z_TYPE_P(_1) == IS_STRING);
	}
	_2 = !(zephir_array_isset_string(config, SS("controller")));
	if (!(_2)) {
		zephir_array_fetch_string(&_3, config, SL("controller"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 81 TSRMLS_CC);
		_2 = !(Z_TYPE_P(_3) == IS_STRING);
	}
	_4 = !(zephir_array_isset_string(config, SS("action")));
	if (!(_4)) {
		zephir_array_fetch_string(&_5, config, SL("action"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 83 TSRMLS_CC);
		_4 = !(Z_TYPE_P(_5) == IS_STRING);
	}
	if (_0) {
		RETURN_MM_NULL();
	} else if (_2) {
		RETURN_MM_NULL();
	} else if (_4) {
		RETURN_MM_NULL();
	} else {
		object_init_ex(return_value, yaf_route_simple_ce);
		zephir_array_fetch_string(&_6, config, SL("module"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 86 TSRMLS_CC);
		zephir_array_fetch_string(&_7, config, SL("controller"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 86 TSRMLS_CC);
		zephir_array_fetch_string(&_8, config, SL("action"), PH_NOISY | PH_READONLY, "yaf/Route/simple.zep", 86 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _6, _7, _8);
		zephir_check_call_status();
		RETURN_MM();
	}

}

