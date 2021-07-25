#include <stdio.h>
#include <stdint.h>

#define is_signed(n) (((n)-1) < 0)
#define dbg_signed(n, w) printf("%s = %lld (%zu-bit)\n", #n, (unsigned long long)n, w)
#define dbg_unsigned(n, w) printf("%s = %llu (%zu-bit)\n", #n, (unsigned long long)n, w)
#define dbg_(n, w) (is_signed(n) ? dbg_signed(n, w) : dbg_unsigned(n, w))
#define dbg(n) dbg_(n, 8 * sizeof(n))

int main()
{
    dbg((int8_t)-1);
    dbg((int16_t)-1);
    dbg((int32_t)-1);
    dbg((int64_t)-1);
    dbg((uint8_t)-1);
    dbg((uint16_t)-1);
    dbg((uint32_t)-1);
    dbg((uint64_t)-1);

    return 0;
}
