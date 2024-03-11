#ifndef FLASH_OPS_H
#define FLASH_OPS_H

#include "flash_data.h"
#include <stddef.h>
#include <stdint.h>

void flash_write_safe(uint32_t offset, flash_data *fd);
void flash_read_safe(uint32_t offset, flash_data *fd);
void flash_erase_safe(uint32_t offset, flash_data *fd);

#endif // FLASH_OPS_H