
extern zend_class_entry *yaf_application_ce;

ZEPHIR_INIT_CLASS(Yaf_Application);

PHP_METHOD(Yaf_Application, __construct);
PHP_METHOD(Yaf_Application, __destruct);
PHP_METHOD(Yaf_Application, bootstrap);
PHP_METHOD(Yaf_Application, run);
PHP_METHOD(Yaf_Application, app);
PHP_METHOD(Yaf_Application, getConfig);
PHP_METHOD(Yaf_Application, getDispatcher);
PHP_METHOD(Yaf_Application, getModules);
PHP_METHOD(Yaf_Application, environ);
PHP_METHOD(Yaf_Application, execute);
PHP_METHOD(Yaf_Application, __clone);
PHP_METHOD(Yaf_Application, __sleep);
PHP_METHOD(Yaf_Application, __wakeup);
PHP_METHOD(Yaf_Application, getAppDirectory);
PHP_METHOD(Yaf_Application, setAppDirectory);
PHP_METHOD(Yaf_Application, isModuleName);
PHP_METHOD(Yaf_Application, setErrorNo);
PHP_METHOD(Yaf_Application, setErrorMsg);
PHP_METHOD(Yaf_Application, clearLastError);
PHP_METHOD(Yaf_Application, getLastErrorMsg);
PHP_METHOD(Yaf_Application, getLastErrorNo);
PHP_METHOD(Yaf_Application, _loadConfig);
PHP_METHOD(Yaf_Application, parseOptions);
PHP_METHOD(Yaf_Application, exceptionHandler);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, config)
	ZEND_ARG_INFO(0, env)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_execute, 0, 0, 1)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_setappdirectory, 0, 0, 1)
	ZEND_ARG_INFO(0, directory)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_ismodulename, 0, 0, 1)
	ZEND_ARG_INFO(0, module)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_seterrorno, 0, 0, 1)
	ZEND_ARG_INFO(0, err)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_seterrormsg, 0, 0, 1)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application__loadconfig, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_parseoptions, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_application_exceptionhandler, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, e, Exception, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_application_method_entry) {
	PHP_ME(Yaf_Application, __construct, arginfo_yaf_application___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Application, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Yaf_Application, bootstrap, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, run, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, app, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Application, getConfig, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, getDispatcher, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, getModules, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, environ, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, execute, arginfo_yaf_application_execute, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Application, __sleep, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Application, __wakeup, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Application, getAppDirectory, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, setAppDirectory, arginfo_yaf_application_setappdirectory, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, isModuleName, arginfo_yaf_application_ismodulename, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Application, setErrorNo, arginfo_yaf_application_seterrorno, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, setErrorMsg, arginfo_yaf_application_seterrormsg, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, clearLastError, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, getLastErrorMsg, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, getLastErrorNo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Application, _loadConfig, arginfo_yaf_application__loadconfig, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Application, parseOptions, arginfo_yaf_application_parseoptions, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Application, exceptionHandler, arginfo_yaf_application_exceptionhandler, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
