// Example of using COIN-OR OSI, building the instance internally
// with sparse matrix object

#ifndef SOLVER
#define SOLVER OsiCbcSolverInterface
#endif

#define STRINGIFY_MACRO(x) STR(x)
#define STR(x) #x
#define EXPAND(x) x
#define CONCAT(n1, n2) STRINGIFY_MACRO(EXPAND(n1)EXPAND(n2))
#define CONCAT3(n1, n2, n3) STRINGIFY_MACRO(EXPAND(n1)EXPAND(n2)EXPAND(n3))

#include <stdio.h>
#include <cfloat>
#include CONCAT3(coin/,SOLVER,.hpp)
#include "coin/CoinPackedMatrix.hpp"
#include "coin/CoinPackedVector.hpp"
#include "coin/OsiCuts.hpp"
#include "coin/OsiBranchingObject.hpp"

// Originally from https://github.com/coin-or/Cbc/blob/713a373/src/Cbc_C_Interface.cpp

extern "C" {

/** @brief Creates a new SOLVER and returns a pointer to an OsiSolverInterface object */
void * Osi_newSolver() {
  return dynamic_cast<OsiSolverInterface *>(new SOLVER);
}


void Osi_addRow(void *osi, const char *name, int nz,
  const int *cols, const double *coefs, char sense, double rhs)
{
  OsiSolverInterface *solver = (OsiSolverInterface *) osi;
  double rowLB = -DBL_MAX, rowUB = DBL_MAX;
  switch (toupper(sense)) {
  case '=':
    rowLB = rowUB = rhs;
    break;
  case 'E':
    rowLB = rowUB = rhs;
    break;
  case '<':
    rowUB = rhs;
    break;
  case 'L':
    rowUB = rhs;
    break;
  case '>':
    rowLB = rhs;
    break;
  case 'G':
    rowLB = rhs;
    break;
  default:
    fprintf(stderr, "unknown row sense %c.", toupper(sense));
    abort();
  }

  solver->addRow(nz, cols, coefs, rowLB, rowUB);
  solver->setRowName(solver->getNumRows()-1, std::string(name));
}

void Osi_setObjSense(void *osi, double sense)
{
  OsiSolverInterface *solver = (OsiSolverInterface *) osi;
  solver->setObjSense(sense);
}

void Osi_setObjCoef(void *osi, int index, double obj)
{
  OsiSolverInterface *osis = (OsiSolverInterface *)osi;
  osis->setObjCoeff( index, obj );
}

/** @brief gets a value considered by the solver to be infinite */
double Osi_getInfinity(void *osi) {
  OsiSolverInterface *solver = (OsiSolverInterface *)osi;
  return solver->getInfinity();
}


/** @brief Write the problem to an LP file */
void Osi_writeLp(void *osi, FILE* fp) {
  OsiSolverInterface *solver = (OsiSolverInterface *)osi;
  return solver->writeLp(fp);
}

/** @brief Solves initial LP relaxation */
void Osi_initialSolve(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  osis->initialSolve();
}

/** @brief Reoptimizes linear program  */
void Osi_resolve(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  osis->resolve();
}

/** @brief Performs branch and bound */
void Osi_branchAndBound(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  osis->branchAndBound();
}

// solution query methods
/** @brief Checks if optimization was abandoned */
char Osi_isAbandoned(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isAbandoned();
}

/** @brief Checks if optimal solution was found */
char Osi_isProvenOptimal(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isProvenOptimal();
}

/** @brief Checks if problem is primal infeasible */
char Osi_isProvenPrimalInfeasible(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isProvenPrimalInfeasible();
}

/** @brief Checks if problem is dual infeasible */
char Osi_isProvenDualInfeasible(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isProvenDualInfeasible();
}

/** @brief Checks if primal objective limit was reached */
char Osi_isPrimalObjectiveLimitReached(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isPrimalObjectiveLimitReached();
}

/** @brief Checks if dual objective limit was reached */
char Osi_isDualObjectiveLimitReached(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isDualObjectiveLimitReached();
}

/** @brief Checks if iteration limit was reached */
char Osi_isIterationLimitReached(void *osi)
{
  OsiSolverInterface *osis = ( OsiSolverInterface *)osi;
  return (char)osis->isIterationLimitReached();
}


int Osi_getNumCols( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getNumCols();
}

/** @brief Copies column name in OsiSolverInterface object */
void Osi_getColName( void *osi, int i, char *name, int maxLen )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  strncpy( name, osiSolver->getColName(i).c_str(), maxLen );
}

/** @brief Returns column lower bounds in OsiSolverInterface object */
const double * Osi_getColLower( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getColLower();
}

/** @brief Returns column upper bounds in OsiSolverInterface object */
const double * Osi_getColUpper( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getColUpper();
}

/** @brief Returns integrality information for columns in OsiSolverInterface object */
int Osi_isInteger( void *osi, int col )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->isInteger(col);
}

/** @brief Returns number of rows in OsiSolverInterface object */
int Osi_getNumRows( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getNumRows();
}

/** @brief Returns number non-zeros in the constraint matrix */
int Osi_getNumNz( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getNumElements();
}

/** @brief Returns number integer/binary variables */
int Osi_getNumIntegers( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getNumIntegers();
}

int Osi_getRowNz(void *osi, int row)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  const CoinPackedMatrix *cpmRow = osiSolver->getMatrixByRow();
  return cpmRow->getVectorLengths()[row];
}

/** @brief Indices of variables that appear on a row */
const int *Osi_getRowIndices(void *osi, int row)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  const CoinPackedMatrix *cpmRow = osiSolver->getMatrixByRow();
  const CoinBigIndex *starts = cpmRow->getVectorStarts();
  const int *ridx = cpmRow->getIndices() + starts[row];
  return ridx;
}

/** @brief Coefficients of variables that appear on this row  */
const double *Osi_getRowCoeffs(void *osi, int row)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  const CoinPackedMatrix *cpmRow = osiSolver->getMatrixByRow();
  const CoinBigIndex *starts = cpmRow->getVectorStarts();
  const double *rcoef = cpmRow->getElements() + starts[row];
  return rcoef;
}

/** @brief Right hand side of a row  */
double Osi_getRowRHS(void *osi, int row)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getRightHandSide()[row];
}

/** @brief Sense a row
     * @param model problem object
     * @param row row index
     * @return row sense: E for =, L for <=, G for >= and R for ranged row
     **/
char Osi_getRowSense(void *osi, int row)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  return osiSolver->getRowSense()[row];
}

/** Creates a new cut pool and returns its pointer */
void * OsiCuts_new() {
  OsiCuts *oc = new OsiCuts();
  return (void *) oc;
}

/** Deletes a cut pool */
void OsiCuts_delete( void *osiCuts ) {
  OsiCuts *oc = (OsiCuts *) osiCuts;
  delete oc;
}

/** Returns the number of row cuts stored */
int OsiCuts_sizeRowCuts( void *osiCuts ) {
  OsiCuts *oc = (OsiCuts *)osiCuts;
  return oc->sizeRowCuts();
}

/** Returns the number of row cuts stored */
int OsiCuts_nzRowCut( void *osiCuts, int iRowCut ) {
  assert(iRowCut >= 0 && iRowCut < OsiCuts_sizeRowCuts(osiCuts) );
  OsiCuts *oc = (OsiCuts *)osiCuts;
  const OsiRowCut &rc = oc->rowCut(iRowCut);
  return rc.row().getNumElements();
}

/** Returns the variable indexes in a row cut */
const int * OsiCuts_idxRowCut( void *osiCuts, int iRowCut ) {
  assert(iRowCut >= 0 && iRowCut < OsiCuts_sizeRowCuts(osiCuts) );
  OsiCuts *oc = (OsiCuts *)osiCuts;
  const OsiRowCut &rc = oc->rowCut(iRowCut);
  return rc.row().getIndices();
}

/** Returns the variable coefficients in a row cut */
const double * OsiCuts_coefRowCut( void *osiCuts, int iRowCut ) {
  assert(iRowCut >= 0 && iRowCut < OsiCuts_sizeRowCuts(osiCuts) );
  OsiCuts *oc = (OsiCuts *)osiCuts;
  const OsiRowCut &rc = oc->rowCut(iRowCut);
  return rc.row().getElements();
}

/** Returns the variable coefficients in a row cut */
double OsiCuts_rhsRowCut( void *osiCuts, int iRowCut ) {
  assert(iRowCut >= 0 && iRowCut < OsiCuts_sizeRowCuts(osiCuts) );
  OsiCuts *oc = (OsiCuts *)osiCuts;
  const OsiRowCut &rc = oc->rowCut(iRowCut);
  return rc.rhs();
}

/** Returns the sense of a row cut */
char OsiCuts_senseRowCut( void *osiCuts, int iRowCut ) {
  assert(iRowCut >= 0 && iRowCut < OsiCuts_sizeRowCuts(osiCuts) );
  OsiCuts *oc = (OsiCuts *)osiCuts;
  const OsiRowCut &rc = oc->rowCut(iRowCut);
  return rc.sense();
}

void OsiCuts_addRowCut( void *osiCuts, int nz, const int *idx, const double *coef, char sense, double rhs )
{
  sense = toupper(sense);
  OsiCuts *oc = (OsiCuts *) osiCuts;

  OsiRowCut orc;
  orc.setRow( nz, idx, coef );


  orc.setLb(-DBL_MAX);
  orc.setUb(DBL_MAX);

  switch (toupper(sense)) {
  case '=':
    orc.setLb(rhs);
    orc.setUb(rhs);
    break;
  case 'E':
    orc.setLb(rhs);
    orc.setUb(rhs);
    break;
  case '<':
    orc.setUb(rhs);
    break;
  case 'L':
    orc.setUb(rhs);
    break;
  case '>':
    orc.setLb(rhs);
    break;
  case 'G':
    orc.setLb(rhs);
    break;
  default:
    fprintf(stderr, "unknown row sense %c.", toupper(sense));
    abort();
  }

  oc->insert(orc);
}

/** adds a row cut (used in callback), stating that this is a globally valid cut */
void OsiCuts_addGlobalRowCut( void *osiCuts, int nz, const int *idx, const double *coef, char sense, double rhs )
{
  sense = toupper(sense);
  OsiCuts *oc = (OsiCuts *) osiCuts;

  OsiRowCut orc;
  orc.setRow( nz, idx, coef );


  orc.setLb(-DBL_MAX);
  orc.setUb(DBL_MAX);

  switch (toupper(sense)) {
  case '=':
    orc.setLb(rhs);
    orc.setUb(rhs);
    break;
  case 'E':
    orc.setLb(rhs);
    orc.setUb(rhs);
    break;
  case '<':
    orc.setUb(rhs);
    break;
  case 'L':
    orc.setUb(rhs);
    break;
  case '>':
    orc.setLb(rhs);
    break;
  case 'G':
    orc.setLb(rhs);
    break;
  default:
    fprintf(stderr, "unknown row sense %c.", toupper(sense));
    abort();
  }

  orc.setGloballyValid(true);
  oc->insert(orc);
}


/** @brief Sets a variable to integer */
void Osi_setInteger(void *osi, int index)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  osiSolver->setInteger(index);
}

/** @brief Sets a variable to continuous */
void Osi_setContinuous(void *osi, int index)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  osiSolver->setContinuous(index);
}

int Osi_getColNz(void *osi, int col)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  const CoinPackedMatrix *cpmCol = osiSolver->getMatrixByCol();
  return cpmCol->getVectorLengths()[col];
}

/** @brief Indices of rows that a column appears 
     *
     * @param model problem object 
     * @param col column index
     * @return indices of rows that this column appears
     **/
const int *Osi_getColIndices(void *osi, int col)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  const CoinPackedMatrix *cpmCol = osiSolver->getMatrixByCol();
  const CoinBigIndex *starts = cpmCol->getVectorStarts();
  const int *cidx = cpmCol->getIndices() + starts[col];
  return cidx;
}

/** @brief Coefficients that a column appear in rows 
     *
     * @param model problem object 
     * @param col column index
     * @return coefficients of this column in rows
     **/
const double *Osi_getColCoeffs(void *osi, int col)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  const CoinPackedMatrix *cpmCol = osiSolver->getMatrixByCol();
  const CoinBigIndex *starts = cpmCol->getVectorStarts();
  const double *rcoef = cpmCol->getElements() + starts[col];
  return rcoef;
}

/** @brief Returns solution vector in OsiSolverInterface object */
const double * Osi_getColSolution( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  return osiSolver->getColSolution();
}

/** Adds a new column */
void Osi_addCol(void *osi, const char *name, double lb,
  double ub, double obj, char isInteger,
  int nz, int *rows, double *coefs)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

    osiSolver->addCol(nz, rows, coefs, lb, ub, obj, std::string(name));
    if (isInteger)
      osiSolver->setInteger(osiSolver->getNumCols() - 1);
}

/** @brief Returns vector of reduced costs */
const double * Osi_getReducedCost( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  return osiSolver->getColSolution();
}

/** @brief Returns vector dual variables */
const double * Osi_getRowPrice( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  return osiSolver->getRowPrice();
}

double Osi_getObjValue( void *osi )
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;

  return osiSolver->getObjValue();
}

/** @brief Sets column upper bound */
void Osi_setColUpper (void *osi, int elementIndex, double ub)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  osiSolver->setColUpper(elementIndex, ub);
}

/** @brief Sets column upper bound */
void Osi_setColLower(void *osi, int elementIndex, double lb)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  osiSolver->setColLower(elementIndex, lb);
}

/** @brief integer tolerance */
double Osi_getIntegerTolerance(void *osi)
{
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  return osiSolver->getIntegerTolerance();
}


/** @brief add a new SOS constraint to the given problem */
void Osi_addSos(void *osi, int numberMembers, const int * columns, const double * weights, const int type) {
  OsiSolverInterface *osiSolver = (OsiSolverInterface *) osi;
  OsiObject *sos = new OsiSOS(osiSolver, numberMembers, columns, weights, type);
  osiSolver->addObjects(1, &sos);
  delete sos;
}

}