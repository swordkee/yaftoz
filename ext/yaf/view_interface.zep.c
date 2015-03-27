
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Yaf View Interface
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_View_Interface) {

	ZEPHIR_REGISTER_INTERFACE(Yaf, View_Interface, yaf, view_interface, yaf_view_interface_method_entry);

	return SUCCESS;

}

/**
 * Set the path to find the view script used by render()
 *
 * @param string The directory to set as the path.
 * @return void
 */
ZEPHIR_DOC_METHOD(Yaf_View_Interface, setScriptPath);

/**
 * Retrieve all view script paths
 *
 * @return array
 */
ZEPHIR_DOC_METHOD(Yaf_View_Interface, getScriptPath);

/**
 * Assign variables to the view script via differing strategies.
 *
 * Suggested implementation is to allow setting a specific key to the
 * specified value, OR passing an array of key => value pairs to set en
 * masse.
 *
 * @param string|array $name The assignment strategy to use
 * (key or array of key => value pairs)
 * @param mixed $value (Optional) If assigning a named variable, use this
 * as the value.
 * @return void
 */
ZEPHIR_DOC_METHOD(Yaf_View_Interface, assign);

/**
 * Processes a view script and returns the output.
 *
 * @param string $tpl The script name to process.
 * @param array $tplVars The script variables.
 * @return string The script output.
 */
ZEPHIR_DOC_METHOD(Yaf_View_Interface, render);

/**
 * Processes a view script and displays the output.
 *
 * @param string $tpl The script name to process.
 * @param array $tplVars The script variables.
 * @return void
 */
ZEPHIR_DOC_METHOD(Yaf_View_Interface, display);

