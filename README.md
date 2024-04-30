# Intro

The Raspberry Pi Pico offers 2MB of flash memory, some of which is used for program execution. This project aims to create an API that ensures safe access to this non-volatile storage, protecting against the possible corruption of essential data. The benefit of such an API is based on its ability to keep data between program sessions, as compared to volatile RAM, which clears stack and heap variables upon program termination. Data stored in flash memory is persistent until actively rewritten, allowing for continuous and pristine functioning across sessions.

# How to use

First, clone the repository locally with the following command:

```bash
$ git clone https://gitlab.uwe.ac.uk/y2-abuhummos/cap-1
$ cd cap-1
```

next a build, run and view output scripts are provided, to build:

```bash
$ ./build.sh
```

to run, first make sure to unplug the pi, and plug it again with the reset button pressed then:

```bash
$ ./run.sh
```

otherwise you can drag and drop the file into the pi.

and finally to view output:

```bash
$ ./out.sh
```

# Architecture

Given C's weak type safety and the fact that the writing function works with character pointers that are each byte in size, a decision was made to improve the process. Rather than just writing raw data to flash memory, a structured approach is used. This structured data contains metadata like length, the number of write operations, and a magic number. This strategy ensures data integrity across sessions, thereby increasing the system's robustness.

## `flash_data` struct and Its Operations

In managing flash memory, each sector, with a size of 4096 bytes, accommodates the `flash_data` struct. To allocate space for metadata within this struct, a portion of the sector is reserved, as depicted:

```c
#define DATA_SIZE FLASH_SECTOR_SIZE - (sizeof(uint32_t) * 3)
```

The remaining bytes are dedicated to storing the actual data.

The inclusion of a magic number ensures sector validity. An incorrect magic number prompts an initialization operation, writing empty data to the flash.

The count of write operations is logged, enabling wear monitoring to mitigate flash damage resulting from continuous writing.

# Implementation and Design Decisions

## Reading a Sector

Reading is the most straightforward operation of the three. It begins by calculating the starting byte of the required sector, ensuring it falls within safe bounds. Subsequently, the entire sector is read into the struct.

## Writing to a Sector

Initially, a write operation entails reading the sector into a temporary struct to safeguard against overwriting the write count inadvertently. The write count is then incremented, and the updated struct with its new data is written back to memory.

## Erasing a Sector

Erase operations resemble writing in terms of reading the sector and maintaining the write count's consistency. The sole distinction lies in writing an empty string upon subsequent writes.

# Limitations

The overhead of these functions is notable due to the necessity of reading and rewriting the entire sector to preserve metadata. However, this approach eliminates the need for bound checking within the sector itself, confining it solely to flash bounds.

# CLI

The app provides a command line interface to interact with the system, offering all commands, bellow is the set of commands:

| Command | Arguments             |
| ------- | --------------------- |
| write   | \<sector\> \<string\> |
| read    | \<sector\> \<size\>   |
| erase   | \<sector\>            |
| test    | -                     |
| exit    | -                     |

## Tests

A dedicated set of unit tests has been written to ensure the functionality of the commands. You can run these tests using the following methods:

1. **CLI Command:** Execute the test command through the CLI.

   ```bash
   Enter command: test
   ```

2. **Function Call:** Alternatively, you can directly call the `run_tests()` function.

   ```c
   run_tests()
   ```
