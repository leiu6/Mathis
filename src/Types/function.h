#ifndef _FUNCTION_H_INCLUDED
#define _FUNCTION_H_INCLUDED

#include "types.h"
#include "matrix.h"


// Defines a standard function f = f(x);
typedef M_type (*M_standard_func)(M_type);

// Defines a standard complex function f_comp = f(a + bi);
typedef M_ctype (*M_complex_func)(M_ctype);

// Defines a standard matrix function
typedef void (*M_matrix_func)(const M_matrix*);

#endif // _FUNCTION_H_INCLUDED
