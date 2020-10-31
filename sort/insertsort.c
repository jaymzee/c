/************************************************
* insertion sort                                *
* best case performance: O(n2)                  *
* worst case performance: O(n2)                 *
* stability: stable                             *
*************************************************/

#include <stdio.h>

#define ANSI 1

int numbers[] = {7, 2, 8, 4, 3, 6, 9, 1, 5};

void printarray(int arr[], int len, int pos, int rest)
{
    for (int i = 0; i < len; i++) {
        if (i == rest && ANSI)
            printf("\033[1;31m");
        if (i == pos && ANSI)
            printf("\033[1;32m%d\033[0m ", arr[i]);
        else
            printf("%d ", arr[i]);
    }
    if (ANSI)
        printf("\033[0m\n");
    else
        printf("\n");
}

void insertsort(int arr[], int len)
{
    int i, j;

    printarray(numbers, len, -1, -1);
    for (i = 1; i < len; i++) {
        for (j = i; j > 0 && arr[j-1] > arr[j]; j--) {
            int tmp = arr[j-1];
            arr[j-1] = arr[j];
            arr[j] = tmp;
        }
        printarray(numbers, len, j, i + 1);
    }
}

int main()
{
    insertsort(numbers, sizeof(numbers) / sizeof(*numbers));

    return 0;
}
