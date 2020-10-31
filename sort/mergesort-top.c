/************************************************
* merge sort top-down implementation            *
* best case time complexity: O(nlogn)           *
* worst case time complexity: O(nlogn)          *
* stability: stable                             *
* preferred for linked lists                    *
*************************************************/

#include <stdio.h>

void
PrintArray(const char *name, const int x[], int n)
{
    printf("%s = [", name);
    for (int i = 0; i < n; i++)
        printf(" %d", x[i]);
    printf(" ]\n");
}

static void
CopyArray(int dst[], const int src[], int end)
{
    for(int n = 0; n < end; n++)
        dst[n] = src[n];
}

//  Left source half is a[beg:mid-1]
// Right source half is a[mid:end-1]
//            Result is b[beg:end-1]
static void
TopDownMerge(const int a[], int b[], int beg, int mid, int end)
{
    int i = beg, j = mid;

    // While there are elements in the left or right runs...
    for (int k = beg; k < end; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < mid && (j >= end || a[i] <= a[j]))
            b[k] = a[i++];
        else
            b[k] = a[j++];
    }
}

// Sort the given run of array a[] using array b[] as a source.
// beg is inclusive; end is exclusive (a[end] is not in the set).
static void
TopDownSplitMerge(int b[], int a[], int beg, int end)
{
    if(end - beg <= 1)                  // if run size == 1
        return;                         //   consider it sorted
    // split the run longer than 1 item into halves
    int mid = (end + beg) / 2;          // mid = mid point
    // recursively sort both runs from array a[] into b[]
    TopDownSplitMerge(a, b, beg, mid);  // sort the left  run
    TopDownSplitMerge(a, b, mid, end);  // sort the right run
    // merge the resulting runs from array b[] into a[]
    TopDownMerge(b, a, beg, mid, end);
}

// a[] has the items to sort; b[] is a work array.
void
TopDownMergeSort(int a[], int b[], int n)
{
    CopyArray(b, a, n);             // copy a[] to b[]
    TopDownSplitMerge(b, a, 0, n);  // sort data from b[] into a[]
}

int
main()
{
    int x[8] = {5, 2, 3, 1, 8, 7, 4, 9};
    int t[8];

    TopDownMergeSort(x, t, 8);

    PrintArray("x", x, 8);
}
