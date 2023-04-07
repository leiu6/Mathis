#include "differentiation.h"


M_type M_diff_symmetrical(M_standard_func func, M_type stepsize, M_type x)
{
    return (func(x + stepsize) - func(x - stepsize)) / (2 * stepsize);
}

