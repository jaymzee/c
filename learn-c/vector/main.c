#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecint.h"

char str[] = "1,2,3,4,5,6,7,8,9";

int main()
{
    struct vecint nums;
    vecint_make(&nums, 0, 4);

    for (char *s = strtok(str, ","); s != NULL; s = strtok(NULL, ",")) {
        vecint_push(&nums, atoi(s));
    }

    vecint_print("nums", &nums);

    free(nums.data);

    return 0;
}
