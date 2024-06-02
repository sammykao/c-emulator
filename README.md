# CPU Emulator

This repository contains a CPU emulator written in C and an accompanying assembly language program. The emulator simulates a simple CPU architecture and can execute programs written in the custom assembly language provided.

## Features

- Emulates a simple CPU with basic instruction set
- Supports arithmetic, logic, and control flow operations
- Includes a custom assembler to convert assembly code into machine code
- Detailed logging for debugging and understanding program flow

## Getting Started

### Prerequisites

- GCC (or any C compiler)
- Make (optional, for build automation)

### Building the Emulator

To build the emulator, navigate to the project directory and run:

```sh
make
```
#### Assembly Language Format
The assembly language supported by this emulator follows a simple format. Here's an example of a program:

``` assembly
; Sample program to add two numbers

START
    LOAD R1, #10      ; Load immediate value 10 into register R1
    LOAD R2, #20      ; Load immediate value 20 into register R2
    ADD R3, R1, R2    ; Add R1 and R2, store result in R3
    HALT              ; Halt the CPU

```


### Contributing
Feel free to contribute to this project by forking the repository, making improvements, and submitting pull requests.

### License
This project is licensed under the MIT License - see the LICENSE file for details.

