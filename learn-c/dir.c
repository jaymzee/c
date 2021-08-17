#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

void print_dir(void)
{
    char path[128];
    pid_t pid = getpid();
    sprintf(path, "/proc/%d/fd", pid);
    DIR *dr = opendir(path);
    struct dirent *de;

    if (dr) {
        while ((de = readdir(dr)) != NULL) {
            printf("%s\n", de->d_name);
        }
        closedir(dr);
    }
}

int main(int argc, char *argv[])
{
    print_dir();
}
