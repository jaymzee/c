struct vecint {
    int *data;
    int capacity;
    int size;       // number of elements
};

void vecint_push(struct vecint *nums, int num);
void vecint_make(struct vecint *nums, int size, int capacity);
void vecint_print(const char *name, struct vecint *nums);
