/*
 *
 *       client.c: Write strings for printing in POSIX shared memory object
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include "common.h"

struct shared_memory *shm_ptr;
sem_t *mutex_sem, *buffer_count_sem, *spool_signal_sem;

void panic(char *msg);
void client(void);
char *strip_newline(char *s);

int main(int argc, char **argv)
{
    int fd_shm;

    //  mutual exclusion semaphore, mutex_sem
    mutex_sem = sem_open(SEM_MUTEX_NAME, 0, 0, 0);
    if (mutex_sem == SEM_FAILED) {
        panic(SEM_MUTEX_NAME);
    }

    // Get shared memory
    fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR, 0);
    if (fd_shm < 0) {
        panic(SHARED_MEM_NAME);
    }
    shm_ptr = mmap(NULL,
                   sizeof(struct shared_memory),
                   PROT_READ | PROT_WRITE,
                   MAP_SHARED,
                   fd_shm,
                   0);
    if (shm_ptr == MAP_FAILED) {
        panic(SHARED_MEM_NAME);
    }

    // counting semaphore, indicating the number of available buffers.
    buffer_count_sem = sem_open(SEM_BUFFER_COUNT_NAME, 0, 0, 0);
    if (buffer_count_sem == SEM_FAILED) {
        panic(SEM_BUFFER_COUNT_NAME);
    }

    // counting semaphore, indicating the number of strings to be printed.
    // initial value = 0
    spool_signal_sem = sem_open(SEM_SPOOL_SIGNAL_NAME, 0, 0, 0);
    if (spool_signal_sem == SEM_FAILED) {
        panic(SEM_SPOOL_SIGNAL_NAME);
    }

    client();

    if (munmap(shm_ptr, sizeof(struct shared_memory)) < 0) {
        panic("munmap");
    }
}

void client(void)
{
    char msg[200];

    printf("Please type a message: ");

    while (fgets(msg, 198, stdin)) {
        strip_newline(msg);

        // get a buffer: P(buffer_count_sem);
        if (sem_wait(buffer_count_sem) < 0) {
            panic("sem_wait: buffer_count_sem");
        }

        /* There might be multiple producers. We must ensure that
            only one producer uses buffer_index at a time.  */
        // P(mutex_sem);
        if (sem_wait(mutex_sem) < 0) {
            panic("sem_wait: mutex_sem");
        }

        // Critical section
        {
            time_t now = time(NULL);
            char *now_s = strip_newline(ctime(&now));
            sprintf(shm_ptr->buf[shm_ptr->buffer_index], "%d: %s %s\n",
                    getpid(), now_s, msg);
            (shm_ptr->buffer_index)++;
            if (shm_ptr->buffer_index == MAX_BUFFERS) {
                shm_ptr->buffer_index = 0;
            }
        }

        // Release mutex sem: V(mutex_sem)
        if (sem_post(mutex_sem) < 0) {
            panic("sem_post: mutex_sem");
        }

        // Tell spooler that there is a string to print: V (spool_signal_sem);
        if (sem_post(spool_signal_sem) < 0) {
            panic("sem_post: spool_signal_sem");
        }

        printf("Please type a message: ");
    }
}

char *strip_newline(char *s)
{
    int len = strlen(s);
    if (s[len - 1] == '\n') {
       s[len - 1] = '\0';
    }
    return s;
}

// Print system error and exit
void panic(char *msg)
{
    perror(msg);
    exit(1);
}
