#include "flash_data.h"
#include <stdio.h>
#include <string.h>

void init_flash_data(flash_data *fd, char *token) {
    memset(fd->data, 0, DATA_SIZE);
    memcpy(fd->data, token, strlen(token));
    fd->len = strlen(token);
    fd->write_count = 0;
    fd->magic_number = FLASH_MAGIC_NUMBER;
}

int first_write(flash_data *fd) {
    if (fd->magic_number != FLASH_MAGIC_NUMBER) {
        return 1;
    } else
        return 0;
}

void reset_data(flash_data *fd) {
    for (int i = 0; i < DATA_SIZE; i++) {
        fd->data[i] = 0;
    }
    fd->len = 0;
}

void print(flash_data *fd, int len) {
    char t = fd->data[len];
    fd->data[len] = '\0';
    printf("\nData: %s, Data length: %d, Number of writes: %d\n", fd->data,
           fd->len, fd->write_count);
    fd->data[len] = t;
}