PHP_ARG_ENABLE(yaf, whether to enable yaf, [ --enable-yaf   Enable Yaf])

if test "$PHP_YAF" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, YAF_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_YAF, 1, [Whether you have Yaf])
	yaf_sources="yaf.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/extended/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c yaf/config/exception.zep.c
	yaf/config/ini.zep.c
	yaf/config/simple.zep.c
	yaf/exception/loadfailed/action.zep.c
	yaf/exception/loadfailed/controller.zep.c
	yaf/exception/loadfailed/loadfailed.zep.c
	yaf/exception/loadfailed/module.zep.c
	yaf/exception/loadfailed/view.zep.c
	yaf/exception/dispatchfailed.zep.c
	yaf/exception/routerfailed.zep.c
	yaf/exception/startuperror.zep.c
	yaf/exception/typeerror.zep.c
	yaf/request/exception.zep.c
	yaf/request/http.zep.c
	yaf/request/simple.zep.c
	yaf/response/cli.zep.c
	yaf/response/exception.zep.c
	yaf/response/http.zep.c
	yaf/route/exception.zep.c
	yaf/route/map.zep.c
	yaf/route/regex.zep.c
	yaf/route/rewrite.zep.c
	yaf/route/simple.zep.c
	yaf/route/supervar.zep.c
	yaf/view/simple.zep.c
	yaf/action_abstract.zep.c
	yaf/application.zep.c
	yaf/bootstrap_abstract.zep.c
	yaf/config_abstract.zep.c
	yaf/controller_abstract.zep.c
	yaf/dispatcher.zep.c
	yaf/exception.zep.c
	yaf/g.zep.c
	yaf/loader.zep.c
	yaf/plugin_abstract.zep.c
	yaf/registry.zep.c
	yaf/request_abstract.zep.c
	yaf/response_abstract.zep.c
	yaf/route_interface.zep.c
	yaf/route_static.zep.c
	yaf/router.zep.c
	yaf/session.zep.c
	yaf/view_interface.zep.c "
	PHP_NEW_EXTENSION(yaf, $yaf_sources, $ext_shared,, )
	PHP_SUBST(YAF_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([yaf], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([yaf], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/yaf], [php_YAF.h])

fi
