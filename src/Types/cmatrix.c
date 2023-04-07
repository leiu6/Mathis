#include "cmatrix.h"
#include "../error.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

struct _M_cmatrix {
    M_ctype **data;
    size_t rows;
    size_t cols;
};


#define FAST_ADDRESS(i, j) (mat->data[i][j])

#define FAST_ADDRESS_MAT(matrix, i, j) (matrix->data[i][j])

#define CHECK_OUTOFBOUNDS(i, j, msg, expression) \
    if (((i) > mat->rows - 1 || (i) < 0) || ((j) > mat->cols - 1 || (j) < 0)) \
    { \
        M_error_throw(M_ERROR_OUTOFBOUNDS, msg); \
        { expression; } \
    }

#define CHECK_SIZE_EQ(matA, matB, msg, expression) \
    if (matA->rows != matB->rows || matA->cols != matB->cols) \
    { \
        M_error_throw(M_ERROR_INVALID_ARGS, msg); \
        { expression; } \
    }

#define CHECK_MULT(matA, matB, msg, expression) \
    if (matA->cols != matB->rows) \
    { \
        M_error_throw(M_ERROR_INVALID_ARGS, msg); \
        { expression; } \
    }

#define CHECK_NULL(matrix, msg, expression) \
    if (matrix == NULL) \
    { \
        M_error_throw(M_ERROR_INVALID_ARGS, msg); \
        { expression; } \
    }


M_cmatrix *M_cmatrix_alloc(size_t rows, size_t cols)
{
    M_cmatrix *mat = malloc(sizeof(M_cmatrix));

    mat->rows = rows;
    mat->cols = cols;

    mat->data = malloc(rows * sizeof(M_ctype*));
    for (size_t i = 0; i < rows; i++)
        mat->data[i] = malloc(cols * sizeof(M_ctype));

    return mat;
}


M_cmatrix *M_cmatrix_initialize(size_t rows, size_t cols, M_ctype value)
{
    M_cmatrix *mat = M_cmatrix_alloc(rows, cols);

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols; col++)
        {
            FAST_ADDRESS(row, col) = value;
        }
    }

    return mat;
}


M_cmatrix *M_cmatrix_copy(const M_cmatrix *mat)
{
    CHECK_NULL(mat, "Cannot copy a NULL matrix", return NULL);

    M_cmatrix *copy = M_cmatrix_alloc(mat->rows, mat->cols);

    for (size_t row = 0; row < mat->rows; row++)
    {
        for (size_t col = 0; col < mat->cols; col++)
        {
            FAST_ADDRESS_MAT(copy, row, col) = FAST_ADDRESS_MAT(mat, row, col);
        }
    }

    return copy;
}


void M_cmatrix_destroy(M_cmatrix *mat)
{
    for (size_t i = 0; i < mat->rows; i++)
        free(mat->data[i]);
    
    free(mat->data);
    free(mat);
}


void M_cmatrix_set(M_cmatrix *mat, size_t row, size_t col, M_ctype value)
{
    CHECK_OUTOFBOUNDS(row, col, "Matrix index out of bounds", return);

    FAST_ADDRESS(row, col) = value;
}


M_ctype M_cmatrix_get(const M_cmatrix *mat, size_t row, size_t col)
{
    CHECK_OUTOFBOUNDS(row, col, "Matrix index out of bounds", return M_CTYPE_CAST(0));

    return FAST_ADDRESS(row, col);
}


M_ctype *M_cmatrix_address(M_cmatrix *mat, size_t row, size_t col)
{
    CHECK_OUTOFBOUNDS(row, col, "Matrix index out of bounds", return NULL);

    return &(FAST_ADDRESS(row, col));
}


void M_cmatrix_print(const M_cmatrix *mat, FILE *fp)
{
    fprintf(fp, "M_cmatrix (%li x %li):\n", mat->rows, mat->cols);
    
    for (size_t row = 0; row < mat->rows; row++)
    {
        if (row == 0) fprintf(fp, "[");
        else fprintf(fp, " ");

        for (size_t col = 0; col < mat->cols; col++)
        {
            if (col == 0)
                fprintf(fp, "[");

            // Bake in some type safety
            if (col >= 0 && col < mat->cols - 1)

            {
#if defined(M_TYPE_FLOAT)
                fprintf(fp, "%f + i%f, ", crealf(FAST_ADDRESS(row, col)), cimagf(FAST_ADDRESS(row, col)));
#elif defined(M_TYPE_DOUBLE)
                fprintf(fp, "%f + i%f, ", creal(FAST_ADDRESS(row, col)), cimag(FAST_ADDRESS(row, col)));
#elif defined(M_TYPE_LDOUBLE)
                fprintf(fp, "%Lf + i%Lf, ", creall(FAST_ADDRESS(row, col)), cimagl(FAST_ADDRESS(row, col)));
#endif
            }

            if (col >= mat->cols - 1)
            {
#if defined(M_TYPE_FLOAT)
                fprintf(fp, "%f + i%f]", crealf(FAST_ADDRESS(row, col)), cimagf(FAST_ADDRESS(row, col)));
#elif defined(M_TYPE_DOUBLE)
                fprintf(fp, "%f + i%f]", creal(FAST_ADDRESS(row, col)), cimag(FAST_ADDRESS(row, col)));
#elif defined(M_TYPE_LDOUBLE)
                fprintf(fp, "%Lf + i%Lf]", creall(FAST_ADDRESS(row, col)), cimagl(FAST_ADDRESS(row, col)));
#endif
            }
        }

        if (row < mat->rows - 1)
            fprintf(fp, ",\n");
        else
            fprintf(fp, "]\n");
    }
}


/* Mathematical Operations */
M_cmatrix *M_cmatrix_add(const M_cmatrix *A, const M_cmatrix *B)
{
    CHECK_SIZE_EQ(A, B, "Matrices must be same size for addition", return NULL);

    M_cmatrix *mat = M_cmatrix_alloc(A->rows, A->cols);

    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t col = 0; col < A->cols; col++)
        {
            FAST_ADDRESS(row, col) = FAST_ADDRESS_MAT(A, row, col) + FAST_ADDRESS_MAT(B, row, col);
        }
    }

    return mat;
}


M_cmatrix *M_cmatrix_subtract(const M_cmatrix *A, const M_cmatrix *B)
{
    CHECK_SIZE_EQ(A, B, "Matrices must be same size for subtraction", return NULL);

    M_cmatrix *mat = M_cmatrix_alloc(A->rows, A->cols);

    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t col = 0; col < A->cols; col++)
        {
            FAST_ADDRESS(row, col) = FAST_ADDRESS_MAT(A, row, col) - FAST_ADDRESS_MAT(B, row, col);
        }
    }

    return mat;
}


M_cmatrix *M_cmatrix_mult(const M_cmatrix *A, const M_cmatrix *B)
{
    CHECK_MULT(A, B, "First matrix must have same number of columns as second matrix has rows for matrix multiplication", return NULL);

    M_cmatrix *mat = M_cmatrix_alloc(A->rows, B->cols);

    for (size_t row = 0; row < A->rows; row++)
    {
        for (size_t col = 0; col < B->cols; col++)
        {
            M_ctype dot_product = M_CTYPE_CAST(0);
            for (size_t i = 0; i < A->cols; i++)
            {
                dot_product += FAST_ADDRESS_MAT(A, row, i) * FAST_ADDRESS_MAT(B, i, col);
            }

            FAST_ADDRESS(row, col) = dot_product;
        }
    }

    return mat;
}


void M_cmatrix_trans(M_cmatrix *mat)
{
    CHECK_NULL(mat, "Cannot transpose a NULL matrix", return;);

    // Transposed version
    M_cmatrix *transposed = M_cmatrix_alloc(mat->cols, mat->rows);

    for (size_t row = 0; row < mat->cols; row++)
    {
        for (size_t col = 0; col < mat->rows; col++)
        {
            FAST_ADDRESS_MAT(transposed, row, col) = FAST_ADDRESS_MAT(mat, col, row);
        }
    }

    M_cmatrix_destroy(mat);
    mat = transposed;
}
