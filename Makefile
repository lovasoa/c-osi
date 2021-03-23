CPLEX_PATH=~/Downloads/cplex/cplex
OSI_OBJ=build/Osi/OsiSolverInterface.o build/Osi/OsiAuxInfo.o build/Osi/OsiBranchingObject.o build/Osi/OsiChooseVariable.o build/Osi/OsiColCut.o build/Osi/OsiCut.o build/Osi/OsiCuts.o build/Osi/OsiFeatures.o build/Osi/OsiNames.o build/Osi/OsiPresolve.o build/Osi/OsiRowCut.o build/Osi/OsiRowCutDebugger.o build/Osi/OsiSolverBranch.o
COINUTILS_OBJ=build/CoinUtils/CoinAdjacencyVector.o build/CoinUtils/CoinAlloc.o build/CoinUtils/CoinBronKerbosch.o build/CoinUtils/CoinBuild.o build/CoinUtils/CoinCliqueExtender.o build/CoinUtils/CoinCliqueList.o build/CoinUtils/CoinCliqueSet.o build/CoinUtils/CoinConflictGraph.o build/CoinUtils/CoinCutPool.o build/CoinUtils/CoinDenseFactorization.o build/CoinUtils/CoinDenseVector.o build/CoinUtils/CoinDynamicConflictGraph.o build/CoinUtils/CoinError.o build/CoinUtils/CoinFactorization1.o build/CoinUtils/CoinFactorization2.o build/CoinUtils/CoinFactorization3.o build/CoinUtils/CoinFactorization4.o build/CoinUtils/CoinFileIO.o build/CoinUtils/CoinFinite.o build/CoinUtils/CoinIndexedVector.o build/CoinUtils/CoinLpIO.o build/CoinUtils/CoinMessage.o build/CoinUtils/CoinMessageHandler.o build/CoinUtils/CoinModel.o build/CoinUtils/CoinModelUseful2.o build/CoinUtils/CoinModelUseful.o build/CoinUtils/CoinMpsIO.o build/CoinUtils/CoinNodeHeap.o build/CoinUtils/CoinOddWheelSeparator.o build/CoinUtils/CoinOslFactorization2.o build/CoinUtils/CoinOslFactorization3.o build/CoinUtils/CoinOslFactorization.o build/CoinUtils/CoinPackedMatrix.o build/CoinUtils/CoinPackedVectorBase.o build/CoinUtils/CoinPackedVector.o build/CoinUtils/CoinParam.o build/CoinUtils/CoinParamUtils.o build/CoinUtils/CoinPostsolveMatrix.o build/CoinUtils/CoinPrePostsolveMatrix.o build/CoinUtils/CoinPresolveDoubleton.o build/CoinUtils/CoinPresolveDual.o build/CoinUtils/CoinPresolveDupcol.o build/CoinUtils/CoinPresolveEmpty.o build/CoinUtils/CoinPresolveFixed.o build/CoinUtils/CoinPresolveForcing.o build/CoinUtils/CoinPresolveHelperFunctions.o build/CoinUtils/CoinPresolveImpliedFree.o build/CoinUtils/CoinPresolveIsolated.o build/CoinUtils/CoinPresolveMatrix.o build/CoinUtils/CoinPresolveMonitor.o build/CoinUtils/CoinPresolvePsdebug.o build/CoinUtils/CoinPresolveSingleton.o build/CoinUtils/CoinPresolveSubst.o build/CoinUtils/CoinPresolveTighten.o build/CoinUtils/CoinPresolveTripleton.o build/CoinUtils/CoinPresolveUseless.o build/CoinUtils/CoinPresolveZeros.o build/CoinUtils/CoinRational.o build/CoinUtils/CoinSearchTree.o build/CoinUtils/CoinShallowPackedVector.o build/CoinUtils/CoinShortestPath.o build/CoinUtils/CoinSimpFactorization.o build/CoinUtils/CoinSnapshot.o build/CoinUtils/CoinStaticConflictGraph.o build/CoinUtils/CoinStructuredModel.o build/CoinUtils/CoinWarmStartBasis.o build/CoinUtils/CoinWarmStartDual.o build/CoinUtils/CoinWarmStartPrimalDual.o build/CoinUtils/CoinWarmStartVector.o
COIN_OBJ=$(COINUTILS_OBJ) $(OSI_OBJ)
CXXFLAGS+=-I "Osi/src/OsiCpx/"
CXXFLAGS+=-I "Osi/src/OsiGlpk/"
CXXFLAGS+=-I "CoinUtils/src/"
CXXFLAGS+=-I "Osi/src/Osi"
CXXFLAGS+=-L $(CPLEX_PATH)/lib/x86-64_linux/static_pic/
BUILD_LIB=$(CXX) $(CXXFLAGS) -shared -o $@ $^ -lstdc++

build/libosiglpk.so: build/OsiGlpkSolverInterface.o build/OsiGlpkSolverInterfaceSource.o $(COIN_OBJ) -lm -lglpk
	$(BUILD_LIB)

build/libosicpx.so: build/OsiCpxSolverInterface.o build/OsiCpxSolverInterfaceSource.o $(COIN_OBJ) -lm -ldl -lpthread
	$(BUILD_LIB) -lcplex

build/OsiCpxSolverInterfaceSource.o: Osi/src/OsiCpx/OsiCpxSolverInterface.cpp | build
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^ -I $(CPLEX_PATH)/include/ilcplex/

build/OsiGlpkSolverInterfaceSource.o: Osi/src/OsiGlpk/OsiGlpkSolverInterface.cpp | build
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^

build/%.o: osi.cpp | build
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^ -DSOLVER="$(notdir $(basename $@))"

build/Osi/%.o: Osi/src/Osi/%.cpp | build
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^

build/CoinUtils/%.o: CoinUtils/src/%.cpp | build
	$(CXX) $(CXXFLAGS) -fPIC -o $@ -c $^

build:
	mkdir -p build/Osi
	mkdir -p build/CoinUtils

build/libosi.so: build/libosiglpk.so # Change this to use another solver. No need to recompile the original example
	 cp $^ $@

build/example: example.c build/libosi.so
	 $(CC) $(CXXFLAGS) $^ -o $@

clean:
	rm -r build/*

all: build/example build/libosiglpk.so