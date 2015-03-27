
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

#include "php_ext.h"
#include "yaf.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *yaf_route_interface_ce;
zend_class_entry *yaf_view_interface_ce;
zend_class_entry *yaf_exception_ce;
zend_class_entry *yaf_exception_loadfailed_loadfailed_ce;
zend_class_entry *yaf_config_abstract_ce;
zend_class_entry *yaf_request_abstract_ce;
zend_class_entry *yaf_response_abstract_ce;
zend_class_entry *yaf_config_simple_ce;
zend_class_entry *yaf_controller_abstract_ce;
zend_class_entry *yaf_action_abstract_ce;
zend_class_entry *yaf_application_ce;
zend_class_entry *yaf_bootstrap_abstract_ce;
zend_class_entry *yaf_config_exception_ce;
zend_class_entry *yaf_config_ini_ce;
zend_class_entry *yaf_dispatcher_ce;
zend_class_entry *yaf_exception_dispatchfailed_ce;
zend_class_entry *yaf_exception_loadfailed_action_ce;
zend_class_entry *yaf_exception_loadfailed_controller_ce;
zend_class_entry *yaf_exception_loadfailed_module_ce;
zend_class_entry *yaf_exception_loadfailed_view_ce;
zend_class_entry *yaf_exception_routerfailed_ce;
zend_class_entry *yaf_exception_startuperror_ce;
zend_class_entry *yaf_exception_typeerror_ce;
zend_class_entry *yaf_g_ce;
zend_class_entry *yaf_loader_ce;
zend_class_entry *yaf_plugin_abstract_ce;
zend_class_entry *yaf_registry_ce;
zend_class_entry *yaf_request_exception_ce;
zend_class_entry *yaf_request_http_ce;
zend_class_entry *yaf_request_simple_ce;
zend_class_entry *yaf_response_cli_ce;
zend_class_entry *yaf_response_exception_ce;
zend_class_entry *yaf_response_http_ce;
zend_class_entry *yaf_route_exception_ce;
zend_class_entry *yaf_route_map_ce;
zend_class_entry *yaf_route_regex_ce;
zend_class_entry *yaf_route_rewrite_ce;
zend_class_entry *yaf_route_simple_ce;
zend_class_entry *yaf_route_static_ce;
zend_class_entry *yaf_route_supervar_ce;
zend_class_entry *yaf_router_ce;
zend_class_entry *yaf_session_ce;
zend_class_entry *yaf_view_simple_ce;

ZEND_DECLARE_MODULE_GLOBALS(yaf)

static PHP_MINIT_FUNCTION(yaf)
{
#if PHP_VERSION_ID < 50500
	char* old_lc_all = setlocale(LC_ALL, NULL);
	if (old_lc_all) {
		size_t len = strlen(old_lc_all);
		char *tmp  = calloc(len+1, 1);
		if (UNEXPECTED(!tmp)) {
			return FAILURE;
		}

		memcpy(tmp, old_lc_all, len);
		old_lc_all = tmp;
	}

	setlocale(LC_ALL, "C");
#endif

	ZEPHIR_INIT(Yaf_Route_Interface);
	ZEPHIR_INIT(Yaf_View_Interface);
	ZEPHIR_INIT(Yaf_Exception);
	ZEPHIR_INIT(Yaf_Exception_LoadFailed_LoadFailed);
	ZEPHIR_INIT(Yaf_Config_Abstract);
	ZEPHIR_INIT(Yaf_Request_Abstract);
	ZEPHIR_INIT(Yaf_Response_Abstract);
	ZEPHIR_INIT(Yaf_Config_Simple);
	ZEPHIR_INIT(Yaf_Controller_Abstract);
	ZEPHIR_INIT(Yaf_Action_Abstract);
	ZEPHIR_INIT(Yaf_Application);
	ZEPHIR_INIT(Yaf_Bootstrap_Abstract);
	ZEPHIR_INIT(Yaf_Config_Exception);
	ZEPHIR_INIT(Yaf_Config_Ini);
	ZEPHIR_INIT(Yaf_Dispatcher);
	ZEPHIR_INIT(Yaf_Exception_DispatchFailed);
	ZEPHIR_INIT(Yaf_Exception_LoadFailed_Action);
	ZEPHIR_INIT(Yaf_Exception_LoadFailed_Controller);
	ZEPHIR_INIT(Yaf_Exception_LoadFailed_Module);
	ZEPHIR_INIT(Yaf_Exception_LoadFailed_View);
	ZEPHIR_INIT(Yaf_Exception_RouterFailed);
	ZEPHIR_INIT(Yaf_Exception_StartupError);
	ZEPHIR_INIT(Yaf_Exception_TypeError);
	ZEPHIR_INIT(Yaf_Loader);
	ZEPHIR_INIT(Yaf_Plugin_Abstract);
	ZEPHIR_INIT(Yaf_Registry);
	ZEPHIR_INIT(Yaf_Request_Exception);
	ZEPHIR_INIT(Yaf_Request_Http);
	ZEPHIR_INIT(Yaf_Request_Simple);
	ZEPHIR_INIT(Yaf_Response_Cli);
	ZEPHIR_INIT(Yaf_Response_Exception);
	ZEPHIR_INIT(Yaf_Response_Http);
	ZEPHIR_INIT(Yaf_Route_Exception);
	ZEPHIR_INIT(Yaf_Route_Map);
	ZEPHIR_INIT(Yaf_Route_Regex);
	ZEPHIR_INIT(Yaf_Route_Rewrite);
	ZEPHIR_INIT(Yaf_Route_Simple);
	ZEPHIR_INIT(Yaf_Route_Static);
	ZEPHIR_INIT(Yaf_Route_Supervar);
	ZEPHIR_INIT(Yaf_Router);
	ZEPHIR_INIT(Yaf_Session);
	ZEPHIR_INIT(Yaf_View_Simple);
	ZEPHIR_INIT(Yaf_g);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(yaf)
{

	zephir_deinitialize_memory(TSRMLS_C);

	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_yaf_globals *zephir_globals TSRMLS_DC)
{
	zephir_globals->initialized = 0;

	/* Memory options */
	zephir_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	zephir_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	zephir_globals->cache_enabled = 1;

	/* Recursive Lock */
	zephir_globals->recursive_lock = 0;


}

static PHP_RINIT_FUNCTION(yaf)
{

	zend_yaf_globals *zephir_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(zephir_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

	zephir_initialize_memory(zephir_globals_ptr TSRMLS_CC);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(yaf)
{

	

	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(yaf)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_YAF_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_YAF_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_YAF_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_YAF_VERSION);
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_YAF_ZEPVERSION);
	php_info_print_table_end();


}

static PHP_GINIT_FUNCTION(yaf)
{
	php_zephir_init_globals(yaf_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(yaf)
{

}


zend_function_entry php_yaf_functions[] = {
ZEND_FE_END

};

zend_module_entry yaf_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_YAF_EXTNAME,
	php_yaf_functions,
	PHP_MINIT(yaf),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(yaf),
#else
	NULL,
#endif
	PHP_RINIT(yaf),
	PHP_RSHUTDOWN(yaf),
	PHP_MINFO(yaf),
	PHP_YAF_VERSION,
	ZEND_MODULE_GLOBALS(yaf),
	PHP_GINIT(yaf),
	PHP_GSHUTDOWN(yaf),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_YAF
ZEND_GET_MODULE(yaf)
#endif
