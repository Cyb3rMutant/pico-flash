#include "cli.h"
#include "custom_fgets.h"
#include "flash_data.h"
#include "flash_ops.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write();
void read();
void erase();
flash_data fd;

// Function: execute_command
// Parses and executes commands related to flash memory operations.
//
// Parameters:
// - command: A string containing the command and its arguments.
//
// The function supports the following commands:
// - WRITE: Writes data to flash memory.
// - READ: Reads data from flash memory.
// - ERASE: Erases a sector of flash memory.
//
// Each command expects specific arguments following the command name.
int execute_command(char *command) {
    // Split the command string into tokens
    char *token = strtok(command, " ");

    // Check for an empty or invalid command
    if (token == NULL) {
        printf("\nInvalid command\n");
        return;
    }

    // Handle the WRITE command
    if (strcmp(token, "write") == 0) {
        write();
    }
    // Handle the READ command
    else if (strcmp(token, "read") == 0) {
        read();
    }
    // Handle the ERASE command
    else if (strcmp(token, "erase") == 0) {
        erase();
    } else if (strcmp(token, "test") == 0) {
        run_tests();
    } else if (strcmp(token, "exit") == 0) {
        return 1;
    }
    // Handle unknown commands
    else {
        printf("\nUnknown command\n");
    }
    return 0;
}

void write() {
    // Parse the address
    char *token = strtok(NULL, " ");
    if (token == NULL) {
        printf("\nWRITE requires an address and data\n");
        return;
    }
    uint32_t address = atoi(token);

    // Parse the data, assuming it's enclosed in quotes
    token = strtok(NULL, "\"");
    if (token == NULL) {
        printf("\nInvalid data format for WRITE\n");
        return;
    }
    init_flash_data(&fd, token);

    // Execute the write operation
    flash_write_safe(address, &fd);
}

void read() {
    // Parse the address
    char *token = strtok(NULL, " ");
    if (token == NULL) {
        printf("\nWRITE requires an address and data\n");
        return;
    }
    uint32_t address = atoi(token);

    // Parse the length of data to read
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("\nInvalid length for READ\n");
        return;
    }
    // Prepare the buffer and execute the read operation
    flash_read_safe(address, &fd);

    // Output the read data
    print(&fd, atoi(token));
}

void erase() {
    // Parse the address
    char *token = strtok(NULL, " ");
    if (token == NULL) {
        printf("\nWRITE requires an address and data\n");
        return;
    }
    uint32_t address = atoi(token);

    // Execute the erase operation
    flash_erase_safe(address, &fd);
}
