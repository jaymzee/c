#include <stdio.h>

#define SO "\x0E" //G1
#define SI "\x0F" //G0
#define NONE ""

void printchars(int first,
                int last,
                const char *prefix,
                const char *postfix,
                const char *heading)
{
    printf("   %s\n", heading);
    printf("   0123456789ABCDEF\n");
    for (int ch = first; ch <= last; ch++) {
        if (ch % 16 == 0)
            printf("%02X %s", ch, prefix);

        if (ch == 0 || ch==8 || ch == 0x0A ||
            (ch >= 0x0C && ch <= 0x0F) ||
            ch==0x1B || ch==0x1C) {
            putchar(' ');
        } else {
            putchar(ch);
        }

        if (ch % 16 == 15)
            printf("%s\n", postfix);
    }
    printf("\n");
}

int main()
{
    //initially G0 and G1 point to tables a and b respectively

    //G0 character set
    //  doesn't seem to have an effect in console
    //  but in tmux the VT100 charset is selected
    printf("\e(0"); //G0 = VT100 graphics instead of lowercase
    printchars(0x20, 0x7F, NONE, NONE, "G0 b VT100 gfx");

    printf("\e(B"); //G0 = ISO 8859-1 (latin)
    printchars(0x20, 0x7F, NONE, NONE, "G0 a ISO 8859-1");

    //G1 character set (0x0E and 0x0F select G1 and G0 characters sets)
    printf("\e)U"); //G1 = null mapping (character ROM, 7F is ⌂, cp437?)
    printchars(0x00, 0x7F, SO, SI, "G1 c character ROM");

    printf("\e)K"); //G1 = user mapping (mapscrn, 7F is Ã)
    printchars(0x00, 0x7F, SO, SI, "G1 d user (mapscrn)");

    printf("\e)B"); //G1 = ISO 8859-1 (latin)
    printchars(0x20, 0x7F, SO, SI, "G1 a ISO 8859-1");

    printf("\e)0"); //G1 = VT100 graphics instead of lowercase
    printchars(0x20, 0x7F, SO, SI, "G1 b VT100 gfx");
    //left off with G1 pointing to table b and G0 pointing to table a

    return 0;
}
