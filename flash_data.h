#ifndef FLASH_DATA_H
#define FLASH_DATA_H

#include "hardware/flash.h" // Include necessary headers for hardware flash operations
#include "pico/stdlib.h" // Include standard library for Pico

// Define the magic number used to identify valid flash data
#define FLASH_MAGIC_NUMBER 434150

// Calculate the data size for the flash data struct, considering the space
// occupied by metadata
#define DATA_SIZE FLASH_SECTOR_SIZE - (sizeof(uint32_t) * 3)

// Define the structure to hold flash data
typedef struct {
    uint8_t data[DATA_SIZE]; // Array to store actual data
    uint32_t len;            // Length of stored data
    uint32_t write_count;    // Number of times data has been written
    uint32_t magic_number;   // Magic number to validate flash data integrity
} flash_data;

// Function to initialize flash data with provided token
void init_flash_data(flash_data *fd, char *token);

// Function to check if it's the first write to flash
int first_write(flash_data *fd);

// Function to reset flash data
void reset_data(flash_data *fd);

// Function to print flash data
void print(flash_data *fd, int len);

#endif
