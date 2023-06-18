//
// Created by filip on 18.06.23.
//

#include "sigterm.h"

void term(int signal)
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
