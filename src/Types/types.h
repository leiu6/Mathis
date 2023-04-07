#include <complex.h>

#if defined(M_TYPE_DOUBLE)
#define M_type double
#define M_ctype double _Complex
#elif defined(M_TYPE_LDOUBLE)
#define M_type long double
#define M_ctype long double _Complex
#else
#define M_type float
#define M_ctype float _Complex
#define M_TYPE_FLOAT
#endif

// Cast a number to the mathematical type used in Mathis
#define M_TYPE_CAST(number) (M_type)(number)

// Cast a number to the complex mathematical type used in Mathis
#define M_CTYPE_CAST(cnumber) (M_ctype)(cnumber)

// Get the current type as a string
const char *M_type_whatis();
