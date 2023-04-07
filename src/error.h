#ifndef _M_ERROR_H_INCLUDED
#define _M_ERROR_H_INCLUDED


#include <stdbool.h>


// This is the size of the buffer for the error messages
#define M_ERROR_MSG_BUFSIZE 256


/* This header defines the error handling for the Mathis library */

/* Errors */
/*
 * Defines the various error codes in the library
 */
typedef enum {

    M_ERROR_NONE =                          0,
    M_ERROR_INVALID_ARGS =                  -1,
    M_ERROR_OVERFLOW =                      -2,
    M_ERROR_UNDERFLOW =                     -3,
    M_ERROR_OUTOFBOUNDS =                   -4,
    M_ERROR_MAXIT_REACHED =                 -5

} M_error;


/*
 * Resets the error status
 */
void M_error_reset();


/*
 * Detect whether an error occurs, and if it did occur, clear the error and
 * return the code via *error pointer
 *
 * error: pointer to an integral type to hold the error code if it happens
 * msg: pointer to a character to hold the string describing the error
 *
 * Returns true if there was an error. Returns false otherwise
 */ 
bool M_error_occurred(M_error *error, char *msg);


/*
 * Throw an error
 *
 * error: the error code
 * msg: a string describing the error
 */
void M_error_throw(M_error error, const char *msg);


/*
 * Print the error code and message to the terminal in a nice readable way
 *
 * error: the error code
 * msg: the message that accompanies the error
 */
void M_error_print(M_error error, const char *msg);


/*
 * Detects if the error occurred and prints it, along with the message
 */
void M_error_detect_and_print();


#endif // _M_ERROR_H_INCLUDED
