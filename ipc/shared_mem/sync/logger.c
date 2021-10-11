/*
 *
 *       logger.c: Write strings in POSIX shared memory to file
 *                 (Server process)
 */

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"

#define LOGFILE "/tmp/example.log"

struct shared_memory *shm_ptr;
sem_t *mutex_sem, *buffer_count_sem, *spool_signal_sem;

void panic(char *msg);
void logger(int fd_log);

int main(int argc, char **argv)
{
    int fd_log, fd_shm;

    // Open log file
    fd_log = open(LOGFILE, O_CREAT | O_WRONLY | O_APPEND | O_SYNC, 0666);
    if (fd_log < 0) {
        panic(LOGFILE);
    }

    // mutual exclusion semaphore, mutex_sem with an initial value 0
    mutex_sem = sem_open(SEM_MUTEX_NAME, O_CREAT, 0660, 0);
    if (mutex_sem == SEM_FAILED) {
        panic(SEM_MUTEX_NAME);
    }

    // counting semaphore, indicating the number of available buffers.
    // initial value = MAX_BUFFERS
    buffer_count_sem = sem_open(SEM_BUFFER_COUNT_NAME,
                                O_CREAT | O_EXCL,
                                0660,
                                MAX_BUFFERS);
    if (buffer_count_sem == SEM_FAILED) {
        panic(SEM_BUFFER_COUNT_NAME);
    }

    // counting semaphore, indicating the number of strings to be printed.
    // initial value = 0
    spool_signal_sem = sem_open(SEM_SPOOL_SIGNAL_NAME,
                                O_CREAT | O_EXCL,
                                0660,
                                0);
    if (spool_signal_sem == SEM_FAILED) {
        panic(SEM_SPOOL_SIGNAL_NAME);
    }

    // Get shared memory
    fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR | O_CREAT | O_EXCL, 0660);
    if (fd_shm < 0) {
        panic(SHARED_MEM_NAME);
    }
    if (ftruncate(fd_shm, sizeof(struct shared_memory)) < 0) {
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
    // Initialize the shared memory
    shm_ptr->buf_index = shm_ptr->buf_print_index = 0;

    // Initialization complete

    logger(fd_log);
}

void logger(int fd_log)
{
    char mybuf[256];

    // we can set mutex semaphore as 1 to
    // indicate shared memory segment is available
    if (sem_post(mutex_sem) < 0) {
        panic("sem_post: mutex_sem");
    }

    while (1) {  // forever
        // Is there a string to print? P(spool_signal_sem);
        if (sem_wait(spool_signal_sem) < 0) {
            panic("sem_wait: spool_signal_sem");
        }

        strcpy(mybuf, shm_ptr->buf[shm_ptr->buf_print_index]);

        /* Since there is only one process (the logger) using the
           buffer_print_index, mutex semaphore is not necessary */
        (shm_ptr->buf_print_index)++;
        if (shm_ptr->buf_print_index == MAX_BUFFERS) {
            shm_ptr->buf_print_index = 0;
        }

        /* Contents of one buffer has been printed.
           One more buffer is available for use by producers.
           Release buffer: V(buffer_count_sem);  */
        if (sem_post(buffer_count_sem) < 0) {
            panic("sem_post: buffer_count_sem");
        }

        // write the string to file
        if (write(fd_log, mybuf, strlen(mybuf)) != strlen(mybuf)) {
            panic("write: logfile");
        }
    }
}

// Print system error and exit
void panic(char *msg)
{
    perror(msg);
    exit(1);
}
