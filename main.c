#include "cli.h"
#include "custom_fgets.h"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    char command[256];

    // Wait for USB connection
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // Command loop
    while (1) {
        printf("\nEnter command: ");
        custom_fgets(command, sizeof(command), stdin);
        if (execute_command(command))
            break;
    }

    return 0;
}
