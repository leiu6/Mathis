#ifndef _M_CMATRIX_H_INCLUDED
#define _M_CMATRIX_H_INCLUDED

#include "types.h"

#include <stddef.h>
#include <stdio.h>

/*
 * Holds the data for a mathematical matrix consisting of entries with the type M_ctype
 * 
 * Consists of a certain number of rows and columns of numbers
 */
typedef struct _M_cmatrix M_cmatrix;


/*
 * Allocate a new matric
 *
 * rows: the number of rows in the matrix
 * cols: the number of columns in the matrix
 * 
 * Returns a pointer to the matrix
 */
M_cmatrix *M_cmatrix_alloc(size_t rows, size_t cols);


/*
 * Allocate a matrix and initialize it to a given value
 *
 * rows: the number of rows in the matrix
 * cols: the number of colunms in the matrix
 * value: the value that all of the entries should be set to
 * 
 * Returns a pointer to the matrix
 */
M_cmatrix *M_cmatrix_initialize(size_t rows, size_t cols, M_ctype value);


/*
 * Copy another M_cmatrix
 *
 * mat: the existing matrix
 * 
 * Returns a pointer to a copy of mat
 */
M_cmatrix *M_cmatrix_copy(const M_cmatrix *mat);


/*
 * Free the memory allocated for a matrix
 *
 * mat: pointer to the matrix to be freed
 */
void M_cmatrix_destroy(M_cmatrix *mat);


/*
 * Set an entry in the matrix to a specific value
 *
 * mat: pointer to the matrix
 * row: the row of the entry
 * col: the column of the entry
 * value: the value of the entry
 */
void M_cmatrix_set(M_cmatrix *mat, size_t row, size_t col, M_ctype value);


/*
 * Get a value at a given entry in the matrix
 *
 * mat: pointer to the matrix
 * row: The row of the entry
 * col: the column of the entry
 * 
 * Returns the value of the entry
 */
M_ctype M_cmatrix_get(const M_cmatrix *mat, size_t row, size_t col);


/*
 * Get the address of a given entry in the matrix
 *
 * mat: pointer to the matrix
 * row: the row of the entry
 * col: the column of the entry
 * 
 * Returns a pointer to the entry
 */
M_ctype *M_cmatrix_address(M_cmatrix *mat, size_t row, size_t col);


/*
 * Print the matrix to the terminal
 *
 * mat: pointer to the matrix
 * fp: file pointer to print to
 */
void M_cmatrix_print(const M_cmatrix *mat, FILE *fp);


/* Mathematical Operations */

// Add two matrices
M_cmatrix *M_cmatrix_add(const M_cmatrix *A, const M_cmatrix *B);

// Subtract two matrices
M_cmatrix *M_cmatrix_subtract(const M_cmatrix *A, const M_cmatrix *B);

// Multiply two matrices
M_cmatrix *M_cmatrix_mult(const M_cmatrix *A, const M_cmatrix *B);

// Transpose a matrix
void M_cmatrix_trans(M_cmatrix *mat);

#endif // _M_CMATRIX_H_INCLUDED
