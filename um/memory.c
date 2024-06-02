/***************************************************************
 *
 *                     memory.c
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This file defines functions for managing memory segments
 *     and loading instructions into memory from a file.
 *
 *
 ***************************************************************/

#include <seq.h>
#include <mem.h>
#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <bitpack.h>
#include "memory.h"
#include <stdint.h>
#include "memoryStruct.h"

/* Name: Memory_new 
 *
 * Description: Create a new Memory instance.
 *
 * Parameters:
 *           None
 * 
 * Return: A new Memory instance.
 *
 * Expects: None.
 *
 * Notes: inits counter to 0 and inits two empty sequences.
 */
Memory Memory_new()
{
        /* Allocate memory for the Memory struct */
        Memory memory = NEW(memory);
        /* Initialize segments sequence */
        memory->segments = Seq_new(0);
        /* Initialize unmapped IDs sequence */         
        memory->unmapped_ids = Seq_new(0);     
        memory->counter = 0;
        return memory;
}

/* Name: Memory_free
 *
 * Description: Free memory allocated for a Memory instance.
 *
 * Parameters:
 *      Memory *memory: Pointer to the Memory instance to be freed.
 *
 * Return: None.
 *
 * Expects: memory must not be NULL.
 *
 * Notes: All memory associated with the Memory instance, 
 *        including segments and unmapped IDs, will be deallocated.
 */
void Memory_free(Memory *memory)
{
        int num_segments = Seq_length((*memory)->segments);
        /* Free memory for each segment */
        for (int i = 0; i < num_segments; i++) {
                Seq_T curr_segment = Seq_get((*memory)->segments, i);
                if (curr_segment != NULL) {
                        Seq_free(&(curr_segment));
                }        
        }

        /* Free memory for the segments sequence and unmapped IDs sequence */
        Seq_free(&((*memory)->segments));
        Seq_free(&((*memory)->unmapped_ids));

        /* Free memory for the Memory instance */
        FREE(*memory);
}

/* Name: load_instructions
 *
 * Description: Load instructions into memory from a file.
 *
 * Parameters:
 *      Memory memory: Memory instance to load instructions into.
 *      FILE *input: File pointer to the input file containing instructions.
 *
 * Return: None.
 *
 * Expects: memory and input must not be NULL.
 *
 * Notes: Each instruction in the file is assumed to be 4 bytes.
 *        Instructions are added to the words sequence of 
 *        the segments in the memory instance.
 */
void load_instructions(Memory memory, FILE *input)
{
        assert(memory != NULL && input != NULL);
        int fd = fileno(input);
        struct stat st;
        fstat(fd, &st);

        /* Assuming each instruction is 4 bytes */
        int fs = st.st_size / 4;

        /* Create a new segment */
        Seq_T segment = Seq_new(fs);    

        /* Read instructions from the file and add them to the segment */
        for (int i = 0; i < fs; i++) {
                int instruction = Bitpack_newu(0, 8, 24, fgetc(input));
                instruction = Bitpack_newu(instruction, 8, 16, fgetc(input));
                instruction = Bitpack_newu(instruction, 8, 8, fgetc(input));
                instruction = Bitpack_newu(instruction, 8, 0, fgetc(input));

        /* Add instruction to the words sequence */
            Seq_addhi(segment, (void *)(uintptr_t)instruction); 
        }
        Seq_addhi(memory->segments, (void *)segment);
}