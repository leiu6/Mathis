#include "root_finding.h"

#include "differentiation.h"
#include "../error.h"

#include <math.h>

#define MAX_IT 1000
#define STEPSIZE M_TYPE_CAST(0.0001)

static inline M_type M_relative_error(M_type x2, M_type x1);


M_type M_relative_error(M_type x2, M_type x1)
{
#if defined(M_TYPE_LDOUBLE)
    return fabsl((x2 - x1) / x2);
#elif defined(M_TYPE_DOUBLE)
    return fabs((x2 - x1) / x2);
#else
    return fabsf((x2 - x1) / x2);
#endif
}


M_type M_rf_newton_raphson(M_standard_func func, M_type x0, M_type error_stop)
{
    M_type x1, x2, rel_error;
    int i = 0;

    x1 = x0;
    rel_error = 1;
    while (rel_error > error_stop && i < MAX_IT)
    {
        x2 = x1 - func(x1) / M_diff_symmetrical(func, STEPSIZE, x1);
        rel_error = M_relative_error(x2, x1);
        i++;
    }

    if (i > MAX_IT)
        M_error_throw(M_ERROR_MAXIT_REACHED, "Newton Raphson: maximum iterations reached");

    return x2;
}