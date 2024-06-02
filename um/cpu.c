/***************************************************************
 *
 *                     cpu.c
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/08/2024
 *
 *     This file defines the instruction functions that can be called
 *     and the data structure for storing the registers
 *
 *
 ***************************************************************/
#include "cpu.h"
#include <seq.h> 
#include <stdint.h>
#include <mem.h>
#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "memoryStruct.h"
#include "memory.h"


#define NUM_REGISTERS 8
#define T CPU

/* CPU struct that stores the eight registers */
struct T {
        uint32_t registers[NUM_REGISTERS];
};


/* 
 * Name: CPU_new
 * 
 * Description: Initializes a new CPU with all eight registers set to zero
 *
 * Parameters:
 *           None
 *
 * Returns: A struct of registers.
 * 
 * Expects: When making the struct, memory is allocated successfully
 *
 * Notes: Throws a c.r.e. if cpu is NULL after memory allocation attempt.
 */
T CPU_new() {
        T cpu = NEW(cpu);
        if (cpu == NULL) {
            /* Handle memory allocation failure */
                return NULL;
        }
        /* Initialize all registers to 0 */
        for (int i = 0; i < NUM_REGISTERS; i++) {
                cpu->registers[i] = 0;
        }
        return cpu;
}

/* 
 * Name: CPU_free
 * 
 * Description: Frees a CPU struct and its eight registers
 *
 * Parameters:
 *           T *cpu: A pointer to a CPU struct
 *
 * Returns: None
 * 
 * Expects: The struct pointer passed in is not NULL
 *
 * Notes: Throws a c.r.e. if the parameter passed in is NULL
 */
void CPU_free(T *cpu) {
        assert(cpu != NULL);
        FREE(*cpu);
        *cpu = NULL;
}

/* 
 * Name: CPU_add
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              adding what is in the second register passed in by what 
 *              is in the third register passed in ensuring that the product
 *              is in bounds, stores the result in the first register.
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Calling the and operation with 0xFFFFFFFF mods the sum by 2^32 so it
 *        remains within the bounds of an unsigned 32 bit integerchanges
 *        the value of the register of the first index passed in
 */
void CPU_add(T cpu, int ra, int rb, int rc)
{
        int sum = cpu->registers[rb] + cpu->registers[rc];
        uint32_t new_sum = sum & 0xFFFFFFFF;
        cpu->registers[ra] = new_sum;
}

/* 
 * Name: CPU_multiply
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              multiplying what is in the second register passed in by what 
 *              is in the third register passed in ensuring that the product
 *              is in bounds, stores the result in the first register.
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Calling the and operation with 0xFFFFFFFF mods the sum by 2^32 so it
 *        remains within the bounds of an unsigned 32 bit integer, changes
 *        the value of the register of the first index passed in
 */
void CPU_multiply(T cpu, int ra, int rb, int rc)
{
        int product = cpu->registers[rb] * cpu->registers[rc];
        uint32_t new_product = product & 0xFFFFFFFF;
        cpu->registers[ra] = new_product;
}

/* 
 * Name: CPU_division
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              dividing what is in the second register passed in by what is 
 *              in the third register passed in, and stores the result in the
 *              first register.
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Dividing by zero will result in an unchecked runtime error, changes
 *        the value of the register of the first index passed in
 */
void CPU_division(T cpu, int ra, int rb, int rc)
{
        /* if cpu->registers[rc] = zero, divide by 0 and allow the segfault */
        int quotient = cpu->registers[rb] / cpu->registers[rc];
        cpu->registers[ra] = quotient;
} 

/* 
 * Name: CPU_nand
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              calling the and bit operation between what is in the second 
 *              register passed in by what is in the third register passed in,
 *              and stores the negated result in the first register.
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Changes the value in the register of the first index passed in
 */
void CPU_nand(T cpu, int ra, int rb, int rc)
{
        uint32_t nand = ~(cpu->registers[rb] & cpu->registers[rc]);
        cpu->registers[ra] = nand;
} 

/* 
 * Name: CPU_conditional
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              and if what is in the third register passed in does not equal 
 *              zero, places what is in the second register passed in into the 
 *              first register passed in
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Depending on the conditional, may change the value in a register 
 */
void CPU_conditional(T cpu, int ra, int rb, int rc)
{
        if (cpu->registers[rc] != 0) {
                cpu->registers[ra] = cpu->registers[rb];
        }
}

/* 
 * Name: CPU_segload
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              and loads a segment of memory that is obtained using the 
 *              the values in the second and third register parameters passed 
 *              in into the first register parameter passed in
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Failure is acceptable in these cases: A segmented load refers to an
 *        unmapped segment, or a segmented load refers to a location outside 
 *        the bounds of a mapped segment.
 */
void CPU_segload(T cpu, struct Memory *memory, int ra, int rb, int rc)
{
        uint32_t seg_num = cpu->registers[rb];

        /* Failure case: there is no segment seq_t where seq_get accesses */
        Seq_T segment = Seq_get(memory->segments, seg_num);
        uint32_t word = (uintptr_t)Seq_get(segment, cpu->registers[rc]);
        cpu->registers[ra] = word;
}

/* 
 * Name: CPU_segstore
 * 
 * Description: An instruction of the UM that takes in three register indices,
 *              and puts what is in the first register passed into a segment 
 *              of memory that is obtained using the values in the second and
 *              third register parameters passed in into the first register
 *              parameter passed in
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *           int ra: A register index
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: None
 *
 * Notes: Failure is acceptable in these cases: A segmented store refers to an
 *        unmapped segment, or a segmented store refers to a location outside 
 *        the bounds of a mapped segment.
 */
void CPU_segstore(T cpu, struct Memory *memory, int ra, int rb, int rc)
{
        int seg_num = cpu->registers[ra];

        /* Failure case: there is no segment seq_t where get or put access */
        Seq_T segment = Seq_get(memory->segments, seg_num);
        Seq_put(segment, cpu->registers[rb], 
                (void *)(uintptr_t)cpu->registers[rc]);
}

/* 
 * Name: halt
 * 
 * Description: Ends the current "program", cleaning up memory and the CPU
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *
 * Returns: None
 * 
 * Expects: cpu and memory to not be NULL
 *
 * Notes: If cpu and memory are already NULL, the program will segfault. Halt
 *        ends the program though, so these would have to be set to NULL
 *        elsewhere (can't call halt more than once)
 */
void CPU_halt(T cpu, struct Memory *memory)
{
        Memory_free(&memory);
        CPU_free(&cpu);
        /* exit the program according to specified exit code */
        exit(EXIT_SUCCESS);
}

/* 
 * Name: CPU_mapsegment
 * 
 * Description: An instruction of the UM that takes in two register indices;
 *              A new segment is created with a number of uint_32t words equal
 *              to the value in $r[rc]. Each word in the new segment is 
 *              initialized to 0. A bit pattern that is not all zeroes and 
 *              that does not identify any currently mapped segment is placed
 *              in $r[rb]. The new segment is mapped in the memory parameter
 *              as $m[$r[rb]].
 *              
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: The value that will be put in $r[rb] to not be zero or map to 
 *          an already mapped segment
 *
 * Notes: Will throw a c.r.e if the value that will be put in $r[rb] is zero
 */
void CPU_mapsegment(T cpu, struct Memory *memory, int rb, int rc)
{
        uint32_t id;
        int length = Seq_length(memory->unmapped_ids);
        if (length != 0) {
                id = (uint32_t)(uintptr_t)Seq_remlo(memory->unmapped_ids);
        } else {
                id = (uint32_t)Seq_length(memory->segments);
        }
        assert(id != 0);
        int seg_length = cpu->registers[rc];
        Seq_T segment = Seq_new(seg_length);
        for (int i = 0; i < seg_length; i++) {
                /* Initialize 0s words sequence */
                Seq_addhi(segment, (void *)(uintptr_t)0); 
        }

        /* Check to see if mapping to an already unmapped segment */
        if (length != 0) {
                Seq_put(memory->segments, id, (void *)segment);
        } else {
                Seq_addhi(memory->segments, (void *)segment);
        }

        cpu->registers[rb] = id;
        return;
}

/* 
 * Name: CPU_unmapsegment
 * 
 * Description: Unmaps the segment stored in $m[$r[rc]], and puts $r[rc] into
 *              the sequence in the memory parameter that stores the list of 
 *              unmapped ids so that future Map Segment instructions may 
 *              reuse that segment later
 *              
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: That what is in the register accessed by rc to not be zero and
 *          will map to an actually mapped segment
 *
 * Notes: Failure condition: An instruction unmaps either $m[0] or a segment 
 *        that is not mapped. Unchecked runtime error in either case
 */
void CPU_unmapsegment(T cpu, struct Memory *memory, int rc)
{
        /* Get the segment number to unmap from register rc */
        uint32_t seg_num = cpu->registers[rc];

        /* Free the segment memory */
        Seq_T segment = Seq_get(memory->segments, seg_num);
        if (segment != NULL) {
                Seq_free(&segment);
                Seq_put(memory->segments, seg_num, NULL);
                
                /* Add the segment identifier to the list of unmapped IDs */
                Seq_addhi(memory->unmapped_ids, (void *)(uintptr_t)seg_num);
        }
}

/* 
 * Name: CPU_output
 * 
 * Description:  The value in the register accessed by the register parameter
 *               is written to the I/O device immediately. Only values from 0
 *               to 255 are allowed.
 *              
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: The value in the specified register to be between 0 and 255
 *
 * Notes: Failure condition: An instruction outputs a value larger than 255.
 */
void CPU_output(T cpu, int rc)
{
        putchar(cpu->registers[rc]);
}

/* 
 * Name: CPU_input
 * 
 * Description:  After accepting input from the I/O device, the register 
 *               accessed by the register parameter is loaded with the input,
 *               which must be a value from 0 to 255. If the end of input has
 *               been signaled, then the register accessed by the register
 *               parameter is loaded with 32-bit word in which every bit is 1.
 *              
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: The input to be between 0 and 255
 *
 * Notes: Will throw a c.r.e. if the input is a value larger than 255.
 */
void CPU_input(T cpu, int rc)
{
        int input = getchar();

        if (input == EOF) {
                cpu->registers[rc] = (uint32_t) ~0;
        } else {
                assert(input <= 255);
                cpu->registers[rc] = (uint32_t) input;
        }
}

/* 
 * Name: CPU_loadprogram
 * 
 * Description:  Checks to see if the register accessed by the first register
 *               parameter is 0, and if it is simply return. If it isn't,
 *               duplicates the segment $m[$r[rb]] is duplicated, and the 
 *               duplicate replaces $m[0], which is abandoned. The program 
 *               counter is set to point to $m[0][$r[rc]].
 *              
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           struct Memory *memory: The instance of memory used for the 
 *                                  current set of instructions
 *           int rb: A register index
 *           int rc: A register index
 *
 * Returns: None
 * 
 * Expects: The segment in memory accessed to exist
 *
 * Notes: Failure condition: An instruction loads a program from a segment 
 *        that is not mapped.
 */
void CPU_loadprogram(T cpu, struct Memory *memory, int rb, int rc)
{
        memory->counter = cpu->registers[rc];

        /* If what is in register rb is 0, loads quickly */
        if (cpu->registers[rb] == 0) {
                return;
        }

        uint32_t seg_num =  cpu->registers[rb];
        Seq_T segment = Seq_get(memory->segments, seg_num);
        int length = Seq_length(segment);

        Seq_T duplicate = Seq_new(length);
        for (int i = 0; i < length; i++) {
                uint32_t dup = (uintptr_t)Seq_get(segment, i);
                Seq_addhi(duplicate, (void *)(uintptr_t) dup);
        }
        Seq_free(&(Seq_get(memory->segments, 0)));
        Seq_put(memory->segments, 0, (void *)duplicate);
}

/* 
 * Name: CPU_loadvalue
 * 
 * Description:  Sets the register accessed bt the register parameter to the
 *               passed in value parameter
 *              
 *
 * Parameters:
 *           T cpu: A CPU struct storing eight registers
 *           int ra: A register index
 *           unisgned value: the value to be stored
 *
 * Returns: None
 * 
 * Expects: The segment in memory accessed to exist
 *
 * Notes: Failure condition: An instruction loads a program from a segment 
 *        that is not mapped.
 */
void CPU_loadvalue(T cpu, int ra, unsigned value)
{
        // printf("LOADVAL: Register Number %d is now %d\n", ra, value);
        cpu->registers[ra] = (uint32_t)value;
}