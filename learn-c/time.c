#include <stdio.h>
#include <time.h>

int main()
{
    time_t now = time(NULL);
    fputs(ctime(&now), stdout);
}
