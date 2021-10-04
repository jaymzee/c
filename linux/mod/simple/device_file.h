#ifndef DEVICE_FILE_H_
#define DEVICE_FILE_H_
#include <linux/compiler.h> /* __must_check */

__must_check int register_device(void); /* 0 if Ok*/
void unregister_device(void);

static inline void cpuGetMSR(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
   __asm__ __volatile__("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

#endif //DEVICE_FILE_H_
