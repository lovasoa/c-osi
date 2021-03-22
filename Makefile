COINLIBS=-lOsi -lCoinUtils

build/libosicbc.a: build/OsiCbcSolverInterface.o -lOsiCbc $(COINLIBS)
	ar rvs $@ $^

build/libosiglpk.a: build/OsiGlpkSolverInterface.o -lOsiGlpk $(COINLIBS)
	ar rvs $@ $^

build/libosiclp.a: build/OsiClpSolverInterface.o -lOsiClp $(COINLIBS)
	ar rvs $@ $^

build/%.o: osi.cpp
	$(CXX) -c $^ -DSOLVER="$(notdir $(basename $@))" $(CXXFLAGS) -o $@

clean:
	rm *.a build/*

all: build/libosiglpk.a build/libosicbc.a build/libosiclp.a