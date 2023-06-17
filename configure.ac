AC_INIT([icuformat], [1.0], [none])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 locales/Makefile
])
AC_CONFIG_MACRO_DIRS([m4])

PKG_CHECK_MODULES(ICU, [icu-i18n, icu-io, icu-uc], CPPFLAGS="$CPPFLAGS $ICU_CFLAGS"; LIBS="$LIBS $ICU_LIBS")

AC_OUTPUT
