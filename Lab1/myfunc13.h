#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Line{
    int m;
    double *line_p;
}Line;

typedef struct Matrix{
    int n;
    Line *fcol_p;
}Matrix;

Matrix *new_matrix(int n);

double *new_line(int m);

void delete_matrix(Matrix *mtrx);

int get_int(int *v);

int get_double(double *v);

int input(Line *L);

Matrix *create_matrix();

int is_equal(double x, double y);

int count_diff(Line *L);

void print_matrix(Matrix *mtrx);

int* get_result(Matrix* S,int *size);

void print_vector(int* V, int size);

