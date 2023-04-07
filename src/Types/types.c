#include "types.h"


const char *M_type_whatis()
{
#if defined(M_TYPE_FLOAT)
    return "float";
#elif defined(M_TYPE_DOUBLE)
    return "double";
#elif defined(M_TYPE_LDOUBLE)
    return "long double";
#endif
}