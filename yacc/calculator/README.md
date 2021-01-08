To build calc:

    lex lexer.l
    yacc -d parser.y
    gcc y.tab.c lex.yy.c

relay calc to tcp listening socket:

    socat TCP-LISTEN:1234,fork exec:./calc,pty,echo=0,stderr

Connect to socket using netcat:

    nc -N localhost 1234

Connect to socket user socat:

    socat - TCP:localhost:1234

Connect to socket using telnet:

    telnet localhost 1234
