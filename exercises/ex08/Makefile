CC=-gcc
CFLAGS=-Wall

# glib flags
GCFLAGS=$(shell pkg-config --cflags glib-2.0)
GLLIBS=$(shell pkg-config --libs glib-2.0)

ex_compile: CFLAGS+=$(GCFLAGS)
ex_compile: LDLIBS+=$(GLLIBS)

word_count: CFLAGS+=$(GCFLAGS)
word_count: LDLIBS+=$(GLLIBS)
