#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "matrix.h"


Matrix * allocate_matrix(int row, int col)
{
    Matrix * m = NULL;

    if (row <= 0 || col <= 0) {
        printf("error: the row or col of Matrix can not be small than zero!\n");
        return m;
    }

    m = (Matrix *) calloc (1, sizeof(Matrix));
    if (!m) {
        printf("error: malloc memory for Matrix failed.(%s)\n", strerror(errno));
        return m;
    }

    m->row = row;
    m->col = col;

    m->element = (complex *) calloc (1, row * col * sizeof(complex)); 
    if (!m->element) {
        printf("error: calloc memory for complex element failed.(%s)\n", strerror(errno));
        free(m);
        m = NULL;
        return m;
    }

    return m;
}

void free_matrix(Matrix * m)
{
    if (m != NULL) {
        if (m->element != NULL) {
            free(m->element);
            m->element = NULL;
        }
        
        free(m);
        m = NULL;
    }
}

void print_matrix(Matrix * m)
{
    int r, c, row, col;
    complex * ele;
    if (m != NULL) { 
        printf("Matrix info: row[%d] col[%d]\n", m->row, m->col);
        
        if (m->element != NULL) {
            row = m->row;
            col = m->col;
            ele = m->element;

            for (r = 0; r < row; r++) {
                printf("row: %d\n", r);

                for (c = 0; c < col; c++, ele++) {
                    if (ele->imag >= 0.0)
                        printf("%lf+%lf\t", ele->real, ele->imag);
                    else
                        printf("%lf%lf\t", ele->real, ele->imag);

                    if ((r * col + c + 1) % 8 == 0)
                        printf("\n");
                }
            }
        } else {
            printf("element of Matrix is NULL\n");
        }
    } else {
        printf("%s can not print the info of NULL memory.\n", __FUNCTION__);
    }
}

Bool log_matrix(Matrix * m)
{
    int r, c, row, col;
    complex * ele;

    FILE * fp = NULL;
    char name[256] = {0};
    time_t * t;
    struct tm * time;
    size_t size;

    



    if (m != NULL) { 
        printf("Matrix info: row[%d] col[%d]\n", m->row, m->col);
        
        if (m->element != NULL) {
            row = m->row;
            col = m->col;
            ele = m->element;

            for (r = 0; r < row; r++) {
                printf("row: %d\n", r);

                for (c = 0; c < col; c++, ele++) {
                    if (ele->imag >= 0.0)
                        printf("%lf+%lf\t", ele->real, ele->imag);
                    else
                        printf("%lf%lf\t", ele->real, ele->imag);

                    if ((r * col + c + 1) % 8 == 0)
                        printf("\n");
                }
            }
        } else {
            printf("element of Matrix is NULL\n");
        }
    } else {
        printf("%s can not print the info of NULL memory.\n", __FUNCTION__);
    }
}

Bool addition_matrix(Matrix *lm, Matrix *rm, Matrix * sum)
{
    int r, c, row, col;
    complex *lele, *rele, *sele;

    if ((lm == NULL) || (lm->element == NULL) ||
        (rm == NULL) || (rm->element == NULL)) {
        printf("error: there is/are NULL in argument Matrix\n");
        return False;
    }
    
    if (sum == NULL)
        sum = rm;
    else {
        assert((sum == NULL) || (sum->element == NULL));

        if (!((lm->row == sum->row) && (lm->col == sum->col))) {
            printf("error: the size of the two matrix can not match\n");
            return False;
        }
    }

    if (!((lm->row == rm->row) && (lm->col == rm->col))) {
        printf("error: the size of the two matrix can not match\n");
        return False;
    }

    row = lm->row;
    col = lm->col;

    lele = lm->element;
    rele = rm->element;
    sele = sum->element;

    for (r = 0; r < row; r++) {
        for (c = 0; c < col; c++, lele++, rele++, sele++) { 
            sele->real = lele->real + rele->real;
            sele->imag = lele->imag + rele->imag;
        }
    }

    return True;
}

Bool num_mul_matrix(int num, Matrix * rm)
{
    int r, c, row, col;
    Bool ret = True; 
    int fnum;
    complex * ele;

    if ((rm == NULL) || (rm->element == NULL)) {
        printf("error: Matrix or element is NULL\n");
        return False;
    }

    fnum = num;
    row = rm->row;
    col = rm->col;
    ele = rm->element;

    for (r = 0; r < row; r++) {
        for (c = 0; c < col; c++, ele++) {
            ele->real *= fnum; 
            ele->imag *= fnum;
        }
    }

    return ret;
}

Bool subtract_matrix(Matrix * lm, Matrix * rm, Matrix * sub)
{
    Bool ret = False;
    if ((ret = num_mul_matrix(-1, rm)) == False)
        return ret;

    return addition_matrix(lm, rm, sub);
}

Bool multiply_matrix(Matrix * lm, Matrix * rm, Matrix * mul)
{

    return True;
}
