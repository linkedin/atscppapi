#
# Copyright (c) 2013 LinkedIn Corp. All rights reserved. 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
# except in compliance with the License. You may obtain a copy of the license at
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the
# License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
# either express or implied.
#

# These first two version numbers are updated on each release.
# Version number is calculated as MAJOR * 1000000 + MINOR * 1000 + MICRO
# Version string is in the form of MAJOR.MINOR.MICRO
m4_define([ATSCPPAPI_VERSION_STR],[1.0.3])
m4_define([ATSCPPAPI_VERSION_NUM],[1000003])
AC_PREREQ([2.63])
AC_INIT([libatscppapi], ATSCPPAPI_VERSION_STR(), [bgeffon@linkedin.com, mnilange@linkedin.com], [atscppapi])
AM_INIT_AUTOMAKE([1.10 -Wall -Werror no-define foreign])

# Libtool versioning uses different conventions on different
# platforms.  At least on FreeBSD, libtool uses an overly complex
# convention that attempts to solve problems that most people just
# don't have and which just causes confusion for most end users.
#
# see: http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
#
ATSCPPAPI_VERSION_MAJOR=$((ATSCPPAPI_VERSION_NUM() / 1000000 ))
ATSCPPAPI_VERSION_MINOR=$(((ATSCPPAPI_VERSION_NUM() / 1000) % 1000 ))
ATSCPPAPI_VERSION_MICRO=$((ATSCPPAPI_VERSION_NUM() % 1000 ))
ATSCPPAPI_LIBTOOL_MAJOR=`echo $((${ATSCPPAPI_VERSION_MAJOR} + ${ATSCPPAPI_VERSION_MINOR}))`
ATSCPPAPI_LIBTOOL_VERSION=$ATSCPPAPI_LIBTOOL_MAJOR:$ATSCPPAPI_VERSION_MICRO:$ATSCPPAPI_VERSION_MINOR
ATSCPPAPI_VERSION_STRING=ATSCPPAPI_VERSION_STR()
ATSCPPAPI_VERSION_NUMBER=ATSCPPAPI_VERSION_NUM()

AC_SUBST(ATSCPPAPI_LIBTOOL_VERSION)
AC_SUBST(ATSCPPAPI_VERSION_STRING)
AC_SUBST(ATSCPPAPI_VERSION_NUMBER)
AC_SUBST(ATSCPPAPI_VERSION_MAJOR)
AC_SUBST(ATSCPPAPI_VERSION_MINOR)
AC_SUBST(ATSCPPAPI_VERSION_MICRO)

AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# This makes the make step quiet, you can override with V=1 w/ make.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_MACRO_DIR([build])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([examples/Makefile])
AC_CONFIG_FILES([examples/helloworld/Makefile])
AC_CONFIG_FILES([examples/globalhook/Makefile])
AC_CONFIG_FILES([examples/transactionhook/Makefile])
AC_CONFIG_FILES([examples/multiple_transaction_hooks/Makefile])
AC_CONFIG_FILES([examples/clientrequest/Makefile])
AC_CONFIG_FILES([examples/data_caching/Makefile])
AC_CONFIG_FILES([examples/serverresponse/Makefile])
AC_CONFIG_FILES([examples/clientredirect/Makefile])
AC_CONFIG_FILES([examples/customresponse/Makefile])
AC_CONFIG_FILES([examples/null_transformation_plugin/Makefile])
AC_CONFIG_FILES([examples/post_buffer/Makefile])
AC_CONFIG_FILES([examples/logger_example/Makefile])
AC_CONFIG_FILES([examples/detachedrequest/Makefile])
AC_CONFIG_FILES([examples/stat_example/Makefile])
AC_CONFIG_FILES([examples/async_http_fetch/Makefile])
AC_CONFIG_FILES([examples/remap_plugin/Makefile])
AC_CONFIG_FILES([examples/gzip_transformation/Makefile])
AC_CONFIG_FILES([examples/timeout_example/Makefile])
AC_CONFIG_FILES([examples/internal_transaction_handling/Makefile])
AC_CONFIG_FILES([examples/async_timer/Makefile])
AC_CONFIG_FILES([examples/request_cookies/Makefile])

ifdef([AM_PROG_AR],
      [AM_PROG_AR])

# Checks for programs.
AC_PROG_CXX

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AC_CONFIG_FILES([docs/Doxyfile])

# Checks for libraries.

AC_CHECK_LIB([rt], [clock_gettime])
AC_CHECK_LIB([pthread], [pthread_create])
AC_CHECK_LIB([zlib], [deflate])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h sys/time.h unistd.h pthread.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_INT64_T
AC_TYPE_UINT64_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([clock_gettime gettimeofday memset select socket strerror])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h sys/socket.h sys/time.h sys/select.h sys/types.h unistd.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_OUTPUT
