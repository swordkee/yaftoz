
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
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/string.h"


/**
 * Yaf Config Ini
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Config_Ini) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Config, Ini, yaf, config_ini, yaf_config_simple_ce, yaf_config_ini_method_entry, 0);

	return SUCCESS;

}

/**
 * Loads the section $section from the config file $filename for
 * access facilitated by nested object properties.
 *
 * If the section name contains a ":" then the section name to the right
 * is loaded and included into the properties. Note that the keys in
 * this $section will override any keys of the same
 * name in the sections that have been included via ":".
 *
 * If the $section is null, then all sections in the ini file are loaded.
 *
 * If any key includes a ".", then this will act as a separator to
 * create a sub-property.
 *
 * example ini file:
 *      [all]
 *      db.connection = database
 *      hostname = live
 *
 *      [staging : all]
 *      hostname = staging
 *
 * after calling $data = new Yaf_Config_Ini($file, 'staging'); then
 *      $data->hostname === "staging"
 *      $data->db->connection === "database"
 *
 * @param  string        $filename
 * @param  mixed         $section
 * @param  boolean $readonly
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Ini, __construct) {

	zephir_fcall_cache_entry *_8 = NULL, *_9 = NULL, *_10 = NULL;
	HashTable *_4, *_14;
	HashPosition _3, _13;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_11 = NULL;
	zval *filename_param = NULL, *section = NULL, *iniArray = NULL, *dataArray = NULL, *sectionName = NULL, *sectionData = NULL, *_2 = NULL, **_5, *_6 = NULL, *_7 = NULL, *_12 = NULL, **_15;
	zval *filename = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &filename_param, &section);

	zephir_get_strval(filename, filename_param);
	if (!section) {
		section = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(dataArray);
	array_init(dataArray);
	ZEPHIR_INIT_VAR(iniArray);
	array_init(iniArray);
	ZEPHIR_INIT_VAR(sectionData);
	array_init(sectionData);
	if (ZEPHIR_IS_EMPTY(filename)) {
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "Unable to find config file ", filename);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 256);
		ZEPHIR_CALL_CE_STATIC(NULL, yaf_exception_ce, "trigger_error", &_0, _1, _2);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(filename) == IS_ARRAY) {
		zephir_update_property_this(this_ptr, SL("_config"), filename TSRMLS_CC);
	} else if (Z_TYPE_P(filename) == IS_STRING) {
		ZEPHIR_CALL_METHOD(&iniArray, this_ptr, "_loadinifile", NULL, filename);
		zephir_check_call_status();
		if (Z_TYPE_P(section) == IS_NULL) {
			zephir_is_iterable(iniArray, &_4, &_3, 0, 0, "yaf/Config/ini.zep", 69);
			for (
			  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
			  ; zephir_hash_move_forward_ex(_4, &_3)
			) {
				ZEPHIR_GET_HMKEY(sectionName, _4, _3);
				ZEPHIR_GET_HVALUE(sectionData, _5);
				if (!(Z_TYPE_P(sectionData) == IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(_2);
					array_init(_2);
					ZEPHIR_CALL_METHOD(&_7, this_ptr, "_processkey", &_8, _2, sectionName, sectionData);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_6, this_ptr, "_arraymergerecursive", &_9, dataArray, _7);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(dataArray, _6);
				} else {
					ZEPHIR_CALL_METHOD(&_6, this_ptr, "_processsection", &_10, iniArray, sectionName);
					zephir_check_call_status();
					zephir_array_update_zval(&dataArray, sectionName, &_6, PH_COPY | PH_SEPARATE);
				}
			}
			ZEPHIR_INIT_VAR(_12);
			ZVAL_BOOL(_12, 1);
			ZEPHIR_CALL_PARENT(NULL, yaf_config_ini_ce, this_ptr, "__construct", &_11, dataArray, _12);
			zephir_check_call_status();
		} else {
			if (!(Z_TYPE_P(section) == IS_ARRAY)) {
				ZEPHIR_INIT_NVAR(section);
				array_init_size(section, 2);
				zephir_array_fast_append(section, section);
			}
			zephir_is_iterable(section, &_14, &_13, 0, 0, "yaf/Config/ini.zep", 85);
			for (
			  ; zephir_hash_get_current_data_ex(_14, (void**) &_15, &_13) == SUCCESS
			  ; zephir_hash_move_forward_ex(_14, &_13)
			) {
				ZEPHIR_GET_HVALUE(sectionName, _15);
				if (!(zephir_array_isset(iniArray, sectionName))) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_config_exception_ce, "There is no section '{sectionName}' in '{filename}'", "yaf/Config/ini.zep", 81);
					return;
				}
				ZEPHIR_CALL_METHOD(&_7, this_ptr, "_processsection", &_10, iniArray, sectionName);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_6, this_ptr, "_arraymergerecursive", &_9, _7, dataArray);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(dataArray, _6);
			}
			ZEPHIR_INIT_NVAR(_12);
			ZVAL_BOOL(_12, 1);
			ZEPHIR_CALL_PARENT(NULL, yaf_config_ini_ce, this_ptr, "__construct", &_11, dataArray, _12);
			zephir_check_call_status();
		}
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Invalid parameters provided, must be path of ini file", "yaf/Config/ini.zep", 88);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Retrieve a value and return null if there is no element set.
 *
 * @param string $name
 * @param mixed $default
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Ini, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_3;
	HashPosition _2;
	zval *name_param = NULL, *result = NULL, *names, *tmpName = NULL, _0, *_1, **_4, *_5, *_6, *_7, *_8 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	if (!(zephir_fast_strlen_ev(name))) {
		RETURN_THIS();
	}
	ZEPHIR_INIT_VAR(result);
	ZVAL_NULL(result);
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, ".", 0);
	ZEPHIR_INIT_VAR(_1);
	zephir_fast_strpos(_1, name, &_0, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(_1)) {
		ZEPHIR_OBS_NVAR(result);
		zephir_read_property_this(&result, this_ptr, SL("_config"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(names);
		zephir_fast_explode_str(names, SL("."), name, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(names, &_3, &_2, 0, 0, "yaf/Config/ini.zep", 124);
		for (
		  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(tmpName, _4);
			if (zephir_array_isset(result, tmpName)) {
				zephir_array_fetch(&_5, result, tmpName, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 118 TSRMLS_CC);
				ZEPHIR_CPY_WRT(result, _5);
			} else {
				ZEPHIR_INIT_NVAR(result);
				ZVAL_NULL(result);
				break;
			}
		}
	} else {
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
		if (zephir_array_key_exists(_6, name TSRMLS_CC)) {
			_7 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
			ZEPHIR_OBS_NVAR(result);
			zephir_array_fetch(&result, _7, name, PH_NOISY, "yaf/Config/ini.zep", 127 TSRMLS_CC);
		}
	}
	if (Z_TYPE_P(result) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(result);
		object_init_ex(result, yaf_config_ini_ce);
		ZEPHIR_CALL_METHOD(&_8, this_ptr, "readonly", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, result, "__construct", NULL, result, _8);
		zephir_check_call_status();
	}
	RETURN_CCTOR(result);

}

/**
 * Load the INI file from disk using parse_ini_file().
 * @param string $filename
 * @return array
 */
PHP_METHOD(Yaf_Config_Ini, _parseIniFile) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *filename_param = NULL, *iniArray = NULL;
	zval *filename = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &filename_param);

	zephir_get_strval(filename, filename_param);


	ZEPHIR_CALL_FUNCTION(&iniArray, "parse_ini_file", &_0, filename, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	RETURN_CCTOR(iniArray);

}

/**
 * Load the ini file and preprocess the section separator (':' in the
 * section name (that is used for section extension) so that the resultant
 * array has the correct section names and the extension information is
 * stored in a sub-key called ';extends'. We use ';extends' as this can
 * never be a valid key name in an INI file that has been loaded using
 * parse_ini_file().
 *
 * @param string $filename
 * @throws Yaf_Config_Exception
 * @return array
 */
PHP_METHOD(Yaf_Config_Ini, _loadIniFile) {

	zephir_fcall_cache_entry *_9 = NULL;
	zval *_7 = NULL;
	HashTable *_1;
	HashPosition _0;
	int ZEPHIR_LAST_CALL_STATUS, _4;
	zval *filename_param = NULL, *loaded = NULL, *iniArray, *key = NULL, *data = NULL, *pieces = NULL, *thisSection = NULL, *extendedSection = NULL, **_2, *_3, *_5, *_6 = NULL;
	zval *filename = NULL, *_8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &filename_param);

	zephir_get_strval(filename, filename_param);


	ZEPHIR_CALL_METHOD(&loaded, this_ptr, "_parseinifile", NULL, filename);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(iniArray);
	array_init(iniArray);
	zephir_is_iterable(loaded, &_1, &_0, 0, 0, "yaf/Config/ini.zep", 186);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(data, _2);
		ZEPHIR_INIT_NVAR(pieces);
		zephir_fast_explode_str(pieces, SL(":"), key, LONG_MAX TSRMLS_CC);
		ZEPHIR_INIT_NVAR(thisSection);
		zephir_array_fetch_long(&_3, pieces, 0, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 173 TSRMLS_CC);
		zephir_fast_trim(thisSection, _3, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		do {
			_4 = zephir_fast_count_int(pieces TSRMLS_CC);
			if (_4 == 1) {
				zephir_array_update_zval(&iniArray, thisSection, &data, PH_COPY | PH_SEPARATE);
				break;
			}
			if (_4 == 2) {
				ZEPHIR_INIT_NVAR(extendedSection);
				zephir_array_fetch_long(&_5, pieces, 1, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 179 TSRMLS_CC);
				zephir_fast_trim(extendedSection, _5, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				ZEPHIR_INIT_NVAR(_6);
				ZEPHIR_INIT_NVAR(_7);
				array_init_size(_7, 2);
				zephir_array_update_string(&_7, SL(";extends"), &extendedSection, PH_COPY | PH_SEPARATE);
				zephir_fast_array_merge(_6, &(_7), &(data) TSRMLS_CC);
				zephir_array_update_zval(&iniArray, thisSection, &_6, PH_COPY | PH_SEPARATE);
				break;
			}
			ZEPHIR_INIT_NVAR(_6);
			object_init_ex(_6, yaf_config_exception_ce);
			ZEPHIR_INIT_LNVAR(_8);
			ZEPHIR_CONCAT_SS(_8, "Section '{thisSection}' may not extend ", "multiple sections in {filename}");
			ZEPHIR_CALL_METHOD(NULL, _6, "__construct", &_9, _8);
			zephir_check_call_status();
			zephir_throw_exception_debug(_6, "yaf/Config/ini.zep", 183 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} while(0);

	}
	RETURN_CCTOR(iniArray);

}

/**
 * Process each element in the section and handle the ";extends" inheritance
 * key. Passes control to _processKey() to handle the nest separator
 * sub-property syntax that may be used within the key name.
 *
 * @param  array  $iniArray
 * @param  string $section
 * @param  array  $config
 * @throws Yaf_Config_Exception
 * @return array
 */
PHP_METHOD(Yaf_Config_Ini, _processSection) {

	zephir_fcall_cache_entry *_5 = NULL, *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *section = NULL;
	zval *iniArray_param = NULL, *section_param = NULL, *config_param = NULL, *thisSection, *key = NULL, *value = NULL, **_2, *_3 = NULL, *_4 = NULL;
	zval *iniArray = NULL, *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &iniArray_param, &section_param, &config_param);

	zephir_get_arrval(iniArray, iniArray_param);
	zephir_get_strval(section, section_param);
	if (!config_param) {
		ZEPHIR_INIT_VAR(config);
		array_init(config);
	} else {
		zephir_get_arrval(config, config_param);
	}


	ZEPHIR_OBS_VAR(thisSection);
	zephir_array_fetch(&thisSection, iniArray, section, PH_NOISY, "yaf/Config/ini.zep", 204 TSRMLS_CC);
	if (Z_TYPE_P(thisSection) == IS_ARRAY) {
		zephir_is_iterable(thisSection, &_1, &_0, 0, 0, "yaf/Config/ini.zep", 220);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(key, _1, _0);
			ZEPHIR_GET_HVALUE(value, _2);
			ZEPHIR_INIT_NVAR(_3);
			zephir_fast_strtolower(_3, key);
			if (ZEPHIR_IS_STRING(_3, ";extends")) {
				if (zephir_array_isset(iniArray, value)) {
					ZEPHIR_CALL_METHOD(&_4, this_ptr, "_processsection", &_5, iniArray, value, config);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(config, _4);
				} else {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_config_exception_ce, "Parent section '{value}' cannot be found", "yaf/Config/ini.zep", 214);
					return;
				}
			} else {
				ZEPHIR_CALL_METHOD(&_4, this_ptr, "_processkey", &_6, config, key, value);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(config, _4);
			}
		}
	}
	RETURN_CTOR(config);

}

/**
 * Assign the key's value to the property list. Handles the
 * nest separator for sub-properties.
 *
 * @param  array  $config
 * @param  string $key
 * @param  string $value
 * @throws Yaf_Config_Exception
 * @return array
 */
PHP_METHOD(Yaf_Config_Ini, _processKey) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _3, _7;
	zval *key = NULL, *value = NULL, *_10;
	zval *config_param = NULL, *key_param = NULL, *value_param = NULL, *pieces, _0, *_1, *_2, *_4, *_5, *_6, *_8 = NULL, *_9 = NULL, *_11 = NULL, *_12, *_13;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &config_param, &key_param, &value_param);

	zephir_get_arrval(config, config_param);
	zephir_get_strval(key, key_param);
	zephir_get_strval(value, value_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, ".", 0);
	ZEPHIR_INIT_VAR(_1);
	zephir_fast_strpos(_1, key, &_0, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(_1)) {
		ZEPHIR_INIT_VAR(pieces);
		zephir_fast_explode_str(pieces, SL("."), key, 2  TSRMLS_CC);
		zephir_array_fetch_long(&_2, pieces, 0, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 241 TSRMLS_CC);
		_3 = (zephir_fast_strlen_ev(_2)) ? 1 : 0;
		if (_3) {
			zephir_array_fetch_long(&_4, pieces, 1, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 241 TSRMLS_CC);
			_3 = (zephir_fast_strlen_ev(_4)) ? 1 : 0;
		}
		if (_3) {
			zephir_array_fetch_long(&_5, pieces, 0, PH_READONLY, "yaf/Config/ini.zep", 243 TSRMLS_CC);
			if (!(zephir_array_isset(config, _5))) {
				zephir_array_fetch_long(&_6, pieces, 0, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 245 TSRMLS_CC);
				_7 = ZEPHIR_IS_LONG_IDENTICAL(_6, 0);
				if (_7) {
					_7 = !(ZEPHIR_IS_EMPTY(config));
				}
				if (_7) {
					ZEPHIR_INIT_NVAR(config);
					array_init_size(config, 2);
					ZEPHIR_OBS_VAR(_8);
					zephir_array_fetch_long(&_8, pieces, 0, PH_NOISY, "yaf/Config/ini.zep", 247 TSRMLS_CC);
					zephir_array_update_zval(&config, _8, &config, PH_COPY);
				} else {
					ZEPHIR_INIT_VAR(_9);
					array_init(_9);
					ZEPHIR_OBS_NVAR(_8);
					zephir_array_fetch_long(&_8, pieces, 0, PH_NOISY, "yaf/Config/ini.zep", 249 TSRMLS_CC);
					zephir_array_update_zval(&config, _8, &_9, PH_COPY | PH_SEPARATE);
				}
			} else {
				ZEPHIR_OBS_NVAR(_8);
				zephir_array_fetch_long(&_8, pieces, 0, PH_NOISY, "yaf/Config/ini.zep", 253 TSRMLS_CC);
				zephir_array_fetch(&_6, config, _8, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 253 TSRMLS_CC);
				if (!(Z_TYPE_P(_6) == IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(_9);
					object_init_ex(_9, yaf_config_exception_ce);
					ZEPHIR_INIT_VAR(_10);
					ZEPHIR_CONCAT_SS(_10, "Cannot create sub-key for '{pieces[0]}' ", "as key already exists");
					ZEPHIR_CALL_METHOD(NULL, _9, "__construct", NULL, _10);
					zephir_check_call_status();
					zephir_throw_exception_debug(_9, "yaf/Config/ini.zep", 254 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
			ZEPHIR_OBS_NVAR(_8);
			zephir_array_fetch_long(&_8, pieces, 0, PH_NOISY, "yaf/Config/ini.zep", 257 TSRMLS_CC);
			zephir_array_fetch(&_6, config, _8, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 257 TSRMLS_CC);
			zephir_array_fetch_long(&_12, pieces, 1, PH_NOISY | PH_READONLY, "yaf/Config/ini.zep", 257 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_11, this_ptr, "_processkey", NULL, _6, _12, value);
			zephir_check_call_status();
			ZEPHIR_OBS_VAR(_13);
			zephir_array_fetch_long(&_13, pieces, 0, PH_NOISY, "yaf/Config/ini.zep", 257 TSRMLS_CC);
			zephir_array_update_zval(&config, _13, &_11, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_config_exception_ce, "Invalid key '{key}'", "yaf/Config/ini.zep", 259);
			return;
		}
	} else {
		zephir_array_update_zval(&config, key, &value, PH_COPY | PH_SEPARATE);
	}
	RETURN_CTOR(config);

}

