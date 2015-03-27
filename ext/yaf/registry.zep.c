
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
#include "kernel/array.h"


/**
 * Yaf Registry
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Registry) {

	ZEPHIR_REGISTER_CLASS(Yaf, Registry, yaf, registry, yaf_registry_method_entry, 0);

	/**
	 * the data array
	 * @var array
	 */
	zend_declare_property_null(yaf_registry_ce, SL("_entrys"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * @set undefined data
 * @param string $index
 * @param mixed $value
 * @return void
 */
PHP_METHOD(Yaf_Registry, set) {

	zval *name, *value;

	zephir_fetch_params(0, 2, 0, &name, &value);



	zephir_update_static_property_array_multi_ce(yaf_registry_ce, SL("_entrys"), &value TSRMLS_CC, SL("z"), 1, name);

}

/**
 * @get variables
 * @param mixed $index
 * @return mixed
 */
PHP_METHOD(Yaf_Registry, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *_0 = NULL, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name);



	ZEPHIR_CALL_SELF(&_0, "has", NULL, name);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		_1 = zephir_fetch_static_property_ce(yaf_registry_ce, SL("_entrys") TSRMLS_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "yaf/registry.zep", 36 TSRMLS_CC);
		RETURN_CTOR(_2);
	} else {
		RETURN_MM_NULL();
	}

}

/**
 * check if the variable is in the registry
 * @param mixed $index
 * @return mixed
 */
PHP_METHOD(Yaf_Registry, has) {

	zval *name, *_0;

	zephir_fetch_params(0, 1, 0, &name);



	_0 = zephir_fetch_static_property_ce(yaf_registry_ce, SL("_entrys") TSRMLS_CC);
	RETURN_BOOL(zephir_array_isset(_0, name));

}

/**
 * @del variables
 * @param mixed $index
 * @return mixed
 */
PHP_METHOD(Yaf_Registry, del) {

	zval *name, *_0, *_1;

	zephir_fetch_params(0, 1, 0, &name);



	_0 = zephir_fetch_static_property_ce(yaf_registry_ce, SL("_entrys") TSRMLS_CC);
	if (zephir_array_isset(_0, name)) {
		_1 = zephir_fetch_static_property_ce(yaf_registry_ce, SL("_entrys") TSRMLS_CC);
		zephir_array_unset(&_1, name, PH_SEPARATE);
	}

}

