
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/exception.h"


/**
 * Yaf Session
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Session) {

	ZEPHIR_REGISTER_CLASS(Yaf, Session, yaf, session, yaf_session_method_entry, 0);

	/**
	 * @var Yaf_Session instance
	 */
	zend_declare_property_null(yaf_session_ce, SL("_instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * @var array holds the session data
	 */
	zend_declare_property_null(yaf_session_ce, SL("session"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var bool whether the session was already started or not
	 */
	zend_declare_property_bool(yaf_session_ce, SL("started"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_class_implements(yaf_session_ce TSRMLS_CC, 1, zend_ce_iterator);
	zend_class_implements(yaf_session_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(yaf_session_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

PHP_METHOD(Yaf_Session, __clone) {



}

PHP_METHOD(Yaf_Session, __construct) {



}

/**
 * Defined by Countable interface
 *
 * @return int
 */
PHP_METHOD(Yaf_Session, count) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	RETURN_LONG(zephir_fast_count_int(_0 TSRMLS_CC));

}

/**
 * Defined by Iterator interface
 *
 * @return mixed
 */
PHP_METHOD(Yaf_Session, current) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("current", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Yaf_Session, del) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "offsetunset", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Yaf_Session, __destruct) {



}

/**
 * Magic function so that $obj->value will work.
 *
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Yaf_Session, __get) {

	zval *name_param = NULL, *result = NULL, *_0, *_1, *_SESSION;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(result);
	ZVAL_NULL(result);
	if (ZEPHIR_IS_STRING(name, "")) {
		RETURN_MM_NULL();
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	if (zephir_array_key_exists(_0, name TSRMLS_CC)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(result);
		zephir_array_fetch(&result, _1, name, PH_NOISY, "yaf/session.zep", 81 TSRMLS_CC);
	} else {
		zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
		if (zephir_array_key_exists(_SESSION, name TSRMLS_CC)) {
			zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
			ZEPHIR_OBS_NVAR(result);
			zephir_array_fetch(&result, _SESSION, name, PH_NOISY, "yaf/session.zep", 85 TSRMLS_CC);
		}
	}
	RETURN_CCTOR(result);

}

/**
 * Retrieve singleton instance
 *
 * @return Yaf_Session
 */
PHP_METHOD(Yaf_Session, getInstance) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(yaf_session_ce, SL("_instance") TSRMLS_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, yaf_session_ce);
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
		zephir_check_call_status();
		zephir_update_static_property_ce(yaf_session_ce, SL("_instance"), &_1 TSRMLS_CC);
		ZEPHIR_CALL_SELF(NULL, "start", NULL);
		zephir_check_call_status();
	}
	_2 = zephir_fetch_static_property_ce(yaf_session_ce, SL("_instance") TSRMLS_CC);
	RETURN_CTOR(_2);

}

PHP_METHOD(Yaf_Session, has) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "offsetexists", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Support isset() overloading on PHP 5.1
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Yaf_Session, __isset) {

	zval *name_param = NULL, *_0, *_1, *_SESSION;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	if (zephir_array_isset(_1, name)) {
		ZVAL_BOOL(_0, 1);
	} else {
		zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
		ZVAL_BOOL(_0, zephir_array_isset(_SESSION, name));
	}
	RETURN_CCTOR(_0);

}

/**
 * Defined by Iterator interface
 *
 * @return mixed
 */
PHP_METHOD(Yaf_Session, key) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
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
PHP_METHOD(Yaf_Session, next) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(NULL, "next", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Support isset() overloading on PHP 5.1
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Yaf_Session, offsetExists) {

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
 * Return a session value specified by name
 * @param  string $name
 * @return mixed
 */
PHP_METHOD(Yaf_Session, offsetGet) {

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
 * Set a key of the session with value
 * @param  string $name
 * @param  string $value
 * @return void
 */
PHP_METHOD(Yaf_Session, offsetSet) {

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
 * @return void
 */
PHP_METHOD(Yaf_Session, offsetUnset) {

	zval *name_param = NULL, *_0, *_SESSION;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	zephir_array_unset(&_0, name, PH_SEPARATE);
	zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
	zephir_array_unset(&_SESSION, name, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Defined by Iterator interface
 *
 */
PHP_METHOD(Yaf_Session, rewind) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(NULL, "reset", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Allow setting of a session variable.
 * Throw an exception if the name is not string.
 *
 * @param  string $name
 * @param  mixed  $value
 * @throws Yaf_Exception
 * @return void
 */
PHP_METHOD(Yaf_Session, __set) {

	int _0;
	zval *name_param = NULL, *value, *_SESSION;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	if (Z_TYPE_P(name) == IS_STRING) {
		zephir_update_property_array(this_ptr, SL("session"), name, value TSRMLS_CC);
		zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
		_0 = zephir_maybe_separate_zval(&_SESSION);
		zephir_array_update_zval(&_SESSION, name, &value, PH_COPY | PH_SEPARATE);
		if (_0) {
			ZEND_SET_SYMBOL(&EG(symbol_table), "_SESSION", _SESSION);
		}
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yaf_exception_ce, "Expect a string key name", "yaf/session.zep", 219);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Session, __sleep) {



}

/**
 * Starts the session
 */
PHP_METHOD(Yaf_Session, start) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *session = NULL, *_0, *_SESSION;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_SELF(&session, "getinstance", NULL);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property(&_0, session, SL("started"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE(_0)) {
		RETURN_MM_BOOL(1);
	} else {
		ZEPHIR_CALL_FUNCTION(NULL, "session_start", NULL);
		zephir_check_call_status();
		zephir_update_property_zval(session, SL("started"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		zephir_get_global(&_SESSION, SS("_SESSION") TSRMLS_CC);
		zephir_update_property_zval(session, SL("session"), _SESSION TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Support unset() overloading on PHP 5.1
 *
 * @param  string $name
 * @return void
 */
PHP_METHOD(Yaf_Session, __unset) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
	zephir_array_unset(&_0, name, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Defined by Iterator interface
 *
 * @return boolean
 */
PHP_METHOD(Yaf_Session, valid) {

	zend_bool _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *key = NULL, *_0, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("session"), PH_NOISY_CC);
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

PHP_METHOD(Yaf_Session, __wakeup) {



}

