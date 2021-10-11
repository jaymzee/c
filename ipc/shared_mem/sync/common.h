#define MAX_BUFFERS 10

#define SEM_MUTEX_NAME "example.mutex"
#define SEM_BUFFER_COUNT_NAME "example.buffer-count"
#define SEM_SPOOL_SIGNAL_NAME "example.spool-signal"
#define SHARED_MEM_NAME "shm.example.shared-memory"

struct shared_memory {
    char buf[MAX_BUFFERS][256];
    int buffer_index;
    int buffer_print_index;
};
