
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"


/**
 * added this class to handle all the global options
 * which are available when yaf.so is loaded
 *
 */
/**
 * @namespace
 */
/**
 * yaf gloab definitions
 */
/*globals_set("Yaf\\VERSION", "2.2.9");
globals_set("Yaf\\ERR\\STARTUP_FAILED", 512);
globals_set("Yaf\\ERR\\ROUTE_FAILED", 513);
globals_set("Yaf\\ERR\\DISPATCH_FAILED", 514);
globals_set("Yaf\\ERR\\AUTOLOAD_FAILED", 520);
globals_set("Yaf\\ERR\\NOTFOUND\\MODULE", 515);
globals_set("Yaf\\ERR\\NOTFOUND\\CONTROLLER", 516);
globals_set("Yaf\\ERR\\NOTFOUND\\ACTION", 517);
globals_set("Yaf\\ERR\\NOTFOUND\\VIEW", 518);
globals_set("Yaf\\ERR\\CALL_FAILED", 519);
globals_set("Yaf\\ERR\\TYPE_ERROR", 521);
*/
ZEPHIR_INIT_CLASS(Yaf_g) {

	ZEPHIR_REGISTER_CLASS(Yaf, g, yaf, g, yaf_g_method_entry, 0);

	zend_declare_property_null(yaf_g_ce, SL("_globals"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(yaf_g_ce, SL("_ini"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_g, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "getglobals", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "getini", NULL);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_g, getGlobals) {

	zval *globals = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(globals);
	zephir_read_static_property_ce(&globals, yaf_g_ce, SL("_globals") TSRMLS_CC);
	if (Z_TYPE_P(globals) == IS_NULL) {
		ZEPHIR_INIT_NVAR(globals);
		array_init_size(globals, 19);
		zephir_array_update_string(&globals, SL("throwException"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&globals, SL("catchException"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(globals, SS("autoload_started"), 0);
		zephir_array_update_string(&globals, SL("configs"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&globals, SL("directory"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&globals, SL("local_library"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		add_assoc_stringl_ex(globals, SS("ext"), SL("php"), 1);
		add_assoc_stringl_ex(globals, SS("view_ext"), SL("phtml"), 1);
		add_assoc_stringl_ex(globals, SS("default_module"), SL("Index"), 1);
		add_assoc_stringl_ex(globals, SS("default_controller"), SL("Index"), 1);
		add_assoc_stringl_ex(globals, SS("default_action"), SL("index"), 1);
		add_assoc_stringl_ex(globals, SS("bootstrap"), SL("Bootstrap"), 1);
		zephir_array_update_string(&globals, SL("modules"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&globals, SL("default_route"), &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		zephir_update_static_property_ce(yaf_g_ce, SL("_globals"), &globals TSRMLS_CC);
	}
	RETURN_CCTOR(globals);

}

PHP_METHOD(Yaf_g, getIni) {

	zval *ini = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(ini);
	zephir_read_static_property_ce(&ini, yaf_g_ce, SL("_ini") TSRMLS_CC);
	if (Z_TYPE_P(ini) == IS_NULL) {
		ZEPHIR_INIT_NVAR(ini);
		array_init_size(ini, 17);
		add_assoc_stringl_ex(ini, SS("yaf.library"), SL(""), 1);
		zephir_array_update_string(&ini, SL("yaf.action_prefer"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&ini, SL("yaf.lowcase_path"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&ini, SL("yaf.use_spl_autoload"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		add_assoc_long_ex(ini, SS("yaf.forward_limit"), 5);
		zephir_array_update_string(&ini, SL("yaf.name_suffix"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		add_assoc_stringl_ex(ini, SS("yaf.name_separator"), SL(""), 1);
		zephir_array_update_string(&ini, SL("yaf.cache_config"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&ini, SL("yaf.st_compatible"), &ZEPHIR_GLOBAL(global_false), PH_COPY | PH_SEPARATE);
		add_assoc_stringl_ex(ini, SS("yaf.environ"), SL("product"), 1);
		zephir_array_update_string(&ini, SL("yaf.use_namespace"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		zephir_update_static_property_ce(yaf_g_ce, SL("_ini"), &ini TSRMLS_CC);
	}
	RETURN_CCTOR(ini);

}

PHP_METHOD(Yaf_g, iniSet) {

	zval *key, *value;

	zephir_fetch_params(0, 2, 0, &key, &value);



	zephir_update_static_property_array_multi_ce(yaf_g_ce, SL("_ini"), &value TSRMLS_CC, SL("z"), 1, key);

}

PHP_METHOD(Yaf_g, iniGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *key, *iniValue = NULL, *value = NULL, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key);



	ZEPHIR_CALL_FUNCTION(&iniValue, "ini_get", &_0, key);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(iniValue)) {
		if (ZEPHIR_IS_LONG(iniValue, 0)) {
			ZEPHIR_INIT_VAR(value);
			ZVAL_BOOL(value, 0);
		} else if (ZEPHIR_IS_LONG(iniValue, 1)) {
			ZEPHIR_INIT_NVAR(value);
			ZVAL_BOOL(value, 1);
		} else {
			ZEPHIR_CPY_WRT(value, iniValue);
		}
		ZEPHIR_CALL_SELF(NULL, "iniset", NULL, key, value);
		zephir_check_call_status();
		RETURN_CCTOR(value);
	} else {
		_1 = zephir_fetch_static_property_ce(yaf_g_ce, SL("_ini") TSRMLS_CC);
		if (zephir_array_isset(_1, key)) {
			_2 = zephir_fetch_static_property_ce(yaf_g_ce, SL("_ini") TSRMLS_CC);
			zephir_array_fetch(&_3, _2, key, PH_NOISY | PH_READONLY, "yaf/g.zep", 112 TSRMLS_CC);
			RETURN_CTOR(_3);
		}
	}
	RETURN_MM_NULL();

}

PHP_METHOD(Yaf_g, set) {

	zval *key, *value;

	zephir_fetch_params(0, 2, 0, &key, &value);



	zephir_update_static_property_array_multi_ce(yaf_g_ce, SL("_globals"), &value TSRMLS_CC, SL("z"), 1, key);

}

PHP_METHOD(Yaf_g, get) {

	zval *key, *_0, *_1, *_2;

	zephir_fetch_params(0, 1, 0, &key);



	_0 = zephir_fetch_static_property_ce(yaf_g_ce, SL("_globals") TSRMLS_CC);
	if (zephir_array_isset(_0, key)) {
		_1 = zephir_fetch_static_property_ce(yaf_g_ce, SL("_globals") TSRMLS_CC);
		zephir_array_fetch(&_2, _1, key, PH_NOISY | PH_READONLY, "yaf/g.zep", 127 TSRMLS_CC);
		RETURN_CTORW(_2);
	}
	RETURN_NULL();

}

PHP_METHOD(Yaf_g, isAbsolutePath) {

	zend_bool _3, _6;
	zval *path, _0, _1, *_2, _4, *_5, *_7, _8, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path);



	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, 0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, 1);
	ZEPHIR_INIT_VAR(_2);
	zephir_substr(_2, path, 0 , 1 , 0);
	_3 = ZEPHIR_IS_STRING(_2, "/");
	if (!(_3)) {
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_STRING(&_4, ":", 0);
		ZEPHIR_INIT_VAR(_5);
		zephir_fast_strpos(_5, path, &_4, 0 );
		_6 = !ZEPHIR_IS_FALSE_IDENTICAL(_5);
		if (_6) {
			ZEPHIR_INIT_VAR(_7);
			ZEPHIR_GET_CONSTANT(_7, "PHP_OS");
			ZEPHIR_SINIT_VAR(_8);
			ZVAL_STRING(&_8, "WIN", 0);
			ZEPHIR_INIT_VAR(_9);
			zephir_fast_strpos(_9, _7, &_8, 0 );
			_6 = !ZEPHIR_IS_FALSE_IDENTICAL(_9);
		}
		_3 = _6;
	}
	if (_3) {
		RETURN_MM_BOOL(1);
	} else {
		RETURN_MM_BOOL(0);
	}

}

