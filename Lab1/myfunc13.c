#include "myfunc13.h"
#include <stdio.h>
#include <stdlib.h>
Matrix *new_matrix(int n){
       Matrix *mtrx = (Matrix*) calloc(1,sizeof(Matrix));
       mtrx->fcol_p = (Line*) calloc(n,sizeof(Line));
       return mtrx;
}

double *new_line(int m){
       return (double*) calloc(m,sizeof(double));
}

void delete_matrix(Matrix *mtrx){
       int i,n  = mtrx->n;
       Line *ptr = mtrx->fcol_p;
       for(i = 0;i < n;i++){
           free((ptr + i)->line_p);
       }
       free(mtrx->fcol_p);
       free(mtrx);
}

int get_int(int *v){
    int n;
    char c;
    do{
    n = scanf_s("%d",v,sizeof(int));
    if (n < 0){
        return 0;
    }
    scanf_s("%c",&c,sizeof(char));
    if (n == 0 || (n > 0 && c != '\n')){
        printf("Error,try again\n");
        scanf_s("%*s",0);
    }
    } while(n == 0 || (n > 0 && c != '\n'));
    return 1;
}

int get_double(double *v){
    int n;
    char c;
    do{
    n = scanf_s("%lf",v,sizeof(double));
    if (n < 0){
        return 0;
    }
    scanf_s("%c",&c,sizeof(char));
    if (n == 0 || (n > 0 && c != '\n')){
        printf("Error,try again\n");
        scanf_s("%*s");
    }
    } while(n == 0 || (n > 0 && c != '\n'));
    return 1;
}

int input(Line *L){
     int t,m = L->m,i;
     double v;
     double *ptr = L->line_p;
     for(i = 0;i < m;i++){
         printf("Please, enter element number %d: \n",i + 1);
         t = get_double(&v);
         if (!t){
             printf("Interrupt input\n");
             return 0;
         }
         *(ptr + i) = v;
     }
     return 1;
}

Matrix *create_matrix(){
       int n,i,m,v;
       Matrix *mtrx = NULL;
       do{
       printf("Please, enter number of strings: \n");
       v = get_int(&n);
       if (!v){
           return NULL;
       }
       if (n <= 0){
           printf("Error,try again\n");
       }
       } while(n <= 0);
       mtrx = new_matrix(n);
       mtrx->n = n;
       Line *ptr = mtrx->fcol_p;
       for (i = 0;i < n;i++){
            printf("Line number %d\n",i + 1);
            do{
            printf("Please, enter number of columns: \n");
            v = get_int(&m);
            if (!v) {
                delete_matrix(mtrx);
                return NULL;
            }
            if (m <= 0){
                printf("Error,try again\n");
            }
            } while (m <= 0);
            (ptr + i)->line_p = new_line(m);
            (ptr + i)->m = m;
            v = input(ptr + i);
            if (!v) {
                delete_matrix(mtrx);
                return NULL;
            }
       }
       /*for (i = 0;i < n;i++){
            printf("Line number %d:\n",i + 1);
            v = input(ptr + i);
            if (!v){
                delete_matrix(mtrx);
                return NULL;
            }
       }*/
       return mtrx;
}

int is_equal(double x, double y){
    double eps = 3E-308;
    return (fabs(x - y) < eps) ? 1:0;
}

int count_diff(Line *L){
    int v,i,j,m = L->m,k = 0;
    double *ptr = L->line_p;
    double x,y;
    int *aptr = (int*) calloc(m,sizeof(int));
    for (i = 0;i < m;i++){
         for (j = i + 1;j < m;j++){
             if (*(aptr + j) != 1) {
                 x = *(ptr + i);
                 y = *(ptr + j);
                 v = is_equal(x, y);
                 if (v) {
                     *(aptr + j) = 1;
                     k++;
                 }
             }
         }
    }
    /*if((m - k) == 1){
        free(aptr);
       return 0;
    }*/
    free(aptr);
    return m - k;
}

void print_matrix(Matrix *mtrx){
     int i,n = mtrx->n,m,j;
     double *lptr = NULL;
     Line *ptr = mtrx->fcol_p;
     for (i = 0;i < n;i++){
          m = (ptr + i)->m;
          lptr = (ptr + i)->line_p;
          for (j = 0;j < m;j++){
              printf("%lf ",*(lptr + j));
         }
         printf("\n");
     }
}

int *get_result(Matrix* S,int *size) {
    int N,i;
    N = S->n;
    Line* ptr = S->fcol_p;
    int* V = (int*)calloc(N, sizeof(int));
    *size = N;
    for (i = 0; i < N; i++) {
        *(V + i) = count_diff(ptr + i);
    }
    return V;
}
void print_vector(int* V, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\n", V[i]);
    }
}

