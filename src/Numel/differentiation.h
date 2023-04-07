#ifndef _DIFFERENTIATION_H_INCLUDED
#define _DIFFERENTIATION_H_INCLUDED


#include "../Types/types.h"
#include "../Types/function.h"


/*
 * Computes an approximation of a derivative using the symmetrical difference formula
 *
 * func: a pointer to the function M_type func(M_type) that you are finding the derivative of
 * stepsize: the stepsize used for the approximation. As stepsize approaches 0, the approximation approaches the true derivative
 * x: the point the derivative should be evaluated at
 * 
 * Returns the value of the derivative at the given point x
 */
M_type M_diff_symmetrical(M_standard_func func, M_type stepsize, M_type x);


#endif // _DIFFERENTIATION_H_INCLUDED
