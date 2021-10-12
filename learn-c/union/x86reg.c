#include <stdio.h>
#include <stdint.h>

struct x86registers {
    union {
        struct {
            uint16_t ax;
            uint16_t bx;
            uint16_t cx;
            uint16_t dx;
        } x16;
        struct {
            uint8_t al;
            uint8_t ah;
            uint8_t bl;
            uint8_t bh;
            uint8_t cl;
            uint8_t ch;
            uint8_t dl;
            uint8_t dh;
        } x8;
    };
    uint16_t si;
    uint16_t di;
    uint16_t bp;
    uint16_t sp;
    uint16_t cs;
    uint16_t ds;
    uint16_t ss;
    uint16_t es;
    uint32_t ip;
    union {
        uint16_t flags;
        struct {
            uint16_t CF:1;
            uint16_t reserved1:1;
            uint16_t PF:1;
            uint16_t reserved3:1;
            uint16_t AF:1;
            uint16_t reserved5:1;
            uint16_t ZF:1;
            uint16_t SF:1;
            uint16_t TF:1;
            uint16_t IF:1;
            uint16_t DF:1;
            uint16_t OF:1;
            uint16_t IOPL:2;
            uint16_t NT:1;
            uint16_t reserved15:1;
        } flag;
    };
};

int main()
{
    struct x86registers r;

    r.x16.ax = 0xcafe;
    r.flag.CF = 1;
    r.flag.ZF = 1;

    printf("ah: %02x, al: %02x\n", r.x8.ah, r.x8.al);
    printf("ip: %08x\n", r.ip);
    printf("flags: 0x%02x, cf: %d, pf: %d, zf: %d, iopl: %d\n", r.flags, r.flag.CF, r.flag.PF, r.flag.ZF, r.flag.IOPL);

    return 0;
}
