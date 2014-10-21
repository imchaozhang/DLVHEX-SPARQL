#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([dlvhex-sparqlplugin],[2.0.0],[e.paissios@gmail.com])
AC_CONFIG_SRCDIR([src/SparqlAtom.cpp])
AC_CONFIG_HEADERS(include/[config.h])

# for documentation of the versioning scheme see
# https://sourceforge.net/apps/trac/dlvhex/wiki/LibraryVersions
DLVHEX_DEFINE_VERSION([SPARQLPLUGIN],[$PACKAGE_VERSION])
DLVHEX_DEFINE_VERSION([DLVHEX_ABI],[7.0.0])

AM_INIT_AUTOMAKE([dist-bzip2])

AC_CANONICAL_HOST

# by default we look into /opt/local and /sw for include files (macports vs. fink)
case $host_os in
     darwin*|macosx*)
	CPPFLAGS="$CPPFLAGS -I/opt/local/include -I/sw/include"
     ;;
esac 


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_LANG([C++])

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h] [sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T 

# Checks for library functions.
AC_FUNC_MALLOC
AC_LIBTOOL_DLOPEN # we build a module library
AC_DISABLE_STATIC # we don't need a static library
AC_PROG_LIBTOOL

AC_ARG_ENABLE(debug-symbols,[  --enable-debug-symbols 	Enable debug symbols for the plugin.],[ DEBUG_FLAGS="-g -Wall" ; AC_SUBST([DEBUG_FLAGS])],
[DEBUG_FLAGS="" ; AC_SUBST([DEBUG_FLAGS])])


# check for dlvhex, sets various variables
DLVHEX_REQUIRE([2.0.0])
# Checks for raptor and dlvhex via pkg-config
PKG_CHECK_MODULES([RAPTOR], [raptor2 >= 2.0.0])
PKG_CHECK_MODULES([REDLAND], [redland >= 1.0.0])


PKG_CHECK_MODULES([SOPRANO],[soprano >= 2.9.0])
AC_SUBST(SOPRANO_CFLAGS)
AC_SUBST(SOPRANO_LIBS)


# checking for QT
PKG_CHECK_MODULES(QT, [QtCore >= 4.6, QtGui >= 4.6, QtMultimedia >= 4.6])
AC_SUBST(QT_CFLAGS)
AC_SUBST(QT_LIBS)


# checking for boost libs
BOOST_REQUIRE([1.41.0])
BOOST_SMART_PTR
BOOST_STRING_ALGO
BOOST_TOKENIZER

AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/$DLVHEX_USERPLUGINDIR],
             [plugindir=$DLVHEX_SYSPLUGINDIR]
             )
AC_SUBST([plugindir])
if test "x$plugindir" == "x"; then
	AC_MSG_ERROR([Cannot determine nonempty value for plugindir!])
fi


AC_CONFIG_FILES([Makefile
				include/Makefile
                src/Makefile])

AC_OUTPUT

dnl output configuration
cat <<EOF
 
$PACKAGE_TARNAME $PACKAGE_VERSION configuration:

 - Compiler settings
 CC: $CC
 CXX: $CXX
 CFLAGS: $CFLAGS
 CPPFLAGS: $CPPFLAGS
 CXXFLAGS: $CXXFLAGS
 LDFLAGS: $LDFLAGS
 RAPTOR:$RAPTOR_LIBS
 QT:$QT_LIBS
 SOPRANO:$SOPRANO_LIBS

 - from pkg-config
 DLVHEX_CFLAGS: $DLVHEX_CFLAGS
 DLVHEX_LIBS: $DLVHEX_LIBS
 DLVHEX_BINDIR: $DLVHEX_BINDIR
 
 ________
 SOPRANO_CFLAGS: $SOPRANO_CFLAGS
 RAPTOR_CFLAGS: $RAPTOR_CFLAGS
 QT_CFLAGS: $QT_CFLAGS
 
 
 - Path settings
 prefix: $prefix
 plugindir: $plugindir
EOF

