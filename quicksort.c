#include <stdio.h>
#include <stdbool.h>

char array[] = {
    'q','w','e','r','t','y','u','i','o','p','7','3',
    'a','s','d','f','g','h','j','k','l','5','1','9',
    'z','x','c','v','b','n','m','4','2','8','6'
};

#define LENGTH sizeof(array) / sizeof(*array)
#define ANSI 1

void print_array(int lo, int hi, int p)
{
    for (int i = 0; i < LENGTH; i++){
        if (i == lo && ANSI)
            printf("\x1b[1;31m");

        if (i == p && ANSI) 
            printf("\x1b[1;32m%c\x1b[31m", array[i]);
        else 
            printf("%c", array[i]);

        if (i == hi && ANSI)
            printf("\x1b[0m");
    }
    if (lo >= 0 && p >= lo && hi >= p)
        printf(" [lo: %2d, hi: %2d, pivot: %2d]\n", lo, hi, p);
    else
        printf("\n");
}

bool is_sorted(char *n, int lo, int hi)
{
    bool sorted = true;

    for (int i = lo; i < hi; i++) {
        if (n[i] > n[i + 1]) {
            sorted = false;
            break;
        }
    }

    return sorted;
}

int partition(char *n, int lo, int hi)
{
    char pivot = n[hi];
    int tmp;
    int i = lo;

    for (int j = lo; j < hi; j++) {
        if (n[j] < pivot) {
            tmp = n[i]; 
            n[i] = n[j]; 
            n[j] = tmp;
            i++; 
        }
    }
    tmp = n[i]; 
    n[i] = n[hi]; 
    n[hi] = tmp;

    return i;
}

void quicksort(char *n, int lo, int hi)
{
    if (lo < hi && !is_sorted(n, lo, hi)) {
        int p = partition(n, lo, hi);
        print_array(lo, hi, p);
        quicksort(n, lo, p - 1);
        quicksort(n, p + 1, hi);
    }
}

int main()
{
    printf("quicksort demonstration\n\n");
    printf("01234567891123456789212345678931234\n");
    print_array(-1, -1, -1);
    quicksort(array, 0, LENGTH - 1);
    
    return 0;
}
