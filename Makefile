
VERSION  := 0.1.0

CXX      ?= g++ 
CXXFLAGS := -std=c++0x -Iinclude -Iinclude/rxml $(CXXFLAGS)
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local
 
HEADERS    = $(wildcard include/*.h)
PRIVHDRS   = $(wildcard rxml/*.h) $(wildcard rxml/*.hpp) $(wildcard rxml/*.hh)
SOURCES    = $(wildcard rxml/*.cpp)
TESTSRCS   = $(wildcard test/*.cpp)

EXTRA_DIST = Makefile README.md rxml/XmlLexer.fpp rxml/XmlParser.ypp 
DIST_FILES = $(HEADERS) $(SOURCES) $(TESTSRCS) $(PRIVHDRS) $(EXTRA_DIST)
 
ifeq ($(OS), Windows_NT)
  EXEEXT    = .exe  
  LIBEXT    = .dll  
else
  EXEEXT    =
  LIBEXT    = .so 
  CXXFLAGS += -fPIC  
endif
 
.PHONY: all check clean install uninstall dist
 
all: librxml$(LIBEXT)

ifeq ($(OS), Windows_NT) 
librxml$(LIBEXT): $(patsubst %.cpp, .obj/%.o, $(SOURCES))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ -o $@ -Wl,--out-implib=$(patsubst %.dll,%.a, $@)
else
librxml$(LIBEXT): $(patsubst %.cpp, .obj/%.o, $(SOURCES))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ -o $@
endif 
 
check: rxml-test$(EXEEXT)	
	cd test && LD_LIBRARY_PATH=.. ../rxml-test$(EXEEXT)
 
rxml-test$(EXEEXT): $(patsubst %.cpp, .obj/%.o, $(TESTSRCS)) librxml$(LIBEXT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
 
clean: 
	rm -rf .obj librxml$(LIBEXT) librxml.a rxml-test$(EXEEXT)	
 
dist:
	mkdir rxml-$(VERSION)
	cp --parents $(DIST_FILES) rxml-$(VERSION)
	tar -czvf rxml-$(VERSION).tar.gz rxml-$(VERSION)
	rm -rf rxml-$(VERSION)
 
install: rxml$(LIBEXT)
	mkdir -p $(prefix)/include/rxml
	cp $(HEADERS) $(prefix)/include/rxml
ifeq ($(OS), Windows_NT)	
	mkdir -p $(prefix)/lib
	cp librxml.a $(prefix)/lib
	mkdir -p $(prefix)/bin
	cp librxml$(LIBEXT) $(prefix)/bin
else
	mkdir -p $(prefix)/lib
	cp librxml.$(LIBEXT) $(prefix)/lib
endif	
 
uninstall:
	rm -r $(prefix)/include/rxml	
ifeq ($(OS), Windows_NT)
	rm $(prefix)/lib/librxml.a
	rm $(prefix)/bin/librxml$(LIBEXT)
else
	rm $(prefix)/lib/librxml$(LIBEXT)	
endif	
 
.obj/%.o : %.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MD -c $< -o $@	
	
rxml/XmlLexer.fpp: rxml/XmlParser.cpp						
rxml/XmlLexer.cpp: rxml/XmlLexer.fpp
	$(FLEX) -o $@ $^

rxml/XmlParser.hpp: rxml/XmlParser.ypp
rxml/XmlParser.cpp: rxml/XmlParser.ypp
	$(BISON) -o $@ $^
 
ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, .obj/%.d, $(SOURCES))
-include $(patsubst %.cpp, .obj/%.d, $(TESTSRCS))
endif