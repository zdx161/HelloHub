#ifndef MATRIX_FUNCTION_H
#define MATRIX_FUNCTION_H

#include "complex.h"

//Region of macro
#define PI (3.14159267)
#define OMEGA(frequency) (2 * PI * frequency)
#define INITPHA(angle) (angle * PI / 180)
#define PHASE(f, t, a) (OMEGA(f) * t + INITPHA(a))
#define DC(x) ((double)x)

//Region of redefine type of data
typedef struct {
    int row;
    int col;
    complex * element;
} Matrix;

typedef enum {
    False = -1,
    True
} Bool;


//Region of functions
//memory operations
Matrix * allocate_matrix(int row, int col);
Matrix * ones_matrix(int row, int col);
void free_matrix(Matrix * m);

//show operations
void print_matrix(Matrix * m);
Bool log_matrix(Matrix * m, Bool imag);

//calculator operations
Bool addition_matrix(Matrix * lm, Matrix * rm, Matrix * sum);
Bool subtract_matrix(Matrix * lm, Matrix * rm, Matrix * sub);

Bool multiply_matrix(Matrix * lm, Matrix * rm, Matrix * mul);
Bool multiply_matrix_r(Matrix * lm, Matrix * rm, Matrix * mul);
Bool num_mul_matrix(int num, Matrix * rm);

Matrix * transpose_matrix(Matrix * m);
Bool swap_matrix(Matrix * inter);

#endif
