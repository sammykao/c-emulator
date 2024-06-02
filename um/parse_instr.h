/***************************************************************
 *
 *                     parse_instr.h
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This header file declares functions for parsing through uint32_t
 *     instructions to figure out what each one wants to accomplish
 *
 ***************************************************************/

#ifndef PARSE_INSTR_H
#define PARSE_INSTR_H

#include "memory.h"
#include "cpu.h"
#include <stdint.h>
#include "memoryStruct.h"

/* Function prototypes */
void handle_instruction(Memory memory, CPU cpu);
void unpack_instruction(Memory memory, CPU cpu, uint32_t word);

#endif /* PARSE_INSTR_H */
