COINLIBS=-lOsi -lCoinUtils
BUILD_LIB=if [[ "$@" == *.a ]]; then ar rvs $@ $^; elif [[ "$@" == *.so ]]; then $(CC) $^ -shared -o $@; else exit 1; fi

build/libosiglpk.so: build/OsiGlpkSolverInterface.o -lOsiGlpk $(COINLIBS)
	$(BUILD_LIB)

build/libosicbc.so: build/OsiCbcSolverInterface.o -lOsiCbc $(COINLIBS)
	$(BUILD_LIB)

build/libosiclp.so: build/OsiClpSolverInterface.o -lOsiClp $(COINLIBS)
	$(BUILD_LIB)

build/%.o: osi.cpp
	$(CXX) -c $^ -DSOLVER="$(notdir $(basename $@))" $(CXXFLAGS) -fPIC -o $@

build/example: example.c build/libosicbc.so
	 $(CC) $^ -O3 -lstdc++ -o $@

clean:
	rm build/*

all: build/example build/libosiglpk.a build/libosicbc.a build/libosiclp.a