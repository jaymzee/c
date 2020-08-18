#include <stdio.h>
#include <stdlib.h>

struct Student {
    char *name;
    int age;
};

void foo(struct Student *s)
{
    printf("%s\n", s->name);
    printf("%d\n", s->age);
}

int main()
{
    struct Student *s1;

    //s1 = malloc(sizeof(struct Student));
    s1 = calloc(1, sizeof(struct Student));

    s1->name = "George";
    s1->age = 5;

    foo(s1);

    free(s1);

    return 0;
}
