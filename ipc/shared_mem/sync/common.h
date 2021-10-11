#define MAX_BUFFERS 10

#define SEM_MUTEX_NAME "logger.mutex"
#define SEM_BUFFER_COUNT_NAME "logger.buffer-count"
#define SEM_SPOOL_SIGNAL_NAME "logger.spool-signal"
#define SHARED_MEM_NAME "shm.logger.shared-memory"

struct shared_memory {
    char buf[MAX_BUFFERS][256];
    int buf_index;
    int buf_print_index;
};
