
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
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "kernel/require.h"


/**
 * Yaf loader
 * @todo
 * check if local namespace from application.ini with , as sep would be
 * transformed to :
 *
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Loader) {

	ZEPHIR_REGISTER_CLASS(Yaf, Loader, yaf, loader, yaf_loader_method_entry, 0);

	/**
	 * @var Yaf_Loader instance
	 */
	zend_declare_property_null(yaf_loader_ce, SL("_instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * @var string default library path
	 */
	zend_declare_property_null(yaf_loader_ce, SL("_library"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string global library path
	 */
	zend_declare_property_null(yaf_loader_ce, SL("_globalLibrary"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string Namespace of classes within this resource
	 */
	zend_declare_property_string(yaf_loader_ce, SL("_localNamespace"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_RESERVERD"), "Yaf_" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_CONTROLLER"), "Controller" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_MODEL"), "Model" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_PLUGIN"), "Plugin" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_DAO"), "Dao_" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LOADER_SERVICE"), "Service_" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_LIBRARY_DIRECTORY_NAME"), "library" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_CONTROLLER_DIRECTORY_NAME"), "controllers" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_PLUGIN_DIRECTORY_NAME"), "plugins" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_MODULE_DIRECTORY_NAME"), "modules" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_VIEW_DIRECTORY_NAME"), "views" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_MODEL_DIRECTORY_NAME"), "models" TSRMLS_CC);

	zend_declare_class_constant_string(yaf_loader_ce, SL("YAF_DEFAULT_VIEW_EXT"), "phtml" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yaf_Loader, internal_autoload) {

	HashTable *_6;
	HashPosition _5;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool autoload = 0, _0, _1;
	zval *classs, *dirs = NULL, *file = NULL, *dirPath = NULL, *dir = NULL, *key = NULL, *_3 = NULL, _4, **_7, _8 = zval_used_for_init, *_9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &classs, &dirs);

	if (!dirs) {
		ZEPHIR_CPY_WRT(dirs, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(dirs);
	}


	_0 = zephir_class_exists(classs, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC);
	if (!(_0)) {
		_0 = zephir_interface_exists(classs, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC);
	}
	if (_0) {
		RETURN_MM_NULL();
	}
	_1 = Z_TYPE_P(dirs) != IS_NULL;
	if (_1) {
		_1 = !(Z_TYPE_P(dirs) == IS_STRING);
	}
	if (_1) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_ce, "Directory argument must be a string", "yaf/loader.zep", 55);
		return;
	}
	if (Z_TYPE_P(dirs) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&dirs, this_ptr, "resolvedirectory", NULL, classs);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&file, this_ptr, "resolveclass", NULL, classs);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(dirs))) {
		ZEPHIR_CALL_FUNCTION(&dirPath, "dirname", &_2, file);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_STRING(&_4, ":", 0);
		zephir_fast_explode(_3, &_4, dirs, LONG_MAX TSRMLS_CC);
		ZEPHIR_CPY_WRT(dirs, _3);
		zephir_is_iterable(dirs, &_6, &_5, 1, 0, "yaf/loader.zep", 76);
		for (
		  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6, &_5)
		) {
			ZEPHIR_GET_HMKEY(key, _6, _5);
			ZEPHIR_GET_HVALUE(dir, _7);
			if (ZEPHIR_IS_STRING(dir, ".")) {
				zephir_array_update_zval(&dirs, key, &dirPath, PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_INIT_NVAR(_3);
				ZEPHIR_SINIT_NVAR(_8);
				ZVAL_STRING(&_8, "\\/", 0);
				zephir_fast_trim(_3, dir, &_8, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
				ZEPHIR_CPY_WRT(dir, _3);
				ZEPHIR_INIT_LNVAR(_9);
				ZEPHIR_CONCAT_VSV(_9, dir, "/", dirPath);
				zephir_array_update_zval(&dirs, key, &_9, PH_COPY | PH_SEPARATE);
			}
		}
		ZEPHIR_INIT_NVAR(_3);
		zephir_basename(_3, file TSRMLS_CC);
		ZEPHIR_CPY_WRT(file, _3);
		ZEPHIR_RETURN_CALL_SELF("import", NULL, file, dirs);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_RETURN_CALL_SELF("import", NULL, file);
		zephir_check_call_status();
		RETURN_MM();
	}

}

/**
 * Attempt to autoload a class
 *
 * @param  string $class
 * @return mixed False if not matched, otherwise result if include operation
 */
PHP_METHOD(Yaf_Loader, autoload) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL, *_12 = NULL, *_13 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool autoload = 0, _0, _10, _14;
	zval *classs_param = NULL, *className = NULL, *appDir = NULL, *directory = NULL, *splAutoLoadIni = NULL, _1, *_2, *_3 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_11 = NULL, *_15 = NULL, *_16;
	zval *classs = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs_param);

	zephir_get_strval(classs, classs_param);


	ZEPHIR_CPY_WRT(className, classs);
	_0 = zephir_class_exists(className, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC);
	if (!(_0)) {
		_0 = zephir_interface_exists(className, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC);
	}
	if (_0) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "Yaf_", 0);
	ZEPHIR_INIT_VAR(_2);
	zephir_fast_strpos(_2, classs, &_1, 0 );
	if (ZEPHIR_IS_LONG_IDENTICAL(_2, 0)) {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, yaf_exception_ce);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_SSS(_4, "You should not use ", "Yaf_", " as class name prefix");
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, _4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "yaf/loader.zep", 103 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "directory", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&appDir, yaf_g_ce, "get", &_5, _3);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(directory);
	ZVAL_STRING(directory, "", 1);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "Model", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "iscategorytype", NULL, classs, _3);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	if (zephir_is_true(_6)) {
		ZEPHIR_INIT_NVAR(directory);
		ZEPHIR_CONCAT_VSSS(directory, appDir, "/", "models", "/");
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "Model", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_7, this_ptr, "resolvecategory", NULL, classs, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		zephir_get_strval(classs, _7);
	} else {
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "Plugin", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_7, this_ptr, "iscategorytype", NULL, classs, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		if (zephir_is_true(_7)) {
			ZEPHIR_INIT_NVAR(directory);
			ZEPHIR_CONCAT_VSS(directory, appDir, "/", "plugins");
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "Plugin", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&_8, this_ptr, "resolvecategory", NULL, classs, _3);
			zephir_check_temp_parameter(_3);
			zephir_check_call_status();
			zephir_get_strval(classs, _8);
		} else {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "Controller", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&_8, this_ptr, "iscategorytype", NULL, classs, _3);
			zephir_check_temp_parameter(_3);
			zephir_check_call_status();
			if (zephir_is_true(_8)) {
				ZEPHIR_INIT_NVAR(directory);
				ZEPHIR_CONCAT_VSS(directory, appDir, "/", "controllers");
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_STRING(_3, "Controller", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_METHOD(&_9, this_ptr, "resolvecategory", NULL, classs, _3);
				zephir_check_temp_parameter(_3);
				zephir_check_call_status();
				zephir_get_strval(classs, _9);
			} else {
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_STRING(_3, "Dao_", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_METHOD(&_9, this_ptr, "iscategorytype", NULL, classs, _3);
				zephir_check_temp_parameter(_3);
				zephir_check_call_status();
				_10 = zephir_is_true(_9);
				if (!(_10)) {
					ZEPHIR_INIT_NVAR(_3);
					ZVAL_STRING(_3, "Service_", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_11, this_ptr, "iscategorytype", NULL, classs, _3);
					zephir_check_temp_parameter(_3);
					zephir_check_call_status();
					_10 = zephir_is_true(_11);
				}
				if (_10) {
					ZEPHIR_INIT_NVAR(directory);
					ZEPHIR_CONCAT_VSS(directory, appDir, "/", "models");
				}
			}
		}
	}
	_10 = !ZEPHIR_IS_STRING(directory, "");
	if (_10) {
		_10 = ZEPHIR_IS_STRING(appDir, "");
	}
	if (_10) {
		ZEPHIR_INIT_LNVAR(_4);
		ZEPHIR_CONCAT_SS(_4, "Couldn't load a framework MVC class without an ", "Yaf_Application initializing ");
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 512);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_12, _4, _3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "yaf.use_spl_autoload", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&splAutoLoadIni, yaf_g_ce, "iniget", &_13, _3);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "internal_autoload", NULL, classs, directory);
	zephir_check_call_status();
	if (zephir_is_true(_7)) {
		_14 = !(zephir_class_exists(className, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC));
		if (_14) {
			_14 = !(zephir_interface_exists(className, zephir_is_true((autoload ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)))  TSRMLS_CC));
		}
		if (_14) {
			if (ZEPHIR_IS_FALSE(splAutoLoadIni)) {
				ZEPHIR_INIT_VAR(_15);
				ZEPHIR_CONCAT_SVSV(_15, "Could not find class ", className, " in ", directory);
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_LONG(_3, 256);
				ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_12, _15, _3);
				zephir_check_call_status();
			} else {
				RETURN_MM_BOOL(0);
			}
		}
	} else {
		if (ZEPHIR_IS_FALSE(splAutoLoadIni)) {
			ZEPHIR_INIT_LNVAR(_15);
			if (!ZEPHIR_IS_STRING(directory, "")) {
				ZEPHIR_CPY_WRT(_15, directory);
			} else {
				ZEPHIR_CALL_METHOD(&_15, this_ptr, "resolvedirectory", NULL, classs);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "resolveclass", NULL, classs);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_16);
			ZEPHIR_CONCAT_SVSV(_16, "Could not find script ", _15, "/", _7);
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_LONG(_3, 512);
			ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_12, _16, _3);
			zephir_check_call_status();
		} else {
			RETURN_MM_BOOL(0);
		}
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(Yaf_Loader, isCategoryType) {

	zend_bool _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *className, *category, *nameSeparator = NULL, *_1 = NULL, *_2 = NULL, _3 = zval_used_for_init, _4 = zval_used_for_init, _6 = zval_used_for_init, _7 = zval_used_for_init, *_8 = NULL, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &className, &category);



	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yaf.name_separator", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&nameSeparator, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "yaf.name_suffix", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_2, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE(_2)) {
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, (zephir_fast_strlen_ev(className) - zephir_fast_strlen_ev(category)));
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_LONG(&_4, zephir_fast_strlen_ev(category));
		ZEPHIR_INIT_NVAR(_1);
		zephir_substr(_1, className, zephir_get_intval(&_3), zephir_get_intval(&_4), 0);
		if (ZEPHIR_IS_EQUAL(category, _1)) {
			_5 = ZEPHIR_IS_STRING(nameSeparator, "");
			if (!(_5)) {
				ZEPHIR_SINIT_VAR(_6);
				ZVAL_LONG(&_6, ((zephir_fast_strlen_ev(className) - zephir_fast_strlen_ev(category)) - zephir_fast_strlen_ev(nameSeparator)));
				ZEPHIR_SINIT_VAR(_7);
				ZVAL_LONG(&_7, zephir_fast_strlen_ev(nameSeparator));
				ZEPHIR_INIT_VAR(_8);
				zephir_substr(_8, className, zephir_get_intval(&_6), zephir_get_intval(&_7), 0);
				_5 = ZEPHIR_IS_EQUAL(_8, nameSeparator);
			}
			if (_5) {
				RETURN_MM_BOOL(1);
			}
		}
	} else {
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_LONG(&_3, 0);
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_LONG(&_4, zephir_fast_strlen_ev(category));
		ZEPHIR_INIT_NVAR(_8);
		zephir_substr(_8, className, 0 , zephir_get_intval(&_4), 0);
		if (ZEPHIR_IS_EQUAL(category, _8)) {
			_5 = ZEPHIR_IS_STRING(nameSeparator, "");
			if (!(_5)) {
				ZEPHIR_SINIT_NVAR(_6);
				ZVAL_LONG(&_6, zephir_fast_strlen_ev(category));
				ZEPHIR_SINIT_NVAR(_7);
				ZVAL_LONG(&_7, zephir_fast_strlen_ev(nameSeparator));
				ZEPHIR_INIT_VAR(_9);
				zephir_substr(_9, className, zephir_get_intval(&_6), zephir_get_intval(&_7), 0);
				_5 = ZEPHIR_IS_EQUAL(_9, nameSeparator);
			}
			if (_5) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Loader, resolveCategory) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *className, *category, *nameSeparator = NULL, *_1 = NULL, *_2 = NULL, _3 = zval_used_for_init, _4 = zval_used_for_init;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &className, &category);



	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yaf.name_separator", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&nameSeparator, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "yaf.name_suffix", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_2, yaf_g_ce, "iniget", &_0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE(_2)) {
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, 0);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_LONG(&_4, ((zephir_fast_strlen_ev(className) - zephir_fast_strlen_ev(category)) - zephir_fast_strlen_ev(nameSeparator)));
		zephir_substr(return_value, className, 0 , zephir_get_intval(&_4), 0);
		RETURN_MM();
	} else {
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_LONG(&_3, (zephir_fast_strlen_ev(category) - zephir_fast_strlen_ev(nameSeparator)));
		ZEPHIR_SINIT_NVAR(_4);
		ZVAL_LONG(&_4, zephir_fast_strlen_ev(className));
		zephir_substr(return_value, className, zephir_get_intval(&_3), zephir_get_intval(&_4), 0);
		RETURN_MM();
	}

}

PHP_METHOD(Yaf_Loader, resolveDirectory) {

	zval *_2;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *classs, *directory = NULL, *_0 = NULL, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "islocalname", NULL, classs);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		ZEPHIR_OBS_VAR(directory);
		zephir_read_property_this(&directory, this_ptr, SL("_library"), PH_NOISY_CC);
	} else {
		ZEPHIR_OBS_NVAR(directory);
		zephir_read_property_this(&directory, this_ptr, SL("_globalLibrary"), PH_NOISY_CC);
	}
	if (ZEPHIR_IS_STRING(directory, "")) {
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_SS(_2, "Yaf_Loader requires Yaf_Application", "(which set the library_directory) to be initialized first");
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, 512);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_1, _2, _3);
		zephir_check_call_status();
	}
	RETURN_CCTOR(directory);

}

PHP_METHOD(Yaf_Loader, resolveClass) {

	HashTable *_10;
	HashPosition _9;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_8 = NULL, *_13 = NULL;
	zval *classs, *className = NULL, *file = NULL, *namespacee = NULL, *lastNsPos = NULL, *segments, *value = NULL, *key = NULL, _0, _1 = zval_used_for_init, _3 = zval_used_for_init, *_4 = NULL, _5 = zval_used_for_init, _6, *_7 = NULL, **_11, *_12 = NULL, *_14 = NULL, *_15 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs);



	ZEPHIR_INIT_VAR(className);
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "\\", 0);
	zephir_fast_trim(className, classs, &_0, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	ZEPHIR_INIT_VAR(file);
	ZVAL_STRING(file, "", 1);
	ZEPHIR_INIT_VAR(namespacee);
	ZVAL_STRING(namespacee, "", 1);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "\\", 0);
	ZEPHIR_CALL_FUNCTION(&lastNsPos, "strripos", &_2, className, &_1);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(lastNsPos)) {
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, 0);
		ZEPHIR_INIT_NVAR(namespacee);
		zephir_substr(namespacee, className, 0 , zephir_get_intval(lastNsPos), 0);
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, (zephir_get_numberval(lastNsPos) + 1));
		ZEPHIR_INIT_VAR(_4);
		zephir_substr(_4, className, zephir_get_intval(&_3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_CPY_WRT(className, _4);
		ZEPHIR_INIT_NVAR(_4);
		ZEPHIR_SINIT_VAR(_5);
		ZVAL_STRING(&_5, "\\", 0);
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "/", 0);
		zephir_fast_str_replace(_4, &_5, &_6, namespacee TSRMLS_CC);
		ZEPHIR_INIT_NVAR(file);
		ZEPHIR_CONCAT_VS(file, _4, "/");
	}
	ZEPHIR_INIT_NVAR(_4);
	ZVAL_STRING(_4, "yaf.lowcase_path", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_7, yaf_g_ce, "iniget", &_8, _4);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE(_7)) {
		ZEPHIR_INIT_NVAR(_4);
		zephir_fast_strtolower(_4, file);
		ZEPHIR_CPY_WRT(file, _4);
		ZEPHIR_INIT_VAR(segments);
		zephir_fast_explode_str(segments, SL("_"), className, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(segments, &_10, &_9, 0, 0, "yaf/loader.zep", 255);
		for (
		  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
		  ; zephir_hash_move_forward_ex(_10, &_9)
		) {
			ZEPHIR_GET_HMKEY(key, _10, _9);
			ZEPHIR_GET_HVALUE(value, _11);
			if (!ZEPHIR_IS_LONG(key, (zephir_fast_count_int(segments TSRMLS_CC) - 1))) {
				ZEPHIR_INIT_NVAR(_4);
				zephir_fast_strtolower(_4, value);
				ZEPHIR_CPY_WRT(value, _4);
			}
		}
		ZEPHIR_INIT_NVAR(_4);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, "/", 0);
		zephir_fast_join(_4, &_3, segments TSRMLS_CC);
		ZEPHIR_INIT_VAR(_14);
		ZVAL_STRING(_14, "ext", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_12, yaf_g_ce, "get", &_13, _14);
		zephir_check_temp_parameter(_14);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_15);
		ZEPHIR_CONCAT_VSV(_15, _4, ".", _12);
		zephir_concat_self(&file, _15 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_4);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, "_", 0);
		ZEPHIR_SINIT_NVAR(_5);
		ZVAL_STRING(&_5, "/", 0);
		zephir_fast_str_replace(_4, &_3, &_5, className TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_14);
		ZVAL_STRING(_14, "ext", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_12, yaf_g_ce, "get", &_13, _14);
		zephir_check_temp_parameter(_14);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_15);
		ZEPHIR_CONCAT_VSV(_15, _4, ".", _12);
		zephir_concat_self(&file, _15 TSRMLS_CC);
	}
	RETURN_CCTOR(file);

}

/**
 * Loads a PHP file.  This is a wrapper for PHP's include() function.
 *
 * $filename must be the complete filename, including any
 * extension such as ".php".  Note that a security check is performed that
 * does not permit extended characters in the filename.  This method is
 * intended for loading Zend Framework files.
 *
 * If $dirs is a string or an array, it will search the directories
 * in the order supplied, and attempt to load the first matching file.
 *
 * If the file was not found in the $dirs, or if no $dirs were specified,
 * it will attempt to load it from PHP's include_path.
 *
 *
 * @param  string        $filename
 * @param  string|array  $dirs - OPTIONAL either a path or array of paths
 *                       to search.
 * @return boolean
 */
PHP_METHOD(Yaf_Loader, import) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL;
	zend_bool _0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *filename_param = NULL, *dirs = NULL, *loader = NULL, *incPath = NULL, *_2, _3, *_5;
	zval *filename = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &filename_param, &dirs);

	zephir_get_strval(filename, filename_param);
	if (!dirs) {
		ZEPHIR_CPY_WRT(dirs, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(dirs);
	}


	ZEPHIR_CALL_SELF(&loader, "getinstance", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, loader, "_securitycheck", NULL, filename);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(incPath);
	ZVAL_BOOL(incPath, 0);
	_0 = !(ZEPHIR_IS_EMPTY(dirs));
	if (_0) {
		_1 = Z_TYPE_P(dirs) == IS_ARRAY;
		if (!(_1)) {
			_1 = Z_TYPE_P(dirs) == IS_STRING;
		}
		_0 = _1;
	}
	if (_0) {
		if (Z_TYPE_P(dirs) == IS_ARRAY) {
			ZEPHIR_INIT_VAR(_2);
			ZEPHIR_SINIT_VAR(_3);
			ZVAL_STRING(&_3, ":", 0);
			zephir_fast_join(_2, &_3, dirs TSRMLS_CC);
			ZEPHIR_CPY_WRT(dirs, _2);
		}
		ZEPHIR_CALL_FUNCTION(&incPath, "get_include_path", &_4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CONCAT_VSV(_5, dirs, ":", incPath);
		ZEPHIR_CALL_FUNCTION(NULL, "set_include_path", &_6, _5);
		zephir_check_call_status();
	}
	if ((zephir_file_exists(filename TSRMLS_CC) == SUCCESS)) {
		if (zephir_require_zval(filename TSRMLS_CC) == FAILURE) {
			RETURN_MM_NULL();
		}
	} else {
		RETURN_MM_BOOL(0);
	}
	if (zephir_is_true(incPath)) {
		ZEPHIR_CALL_FUNCTION(NULL, "set_include_path", &_6, incPath);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);

}

/**
 * Ensure that filename does not contain exploits
 *
 * @param  string $filename
 * @return void
 * @throws Yaf_Exception
 */
PHP_METHOD(Yaf_Loader, _securityCheck) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *filename_param = NULL, *_0, *_1 = NULL;
	zval *filename = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &filename_param);

	zephir_get_strval(filename, filename_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "/[^a-z0-9\\/\\\\_.:-]/i", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&_1, "preg_match", &_2, _0, filename);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_ce, "Security check: Illegal character in filename", "yaf/loader.zep", 335);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Loader, clearLocalNamespace) {

	zval *_0;


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_STRING(_0, "", 1);
	zephir_update_property_this(this_ptr, SL("_localNamespace"), _0 TSRMLS_CC);

}

/**
 * not possible to clone
 */
PHP_METHOD(Yaf_Loader, __clone) {



}

/**
 * Constructor
 *
 * @param
 * @return void
 */
PHP_METHOD(Yaf_Loader, __construct) {



}

/**
 * Retrieve singleton instance
 *
 * @return Yaf_Loader
 */
PHP_METHOD(Yaf_Loader, getInstance) {

	zephir_fcall_cache_entry *_5 = NULL;
	zval *_4 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *library = NULL, *globalLibrary = NULL, *instance = NULL, *_0, *_1 = NULL, *_2 = NULL, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &library, &globalLibrary);

	if (!library) {
		library = ZEPHIR_GLOBAL(global_null);
	}
	if (!globalLibrary) {
		globalLibrary = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_static_property_ce(yaf_loader_ce, SL("_instance") TSRMLS_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, yaf_loader_ce);
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
		zephir_check_call_status();
		zephir_update_static_property_ce(yaf_loader_ce, SL("_instance"), &_1 TSRMLS_CC);
		ZEPHIR_OBS_VAR(instance);
		zephir_read_static_property_ce(&instance, yaf_loader_ce, SL("_instance") TSRMLS_CC);
		if (Z_TYPE_P(library) != IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_BOOL(_1, 0);
			ZEPHIR_CALL_METHOD(NULL, instance, "setlibrarypath", NULL, library, _1);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(globalLibrary) != IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_BOOL(_1, 1);
			ZEPHIR_CALL_METHOD(NULL, instance, "setlibrarypath", NULL, globalLibrary, _1);
			zephir_check_call_status();
		} else {
			if (Z_TYPE_P(library) != IS_NULL) {
				ZEPHIR_INIT_NVAR(_1);
				ZVAL_BOOL(_1, 1);
				ZEPHIR_CALL_METHOD(NULL, instance, "setlibrarypath", NULL, library, _1);
				zephir_check_call_status();
			}
		}
		ZEPHIR_CALL_FUNCTION(&_2, "phpversion", &_3);
		zephir_check_call_status();
		if ((_2, "5.3")) {
			ZEPHIR_INIT_VAR(_4);
			array_init_size(_4, 3);
			zephir_array_fast_append(_4, instance);
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "autoload", 1);
			zephir_array_fast_append(_4, _1);
			ZEPHIR_CALL_FUNCTION(NULL, "spl_autoload_register", &_5, _4, ZEPHIR_GLOBAL(global_true), ZEPHIR_GLOBAL(global_false));
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_4);
			array_init_size(_4, 3);
			zephir_array_fast_append(_4, instance);
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "autoload", 1);
			zephir_array_fast_append(_4, _1);
			ZEPHIR_CALL_FUNCTION(NULL, "spl_autoload_register", &_5, _4, ZEPHIR_GLOBAL(global_true));
			zephir_check_call_status();
		}
	} else {
		ZEPHIR_OBS_NVAR(instance);
		zephir_read_static_property_ce(&instance, yaf_loader_ce, SL("_instance") TSRMLS_CC);
		if (Z_TYPE_P(library) != IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_BOOL(_1, 0);
			ZEPHIR_CALL_METHOD(NULL, instance, "setlibrarypath", NULL, library, _1);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(globalLibrary) != IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_BOOL(_1, 1);
			ZEPHIR_CALL_METHOD(NULL, instance, "setlibrarypath", NULL, globalLibrary, _1);
			zephir_check_call_status();
		}
	}
	_6 = zephir_fetch_static_property_ce(yaf_loader_ce, SL("_instance") TSRMLS_CC);
	RETURN_CTOR(_6);

}

/**
 * Get base path to this set of resources
 *
 * @return string
 */
PHP_METHOD(Yaf_Loader, getLibraryPath) {

	zval *isGlobal = NULL;

	zephir_fetch_params(0, 0, 1, &isGlobal);

	if (!isGlobal) {
		isGlobal = ZEPHIR_GLOBAL(global_false);
	}


	if (ZEPHIR_IS_TRUE(isGlobal)) {
		RETURN_MEMBER(this_ptr, "_globalLibrary");
	} else {
		RETURN_MEMBER(this_ptr, "_library");
	}

}

/**
 * Get namespace this autoloader handles
 *
 * @return string
 */
PHP_METHOD(Yaf_Loader, getLocalNamespace) {


	RETURN_MEMBER(this_ptr, "_localNamespace");

}

PHP_METHOD(Yaf_Loader, isLocalName) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *className = NULL, *namespaces = NULL, *prefix = NULL, *pos = NULL, *classs = NULL, *prefixes, *_0, _1, _2, _3 = zval_used_for_init, _4 = zval_used_for_init, _5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &className);

	ZEPHIR_SEPARATE_PARAM(className);


	ZEPHIR_CALL_METHOD(&namespaces, this_ptr, "getlocalnamespace", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(namespaces) == IS_NULL) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "\\", 0);
	zephir_fast_trim(_0, className, &_1, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	ZEPHIR_CPY_WRT(className, _0);
	ZEPHIR_INIT_VAR(prefix);
	ZVAL_STRING(prefix, "", 1);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "_", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, className, &_2, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, 0);
		ZEPHIR_INIT_NVAR(prefix);
		zephir_substr(prefix, className, 0 , zephir_get_intval(pos), 0);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_LONG(&_4, (zephir_get_numberval(pos) + 1));
		ZEPHIR_INIT_VAR(classs);
		zephir_substr(classs, className, zephir_get_intval(&_4), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	} else {
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, "\\", 0);
		ZEPHIR_INIT_NVAR(pos);
		zephir_fast_strpos(pos, className, &_3, 0 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
			ZEPHIR_SINIT_NVAR(_4);
			ZVAL_LONG(&_4, 0);
			ZEPHIR_INIT_NVAR(prefix);
			zephir_substr(prefix, className, 0 , zephir_get_intval(pos), 0);
			ZEPHIR_SINIT_VAR(_5);
			ZVAL_LONG(&_5, (zephir_get_numberval(pos) + 1));
			ZEPHIR_INIT_NVAR(classs);
			zephir_substr(classs, className, zephir_get_intval(&_5), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		}
	}
	if (ZEPHIR_IS_STRING(prefix, "")) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(prefixes);
	ZEPHIR_SINIT_NVAR(_3);
	ZVAL_STRING(&_3, ":", 0);
	zephir_fast_explode(prefixes, &_3, namespaces, LONG_MAX TSRMLS_CC);
	if (zephir_fast_in_array(prefix, prefixes TSRMLS_CC)) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * register a namespace for the loader
 *
 * @param  string|array $namespace
 * * @throws Yaf_Exception if namespace is not string or array
 */
PHP_METHOD(Yaf_Loader, registerLocalNamespace) {

	HashTable *_5;
	HashPosition _4;
	zval *_2 = NULL;
	zend_bool _0;
	zval *namespacee, *directorySeparator, *value = NULL, *_1, *_3 = NULL, **_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &namespacee);



	_0 = !(Z_TYPE_P(namespacee) == IS_STRING);
	if (_0) {
		_0 = !(Z_TYPE_P(namespacee) == IS_ARRAY);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_ce, "Invalid parameters provided, must be a string, or an array", "yaf/loader.zep", 486);
		return;
	}
	ZEPHIR_INIT_VAR(directorySeparator);
	ZVAL_STRING(directorySeparator, ":", 1);
	if (Z_TYPE_P(namespacee) == IS_STRING) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_localNamespace"), PH_NOISY_CC);
		if (ZEPHIR_IS_STRING(_1, "")) {
			zephir_update_property_this(this_ptr, SL("_localNamespace"), directorySeparator TSRMLS_CC);
		}
		zephir_get_strval(_2, namespacee);
		ZEPHIR_INIT_VAR(_3);
		ZEPHIR_CONCAT_VV(_3, _2, directorySeparator);
		zephir_update_property_this(this_ptr, SL("_localNamespace"), _3 TSRMLS_CC);
	} else {
		if (Z_TYPE_P(namespacee) == IS_ARRAY) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_localNamespace"), PH_NOISY_CC);
			if (ZEPHIR_IS_STRING(_1, "")) {
				zephir_update_property_this(this_ptr, SL("_localNamespace"), directorySeparator TSRMLS_CC);
			}
			zephir_is_iterable(namespacee, &_5, &_4, 0, 0, "yaf/loader.zep", 506);
			for (
			  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			  ; zephir_hash_move_forward_ex(_5, &_4)
			) {
				ZEPHIR_GET_HVALUE(value, _6);
				ZEPHIR_INIT_LNVAR(_3);
				ZEPHIR_CONCAT_VV(_3, value, directorySeparator);
				zephir_update_property_this(this_ptr, SL("_localNamespace"), _3 TSRMLS_CC);
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Set base path for this set of resources
 *
 * @param  string $path
 * @return void
 */
PHP_METHOD(Yaf_Loader, setLibraryPath) {

	zval *path_param = NULL, *isGlobal = NULL;
	zval *path = NULL, *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &path_param, &isGlobal);

	zephir_get_strval(path, path_param);
	if (!isGlobal) {
		isGlobal = ZEPHIR_GLOBAL(global_false);
	}


	if (ZEPHIR_IS_TRUE(isGlobal)) {
		zephir_get_strval(_0, path);
		zephir_update_property_this(this_ptr, SL("_globalLibrary"), _0 TSRMLS_CC);
	} else {
		zephir_get_strval(_1, path);
		zephir_update_property_this(this_ptr, SL("_library"), _1 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Loader, __sleep) {



}

PHP_METHOD(Yaf_Loader, __wakeup) {



}

