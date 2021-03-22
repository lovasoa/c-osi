COINLIBS=-lOsi -lCoinUtils
BUILD_LIB=ar rcs $@ $^
CPLEX_PATH=~/Downloads/cplex/cplex
CXXFLAGS+=-I "Osi/src/OsiCpx/"
CXXFLAGS+=-I "/usr/include/coin/"
CXXFLAGS+=-L $(CPLEX_PATH)/lib/x86-64_linux/static_pic/

build/libosiglpk.a: build/OsiGlpkSolverInterface.o build/OsiGlpkSolverInterfaceSource.o
	$(BUILD_LIB)

build/libosicbc.a: build/OsiCbcSolverInterface.o
	$(BUILD_LIB)

build/libosiclp.a: build/OsiClpSolverInterface.o
	$(BUILD_LIB)

build/libosicpx.a: build/OsiCpxSolverInterface.o build/OsiCpxSolverInterfaceSource.o
	$(BUILD_LIB)

build/OsiCpxSolverInterfaceSource.o: Osi/src/OsiCpx/OsiCpxSolverInterface.cpp
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^ -I $(CPLEX_PATH)/include/ilcplex/

build/OsiGlpkSolverInterfaceSource.o: Osi/src/OsiGlpk/OsiGlpkSolverInterface.cpp
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^

build/%.o: osi.cpp
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^ -DSOLVER="$(notdir $(basename $@))"

build/example-glpk: example.c build/OsiGlpkSolverInterface.o build/OsiGlpkSolverInterfaceSource.o -lglpk  $(COINLIBS)
	 $(CC) $(CXXFLAGS) $^ -lstdc++ -o $@

build/example-cplex: example.c build/libosicpx.a $(COINLIBS)
	 $(CC) $(CXXFLAGS) $^ -lcplex -lstdc++ -lm -ldl -lpthread -o $@

clean:
	rm build/*

all: build/example build/libosiglpk.a build/libosicbc.a build/libosiclp.a