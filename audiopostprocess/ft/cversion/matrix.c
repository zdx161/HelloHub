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

Matrix * ones_matrix(int row, int col)
{
    int r, c, rc;
    complex * ele;
    Matrix * ones = NULL;
    complex com = {1, 0};

    ones = allocate_matrix(row, col);
    ele = ones->element;

    for (r = 0; r < row; r++) {
        rc = r * col;
        for (c = 0; c < col; c++, ele++) {
            *ele = com;
        }
    }

    return ones;
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
                //printf("row: %d\n", r);

                for (c = 0; c < col; c++, ele++) {
                    if (ele->imag >= 0.0)
                        printf("%lf+%lfi\t", ele->real, ele->imag);
                    else
                        printf("%lf%lfi\t", ele->real, ele->imag);

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

Bool log_matrix(Matrix * m, Bool imag)
{
    int r, c, row, col;
    complex * ele;
    Bool ret = True;

    FILE * fp = NULL;
    char name[256] = {0};
    time_t t;
    struct tm * stm;
    size_t size;

    if (m != NULL) {
        if (m->element != NULL) {
            t = time(NULL);
            stm = localtime(&t);
            size = strftime(name, 256, "%F", stm);
            strftime(name+size, 256 - size, "-%T", stm);
            printf("log file -> %s\n", name);

            fp = fopen(name, "w+");
            if (!fp) {
                printf("error: %s\n", strerror(errno));
                ret = False;
                goto OUT;
            }

            row = m->row;
            col = m->col;
            ele = m->element;

            if (imag == False) {
                for (r = 0; r < row; r++) {
                    for (c = 0; c < col; c++, ele++) {
                        //fwrite(&ele->real, sizeof(double), 1, fp);
                        fprintf(fp, "%lf", ele->real);
                        if ((r * col + c + 1) % 16 == 0)
                            fprintf(fp, "\n");//fputc(0x0a, fp);
                        else
                            fprintf(fp, " ");//fputc(0x20, fp);
                    }
                }
            } else {
                for (r = 0; r < row; r++) {
                    for (c = 0; c < col; c++, ele++) {
                        fwrite(&ele->real, sizeof(double), 1, fp);
                        fputc(0x20, fp);
                        fwrite(&ele->imag, sizeof(double), 1, fp);
                        if ((r * col + c + 1) % 8 == 0)
                            fputc(0x0a, fp);
                        else
                            fputc(0x20, fp);
                    }
                }
            }
        } else {
            printf("element of Matrix is NULL\n");
            ret = False;
        }
    } else {
        printf("%s can not print the info of NULL memory.\n", __FUNCTION__);
        ret = False;
    }

OUT:
    if (fp)
        fclose(fp);

    return ret;
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
    int lr, lc, rr, rc, mr, mc, lrow, lcol, rrow, rcol, mrow, mcol;
    complex *lele, *rele, *mele;
    complex c1, c2, m;

    if (lm == NULL || rm == NULL || mul == NULL) {
        printf("error: matrix can not be NULL.\n");
        return False;
    }

    if (lm->element == NULL || rm->element == NULL || mul->element == NULL) {
        printf("error: there is no memory in element of matrix.\n");
        return False;
    }

    if (!((lm->row > 0 && lm->col > 0) && (rm->row > 0 && rm->col >0) &&
            (mul->row > 0 && mul->col > 0))) {
        printf("error: row or col can not be zero.\n");
        return False;
    }

    if (!((lm->col == rm->row) && (mul->row == lm->row) && (mul->col == rm->col))) {
        printf("error: the attribute of matrix can not match\n");
        return False;
    }

    lrow = lm->row;
    lcol = lm->col;
    rrow = rm->row;
    rcol = rm->col;
    mrow = mul->row;
    mcol = mul->col;
    lele = lm->element;
    rele = rm->element;
    mele = mul->element;

    for (mr = 0; mr < mrow; mr++) {
        for (mc = 0; mc < mcol; mc++, mele++) {
            for (lc = 0; lc < lcol; lc++) {
                c1 = *(lele + mr * lcol + lc);
                c2 = *(rele + lc * rcol + mc);
                //m = multiply_complex(c1, c2);
                m = num_mul_complex(c1, c2.real);
                *mele = addition_complex(*mele, m);
            }
        }
    }

    return True;
}

Bool swap_matrix(Matrix * inter)
{
    int r, row;
    complex * ele;

    if (inter == NULL || inter->row == 0 || inter->element == NULL) {
        printf("error: there are some errors in Matrix.\n");
        return False;
    }

    row = inter->row;
    ele = inter->element;

    return True;
}
