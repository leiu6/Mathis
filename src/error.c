#include "error.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static M_error M_errno = M_ERROR_NONE;
static char M_errno_msg[M_ERROR_MSG_BUFSIZE];


void M_error_reset()
{
    M_errno = M_ERROR_NONE;
}


bool M_error_occurred(M_error *error, char *msg)
{
    if (M_errno == M_ERROR_NONE)
        return false;

    *error = M_errno;
    if (msg != NULL)
        strncpy(msg, M_errno_msg, M_ERROR_MSG_BUFSIZE);
    M_error_reset();
    return true;
}


void M_error_throw(M_error error, const char *msg)
{
    // You can't clear the error this way. Read the error code instead
    if (error == M_ERROR_NONE) return;

    strncpy(M_errno_msg, msg, M_ERROR_MSG_BUFSIZE);
    M_errno = error;
}


void M_error_print(M_error error, const char *msg)
{
    fprintf(stderr, "MATHIS_ERROR: Code: %i. Msg: %s\n", error, msg);
}


void M_error_detect_and_print()
{
    M_error error;
    char msg[M_ERROR_MSG_BUFSIZE];

    if (M_error_occurred(&error, msg))
    {
        M_error_print(error, msg);
    }
}
