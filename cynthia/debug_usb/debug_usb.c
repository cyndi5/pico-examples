#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    uint subs = 33;
    while (true) {
        printf("Cynthia: Hunter of Knowledge. Subscribers: %d\n", subs);
        sleep_ms(1000);
        subs++;
    }
    return 0;
}
