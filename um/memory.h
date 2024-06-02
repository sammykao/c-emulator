/***************************************************************
 *
 *                     memory.h
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This header file declares functions for managing memory segments
 *     and loading instructions into memory from a file.
 *
 ***************************************************************/

#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED

#include <seq.h>
#include <mem.h>
#include <stdio.h>
#include "memoryStruct.h"

/* Define the Memory struct and its pointer */
typedef struct Memory *Memory;


/* Create a new Memory instance */
extern Memory Memory_new();

/* Free memory allocated for a Memory instance */
extern void Memory_free(Memory *memory);

/* Load instructions into memory from a file */
extern void load_instructions(Memory memory, FILE *input);


#endif