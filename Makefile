COINLIBS=-lOsi -lCoinUtils
BUILD_LIB=ar rcs $@ $^

build/libosiglpk.a: build/OsiGlpkSolverInterface.o
	$(BUILD_LIB)

build/libosicbc.a: build/OsiCbcSolverInterface.o
	$(BUILD_LIB)

build/libosiclp.a: build/OsiClpSolverInterface.o
	$(BUILD_LIB)

build/%.o: osi.cpp
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^ -DSOLVER="$(notdir $(basename $@))"

build/example: example.c build/libosiglpk.a -lOsiGlpk $(COINLIBS)
	 $(CC) $^ -lstdc++ -o $@

clean:
	rm build/*

all: build/example build/libosiglpk.a build/libosicbc.a build/libosiclp.a