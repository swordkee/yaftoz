
extern zend_class_entry *yaf_loader_ce;

ZEPHIR_INIT_CLASS(Yaf_Loader);

PHP_METHOD(Yaf_Loader, internal_autoload);
PHP_METHOD(Yaf_Loader, autoload);
PHP_METHOD(Yaf_Loader, isCategoryType);
PHP_METHOD(Yaf_Loader, resolveCategory);
PHP_METHOD(Yaf_Loader, resolveDirectory);
PHP_METHOD(Yaf_Loader, resolveClass);
PHP_METHOD(Yaf_Loader, import);
PHP_METHOD(Yaf_Loader, _securityCheck);
PHP_METHOD(Yaf_Loader, clearLocalNamespace);
PHP_METHOD(Yaf_Loader, __clone);
PHP_METHOD(Yaf_Loader, __construct);
PHP_METHOD(Yaf_Loader, getInstance);
PHP_METHOD(Yaf_Loader, getLibraryPath);
PHP_METHOD(Yaf_Loader, getLocalNamespace);
PHP_METHOD(Yaf_Loader, isLocalName);
PHP_METHOD(Yaf_Loader, registerLocalNamespace);
PHP_METHOD(Yaf_Loader, setLibraryPath);
PHP_METHOD(Yaf_Loader, __sleep);
PHP_METHOD(Yaf_Loader, __wakeup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_internal_autoload, 0, 0, 1)
	ZEND_ARG_INFO(0, classs)
	ZEND_ARG_INFO(0, dirs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_autoload, 0, 0, 1)
	ZEND_ARG_INFO(0, classs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_iscategorytype, 0, 0, 2)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_resolvecategory, 0, 0, 2)
	ZEND_ARG_INFO(0, className)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_resolvedirectory, 0, 0, 1)
	ZEND_ARG_INFO(0, classs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_resolveclass, 0, 0, 1)
	ZEND_ARG_INFO(0, classs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_import, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, dirs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader__securitycheck, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_getinstance, 0, 0, 0)
	ZEND_ARG_INFO(0, library)
	ZEND_ARG_INFO(0, globalLibrary)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_getlibrarypath, 0, 0, 0)
	ZEND_ARG_INFO(0, isGlobal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_islocalname, 0, 0, 1)
	ZEND_ARG_INFO(0, className)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_registerlocalnamespace, 0, 0, 1)
	ZEND_ARG_INFO(0, namespacee)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_loader_setlibrarypath, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, isGlobal)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_loader_method_entry) {
	PHP_ME(Yaf_Loader, internal_autoload, arginfo_yaf_loader_internal_autoload, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, autoload, arginfo_yaf_loader_autoload, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, isCategoryType, arginfo_yaf_loader_iscategorytype, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, resolveCategory, arginfo_yaf_loader_resolvecategory, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, resolveDirectory, arginfo_yaf_loader_resolvedirectory, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, resolveClass, arginfo_yaf_loader_resolveclass, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, import, arginfo_yaf_loader_import, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Loader, _securityCheck, arginfo_yaf_loader__securitycheck, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, clearLocalNamespace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Loader, getInstance, arginfo_yaf_loader_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Loader, getLibraryPath, arginfo_yaf_loader_getlibrarypath, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, getLocalNamespace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, isLocalName, arginfo_yaf_loader_islocalname, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, registerLocalNamespace, arginfo_yaf_loader_registerlocalnamespace, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, setLibraryPath, arginfo_yaf_loader_setlibrarypath, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Loader, __sleep, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Loader, __wakeup, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
