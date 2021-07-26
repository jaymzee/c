#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main(void) {
    // register hadndler for SIGINT (CTRL-C)
   signal(SIGINT, intHandler);

   while (keepRunning) {
       printf("working...\n");
       sleep(1);
   }

   // show that the signal was caught and handled
   printf("cleaning up");

   return 0;
}
