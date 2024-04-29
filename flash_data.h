#ifndef FLASH_DATA_H
#define FLASH_DATA_H
#include "hardware/flash.h"
#include "pico/stdlib.h"

#define FLASH_MAGIC_NUMBER 434150
#define DATA_SIZE FLASH_SECTOR_SIZE - (sizeof(uint32_t) * 3)

typedef struct {
    uint8_t data[DATA_SIZE];
    uint32_t len;
    uint32_t write_count;
    uint32_t magic_number;
} flash_data;

void init_flash_data(flash_data *fd, char *token);
int first_write(flash_data *fd);
void reset_data(flash_data *fd);
void print(flash_data *fd, int len);

#endif