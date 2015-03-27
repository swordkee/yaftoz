
extern zend_class_entry *yaf_session_ce;

ZEPHIR_INIT_CLASS(Yaf_Session);

PHP_METHOD(Yaf_Session, __clone);
PHP_METHOD(Yaf_Session, __construct);
PHP_METHOD(Yaf_Session, count);
PHP_METHOD(Yaf_Session, current);
PHP_METHOD(Yaf_Session, del);
PHP_METHOD(Yaf_Session, __destruct);
PHP_METHOD(Yaf_Session, __get);
PHP_METHOD(Yaf_Session, getInstance);
PHP_METHOD(Yaf_Session, has);
PHP_METHOD(Yaf_Session, __isset);
PHP_METHOD(Yaf_Session, key);
PHP_METHOD(Yaf_Session, next);
PHP_METHOD(Yaf_Session, offsetExists);
PHP_METHOD(Yaf_Session, offsetGet);
PHP_METHOD(Yaf_Session, offsetSet);
PHP_METHOD(Yaf_Session, offsetUnset);
PHP_METHOD(Yaf_Session, rewind);
PHP_METHOD(Yaf_Session, __set);
PHP_METHOD(Yaf_Session, __sleep);
PHP_METHOD(Yaf_Session, start);
PHP_METHOD(Yaf_Session, __unset);
PHP_METHOD(Yaf_Session, valid);
PHP_METHOD(Yaf_Session, __wakeup);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_del, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_has, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yaf_session___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yaf_session_method_entry) {
	PHP_ME(Yaf_Session, __clone, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Session, __construct, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_CTOR)
	PHP_ME(Yaf_Session, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, del, arginfo_yaf_session_del, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Yaf_Session, __get, arginfo_yaf_session___get, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, getInstance, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Session, has, arginfo_yaf_session_has, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, __isset, arginfo_yaf_session___isset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, offsetExists, arginfo_yaf_session_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, offsetGet, arginfo_yaf_session_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, offsetSet, arginfo_yaf_session_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, offsetUnset, arginfo_yaf_session_offsetunset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, __set, arginfo_yaf_session___set, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, __sleep, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Yaf_Session, start, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Yaf_Session, __unset, arginfo_yaf_session___unset, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yaf_Session, __wakeup, NULL, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
