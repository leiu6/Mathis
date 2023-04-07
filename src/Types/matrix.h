#ifndef _M_MATRIX_H_INCLUDED
#define _M_MATRIX_H_INCLUDED

#include "types.h"

#include <stddef.h>
#include <stdio.h>

/*
 * Holds the data for a mathematical matrix consisting of entries with the type M_type
 * 
 * Consists of a certain number of rows and columns of numbers
 */
typedef struct _M_matrix M_matrix;


/*
 * Allocate a new matric
 *
 * rows: the number of rows in the matrix
 * cols: the number of columns in the matrix
 * 
 * Returns a pointer to the matrix
 */
M_matrix *M_matrix_alloc(size_t rows, size_t cols);


/*
 * Allocate a matrix and initialize it to a given value
 *
 * rows: the number of rows in the matrix
 * cols: the number of colunms in the matrix
 * value: the value that all of the entries should be set to
 * 
 * Returns a pointer to the matrix
 */
M_matrix *M_matrix_initialize(size_t rows, size_t cols, M_type value);


/*
 * Copy another M_matrix
 *
 * mat: the existing matrix
 * 
 * Returns a pointer to a copy of mat
 */
M_matrix *M_matrix_copy(const M_matrix *mat);


/*
 * Free the memory allocated for a matrix
 *
 * mat: pointer to the matrix to be freed
 */
void M_matrix_destroy(M_matrix *mat);


/*
 * Set an entry in the matrix to a specific value
 *
 * mat: pointer to the matrix
 * row: the row of the entry
 * col: the column of the entry
 * value: the value of the entry
 */
void M_matrix_set(M_matrix *mat, size_t row, size_t col, M_type value);


/*
 * Get a value at a given entry in the matrix
 *
 * mat: pointer to the matrix
 * row: The row of the entry
 * col: the column of the entry
 * 
 * Returns the value of the entry
 */
M_type M_matrix_get(const M_matrix *mat, size_t row, size_t col);


/*
 * Get the address of a given entry in the matrix
 *
 * mat: pointer to the matrix
 * row: the row of the entry
 * col: the column of the entry
 * 
 * Returns a pointer to the entry
 */
M_type *M_matrix_address(M_matrix *mat, size_t row, size_t col);


/*
 * Print the matrix to the terminal
 *
 * mat: pointer to the matrix
 * fp: file pointer to print to
 */
void M_matrix_print(const M_matrix *mat, FILE *fp);


/* Mathematical Operations */

// Add two matrices
M_matrix *M_matrix_add(const M_matrix *A, const M_matrix *B);

// Subtract two matrices
M_matrix *M_matrix_subtract(const M_matrix *A, const M_matrix *B);

// Multiply two matrices
M_matrix *M_matrix_mult(const M_matrix *A, const M_matrix *B);

// Transpose a matrix
void M_matrix_trans(M_matrix *mat);

#endif // _M_MATRIX_H_INCLUDED
