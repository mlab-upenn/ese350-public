#include "uart.h"
#include <stdio.h>

void smash_stack() {
    char first_var;
    char * p = &first_var;
    *(p+5) += 7;
    return;
}

void how_did_i_get_here() {
    printf("How did I get here?\n");
}

void main(void) {
    uart_init();
    int a = 3;
    smash_stack();
    while (a == 3);
    how_did_i_get_here();
    for (;;);
}
