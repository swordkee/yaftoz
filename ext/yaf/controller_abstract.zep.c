
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
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/concat.h"

ZEPHIR_INIT_CLASS(Yaf_Controller_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Controller_Abstract, yaf, controller_abstract, yaf_controller_abstract_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(yaf_controller_abstract_ce, SL("actions"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(yaf_controller_abstract_ce, SL("_module"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(yaf_controller_abstract_ce, SL("_name"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Yaf_Request_Abstract object wrapping the request environment
	 * @var Yaf_Request_Abstract
	 */
	zend_declare_property_null(yaf_controller_abstract_ce, SL("_request"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Yaf_Response_Abstract object wrapping the response
	 * @var Yaf_Response_Abstract
	 */
	zend_declare_property_null(yaf_controller_abstract_ce, SL("_response"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Array of arguments provided to the constructor, minus the
	 * {@link $_request Request object}.
	 * @var array
	 */
	zend_declare_property_null(yaf_controller_abstract_ce, SL("_invokeArgs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * View object
	 * @var Yaf_View_Interface
	 */
	zend_declare_property_null(yaf_controller_abstract_ce, SL("_view"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Class constructor
 *
 * The request and response objects should be registered with the
 * controller, as should be any additional optional arguments; these will be
 * available via {@link getRequest()}, {@link getResponse()}, and
 * {@link getInvokeArgs()}, respectively.
 *
 * @param Yaf_Request_Abstract $request
 * @param Yaf_Response_Abstract $response
 * @param Yaf_View_Interface $view
 * @param array $invokeArgs Any additional invocation arguments
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *invokeArgs = NULL;
	zval *request, *response, *view, *invokeArgs_param = NULL, *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &request, &response, &view, &invokeArgs_param);

	if (!invokeArgs_param) {
		ZEPHIR_INIT_VAR(invokeArgs);
		array_init(invokeArgs);
	} else {
		zephir_get_arrval(invokeArgs, invokeArgs_param);
	}


	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_invokeArgs"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_request"), request TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_response"), response TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_view"), view TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_invokeArgs"), invokeArgs TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, request, "getmodulename", NULL);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_module"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	zephir_get_class(_2, this_ptr, 0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_name"), _2 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "init", NULL);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Render a view
 *
 * Renders a view. By default, views are found in the view script path as
 * <controller>/<action>.phtml. You may change the script suffix by
 * resetting {@link $viewSuffix}.
 *
 *
 * @see Yaf_Response_Abstract::appendBody()
 * @param  string|null $tpl Defaults to action registered in request object
 * @param  array $parameters  add those variables to the view
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, display) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL;
	zval *tpl = NULL, *parameters_param = NULL, *view = NULL, *script = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &tpl, &parameters_param);

	if (!tpl) {
		tpl = ZEPHIR_GLOBAL(global_null);
	}
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(parameters);
		array_init(parameters);
	} else {
		zephir_get_arrval(parameters, parameters_param);
	}


	ZEPHIR_CALL_METHOD(&view, this_ptr, "initview", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&script, this_ptr, "getviewscript", NULL, tpl);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, view, "display", NULL, script, parameters);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Forward to another controller/action.
 *
 * It is important to supply the unformatted names, i.e. "article"
 * rather than "ArticleController".  The dispatcher will do the
 * appropriate formatting when the request is received.
 *
 * If only an action name is provided, forwards to that action in this
 * controller.
 *
 * If an action and controller are specified, forwards to that action and
 * controller in this module.
 *
 * Specifying an action, controller, and module is the most specific way to
 * forward.
 *
 * A fourth argument, $params, will be used to set the request parameters.
 * If either the controller or module are unnecessary for forwarding,
 * simply pass null values for them before specifying the parameters.
 *
 * @todo this should be checked again within a test
 * @param string $action
 * @param string $controller
 * @param string $module
 * @param array $args
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, forward) {

	zend_bool _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *args = NULL;
	zval *module_param = NULL, *controller_param = NULL, *action_param = NULL, *args_param = NULL, *request = NULL, *_1 = NULL, *_2;
	zval *module = NULL, *controller = NULL, *action = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &module_param, &controller_param, &action_param, &args_param);

	zephir_get_strval(module, module_param);
	if (!controller_param) {
		ZEPHIR_INIT_VAR(controller);
		ZVAL_EMPTY_STRING(controller);
	} else {
		zephir_get_strval(controller, controller_param);
	}
	if (!action_param) {
		ZEPHIR_INIT_VAR(action);
		ZVAL_EMPTY_STRING(action);
	} else {
		zephir_get_strval(action, action_param);
	}
	if (!args_param) {
	ZEPHIR_INIT_VAR(args);
	array_init(args);
	} else {
		zephir_get_arrval(args, args_param);
	}


	ZEPHIR_CALL_METHOD(&request, this_ptr, "getrequest", NULL);
	zephir_check_call_status();
	if (!ZEPHIR_IS_STRING_IDENTICAL(args, "")) {
		ZEPHIR_CALL_METHOD(NULL, request, "setparams", NULL, args);
		zephir_check_call_status();
	}
	_0 = ZEPHIR_IS_STRING(controller, "");
	if (_0) {
		_0 = ZEPHIR_IS_STRING(action, "");
	}
	if (_0) {
		ZEPHIR_CPY_WRT(action, module);
		ZEPHIR_INIT_NVAR(module);
		ZVAL_EMPTY_STRING(module);
	} else {
		if (ZEPHIR_IS_STRING(action, "")) {
			ZEPHIR_CPY_WRT(action, controller);
			ZEPHIR_CPY_WRT(controller, module);
			ZEPHIR_INIT_NVAR(module);
			ZVAL_EMPTY_STRING(module);
		}
	}
	if (!ZEPHIR_IS_STRING(module, "")) {
		ZEPHIR_CALL_METHOD(NULL, request, "setmodulename", NULL, module);
		zephir_check_call_status();
	}
	if (!ZEPHIR_IS_STRING(controller, "")) {
		ZEPHIR_CALL_METHOD(NULL, request, "setcontrollername", NULL, controller);
		zephir_check_call_status();
	}
	if (!ZEPHIR_IS_STRING(action, "")) {
		ZEPHIR_CALL_METHOD(NULL, request, "setactionname", NULL, action);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_1, request, "setactionname", NULL, action);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	ZVAL_BOOL(_2, 0);
	ZEPHIR_CALL_METHOD(NULL, _1, "setdispatched", NULL, _2);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Return a single invocation argument
 *
 * @param string $key
 * @return mixed
 */
PHP_METHOD(Yaf_Controller_Abstract, getInvokeArg) {

	zval *key_param = NULL, *_0, *_1, *_2;
	zval *key = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(key, key_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_invokeArgs"), PH_NOISY_CC);
	if (zephir_array_isset(_0, key)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_invokeArgs"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, key, PH_NOISY | PH_READONLY, "yaf/controller_abstract.zep", 159 TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	RETURN_MM_NULL();

}

/**
 * Return the array of constructor arguments (minus the Request object)
 *
 * @return array
 */
PHP_METHOD(Yaf_Controller_Abstract, getInvokeArgs) {


	RETURN_MEMBER(this_ptr, "_invokeArgs");

}

/**
 * return the current module name
 */
PHP_METHOD(Yaf_Controller_Abstract, getModuleName) {


	RETURN_MEMBER(this_ptr, "_module");

}

/**
 * Return the Request object
 *
 * @return Zend_Controller_Request_Abstract
 */
PHP_METHOD(Yaf_Controller_Abstract, getRequest) {


	RETURN_MEMBER(this_ptr, "_request");

}

/**
 * Return the Response object
 *
 * @return Yaf_Response_Abstract
 */
PHP_METHOD(Yaf_Controller_Abstract, getResponse) {


	RETURN_MEMBER(this_ptr, "_response");

}

/**
 * Return the View object
 *
 * @return Yaf_View_Interface
 */
PHP_METHOD(Yaf_Controller_Abstract, getView) {


	RETURN_MEMBER(this_ptr, "_view");

}

PHP_METHOD(Yaf_Controller_Abstract, getViewpath) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *view = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&view, this_ptr, "getview", NULL);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(view, "getscriptpath", NULL);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Initialize object
 *
 * Called from {@link __construct()} as final step of object instantiation.
 *
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, init) {



}

/**
 * Initialize View object
 * @todo this does nothing for now
 *
 * @return Yaf_View_Interface
 */
PHP_METHOD(Yaf_Controller_Abstract, initView) {


	RETURN_MEMBER(this_ptr, "_view");

}

/**
 * Render a view
 *
 * Renders a view. By default, views are found in the view script path as
 * <controller>/<action>.phtml. You may change the script suffix by
 * resetting {@link $viewSuffix}.
 *
 *
 * @see Yaf_Response_Abstract::appendBody()
 * @param  string|null $tpl Defaults to action registered in request object
 * @param  array $parameters  add those variables to the view
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, render) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL;
	zval *tpl = NULL, *parameters_param = NULL, *view = NULL, *script = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &tpl, &parameters_param);

	if (!tpl) {
		tpl = ZEPHIR_GLOBAL(global_null);
	}
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(parameters);
		array_init(parameters);
	} else {
		zephir_get_arrval(parameters, parameters_param);
	}


	ZEPHIR_CALL_METHOD(&view, this_ptr, "initview", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&script, this_ptr, "getviewscript", NULL, tpl);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(view, "render", NULL, script, parameters);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Redirect to another URL
 *
 * @param string $url
 * @return void
 */
PHP_METHOD(Yaf_Controller_Abstract, redirect) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *response = NULL;
	zval *url = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &url_param);

	zephir_get_strval(url, url_param);


	ZEPHIR_CALL_METHOD(&response, this_ptr, "getresponse", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, response, "setredirect", NULL, url);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yaf_Controller_Abstract, setViewpath) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *templateDir, *view = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &templateDir);



	ZEPHIR_CALL_METHOD(&view, this_ptr, "getview", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, view, "setscriptpath", NULL, templateDir);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Construct view script path
 *
 * Used by render() and display to determine the path to the view script.
 *
 * @param  string $action Defaults to action registered in request object
 * @return string
 * @throws InvalidArgumentException with bad $action
 */
PHP_METHOD(Yaf_Controller_Abstract, getViewScript) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *action_param = NULL, *request = NULL, *script = NULL, *controller = NULL, *tmpAction = NULL, *_0, _1, _2, *_3 = NULL, *_5 = NULL, _6, _7, *_8;
	zval *action = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &action_param);

	if (!action_param) {
		ZEPHIR_INIT_VAR(action);
		ZVAL_EMPTY_STRING(action);
	} else {
		zephir_get_strval(action, action_param);
	}


	ZEPHIR_CALL_METHOD(&request, this_ptr, "getrequest", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(action, "")) {
		ZEPHIR_CALL_METHOD(&tmpAction, request, "getactionname", NULL);
		zephir_check_call_status();
		zephir_get_strval(action, tmpAction);
	} else if (!(Z_TYPE_P(action) == IS_STRING)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Invalid action for view rendering", "yaf/controller_abstract.zep", 313);
		return;
	}
	ZEPHIR_INIT_NVAR(action);
	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtolower(_0, action);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "_", 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "/", 0);
	zephir_fast_str_replace(action, &_1, &_2, _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_STRING(_5, "view_ext", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_3, yaf_g_ce, "get", &_4, _5);
	zephir_check_temp_parameter(_5);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(script);
	ZEPHIR_CONCAT_VSV(script, action, ".", _3);
	ZEPHIR_CALL_METHOD(&controller, request, "getcontrollername", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(controller) != IS_NULL) {
		ZEPHIR_INIT_NVAR(controller);
		ZEPHIR_INIT_NVAR(_5);
		zephir_fast_strtolower(_5, controller);
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "_", 0);
		ZEPHIR_SINIT_VAR(_7);
		ZVAL_STRING(&_7, "/", 0);
		zephir_fast_str_replace(controller, &_6, &_7, _5 TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_CONCAT_VSV(_8, controller, "/", script);
	ZEPHIR_CPY_WRT(script, _8);
	RETURN_CCTOR(script);

}

