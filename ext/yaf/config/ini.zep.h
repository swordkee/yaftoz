
extern zend_class_entry *yaf_config_ini_ce;

ZEPHIR_INIT_CLASS(Yaf_Config_Ini);

PHP_METHOD(Yaf_Config_Ini, __construct);
PHP_METHOD(Yaf_Config_Ini, get);
PHP_METHOD(Yaf_Config_Ini, _parseIniFile);
PHP_METHOD(Yaf_Config_Ini, _loadIniFile);
PHP_METHOD(Yaf_Config_Ini, _processSection);
PHP_METHOD(Yaf_Config_Ini, _processKey);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, section)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini_get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini__parseinifile, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini__loadinifile, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini__processsection, 0, 0, 2)
	ZEND_ARG_ARRAY_INFO(0, iniArray, 0)
	ZEND_ARG_INFO(0, section)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_config_ini__processkey, 0, 0, 3)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_config_ini_method_entry) {
	PHP_ME(Yaf_Config_Ini, __construct, arginfo_yaf_config_ini___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Config_Ini, get, arginfo_yaf_config_ini_get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Config_Ini, _parseIniFile, arginfo_yaf_config_ini__parseinifile, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Config_Ini, _loadIniFile, arginfo_yaf_config_ini__loadinifile, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Config_Ini, _processSection, arginfo_yaf_config_ini__processsection, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Config_Ini, _processKey, arginfo_yaf_config_ini__processkey, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
