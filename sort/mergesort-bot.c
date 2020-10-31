/************************************************
* merge sort bottom-up implementation           *
* best case time complexity: O(nlogn)           *
* worst case time complexity: O(nlogn)          *
* stability: stable                             *
* preferred for linked lists                    *
*************************************************/

#include <stdio.h>

void
PrintArray(const char *name, int x[], int n)
{
    printf("%s = [", name);
    for(int i = 0; i < n; i++)
        printf(" %d", x[i]);
    printf(" ]\n");
}

static int
min(int x, int y)
{
    if (x > y)
        return y;
    else
        return x;
}

static void
CopyArray(int dst[], const int src[], int n)
{
    for(int i = 0; i < n; i++)
        dst[i] = src[i];
}

//  Left run is a[ left:right-1]
// Right run is a[right:end-1  ]
static void
BottomUpMerge(const int a[], int b[], int left, int right, int end)
{
    int i = left, j = right;
    // While there are elements in the left or right runs...
    for (int k = left; k < end; k++) {
        // If left run head exists and is <= existing right run head
        if (i < right && (j >= end || a[i] <= a[j]))
            b[k] = a[i++];
        else
            b[k] = a[j++];
    }
}

// a[] has the items to sort; b[] is a work array
void
BottomUpMergeSort(int a[], int b[], int n)
{
    // Each 1-element run in a is already "sorted"
    // Make successively longer sorted runs of length 2, 4, 8, 16...
    // until whole array is sorted.
    for (int w = 1; w < n; w *= 2)
    {
        // Array a is full of runs of length width.
        for (int i = 0; i < n; i += 2 * w)
        {
            // Merge two runs: a[i:i + w-1] and a[i + w:i + 2*w - 1] to b[]
            // or copy a[i:n-1] to b[] ( if(i + w >= n) )
            BottomUpMerge(a, b, i, min(i + w, n), min(i + 2 * w, n));
        }

        // Now work array b is full of runs of length 2 * w
        // Copy array b to array a for next iteration
        // A more efficient implementation would swap the roles of a and b
        CopyArray(a, b, n);
        // Now array a is full of runs of length 2 * w
    }
}

int main()
{
    int x[8] = {5, 2, 3, 1, 8, 7, 4, 9};
    int t[8];

    BottomUpMergeSort(x, t, 8);
    PrintArray("x", x, 8);
}
