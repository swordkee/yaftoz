
extern zend_class_entry *yaf_route_interface_ce;

ZEPHIR_INIT_CLASS(Yaf_Route_Interface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_route_interface_route, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_route_interface_method_entry) {
	PHP_ABSTRACT_ME(Yaf_Route_Interface, route, arginfo_yaf_route_interface_route)
  PHP_FE_END
};
