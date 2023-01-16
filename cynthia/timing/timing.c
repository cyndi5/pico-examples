#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    uint subs = 33;

    sleep_ms(875);
    printf("seems to get lost\n");
    printf("seems to get lost as well\n");
    sleep_ms(1000);

    // printf("Hi 1.\n");
    // sleep_ms(1000);

    // printf("Hi 2.\n");
    // sleep_ms(1000);

    // printf("Hi 3.\n");
    // sleep_ms(1000);

    while (true) {
        printf("Cynthia: Hunter of Knowledge! Subscribers: %d\n", subs);
        sleep_ms(1000);
        subs++;
    }
    return 0;
}
