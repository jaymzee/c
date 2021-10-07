#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecint.h"

void vecint_push(struct vecint *nums, int num)
{
    if (nums->size >= nums->capacity) {
        // grow the array
        nums->capacity *= 2;
        int datasize = nums->capacity * sizeof(int);
        int *newdata = malloc(datasize);
        memcpy(newdata, nums->data, datasize);
        free(nums->data);
        nums->data = newdata;
    }
    nums->data[nums->size] = num;
    nums->size++;
}

void vecint_make(struct vecint *nums, int size, int capacity)
{
    capacity = size > capacity ? size : capacity;
    nums->data = calloc(capacity, sizeof(int));
    nums->capacity = capacity;
    nums->size = size;
}

void vecint_print(const char *name, struct vecint *nums)
{
    printf("%s (size=%d, cap=%d) = {\n", name, nums->size, nums->capacity);
    for (int i = 0; i < nums->size; i++) {
        printf("    %d,\n", nums->data[i]);
    }
    printf("}\n");
}
