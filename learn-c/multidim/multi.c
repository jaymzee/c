/*
 * demonstrate how C multidimensional arrays are row-major
 */

#include <stdio.h>

#define ROWS 3
#define COLS 3

int A[ROWS][COLS];

void print_matrix(char *name, int x[ROWS][COLS]) {
    printf("%s = [\n", name);
    for (int i = 0; i < ROWS; i++) {
        printf("  ");
        for (int j = 0; j < COLS; j++) {
            printf("%d ", x[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

void print_vector(char *name, int x[], int length) {
    printf("%s = [ ", name);
    for (int *p = (int *)A, i = 0; i < length; i++) {
        printf("%d ", p[i]);
    }
    printf("]\n");
}

int main()
{
    for (int *p = (int *)A, i = 0; i < ROWS*COLS; i++)
        *p++ = i + 1;

    print_vector("A", (int *)A, ROWS*COLS);
    print_matrix("A", A);

    return 0;
}
