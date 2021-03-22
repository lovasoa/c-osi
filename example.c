// Bare bones example of using COIN-OR OSI

#include "osi.h"
#include <stdio.h>

int main(void) {
   printf("Creating an OSI solver instance.\n");
   void* si = Osi_newSolver();

   // Maximize x + y

   //Define the variable lower/upper bounds.
   // x0 >= 0   =>  0 <= x0 <= infinity
   // x1 >= 0   =>  0 <= x1 <= infinity
   printf("Adding variable x >= 0.\n");
   double x_lower_bound = 0.0;
   double x_upper_bound = Osi_getInfinity(si);
   double x_objective_coef = 1.0;
   char x_is_integer = 0; // false
   Osi_addCol(si, "x", x_lower_bound, x_upper_bound, x_objective_coef, x_is_integer, 0, 0, 0);

   printf("Adding variable y >= 0.\n");
   double y_lower_bound = 0.0;
   double y_upper_bound = Osi_getInfinity(si);
   double y_objective_coef = 1.0;
   char y_is_integer = 0;
   Osi_addCol(si, "y", y_lower_bound, y_upper_bound, y_objective_coef, y_is_integer, 0, 0, 0);

   printf("Setting maximization.\n");
   Osi_setObjSense(si, -1.0);

   printf("Adding constraint row1: x + 2*y <= 3.\n");
   int row1_nz = 2;
   int row1_cols[2] = {0, 1};
   double row1_coefs[2] = {1.0, 2.0};
   double row1_rhs = 3.0;
   Osi_addRow(si, "row1", row1_nz, row1_cols, row1_coefs, '<', row1_rhs);

   printf("Adding constraint row1: 2*x + y <= 3.\n");
   int row2_nz = 2;
   int row2_cols[2] = {0, 1};
   double row2_coefs[2] = {2.0, 1.0};
   double row2_rhs = 3.0;
   Osi_addRow(si, "row1", row2_nz, row2_cols, row2_coefs, '<', row2_rhs);


   printf("Here is the problem in the LP format: \n");
   Osi_writeLp(si, stdout);

   // Solve the (relaxation of the) problem
   Osi_initialSolve(si);

   // Check the solution
   if ( Osi_isProvenOptimal(si) ) {
      printf("Found optimal solution!\n");
      printf("Objective value is %.2f \n", Osi_getObjValue(si));

      int n = Osi_getNumCols(si);
      const double* solution = Osi_getColSolution(si);

      // We can then print the solution or could examine it.
      for( int i = 0; i < n; ++i ) {
         char name[255];
         Osi_getColName(si, i, name, 255);
         printf("%s = %f\n", name, solution[i]);
      }
   } else {
      printf("Didn't find optimal solution.\n");
      // Could then check other status functions.
   }
   Osi_deleteSolver(si);
   return 0;
}