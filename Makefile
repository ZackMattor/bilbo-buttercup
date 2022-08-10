CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS := $(wildcard src/*.cc)
OBJS=$(subst .cc,.o,$(SRCS))

all: mud

mud: $(OBJS)
	$(CXX) $(LDFLAGS) -o mud $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) mud
