// Open Solver Interface C interface

#include <stdio.h>

/** @brief Creates a new SOLVER and returns a pointer to an OsiSolverInterface object */
void * Osi_newSolver();

/** @brief Adds a constraint to the problem. */
void Osi_addRow(void *osi, const char *name, int nz,
  const int *cols, const double *coefs, char sense, double rhs);

/** @brief Set whether the objective should be minimized (sense=1) or maximized (sense=-1) */
void Osi_setObjSense(void *osi, double sense);

/** Set the coefficient before the column at position `index` in the objective function */
void Osi_setObjCoef(void *osi, int index, double obj);

/** @brief Write the problem to an LP file */
void Osi_writeLp(void *osi, FILE* fp);

/** @brief Solves initial LP relaxation */
void Osi_initialSolve(void *osi);

/** @brief Reoptimizes linear program  */
void Osi_resolve(void *osi);

/** @brief Performs branch and bound */
void Osi_branchAndBound(void *osi);

// solution query methods
/** @brief Checks if optimization was abandoned */
char Osi_isAbandoned(void *osi);

/** @brief Checks if optimal solution was found */
char Osi_isProvenOptimal(void *osi);

/** @brief gets a value considered by the solver to be infinite */
double Osi_getInfinity(void *osi);

/** @brief Checks if problem is primal infeasible */
char Osi_isProvenPrimalInfeasible(void *osi);

/** @brief Checks if problem is dual infeasible */
char Osi_isProvenDualInfeasible(void *osi);

/** @brief Checks if primal objective limit was reached */
char Osi_isPrimalObjectiveLimitReached(void *osi);

/** @brief Checks if dual objective limit was reached */
char Osi_isDualObjectiveLimitReached(void *osi);

/** @brief Checks if iteration limit was reached */
char Osi_isIterationLimitReached(void *osi);


int Osi_getNumCols( void *osi );

/** @brief Returns column name in OsiSolverInterface object */
void Osi_getColName( void *osi, int i, char *name, int maxLen );

/** @brief Returns column lower bounds in OsiSolverInterface object */
const double * Osi_getColLower( void *osi );

/** @brief Returns column upper bounds in OsiSolverInterface object */
const double * Osi_getColUpper( void *osi );

/** @brief Returns integrality information for columns in OsiSolverInterface object */
int Osi_isInteger( void *osi, int col );

/** @brief Returns number of rows in OsiSolverInterface object */
int Osi_getNumRows( void *osi );

/** @brief Returns number non-zeros in the constraint matrix */
int Osi_getNumNz( void *osi );

/** @brief Returns number integer/binary variables */
int Osi_getNumIntegers( void *osi );

int Osi_getRowNz(void *osi, int row);

/** @brief Indices of variables that appear on a row */
const int *Osi_getRowIndices(void *osi, int row);

/** @brief Coefficients of variables that appear on this row  */
const double *Osi_getRowCoeffs(void *osi, int row);

/** @brief Right hand side of a row  */
double Osi_getRowRHS(void *osi, int row);

/** @brief Sense a row
     * @param model problem object
     * @param row row index
     * @return row sense: E for =, L for <=, G for >= and R for ranged row
     **/
char Osi_getRowSense(void *osi, int row);

/** Creates a new cut pool and returns its pointer */
void * OsiCuts_new();

/** Deletes a cut pool */
void OsiCuts_delete( void *osiCuts );

/** Returns the number of row cuts stored */
int OsiCuts_sizeRowCuts( void *osiCuts );

/** Returns the number of row cuts stored */
int OsiCuts_nzRowCut( void *osiCuts, int iRowCut );

/** Returns the variable indexes in a row cut */
const int * OsiCuts_idxRowCut( void *osiCuts, int iRowCut );

/** Returns the variable coefficients in a row cut */
const double * OsiCuts_coefRowCut( void *osiCuts, int iRowCut );

/** Returns the variable coefficients in a row cut */
double OsiCuts_rhsRowCut( void *osiCuts, int iRowCut );

/** Returns the sense of a row cut */
char OsiCuts_senseRowCut( void *osiCuts, int iRowCut );

void OsiCuts_addRowCut( void *osiCuts, int nz, const int *idx, const double *coef, char sense, double rhs );

/** adds a row cut (used in callback), stating that this is a globally valid cut */
void OsiCuts_addGlobalRowCut( void *osiCuts, int nz, const int *idx, const double *coef, char sense, double rhs );


/** @brief Sets a variable to integer */
void Osi_setInteger(void *osi, int index);

/** @brief Sets a variable to continuous */
void Osi_setContinuous(void *osi, int index);

int Osi_getColNz(void *osi, int col);

/** @brief Indices of rows that a column appears 
     *
     * @param model problem object 
     * @param col column index
     * @return indices of rows that this column appears
     **/
const int *Osi_getColIndices(void *osi, int col);

/** @brief Coefficients that a column appear in rows 
     *
     * @param model problem object 
     * @param col column index
     * @return coefficients of this column in rows
     **/
const double *Osi_getColCoeffs(void *osi, int col);

/** @brief Returns solution vector in OsiSolverInterface object */
const double * Osi_getColSolution( void *osi );

/** Adds a new column */
void Osi_addCol(void *osi, const char *name, double lb,
  double ub, double obj, char isInteger,
  int nz, int *rows, double *coefs);

/** @brief Returns vector of reduced costs */
const double * Osi_getReducedCost( void *osi );

/** @brief Returns vector dual variables */
const double * Osi_getRowPrice( void *osi );

double Osi_getObjValue( void *osi );

/** @brief Sets column upper bound */
void Osi_setColUpper (void *osi, int elementIndex, double ub);

/** @brief Sets column upper bound */
void Osi_setColLower(void *osi, int elementIndex, double lb);

/** @brief integer tolerance */
double Osi_getIntegerTolerance(void *osi);


/** @brief add a new SOS constraint to the given problem */
void Osi_addSos(void *osi, int numberMembers, const int * columns, const double * weights, const int type);