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
