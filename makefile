

ifndef BUILDDIR 
	export BUILDDIR=$(shell pwd)/build
endif

ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
	LIBFILE=libdatetime.dll
else
#linux and mac here
	OS=$(shell uname -s)
	MD=mkdir -p
	ifeq ($(OS),Linux)
		LIBFILE=libdatetime.so
	else
		LIBFILE=libdatetime.dylib
	endif
endif

ifeq ($(PREFIX),)
#install path
	PREFIX=/usr/local
endif


.PHONY: all lib obj clean test install testinstall uninstall

all: obj lib

windows: winobj winlib

obj:
	$(MD) $(BUILDDIR)
	cd src; make obj

lib:
	$(MD) lib
	cd src; make lib

winobj:
	$(MD) $(BUILDDIR)
	cd src; make winobj

winlib: 
	$(MD) lib
	cd src; make winlib


test:
	cd test; make all

clean:
	-rm -v build/*.o
	-rmdir -v build
	-rm -v testinstall
	-rm -v lib/$(LIBFILE)
	cd test; make clean

install:
	cp -v include/datetime.h $(PREFIX)/include

	cp -v lib/$(LIBFILE) $(PREFIX)/lib
	chmod 0775 $(PREFIX)/lib/$(LIBFILE)
ifeq ($(OS),Linux)
	ldconfig
endif


uninstall:
	rm -v $(PREFIX)/include/datetime.h
	rm -v $(PREFIX)/lib/$(LIBFILE)
ifeq ($(OS),Linux)
	ldconfig
endif

testinstall:
	g++ -std=c++17 test/testcc.cc -o testinstall -ldatetime
	./testinstall
	rm -v testinstall