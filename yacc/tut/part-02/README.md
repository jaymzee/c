To build:

    lex calc.l
    yacc -d calc.y
    gcc y.tab.c lex.yy.c


Listen on tcp socket:

    socat TCP-LISTEN:1234,fork exec:./calc,pty,echo=0,stderr

