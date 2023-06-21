bin_PROGRAMS = icuformat
icuformat_SOURCES = icuformat.cpp

lib_LTLIBRARIES = libi18n.la
libi18n_la_SOURCES= i18n.cpp
include_HEADERS = i18n.h

icuformat_LDADD = libi18n.la

AM_CPPFLAGS = -DLOCALES_DATA='"$(LOCALES_DATA)"'
