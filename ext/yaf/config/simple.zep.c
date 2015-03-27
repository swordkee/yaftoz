
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
#include "kernel/object.h"
#include "kernel/hash.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/array.h"


/**
 * Yaf Config Simple
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Config_Simple) {

	ZEPHIR_REGISTER_CLASS_EX(Yaf\\Config, Simple, yaf, config_simple, yaf_config_abstract_ce, yaf_config_simple_method_entry, 0);

	/**
	 * Used when unsetting values during iteration to ensure we do not skip
	 * the next element
	 *
	 * @var boolean
	 */
	zend_declare_property_null(yaf_config_simple_ce, SL("_skipNextIteration"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_config_simple_ce TSRMLS_CC, 1, zend_ce_iterator);
	zend_class_implements(yaf_config_simple_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(yaf_config_simple_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

/**
 * Yaf_Config_Simple provides a property based interface to
 * an array. The data are read-only unless $readonly
 * is set to true on construction.
 *
 * Yaf_Config_Simple also implements Countable and Iterator to
 * facilitate easy access to the data.
 *
 * @param  array   $array
 * @param  boolean $readonly
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, __construct) {

	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	zend_bool readonly;
	zval *config_param = NULL, *readonly_param = NULL, *key = NULL, *value = NULL, *_0, **_3, *_4 = NULL;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &config_param, &readonly_param);

	zephir_get_arrval(config, config_param);
	if (!readonly_param) {
		readonly = 0;
	} else {
		readonly = zephir_get_boolval(readonly_param);
	}


	if (Z_TYPE_P(config) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_update_property_this(this_ptr, SL("_config"), _0 TSRMLS_CC);
		zephir_is_iterable(config, &_2, &_1, 0, 0, "yaf/Config/simple.zep", 44);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HMKEY(key, _2, _1);
			ZEPHIR_GET_HVALUE(value, _3);
			if (Z_TYPE_P(value) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(_4);
				object_init_ex(_4, yaf_config_simple_ce);
				ZEPHIR_CALL_METHOD(NULL, _4, "__construct", &_5, value, (readonly ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
				zephir_check_call_status();
				zephir_update_property_array(this_ptr, SL("_config"), key, _4 TSRMLS_CC);
			} else {
				zephir_update_property_array(this_ptr, SL("_config"), key, value TSRMLS_CC);
			}
		}
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_typeerror_ce, "Invalid parameters provided, must be an array", "yaf/Config/simple.zep", 45);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_readonly"), readonly ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Defined by Countable interface
 *
 * @return int
 */
PHP_METHOD(Yaf_Config_Simple, count) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

/**
 * Defined by Iterator interface
 *
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Simple, current) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	zephir_update_property_this(this_ptr, SL("_skipNextIteration"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("current", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Magic function so that $obj->value will work.
 *
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Simple, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "get", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Support isset() overloading on PHP 5.1
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Yaf_Config_Simple, __isset) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(_0, name));

}

/**
 * Support isset() overloading on PHP 5.1
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Yaf_Config_Simple, offsetExists) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__isset", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a config value specified by name
 * @param  string $name
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Simple, offsetGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__get", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Set a key of the config with value
 * @param  string $name
 * @param  string $value
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, offsetSet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value_param = NULL;
	zval *name = NULL, *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value_param);

	zephir_get_strval(name, name_param);
	zephir_get_strval(value, value_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__set", NULL, name, value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Support unset() overloading on PHP 5.1
 *
 * @param  string $name
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, offsetUnset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0 = NULL, *_1;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "readonly", NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
		zephir_array_unset(&_1, name, PH_SEPARATE);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Defined by Iterator interface
 *
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Simple, key) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("key", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Defined by Iterator interface
 *
 */
PHP_METHOD(Yaf_Config_Simple, next) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_skipNextIteration"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		zephir_update_property_this(this_ptr, SL("_skipNextIteration"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		RETURN_MM_NULL();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	Z_SET_ISREF_P(_1);
	ZEPHIR_CALL_FUNCTION(NULL, "next", &_2, _1);
	Z_UNSET_ISREF_P(_1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Defined by Iterator interface
 *
 */
PHP_METHOD(Yaf_Config_Simple, rewind) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	zephir_update_property_this(this_ptr, SL("_skipNextIteration"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(NULL, "reset", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Only allow setting of a property if $readonly
 * was set to true on construction. Otherwise, throw an exception.
 *
 * @param  string $name
 * @param  mixed  $value
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *_0 = NULL, *_1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "readonly", NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		if (Z_TYPE_P(name) == IS_STRING) {
			if (Z_TYPE_P(value) == IS_ARRAY) {
				ZEPHIR_INIT_VAR(_1);
				object_init_ex(_1, yaf_config_simple_ce);
				ZEPHIR_INIT_VAR(_2);
				ZVAL_BOOL(_2, 0);
				ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, value, _2);
				zephir_check_call_status();
				zephir_update_property_array(this_ptr, SL("_config"), name, _1 TSRMLS_CC);
			} else {
				zephir_update_property_array(this_ptr, SL("_config"), name, value TSRMLS_CC);
			}
		} else {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_config_exception_ce, "Expect a string key name", "yaf/Config/simple.zep", 201);
			return;
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Return an associative array of the stored data.
 *
 * @return array
 */
PHP_METHOD(Yaf_Config_Simple, toArray) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *myArray, *data, *key = NULL, *value = NULL, **_2, *_3 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(myArray);
	array_init(myArray);
	ZEPHIR_OBS_VAR(data);
	zephir_read_property_this(&data, this_ptr, SL("_config"), PH_NOISY_CC);
	zephir_is_iterable(data, &_1, &_0, 0, 0, "yaf/Config/simple.zep", 227);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if (zephir_instance_of_ev(value, yaf_config_simple_ce TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_3, value, "toarray", NULL);
			zephir_check_call_status();
			zephir_array_update_zval(&myArray, key, &_3, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&myArray, key, &value, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(myArray);

}

/**
 * Defined by Iterator interface
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Config_Simple, valid) {

	zend_bool _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *key = NULL, *_0, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(&key, "key", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	_3 = Z_TYPE_P(key) == IS_NULL;
	if (!(_3)) {
		_3 = ZEPHIR_IS_FALSE(key);
	}
	if (_3) {
		ZVAL_BOOL(_2, 0);
	} else {
		ZVAL_BOOL(_2, 1);
	}
	RETURN_CCTOR(_2);

}

/**
 * Support unset() overloading on PHP 5.1
 *
 * @param  string $name
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, __unset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0 = NULL, *_1;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "readonly", NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
		zephir_array_unset(&_1, name, PH_SEPARATE);
		zephir_update_property_this(this_ptr, SL("_skipNextIteration"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_config_exception_ce, "Config is read only", "yaf/Config/simple.zep", 258);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Retrieve a value and return $default if there is no element set.
 *
 * @param string $name
 * @param mixed $default
 * @return mixed
 */
PHP_METHOD(Yaf_Config_Simple, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *result = NULL, *_0, *_1, *_2 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(result);
	ZVAL_BOOL(result, 0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
	if (zephir_array_key_exists(_0, name TSRMLS_CC)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_config"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(result);
		zephir_array_fetch(&result, _1, name, PH_NOISY, "yaf/Config/simple.zep", 276 TSRMLS_CC);
	}
	if (Z_TYPE_P(result) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(result);
		object_init_ex(result, yaf_config_simple_ce);
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "readonly", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, result, "__construct", NULL, result, _2);
		zephir_check_call_status();
	}
	RETURN_CCTOR(result);

}

/**
 * Only allow setting of a property if $readonly
 * was set to true on construction. Otherwise, throw an exception.
 *
 * @param  string $name
 * @param  mixed  $value
 * @throws Yaf_Config_Exception
 * @return void
 */
PHP_METHOD(Yaf_Config_Simple, set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__set", NULL, name, value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Merge two arrays recursively, overwriting keys of the same name
 * in $firstArray with the value in $secondArray.
 *
 * @param  mixed $firstArray  First array
 * @param  mixed $secondArray Second array to merge into first array
 * @return array
 */
PHP_METHOD(Yaf_Config_Simple, _arrayMergeRecursive) {

	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	zend_bool _0;
	zval *firstArray = NULL, *secondArray, *key = NULL, *value = NULL, **_3, *_4 = NULL, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &firstArray, &secondArray);

	ZEPHIR_SEPARATE_PARAM(firstArray);


	_0 = Z_TYPE_P(firstArray) == IS_ARRAY;
	if (_0) {
		_0 = Z_TYPE_P(secondArray) == IS_ARRAY;
	}
	if (_0) {
		zephir_is_iterable(secondArray, &_2, &_1, 0, 0, "yaf/Config/simple.zep", 325);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HMKEY(key, _2, _1);
			ZEPHIR_GET_HVALUE(value, _3);
			if (zephir_array_isset(firstArray, key)) {
				zephir_array_fetch(&_5, firstArray, key, PH_NOISY | PH_READONLY, "yaf/Config/simple.zep", 316 TSRMLS_CC);
				ZEPHIR_CALL_METHOD(&_4, this_ptr, "_arraymergerecursive", &_6, _5, value);
				zephir_check_call_status();
				zephir_array_update_zval(&firstArray, key, &_4, PH_COPY | PH_SEPARATE);
			} else {
				if (ZEPHIR_IS_LONG_IDENTICAL(key, 0)) {
					ZEPHIR_INIT_NVAR(firstArray);
					array_init_size(firstArray, 2);
					ZEPHIR_CALL_METHOD(&_4, this_ptr, "_arraymergerecursive", &_6, firstArray, value);
					zephir_check_call_status();
					zephir_array_update_long(&firstArray, 0, &_4, PH_COPY, "yaf/Config/simple.zep", 319);
				} else {
					zephir_array_update_zval(&firstArray, key, &value, PH_COPY | PH_SEPARATE);
				}
			}
		}
	} else {
		ZEPHIR_CPY_WRT(firstArray, secondArray);
	}
	RETVAL_ZVAL(firstArray, 1, 0);
	RETURN_MM();

}

