lib_LTLIBRARIES = libmrss.la

libmrss_la_SOURCES = \
	mrss_free.c \
	mrss_parser.c \
	mrss_write.c \
	mrss_download.c \
	mrss_edit.c \
	mrss_generic.c \
	mrss_options.c \
	mrss_search.c

libmrss_la_LDFLAGS = -version-info @LIBMRSS_VERSION_INFO@

EXTRA_DIST = mrss.h.in mrss.h mrss_internal.h

incdir = $(includedir)
inc_DATA = mrss.h

