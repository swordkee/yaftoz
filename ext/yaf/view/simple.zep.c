
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
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/require.h"

ZEPHIR_INIT_CLASS(Yaf_View_Simple) {

	ZEPHIR_REGISTER_CLASS(Yaf\\View, Simple, yaf, view_simple, yaf_view_simple_method_entry, 0);

	/**
	 * List of Variables which will be replaced in the
	 * template
	 * @var array
	 */
	zend_declare_property_null(yaf_view_simple_ce, SL("_tpl_vars"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Directory where the templates exists
	 * @var string
	 */
	zend_declare_property_string(yaf_view_simple_ce, SL("_tpl_dir"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yaf_view_simple_ce, SL("_options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(yaf_view_simple_ce TSRMLS_CC, 1, yaf_view_interface_ce);
	return SUCCESS;

}

/**
 * Assigns variables to the view script via differing strategies.
 *
 * Yaf_View_Simple::assign('name', $value) assigns a variable called 'name'
 * with the corresponding $value.
 *
 * Yaf_View_Simple::assign($array) assigns the array keys as variable
 * names (with the corresponding array values).
 *
 * @see    __set()
 * @param  string|array The assignment strategy to use.
 * @param  mixed (Optional) If assigning a named variable, use this
 * as the value.
 * @return Yaf_View_Simple
 * @throws Yaf_Exception_LoadFailed_View if $name is
 * neither a string nor an array,
 */
PHP_METHOD(Yaf_View_Simple, assign) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *name = NULL, *value = NULL, *key = NULL, *val = NULL, **_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &value);

	if (!value) {
		value = ZEPHIR_GLOBAL(global_null);
	}
	ZEPHIR_INIT_VAR(key);
	ZVAL_STRING(key, "", 1);


	ZEPHIR_INIT_VAR(val);
	array_init(val);
	if (Z_TYPE_P(name) == IS_STRING) {
		zephir_update_property_array(this_ptr, SL("_tpl_vars"), name, value TSRMLS_CC);
	} else if (Z_TYPE_P(name) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(name);
		array_init(name);
		zephir_is_iterable(name, &_1, &_0, 0, 0, "yaf/View/simple.zep", 53);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(key, _1, _0);
			ZEPHIR_GET_HVALUE(val, _2);
			zephir_update_property_array(this_ptr, SL("_tpl_vars"), key, val TSRMLS_CC);
		}
	} else {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, yaf_exception_ce);
		ZEPHIR_INIT_VAR(_4);
		zephir_gettype(_4, name TSRMLS_CC);
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CONCAT_SV(_5, "assign() expects a string or array, received ", _4);
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, _5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "yaf/View/simple.zep", 54 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * Assigns by reference a variable to the view script.
 *
 * @param  string The name of the variable to be used in the template .
 * @param  mixed the variable value
 * @return Yaf_View_Simple
 * @throws Yaf_Exception_LoadFailed_View if $name is not a string,
 */
PHP_METHOD(Yaf_View_Simple, assignRef) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *value, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name, &value);



	if (Z_TYPE_P(name) == IS_STRING) {
		zephir_update_property_array(this_ptr, SL("_tpl_vars"), name, value TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, yaf_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		zephir_gettype(_1, name TSRMLS_CC);
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_SV(_2, "assign() expects a string, received ", _1);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _2);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "yaf/View/simple.zep", 76 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_THIS();

}

/**
 * Set the path to find the view script used by render()
 *
 * @param string The directory to set as the path.
 * @return void
 */
PHP_METHOD(Yaf_View_Simple, setScriptPath) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zend_bool _0;
	zval *templateDir, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &templateDir);



	_0 = Z_TYPE_P(templateDir) == IS_STRING;
	if (_0) {
		ZEPHIR_CALL_CE_STATIC(&_1, yaf_g_ce, "isabsolutepath", &_2, templateDir);
		zephir_check_call_status();
		_0 = zephir_is_true(_1);
	}
	if (_0) {
		zephir_update_property_this(this_ptr, SL("_tpl_dir"), templateDir TSRMLS_CC);
	}
	RETURN_THIS();

}

/**
 * Return path to find the view script used by render()
 *
 * @return null|string Null if script not found
 */
PHP_METHOD(Yaf_View_Simple, getScriptPath) {


	RETURN_MEMBER(this_ptr, "_tpl_dir");

}

PHP_METHOD(Yaf_View_Simple, clear) {

	zval *name = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &name);

	if (!name) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_STRING(name, "", 1);
	}


	if (!ZEPHIR_IS_STRING(name, "")) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
		if (zephir_array_isset(_0, name)) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
			zephir_array_unset(&_1, name, PH_SEPARATE);
		}
	} else {
		ZEPHIR_INIT_VAR(_2);
		array_init(_2);
		zephir_update_property_this(this_ptr, SL("_tpl_vars"), _2 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Constructor.
 *
 * @param array $config Configuration key-value pairs.
 */
PHP_METHOD(Yaf_View_Simple, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *templateDir, *options = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &templateDir, &options);

	if (!options) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	}


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_options"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("_tpl_vars"), _1 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setscriptpath", NULL, templateDir);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_options"), options TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Processes a view script and displays the output.
 *
 * @param string $tpl The script name to process.
 * @param string $tpl_vars The variables to use in the view.
 * @return string The script output.
 */
PHP_METHOD(Yaf_View_Simple, display) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *tpl_param = NULL, *tplVars = NULL, *template = NULL, *_1 = NULL;
	zval *tpl = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tpl_param, &tplVars);

	zephir_get_strval(tpl, tpl_param);
	if (!tplVars) {
		ZEPHIR_INIT_VAR(tplVars);
		array_init(tplVars);
	}


	_0 = !(Z_TYPE_P(tpl) == IS_STRING);
	if (!(_0)) {
		_0 = ZEPHIR_IS_STRING(tpl, "");
	}
	if (_0) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&template, this_ptr, "_script", NULL, tpl);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "_run", NULL, template, tplVars);
	zephir_check_call_status();
	zend_print_zval(_1, 0);
	RETURN_MM_BOOL(1);

}

/**
 * Processes a view script and returns the output.
 *
 * @param string $tpl The script name to process.
 * @param string $tpl_vars The variables to use in the view.
 * @return string The script output.
 */
PHP_METHOD(Yaf_View_Simple, evaluate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *tpl_content, *vars = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tpl_content, &vars);

	if (!vars) {
		ZEPHIR_INIT_VAR(vars);
		array_init(vars);
	}


	_0 = !(Z_TYPE_P(tpl_content) == IS_STRING);
	if (!(_0)) {
		_0 = Z_TYPE_P(tpl_content) == IS_NULL;
	}
	if (_0) {
		RETURN_MM_STRING("", 1);
	}
	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 1);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "_run", NULL, tpl_content, vars, _1);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Yaf_View_Simple, __call) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *arguments, *_0, *_1, *_2 = NULL, *_3, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name, &arguments);



	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtolower(_0, name);
	do {
		if (ZEPHIR_IS_STRING(_0, "eval")) {
			zephir_array_fetch_long(&_1, arguments, 0, PH_NOISY | PH_READONLY, "yaf/View/simple.zep", 177 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_2);
			if (zephir_array_isset_long(arguments, 1)) {
				ZEPHIR_OBS_NVAR(_2);
				zephir_array_fetch_long(&_2, arguments, 1, PH_NOISY, "yaf/View/simple.zep", 177 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(_2);
				array_init(_2);
			}
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "evaluate", NULL, _1, _2);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, yaf_exception_ce);
		ZEPHIR_INIT_VAR(_4);
		zephir_get_class(_4, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_2);
		ZEPHIR_CONCAT_SVSVS(_2, "Call to undefined method ", _4, "::", name, "()");
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, _2);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "yaf/View/simple.zep", 181 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

}

/**
 * return the assigned template variable
 *
 * @param  string $name
 * @return null
 */
PHP_METHOD(Yaf_View_Simple, get) {

	zval *name_param = NULL, *_0, *_1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &name_param);

	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_STRING(name, "", 1);
	} else {
		zephir_get_strval(name, name_param);
	}


	if (!ZEPHIR_IS_STRING(name, "")) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
		if (zephir_array_isset(_0, name)) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
			zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "yaf/View/simple.zep", 197 TSRMLS_CC);
			RETURN_CTOR(_2);
		}
	} else {
		RETURN_MM_MEMBER(this_ptr, "_tpl_vars");
	}
	RETURN_MM_NULL();

}

/**
 * return the assigned template variable
 *
 * @param  string $name
 * @return null
 */
PHP_METHOD(Yaf_View_Simple, __get) {

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
 * Allows testing with empty() and isset() to work inside
 * templates.
 *
 * @param  string $key
 * @return boolean
 */
PHP_METHOD(Yaf_View_Simple, __isset) {

	zval *name, *_0;

	zephir_fetch_params(0, 1, 0, &name);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
	RETURN_BOOL(zephir_array_isset(_0, name));

}

/**
 * Assigns a variable or an associative array to the view script.
 * @see assign()
 *
 * @param string $name The variable name or array.
 * @param mixed $value The variable value.
 * @return void
 */
PHP_METHOD(Yaf_View_Simple, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "assign", NULL, name, value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Allows unset() on object properties to work
 *
 * @param string $key
 * @return void
 */
PHP_METHOD(Yaf_View_Simple, __unset) {

	zval *name, *_0, *_1;

	zephir_fetch_params(0, 1, 0, &name);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
	if (zephir_array_isset(_0, name)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
		zephir_array_unset(&_1, name, PH_SEPARATE);
	}

}

/**
 * Processes a view script and returns the output.
 *
 * @param string $tpl The script name to process.
 * @param string $tpl_vars The variables to use in the view.
 * @return string The script output.
 */
PHP_METHOD(Yaf_View_Simple, render) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *tpl_param = NULL, *tplVars = NULL, *template = NULL;
	zval *tpl = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tpl_param, &tplVars);

	zephir_get_strval(tpl, tpl_param);
	if (!tplVars) {
		ZEPHIR_INIT_VAR(tplVars);
		array_init(tplVars);
	}


	_0 = !(Z_TYPE_P(tpl) == IS_STRING);
	if (!(_0)) {
		_0 = ZEPHIR_IS_STRING(tpl, "");
	}
	if (_0) {
		RETURN_MM_STRING("", 1);
	}
	ZEPHIR_CALL_METHOD(&template, this_ptr, "_script", NULL, tpl);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "_run", NULL, template, tplVars);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Finds a view script from the available directory.
 *
 * @param string $name The base name of the script.
 * @return void
 */
PHP_METHOD(Yaf_View_Simple, _script) {

	zend_bool _5;
	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_1 = NULL, *_3 = NULL, *_6 = NULL, *_8, *_9 = NULL, *_10 = NULL, *_11;
	zval *name = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_dir"), PH_NOISY_CC);
	if (ZEPHIR_IS_STRING(_0, "")) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, yaf_exception_loadfailed_view_ce);
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_SS(_2, "Could not determine the view script path, ", "you should call Yaf_View_Simple::setScriptPath to specific it");
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _2);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1, "yaf/View/simple.zep", 297 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "isabsolutepath", &_4, name);
	zephir_check_call_status();
	_5 = zephir_is_true(_3);
	if (_5) {
		ZEPHIR_CALL_FUNCTION(&_6, "is_readable", &_7, name);
		zephir_check_call_status();
		_5 = zephir_is_true(_6);
	}
	if (_5) {
		RETURN_CTOR(name);
	} else {
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_dir"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_9);
		ZEPHIR_CONCAT_VSV(_9, _8, "/", name);
		ZEPHIR_CALL_FUNCTION(&_10, "is_readable", &_7, _9);
		zephir_check_call_status();
		if (zephir_is_true(_10)) {
			_11 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_dir"), PH_NOISY_CC);
			ZEPHIR_CONCAT_VSV(return_value, _11, "/", name);
			RETURN_MM();
		}
	}
	ZEPHIR_INIT_NVAR(_1);
	object_init_ex(_1, yaf_exception_loadfailed_view_ce);
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_dir"), PH_NOISY_CC);
	ZEPHIR_INIT_LNVAR(_9);
	ZEPHIR_CONCAT_SVSV(_9, "Unable to find template ", _8, "/", name);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _9);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "yaf/View/simple.zep", 310 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Yaf_View_Simple, _run) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_5 = NULL, *_7 = NULL;
	zend_bool _0;
	zval *template, *vars = NULL, *useEval = NULL, *content = NULL, *_1, *_2 = NULL, *_3, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &template, &vars, &useEval);

	ZEPHIR_SEPARATE_PARAM(vars);
	if (!useEval) {
		useEval = ZEPHIR_GLOBAL(global_false);
	}


	_0 = Z_TYPE_P(vars) == IS_NULL;
	if (_0) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
		_0 = zephir_fast_count_int(_1 TSRMLS_CC) > 0;
	}
	if (_0) {
		ZEPHIR_OBS_NVAR(vars);
		zephir_read_property_this(&vars, this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
	} else {
		ZEPHIR_INIT_VAR(_2);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("_tpl_vars"), PH_NOISY_CC);
		zephir_fast_array_merge(_2, &(vars), &(_3) TSRMLS_CC);
		ZEPHIR_CPY_WRT(vars, _2);
	}
	if (Z_TYPE_P(vars) != IS_NULL) {
		Z_SET_ISREF_P(vars);
		ZEPHIR_CALL_FUNCTION(NULL, "extract", &_4, vars);
		Z_UNSET_ISREF_P(vars);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", &_5);
	zephir_check_call_status();
	if (ZEPHIR_IS_TRUE(useEval)) {
		ZEPHIR_INIT_NVAR(_2);
		ZEPHIR_INIT_VAR(_6);
		ZEPHIR_CONCAT_SV(_6, "?>", template);
		zephir_eval_php(_6, _2, "/opt/yaf/yaf/View/simple.zep:330" TSRMLS_CC);
	} else {
		if ((zephir_file_exists(template TSRMLS_CC) == SUCCESS)) {
			if (zephir_require_zval(template TSRMLS_CC) == FAILURE) {
				RETURN_MM_NULL();
			}
		}
	}
	ZEPHIR_CALL_FUNCTION(&content, "ob_get_clean", &_7);
	zephir_check_call_status();
	RETURN_CCTOR(content);

}

