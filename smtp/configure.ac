dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(zapata-smtp, 2.0.0-1artful10, Matheus Henrique dos Santos <vorj.dux@gmail.com>)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])

AC_LANG_CPLUSPLUS
AC_ENABLE_SHARED(yes)
AC_ENABLE_STATIC(yes)

dnl Check for libraries
AC_HAVE_LIBRARY(dl)
AC_HAVE_LIBRARY(magic)
AC_HAVE_LIBRARY(z)
AC_HAVE_LIBRARY(ssl)
AC_HAVE_LIBRARY(crypto)
AC_HAVE_LIBRARY(mosquitto)
AC_CHECK_LIB(zapata-base, zpt_base)
AC_CHECK_LIB(zapata-json, zpt_json)

AC_CANONICAL_SYSTEM

dnl Create config.h header file
AH_TOP([#include <zapata/smtp/unconfig.h>])
AC_CONFIG_HEADERS([include/zapata/smtp/config.h])

dnl Initialize automake
AM_INIT_AUTOMAKE([subdir-objects tar-pax])

dnl this allows us specify individual liking flags for each target
AC_PROG_CXX
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
        debian/Makefile
        include/Makefile
        src/smtp/Makefile)

AC_OUTPUT
