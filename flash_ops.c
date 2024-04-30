#include "flash_ops.h"      // Include the flash operations header
#include "flash_data.h"     // Include the flash data header
#include "hardware/flash.h" // Include hardware-specific flash operations
#include "hardware/sync.h"  // Include synchronization functions
#include "pico/stdlib.h"    // Include standard library for Pico
#include <stdio.h>          // Standard input/output operations

#define FLASH_TARGET_OFFSET                                                    \
    (256 * 1024) // Offset where user data starts (256KB into flash)
#define FLASH_SIZE PICO_FLASH_SIZE_BYTES // Total flash size available

/**
 * @brief Writes flash data safely to the specified offset.
 *
 * @param offset Offset in flash memory where data should be written.
 * @param fd Pointer to flash_data structure containing data to be written.
 *
 * @return void
 *
 * @note This function writes flash data pointed to by 'fd' to the specified
 * 'offset' in flash memory. It ensures that the write operation is safe and
 * does not exceed flash memory bounds. It also handles write count increment
 * and performs flash sector erase and write operations.
 */
void flash_write_safe(uint32_t offset, flash_data *fd) {
    // Calculate the flash address where data will be written
    uint32_t flash_address = FLASH_TARGET_OFFSET + (FLASH_SECTOR_SIZE * offset);
    // Check if writing exceeds flash memory bounds
    if (FLASH_SIZE <= flash_address + FLASH_SECTOR_SIZE) {
        printf("Out of bounds\n");
        return;
    }

    // Read existing flash data at the specified offset
    flash_data temp_fd;
    flash_read_safe(offset, &temp_fd);
    // If it's not the first write, update write count
    if (!first_write(&temp_fd)) {
        fd->write_count = temp_fd.write_count;
    }
    // Increment write count
    fd->write_count++;
    // Save interrupts state and disable interrupts
    uint32_t ints = save_and_disable_interrupts();
    // Erase flash sector
    flash_range_erase(flash_address, FLASH_SECTOR_SIZE);
    // write flash data to the specified address
    flash_range_program(flash_address, fd, FLASH_SECTOR_SIZE);
    // Restore interrupts
    restore_interrupts(ints);
}

/**
 * @brief Reads flash data safely from the specified offset.
 *
 * @param offset Offset in flash memory from where data should be read.
 * @param fd Pointer to flash_data structure where read data should be stored.
 *
 * @return void
 *
 * @note This function reads flash data from the specified 'offset' in flash
 * memory and stores it in the flash_data structure pointed to by 'fd'. It
 * ensures that the read operation is safe and does not exceed flash memory
 * bounds.
 */
void flash_read_safe(uint32_t offset, flash_data *fd) {
    // Calculate the flash address from where data will be read
    uint32_t flash_address = FLASH_TARGET_OFFSET + (FLASH_SECTOR_SIZE * offset);
    // Check if reading exceeds flash memory bounds
    if (FLASH_SIZE <= flash_address + FLASH_SECTOR_SIZE) {
        printf("Out of bounds\n");
        return;
    }
    // Copy flash data from flash memory to the specified structure
    memcpy(fd, (flash_data *)(XIP_BASE + flash_address), FLASH_SECTOR_SIZE);
}

/**
 * @brief Erases flash data safely at the specified offset.
 *
 * @param offset Offset in flash memory where data should be erased.
 * @param fd Pointer to flash_data structure to be reset after erasure.
 *
 * @return void
 *
 * @note This function erases flash data at the specified 'offset' in flash
 * memory. It ensures that the erasure operation is safe and does not exceed
 * flash memory bounds. After erasure, it resets the flash_data structure
 * pointed to by 'fd' and writes it back to flash memory.
 */
void flash_erase_safe(uint32_t offset, flash_data *fd) {
    // Calculate the flash address where data will be erased
    uint32_t flash_address = FLASH_TARGET_OFFSET + (FLASH_SECTOR_SIZE * offset);
    // Check if erasing exceeds flash memory bounds
    if (FLASH_SIZE <= flash_address + FLASH_SECTOR_SIZE) {
        printf("Out of bounds\n");
        return;
    }
    // Read existing flash data at the specified offset
    flash_read_safe(offset, fd);
    // Save interrupts state and disable interrupts
    uint32_t ints = save_and_disable_interrupts();
    // Erase flash sector
    flash_range_erase(flash_address, FLASH_SECTOR_SIZE);
    // Restore interrupts
    restore_interrupts(ints);
    // If it's the first write, initialize flash data with an empty string, else
    // reset it
    if (first_write(fd)) {
        init_flash_data(fd, "");
    } else {
        reset_data(fd);
    }
    // Write the reset flash data back to flash memory
    flash_write_safe(offset, fd);
}
