#include "flash_data.h"
#include "flash_ops.h"

void run_tests(flash_data *fd) {
    test1(fd);
    test2(fd);
    test3(fd);
    test4(fd);
    test5(fd);
    test6(fd);
    test7(fd);
    test8(fd);
    test9(fd);
    test10(fd);
    test11(fd);
    test12(fd);
    // test13(fd);
    // test14(fd);
    // test15(fd);
    // test16(fd);
    // test17(fd);
    // test18(fd);
    // test19(fd);
    // test20(fd);
    // test21(fd);
    // test22(fd);
    // test23(fd);
    // test24(fd);
    // test25(fd);
    // test26(fd);
    // test27(fd);
    // test28(fd);
    // test29(fd);
    // test30(fd);
    // test31(fd);
    // test32(fd);
    // test33(fd);
    // test34(fd);
    // test35(fd);
    // test36(fd);
    // test37(fd);
}

void test1(flash_data *fd) {
    // Test 1: writing data to flash memory increments the write count
    printf("Test 1: writing data to flash memory increments the write count\n");
    flash_read_safe(0, fd);
    uint32_t write_count = fd->write_count;
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->write_count == write_count + 1) {
        printf("Test 1 passed\n");
    } else {
        printf("Test 1 failed\n");
    }
}

void test2(flash_data *fd) {
    // Test 2: reading data from flash memory does not increment the write count
    printf("Test 2: reading data from flash memory does not increment the "
           "write count\n");
    flash_read_safe(0, fd);
    uint32_t write_count = fd->write_count;
    flash_read_safe(0, fd);
    if (fd->write_count == write_count) {
        printf("Test 2 passed\n");
    } else {
        printf("Test 2 failed\n");
    }
}

void test3(flash_data *fd) {
    // Test 3: writing data to flash memory sets the length of the data
    // correctly
    printf("Test 3: writing data to flash memory sets the length of the data "
           "correctly\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->len == strlen(data)) {
        printf("Test 3 passed\n");
    } else {
        printf("Test 3 failed\n");
    }
}

void test4(flash_data *fd) {
    // Test 4: reading data from flash memory returns the correct data
    printf("Test 4: reading data from flash memory returns the correct data\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (strcmp(fd->data, data) == 0) {
        printf("Test 4 passed\n");
    } else {
        printf("Test 4 failed\n");
    }
}

void test5(flash_data *fd) {
    // Test 5: erasing a sector of flash memory clears the data
    printf("Test 5: erasing a sector of flash memory clears the data\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    flash_erase_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->len == 0) {
        printf("Test 5 passed\n");
    } else {
        printf("Test 5 failed\n");
    }
}

void test6(flash_data *fd) {
    // Test 6: erasing a sector of flash memory does not affect other sectors
    printf("Test 6: erasing a sector of flash memory does not affect other "
           "sectors\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    flash_write_safe(1, fd);
    flash_erase_safe(0, fd);
    flash_read_safe(1, fd);
    if (strcmp(fd->data, data) == 0) {
        printf("Test 6 passed\n");
    } else {
        printf("Test 6 failed\n");
    }
}

void test7(flash_data *fd) {
    // Test 7: overwriting data in flash memory does not overlap with the
    // previous data
    printf("Test 7: overwriting data in flash memory does not overlap with the "
           "previous data\n");
    char data1[] = "Hello, world!";
    char data2[] = "Goodbye, world!";
    init_flash_data(fd, data1);
    flash_write_safe(0, fd);
    init_flash_data(fd, data2);
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (strcmp(fd->data, data2) == 0) {
        printf("Test 7 passed\n");
    } else {
        printf("Test 7 failed\n");
    }
}

void test8(flash_data *fd) {
    // Test 8: reading data from an erased sector returns an empty string
    printf(
        "Test 8: reading data from an erased sector returns an empty string\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    flash_erase_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->len == 0) {
        printf("Test 8 passed\n");
    } else {
        printf("Test 8 failed\n");
    }
}

void test9(flash_data *fd) {
    // Test 9: writing data to a sector does not affect other sectors
    printf("Test 9: writing data to a sector does not affect other sectors\n");
    char data1[] = "Hello, world!";
    char data2[] = "Goodbye, world!";
    init_flash_data(fd, data1);
    flash_write_safe(0, fd);
    init_flash_data(fd, data2);
    flash_write_safe(1, fd);
    flash_read_safe(0, fd);
    if (strcmp(fd->data, data1) == 0) {
        printf("Test 9 passed\n");
    } else {
        printf("Test 9 failed\n");
    }
}

void test10(flash_data *fd) {
    // Test 10: writing empty data to a sector clears the data
    printf("Test 10: writing empty data to a sector clears the data\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    init_flash_data(fd, "");
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->len == 0) {
        printf("Test 10 passed\n");
    } else {
        printf("Test 10 failed\n");
    }
}

void test11(flash_data *fd) {
    // Test 11: writing data to a sector does not affect the write count of
    // other sectors
    printf(
        "Test 11: writing data to a sector does not affect the write count of "
        "other sectors\n");
    flash_read_safe(0, fd);
    uint32_t write_count = fd->write_count;
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(1, fd);
    flash_read_safe(0, fd);
    if (fd->write_count == write_count) {
        printf("Test 11 passed\n");
    } else {
        printf("Test 11 failed\n");
    }
}

void test12(flash_data *fd) {
    // Test 12: writing empty data to a sector sets the length to 0
    printf("Test 12: writing empty data to a sector sets the length to 0\n");
    char data[] = "Hello, world!";
    init_flash_data(fd, data);
    flash_write_safe(0, fd);
    init_flash_data(fd, "");
    flash_write_safe(0, fd);
    flash_read_safe(0, fd);
    if (fd->len == 0) {
        printf("Test 12 passed\n");
    } else {
        printf("Test 12 failed\n");
    }
}
