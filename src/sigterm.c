#include "../hdr/sigterm.h"

void term(__attribute__((unused)) int signum)
{
    printf("Closing program...\n");
    done = 1;
}

void SIGTERM_init(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
}
