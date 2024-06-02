/***************************************************************
 *
 *                     parse_instr.c
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This header file defines the functions for parsing through uint32_t
 *     instructions to figure out what each one wants to accomplish
 *
 ***************************************************************/
#include "memory.h"
#include "cpu.h"
#include "parse_instr.h"
#include <seq.h>
#include <bitpack.h>
#include <stdint.h>
#include "memoryStruct.h"
#include <assert.h>

/* Name: handle_instruction
 *
 * Description: Gets the next word from the instruction segment in memory and
 *              passes it to a function that will figure out what needs to be
 *              done with it.
 *
 * Parameters:
 *      Memory memory: Memory instance to load instructions into.
 *      CPU cpu: A CPU struct storing eight registers
 *
 * Return: None.
 *
 * Expects: memory and cpu must not be NULL, also that counter is not at
 *          the end of the instruction segment
 *
 * Notes: Will throw a c.r.e. if memory and cpu are NULL and also if the 
 *        counter points to the end of the instruction segment
 */
void handle_instruction(Memory memory, CPU cpu) 
{
        /* Make sure our parameters are not NULL */
        assert(memory != NULL && cpu != NULL);
        Seq_T instructions = Seq_get(memory->segments, 0);

        /* Obtain the next word from our instruction segment */
        int counter = memory->counter;
        assert(counter != Seq_length(instructions));
        uint32_t word = (uintptr_t) Seq_get(instructions, memory->counter);
        (memory->counter)++;
        unpack_instruction(memory, cpu, word);
}

/* Name: unpack_instruction
 *
 * Description: Takes in a uint32_t word, and calls the relevant instruction
 *              function based on the opcode from the word, passing in the
 *              relevant register index paramaters also obtained from the word
 *
 * Parameters:
 *      T memory: Memory instance to load instructions into.
 *      CPU cpu: A CPU struct storing eight registers
 *      uint32_t word: A bitpacked instruction from the passed in file
 *
 * Return: None.
 *
 * Expects: The opcode to be between 0 and 14.
 *
 * Notes: Will throw a c.r.e. if the opcode is not between 0 and 14
 */
void unpack_instruction(Memory memory, CPU cpu, uint32_t word)
{
        /* First understand what the opcode is */
        int opcode = Bitpack_getu(word, 4, 28);
        int ra, rb, rc;

        /* Check if instruction 13 with a different format is being called */
        if (opcode == 13) {
                ra = Bitpack_getu(word, 3, 25);
                unsigned value = Bitpack_getu(word, 25, 0);
                CPU_loadvalue(cpu, ra, value);
                return;
        }

        /* Format for instructions 0 to 12 */
        rc = Bitpack_getu(word, 3, 0);
        rb = Bitpack_getu(word, 3, 3);
        ra = Bitpack_getu(word, 3, 6);

        /* Instruction cases */
        switch(opcode) {
                case 0:
                        CPU_conditional(cpu, ra, rb, rc);
                        break;
                case 1:
                        CPU_segload(cpu, memory, ra, rb, rc);
                        break;
                case 2:
                        CPU_segstore(cpu, memory, ra, rb, rc);
                        break;
                case 3:
                        CPU_add(cpu, ra, rb, rc);
                        break;
                case 4:
                        CPU_multiply(cpu, ra, rb, rc);
                        break;
                case 5:
                        CPU_division(cpu, ra, rb, rc);
                        break;
                case 6:
                        CPU_nand(cpu, ra, rb, rc);
                        break;
                case 7:
                        CPU_halt(cpu, memory);
                        break;
                case 8:
                        CPU_mapsegment(cpu, memory, rb, rc);
                        break;
                case 9:
                        CPU_unmapsegment(cpu, memory, rc);
                        break;
                case 10:
                        CPU_output(cpu, rc);
                        break;
                case 11:
                        CPU_input(cpu, rc);
                        break;
                case 12:
                        CPU_loadprogram(cpu, memory, rb, rc);
                        break;
        }
}


