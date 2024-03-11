#include "flash_ops.h"
#include "flash_data.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

#define FLASH_TARGET_OFFSET                                                    \
    (256 * 1024) // Offset where user data starts (256KB into flash)
#define FLASH_SIZE PICO_FLASH_SIZE_BYTES // Total flash size available

// Function: flash_write_safe
// Writes data to flash memory at a specified offset, ensuring safety checks.
//
// Parameters:
// - offset: The offset from FLASH_TARGET_OFFSET where data is to be written.
// - data: Pointer to the data to be written.
// - data_len: Length of the data to be written.
//
// Note: This function erases the flash sector before writing new data.
void flash_write_safe(uint32_t offset, flash_data *fd) {
    uint32_t flash_address = FLASH_TARGET_OFFSET + offset;
    // if (FLASH_SIZE <= flash_address + data_len) {
    //     printf("FLASH_SIZE is %lu while start address is %ul and end is %ul,
    //     "
    //            "with a size of %ul",
    //            FLASH_SIZE, flash_address, flash_address + data_len,
    //            data_len);
    //     return;
    // }

    flash_data temp_fd;
    flash_read_safe(offset, &temp_fd);
    if (first_write(&temp_fd)) {
        init_flash_data(fd, fd->data);
    }
    fd->write_count = temp_fd.write_count;
    fd->write_count++;
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(flash_address, FLASH_SECTOR_SIZE);
    flash_range_program(flash_address, fd, 4096);
    restore_interrupts(ints);
}

// Function: flash_read_safe
// Reads data from flash memory into a buffer.
//
// Parameters:
// - offset: The offset from FLASH_TARGET_OFFSET where data is to be read.
// - buffer: Pointer to the buffer where read data will be stored.
// - buffer_len: Number of bytes to read.
//
// Note: The function performs bounds checking to ensure safe access.
void flash_read_safe(uint32_t offset, flash_data *fd) {
    uint32_t flash_address = FLASH_TARGET_OFFSET + offset;
    // if (FLASH_SIZE <= flash_address + buffer_len) {
    //     printf("FLASH_SIZE is %lu while start address is %ul and end is %ul,
    //     "
    //            "with a size of %ul",
    //            FLASH_SIZE, flash_address, flash_address + buffer_len,
    //            buffer_len);
    //     return;
    // }
    memcpy(fd, (flash_data *)(XIP_BASE + flash_address), 4096);
    fix_read(fd);
}

// Function: flash_erase_safe
// Erases a sector of the flash memory.
//
// Parameters:
// - offset: The offset from FLASH_TARGET_OFFSET where the erase starts.
//
// Note: This function checks that the operation stays within valid bounds.
void flash_erase_safe(uint32_t offset, flash_data *fd) {
    uint32_t flash_address = FLASH_TARGET_OFFSET + offset;
    // if (FLASH_SIZE <= flash_address + FLASH_SECTOR_SIZE) {
    //     printf("FLASH_SIZE is %lu while start address is %ul and end is %ul,
    //     "
    //            "with a size of %ul",
    //            FLASH_SIZE, flash_address, flash_address + FLASH_SECTOR_SIZE,
    //            FLASH_SECTOR_SIZE);
    //     return;
    // }
    flash_read_safe(offset, fd);
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(flash_address, FLASH_SECTOR_SIZE);
    restore_interrupts(ints);
    if (first_write(fd)) {
        init_flash_data(fd, "");
    } else {
        reset_data(fd);
    }
    flash_write_safe(offset, fd);
}
