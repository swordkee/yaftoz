
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


/**
 * Yaf Plugin Abstract
 */
/**
 * @namespace
 */
ZEPHIR_INIT_CLASS(Yaf_Plugin_Abstract) {

	ZEPHIR_REGISTER_CLASS(Yaf, Plugin_Abstract, yaf, plugin_abstract, yaf_plugin_abstract_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Yaf_Plugin_Abstract, dispatchLoopShutdown) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

PHP_METHOD(Yaf_Plugin_Abstract, dispatchLoopStartup) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

PHP_METHOD(Yaf_Plugin_Abstract, postDispatch) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

PHP_METHOD(Yaf_Plugin_Abstract, preDispatch) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

PHP_METHOD(Yaf_Plugin_Abstract, routerShutdown) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

PHP_METHOD(Yaf_Plugin_Abstract, routerStartup) {

	zval *request, *response;

	zephir_fetch_params(0, 2, 0, &request, &response);




}

