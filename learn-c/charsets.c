/***********************************************************************
 * VT100 escape codes
 * https://espterm.github.io/docs/VT100%20escape%20codes.html

Name                  Description                            Esc Code

setnl LMN             Set new line mode                      ^[[20h
setappl DECCKM        Set cursor key to application          ^[[?1h
setansi DECANM        Set ANSI (versus VT52)                 none
setcol DECCOLM        Set number of columns to 132           ^[[?3h
setsmooth DECSCLM     Set smooth scrolling                   ^[[?4h
setrevscrn DECSCNM    Set reverse video on screen            ^[[?5h
setorgrel DECOM       Set origin to relative                 ^[[?6h
setwrap DECAWM        Set auto-wrap mode                     ^[[?7h
setrep DECARM         Set auto-repeat mode                   ^[[?8h
setinter DECINLM      Set interlacing mode                   ^[[?9h

setlf LMN             Set line feed mode                     ^[[20l
setcursor DECCKM      Set cursor key to cursor               ^[[?1l
setvt52 DECANM        Set VT52 (versus ANSI)                 ^[[?2l
resetcol DECCOLM      Set number of columns to 80            ^[[?3l
setjump DECSCLM       Set jump scrolling                     ^[[?4l
setnormscrn DECSCNM   Set normal video on screen             ^[[?5l
setorgabs DECOM       Set origin to absolute                 ^[[?6l
resetwrap DECAWM      Reset auto-wrap mode                   ^[[?7l
resetrep DECARM       Reset auto-repeat mode                 ^[[?8l
resetinter DECINLM    Reset interlacing mode                 ^[[?9l

altkeypad DECKPAM     Set alternate keypad mode              ^[=
numkeypad DECKPNM     Set numeric keypad mode                ^[>

setukg0               Set United Kingdom G0 character set    ^[(A
setukg1               Set United Kingdom G1 character set    ^[)A
setusg0               Set United States G0 character set     ^[(B
setusg1               Set United States G1 character set     ^[)B
setspecg0             Set G0 special chars. & line set       ^[(0
setspecg1             Set G1 special chars. & line set       ^[)0
setaltg0              Set G0 alternate character ROM         ^[(1
setaltg1              Set G1 alternate character ROM         ^[)1
setaltspecg0          Set G0 alt char ROM and spec. graphics ^[(2
setaltspecg1          Set G1 alt char ROM and spec. graphics ^[)2

setss2 SS2            Set single shift 2                     ^[N
setss3 SS3            Set single shift 3                     ^[O

modesoff SGR0         Turn off character attributes          ^[[m
modesoff SGR0         Turn off character attributes          ^[[0m
bold SGR1             Turn bold mode on                      ^[[1m
lowint SGR2           Turn low intensity mode on             ^[[2m
underline SGR4        Turn underline mode on                 ^[[4m
blink SGR5            Turn blinking mode on                  ^[[5m
reverse SGR7          Turn reverse video on                  ^[[7m
invisible SGR8        Turn invisible text mode on            ^[[8m

setwin DECSTBM        Set top and bottom line#s of a window  ^[[<v>;<v>r

cursorup(n) CUU       Move cursor up n lines                 ^[[<n>A
cursordn(n) CUD       Move cursor down n lines               ^[[<n>B
cursorrt(n) CUF       Move cursor right n lines              ^[[<n>C
cursorlf(n) CUB       Move cursor left n lines               ^[[<n>D
cursorhome            Move cursor to upper left corner       ^[[H
cursorhome            Move cursor to upper left corner       ^[[;H
cursorpos(v,h) CUP    Move cursor to screen location v,h     ^[[<v>;<h>H
hvhome                Move cursor to upper left corner       ^[[f
hvhome                Move cursor to upper left corner       ^[[;f
hvpos(v,h) CUP        Move cursor to screen location v,h     ^[[<v>;<h>f
index IND             Move/scroll window up one line         ^[D
revindex RI           Move/scroll window down one line       ^[M
nextline NEL          Move to next line                      ^[E
savecursor DECSC      Save cursor position and attributes    ^[7
restorecursor DECSC   Restore cursor position and attributes ^[8

tabset HTS            Set a tab at the current column        ^[H
tabclr TBC            Clear a tab at the current column      ^[[g
tabclr TBC            Clear a tab at the current column      ^[[0g
tabclrall TBC         Clear all tabs                         ^[[3g

dhtop DECDHL          Double-height letters, top half        ^[#3
dhbot DECDHL          Double-height letters, bottom half     ^[#4
swsh DECSWL           Single width, single height letters    ^[#5
dwsh DECDWL           Double width, single height letters    ^[#6

cleareol EL0          Clear line from cursor right           ^[[K
cleareol EL0          Clear line from cursor right           ^[[0K
clearbol EL1          Clear line from cursor left            ^[[1K
clearline EL2         Clear entire line                      ^[[2K

cleareos ED0          Clear screen from cursor down          ^[[J
cleareos ED0          Clear screen from cursor down          ^[[0J
clearbos ED1          Clear screen from cursor up            ^[[1J
clearscreen ED2       Clear entire screen                    ^[[2J

devstat DSR           Device status report                   ^[5n
termok DSR               Response: terminal is OK            ^[0n
termnok DSR              Response: terminal is not OK        ^[3n

getcursor DSR         Get cursor position                    ^[6n
cursorpos CPR            Response: cursor is at v,h          ^[<v>;<h>R

ident DA              Identify what terminal type            ^[[c
ident DA              Identify what terminal type (another)  ^[[0c
gettype DA               Response: terminal type code n      ^[[?1;<n>0c

reset RIS             Reset terminal to initial state        ^[c

align DECALN          Screen alignment display               ^[#8
testpu DECTST         Confidence power up test               ^[[2;1y
testlb DECTST         Confidence loopback test               ^[[2;2y
testpurep DECTST      Repeat power up test                   ^[[2;9y
testlbrep DECTST      Repeat loopback test                   ^[[2;10y

ledsoff DECLL0        Turn off all four leds                 ^[[0q
led1 DECLL1           Turn on LED #1                         ^[[1q
led2 DECLL2           Turn on LED #2                         ^[[2q
led3 DECLL3           Turn on LED #3                         ^[[3q
led4 DECLL4           Turn on LED #4                         ^[[4q

#
#  All codes below are for use in VT52 compatibility mode.
#

setansi               Enter/exit ANSI mode (VT52)            ^[<

altkeypad             Enter alternate keypad mode            ^[=
numkeypad             Exit alternate keypad mode             ^[>

setgr                 Use special graphics character set     ^[F
resetgr               Use normal US/UK character set         ^[G

cursorup              Move cursor up one line                ^[A
cursordn              Move cursor down one line              ^[B
cursorrt              Move cursor right one char             ^[C
cursorlf              Move cursor left one char              ^[D
cursorhome            Move cursor to upper left corner       ^[H
cursorpos(v,h)        Move cursor to v,h location            ^[<v><h>
revindex              Generate a reverse line-feed           ^[I

cleareol              Erase to end of current line           ^[K
cleareos              Erase to end of screen                 ^[J

ident                 Identify what the terminal is          ^[Z
identresp             Correct response to ident              ^[/Z

<hr>

#
# VT100 Special Key Codes
#
# These are sent from the terminal back to the computer when the
# particular key is pressed.  Note that the numeric keypad keys
# send different codes in numeric mode than in alternate mode.
# See escape codes above to change keypad mode.
#

# Function Keys:

PF1     ^[OP
PF2     ^[OQ
PF3     ^[OR
PF4     ^[OS


# Arrow Keys:
        Reset    Set
        -----    ---
up      ^[A ^[OA
down        ^[B ^[OB
right       ^[C ^[OC
left        ^[D ^[OD


# Numeric Keypad Keys:

        Keypad Mode
        -----------------
Keypad Key  Numeric Alternate
----------  ------- ---------
0       0   ^[Op
1       1   ^[Oq
2       2   ^[Or
3       3   ^[Os
4       4   ^[Ot
5       5   ^[Ou
6       6   ^[Ov
7       7   ^[Ow
8       8   ^[Ox
9       9   ^[Oy
- (minus)   -   ^[Om
, (comma)   ,   ^[Ol
. (period)  .   ^[On
ENTER       ^M  ^[OM


***********************************************************************
* The console character sets
* http://web.mit.edu/linux/redhat/redhat-4.0.0/i386/doc/HTML/ldp/Keyboard-HOWTO-6.html
*

The kernel knows about 4 translations of bytes into console-screen symbols. The four tables are: a) Latin1 -> PC, b) VT100 graphics -> PC, c) PC -> PC, d) user-defined.

There are two character sets, called G0 and G1, and one of them is the current character set. (Initially G0.) Typing ˆN causes G1 to become current, ˆO causes G0 to become current.

These variables G0 and G1 point at a translation table, and can be changed by the user. Initially they point at tables a) and b), respectively. The sequences ESC ( B and ESC ( 0 and ESC ( U and ESC ( K cause G0 to point at translation table a), b), c) and d), respectively. The sequences ESC ) B and ESC ) 0 and ESC ) U and ESC ) K cause G1 to point at translation table a), b), c) and d), respectively.

The sequence ESC c causes a terminal reset, which is what you want if the screen is all garbled. The oft-advised echo ˆVˆO will only make G0 current, but there is no guarantee that G0 points at table a). In some distributions there is a program reset(1) that just does echo ˆ[c. If your termcap entry for the console is correct (and has an entry :rs=\Ec:), then also setterm -reset will work.

The user-defined mapping table can be set using mapscrn(8). The result of the mapping is that if a symbol c is printed, the symbol s = map[c] is sent to the video memory. The bitmap that corresponds to s is found in the character ROM, and can be changed using setfont(8).
***********************************************************************/


/*
 * Note 1)
 * only use special chars 60h, 61h, 66h, 67h, 6Ah-6Eh, 74h-7Eh
 *                        ◆    ▒    °    ±    ┘┐┌└┼⎺   ├┤┴┬│≤≥π≠£·
 * to maintain compatibility in terminal, console, and tmux (in console)
 */


#include <stdio.h>

// 0x0E and 0x0F select G1 and G0 characters sets
#define G1 "\x0E" //G1
#define G0 "\x0F" //G0
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

        // don't print ctrl chars
        if (ch == 0 || ch == 8 || ch == 0x0A ||
            (ch >= 0x0C && ch <= 0x0F) ||
            ch == 0x1B || ch == 0x1C) {
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

    // Set G0 to DEC Special Graphics characters
    // no effect in console
    // 0 is graphic in tmux
    printf("\e(0"); // setspecg0
    printchars(0x20, 0x7F, NONE, NONE, "G0 B VT100 GFX");

    // Set United States G0 character set
    printf("\e(B"); // setusg0
    printchars(0x20, 0x7F, NONE, NONE, "G0 a ISO-8859-1");

/*
    printf("\e(U");
    printchars(0x20, 0x7F, NONE, NONE, "G0 c character ROM");

    printf("\e(K");
    printchars(0x20, 0x7F, NONE, NONE, "G0 d user (mapscrn)");
*/

    // Set G1 to DEC Special Graphics characters
    // partially implemented in console (see Note 1)
    // partially implemented in tmux (see Note 1)
    printf("\e)0"); // setspecg1
    printchars(0x20, 0x7F, G1, G0, "G1 b VT100 gfx");

    // Set United States G1 character set
    printf("\e)B"); // setusg1
    printchars(0x20, 0x7F, G1, G0, "G1 a ISO-8859-1");

/*
    printf("\e)U"); // G1 = null mapping (character ROM, 7F is ⌂)
    printchars(0x00, 0x7F, G1, G0, "G1 c character ROM");

    printf("\e)K"); // G1 = user mapping (mapscrn, 7F is Ã)
    printchars(0x00, 0x7F, G1, G0, "G1 d user (mapscrn)");
*/

    //left off with G0 pointing to table a and G1 pointing to table b

    return 0;
}
