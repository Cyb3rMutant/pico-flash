#include "flash_data.h"
#include <stdio.h>
#include <string.h>

void init_flash_data(flash_data *fd, char *token) {
    memcpy(fd->data, token, strlen(token));
    fd->len = strlen(token);
    fd->write_count = 0;
    fd->magic_number = FLASH_MAGIC_NUMBER;
}

void fix_read(flash_data *fd) {
    printf("\n%d, %d, %d\n%x %x %x", fd->len, fd->write_count, fd->magic_number,
           fd->len, fd->write_count, fd->magic_number);
    fd->len &= 0x00FFFFFF;
    fd->write_count &= 0x00FFFFFF;
    fd->magic_number &= 0x00FFFFFF;
    printf("\n%d, %d, %d\n%x %x %x", fd->len, fd->write_count, fd->magic_number,
           fd->len, fd->write_count, fd->magic_number);
}

int first_write(flash_data *fd) {
    if (fd->magic_number != FLASH_MAGIC_NUMBER) {
        return 1;
    } else
        return 0;
}

void reset_data(flash_data *fd) {
    for (int i = 0; i < SECTOR_SIZE; i++) {
        fd->data[i] = 0;
    }
    fd->len = 0;
}
void print(flash_data *fd) {
    printf("\nData: %s, Data length: %d, Number of writes: %d\n", fd->data,
           fd->len, fd->write_count);
}