noinst_PROGRAMS = parser time write search
check_PROGRAMS = new
TESTS = $(check_PROGRAMS)

parser_SOURCES = parser.c
parser_LDADD = ../src/libmrss.la

write_SOURCES = write.c
write_LDADD = ../src/libmrss.la

new_SOURCES = new.c
new_LDADD = ../src/libmrss.la

time_SOURCES = time.c
time_LDADD = ../src/libmrss.la

search_SOURCES = search.c
search_LDADD = ../src/libmrss.la

AM_CPPFLAGS = -I$(srcdir)/../src
