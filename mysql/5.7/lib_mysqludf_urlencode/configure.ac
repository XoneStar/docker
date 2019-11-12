AC_PREREQ(2.59)

AC_INIT([libmysqludf], [0.3], [mike@iworks.at])
AC_SUBST([PACKAGE_NAME])
AC_SUBST([PACKAGE_VERSION])
AC_SUBST([PACKAGE_BUGREPORT])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h strings.h time.h sys/types.h])
AC_C_CONST
AC_C_INLINE
AC_CHECK_SIZEOF(long, 4)

AC_ARG_WITH([mysql], AC_HELP_STRING([--with-mysql], [where mysql is installed]))
AC_ARG_WITH([mysql_config], AC_HELP_STRING([--with-mysql_config], [where mysql_config is located]))
AC_ARG_WITH([mysql-includes], AC_HELP_STRING([--with-mysql-include], [where mysql include directory is located]))

MYSQL_INCLUDES=
AC_MSG_CHECKING([for mysql headers])
for i in "$with_mysql_includes" "`$with_mysql_config --include 2>&1|$SED -e's/-I//'`" "$with_mysql/include" /usr/include/mysql; do
	if test -f "$i/mysql.h"; then
		MYSQL_INCLUDES=$i
		break
	fi
done
if test -z "$MYSQL_INCLUDES"; then
	AC_MSG_ERROR([could not find mysql headers])
else
	AC_MSG_RESULT([$MYSQL_INCLUDES])
fi

INCLUDES="-I$MYSQL_INCLUDES $INCLUDES"
AC_SUBST(INCLUDES)

AC_CONFIG_SRCDIR([lib])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADER([lib/mysqludf_config.h])

AM_INIT_AUTOMAKE
AC_OUTPUT

$ECHO
$ECHO "WARNING: remember to set the prefix to the mysql installation directory,"
$ECHO "         respectively to set the libdir to the one mysql uses for UDFs"
$ECHO
