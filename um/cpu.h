/***************************************************************
 *
 *                     cpu.h
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/08/2024
 *
 *     This file declares the instruction functions that can be called
 *     by the UM program
 *
 *
 ***************************************************************/

#ifndef CPU_INCLUDED
#define CPU_INCLUDED

#include "memoryStruct.h" 

/* Define the CPU struct and its pointer */
#define T CPU
typedef struct T *T;

extern T CPU_new();
extern void CPU_free(T *cpu);
extern void CPU_add(T cpu, int ra, int rb, int rc);
extern void CPU_multiply(T cpu, int ra, int rb, int rc);
extern void CPU_division(T cpu, int ra, int rb, int rc);
extern void CPU_nand(T cpu, int ra, int rb, int rc);
extern void CPU_conditional(T cpu, int ra, int rb, int rc);
extern void CPU_segload(T cpu, struct Memory *memory, int ra, int rb, int rc);
extern void CPU_segstore(T cpu, struct Memory *memory, int ra, int rb, int rc);
extern void CPU_halt(T cpu, struct Memory *memory);
extern void CPU_mapsegment(T cpu, struct Memory *memory, int rb, int rc);
extern void CPU_unmapsegment(T cpu, struct Memory *memory, int rc);
extern void CPU_output(T cpu, int rc);
extern void CPU_input(T cpu, int rc);
extern void CPU_loadprogram(T cpu, struct Memory *memory, int rb, int rc);
extern void CPU_loadvalue(T cpu, int ra, unsigned value);

#undef T
#endif