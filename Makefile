
VERSION  := 0.1.0

CXX      ?= g++ 
CXXFLAGS := -std=c++0x -I. $(CXXFLAGS)
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local
 

HEADERS    = $(wildcard rxml/*.h) $(wildcard rxml/*.hpp) $(wildcard rxml/*.hh)
SOURCES    = rxml/XmlParser.cpp rxml/XmlLexer.cpp $(wildcard rxml/*.cpp)
TESTSRCS   = $(wildcard rxml-test/*.cpp)

EXTRA_DIST = Makefile README.md rxml/XmlLexer.fpp rxml/XmlParser.ypp $(wildcard rxml-test/*.h)
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
	./rxml-test$(EXEEXT)
 
rxml-test$(EXEEXT): $(patsubst %.cpp, .obj/%.o, $(TESTSRCS)) librxml$(LIBEXT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
 
clean: 
	rm -rf .obj librxml$(LIBEXT) librxml.a rxml-test$(EXEEXT)
 
distclean: clean
	rm -rf rxml/XMLLexer.cpp rxml/XMLParser.cpp rxml/XMLParser.hpp rxml/XMLParser.output rxml/location.hh rxml/position.hh 

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

%.cpp: %.fpp
	$(FLEX) -o $@ $^

%.cpp: %.ypp
	$(BISON) --report=all -o $@ $^

rxml/XmlParser.hpp: rxml/XmlParser.cpp

ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, .obj/%.d, $(SOURCES))
-include $(patsubst %.cpp, .obj/%.d, $(TESTSRCS))
endif