COINLIBS=lib/libCoinUtils.a lib/libOsi.a
BUILD_LIB=$(CC) $^ -shared -o $@
CXXFLAGS+=-I ./include/coin-or/ -L ./lib
CBC_DISTRIB='https://bintray.com/coin-or/download/download_file?file_path=Cbc-configure-update-static-xenial-linux-x86_64-gcc5.4.0.tgz'

include/% lib/%:
	curl --location $(CBC_DISTRIB) | tar --skip-old-files -xvzf -

build/libosiglpk.so: build/OsiGlpkSolverInterface.o lib/libOsiGlpk.a $(COINLIBS)
	$(BUILD_LIB)

build/libosicbc.so: $(COINLIBS) lib/libOsiCbc.a build/OsiCbcSolverInterface.o
	$(BUILD_LIB)

build/libosiclp.so: build/OsiClpSolverInterface.o -lOsiClp $(COINLIBS)
	$(BUILD_LIB)

build/%.o: osi.cpp | include/
	$(CXX) -c $^ -DSOLVER="$(notdir $(basename $@))" $(CXXFLAGS) -fPIC -o $@

build/example: example.c build/libosicbc.so
	 $(CC) $^ -lstdc++ -o $@

clean:
	rm build/*

all: build/example build/libosiglpk.a build/libosicbc.a build/libosiclp.a