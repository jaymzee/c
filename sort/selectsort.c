/************************************************
* selection sort                                *
* best case performance: O(n2)                  *
* worst case performance: O(n2)                 *
* stability: not stable                         *
*************************************************/

#include <stdio.h>
#define ANSI 1

int numbers[] = {7, 2, 8, 4, 3, 6, 9, 1, 5};

void printarray(int *arr, int len, int first, int min)
{
    int last;
    if (first >= 0)
        last = len - 1;
    else
        last = -1;

    for (int i = 0; i < len; i++) {
        if (i == first && ANSI)
            printf("\033[1;31m");
        if (i == min && ANSI)
            printf("\033[1;32m%d\033[1;31m ", arr[i]);
        else
            printf("%d ", arr[i]);
        if (i == last && ANSI) {
            printf("\033[0m");
        }
    }

    printf("\n");
}

void selectsort(int *arr, int len)
{
    for (int i = 0; i < len; i++) {
        int min = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        printarray(arr, len, i + 1, min);
        if (min > i) {
            int tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
    printarray(arr, len, -1, -1);
}

int main()
{
    selectsort(numbers, sizeof(numbers) / sizeof(int));
    return 0;
}
