
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Yaf Route Interface
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Route_Interface) {

	ZEPHIR_REGISTER_INTERFACE(Yaf, Route_Interface, yaf, route_interface, yaf_route_interface_method_entry);

	return SUCCESS;

}

/**
 * Processes a request and sets its controller and action.  If
 * no route was possible, default route is set.
 *
 * @param  Yaf_Request_Abstract
 * @return Yaf_Request_Abstract|boolean
 */
ZEPHIR_DOC_METHOD(Yaf_Route_Interface, route);

