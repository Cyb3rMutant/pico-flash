#include "flash_data.h" // Include the flash data header

#include <stdio.h>  // Standard input/output operations
#include <string.h> // String manipulation functions

/**
 * @brief Initializes flash data structure with provided token.
 *
 * @param fd Pointer to flash_data structure to be initialized.
 * @param token Token string to be stored in flash data.
 *
 * @return void
 *
 * @note This function initializes the flash_data structure pointed to by 'fd'
 * with the provided 'token'. It sets the data length, write count, and magic
 * number to appropriate values.
 */
void init_flash_data(flash_data *fd, char *token) {
    // Initialize flash data with zeros
    memset(fd->data, 0, DATA_SIZE);
    // Copy token into flash data
    memcpy(fd->data, token, strlen(token));
    // Set data length to length of token
    fd->len = strlen(token);
    // Reset write count
    fd->write_count = 0;
    // Set magic number to indicate valid flash data
    fd->magic_number = FLASH_MAGIC_NUMBER;
}

/**
 * @brief Checks if it's the first write to flash.
 *
 * @param fd Pointer to flash_data structure.
 *
 * @return 1 if it's the first write, 0 otherwise.
 *
 * @note This function checks whether the magic number in the flash_data
 * structure pointed to by 'fd' matches the predefined FLASH_MAGIC_NUMBER. If
 * they match, it returns 0, indicating that it's not the first write.
 * Otherwise, it returns 1, indicating that it's the first write.
 */
int first_write(flash_data *fd) {
    // Check if magic number matches to verify if it's the first write
    if (fd->magic_number != FLASH_MAGIC_NUMBER) {
        return 1; // Indicates it's the first write
    } else {
        return 0; // Indicates it's not the first write
    }
}

/**
 * @brief Resets flash data by setting all elements to zero.
 *
 * @param fd Pointer to flash_data structure to be reset.
 *
 * @return void
 *
 * @note This function resets the flash_data structure pointed to by 'fd' by
 * setting all elements of the data array to zero and resetting the data length
 * to zero.
 */
void reset_data(flash_data *fd) {
    // Set all elements of data array to zero
    for (int i = 0; i < DATA_SIZE; i++) {
        fd->data[i] = 0;
    }
    // Reset data length
    fd->len = 0;
}

/**
 * @brief Prints flash data along with length and number of writes.
 *
 * @param fd Pointer to flash_data structure to be printed.
 * @param len Length up to which data should be printed.
 *
 * @return void
 *
 * @note This function prints the data stored in the flash_data structure
 * pointed to by 'fd' up to the specified 'len'. It also prints the data length
 * and the number of writes performed on the flash data.
 */
void print(flash_data *fd, int len) {
    char t = fd->data[len]; // Temporary variable to store data at given length
    fd->data[len] = '\0';   // Terminate string at given length for printing
    // Print flash data, length, and number of writes
    printf("\nData: %s, Data length: %d, Number of writes: %d\n", fd->data,
           fd->len, fd->write_count);
    fd->data[len] = t; // Restore data at given length
}
