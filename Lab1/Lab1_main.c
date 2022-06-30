#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myfunc13.h"
int main() {
    int N,size;
    Matrix* S = create_matrix();
    if (!S) {
        printf("End of programm\n");
        return 0;
    }
    printf("Your matrix:\n");
    print_matrix(S);
    int* V = get_result(S,&size);
    printf("Vector :\n");
    print_vector(V,size);
    free(V);
    delete_matrix(S);
    return 0;
}
