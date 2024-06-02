/***************************************************************
 *
 *                     um.c
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This file defines the main function for our UM that calls the loop
 *     function that runs through all instructions from the file passed in
 *
 *
 ***************************************************************/
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "memory.h"
#include "cpu.h"
#include "parse_instr.h"
#include <seq.h>

/* 
 * Name: main
 * 
 * Description: Takes in a file with um instructions, initializes memory and
 *              the cpu, then calls the loop function to handle the passed in
 *              instructions.
 *
 * Parameters:
 *           int argc: the amount of arguments passed in from the command line
 *           char *argv[]: an array of strings storing the command line
 *                         arguments
 *
 * Returns: An integer
 * 
 * Expects: Two arguments provided on the command line, an executable and file
 *
 * Notes: Returns EXIT_FAILURE if two arguments are not provided.
 */
int main(int argc, char *argv[]) {
    // Check if filename is provided as argument
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        // File pointer
        FILE *fp;
        fp = fopen(argv[1], "r");
        assert(fp != NULL);

        // New instance of Memory
        Memory memory = Memory_new();

        // New CPU instance
        CPU cpu = CPU_new();

        // Instruction handler
        load_instructions(memory, fp);
        // Close the file
        fclose(fp);

        while (memory->counter != Seq_length(Seq_get(memory->segments, 0))) {
                handle_instruction(memory, cpu);
        }
        // Free memory instance and CPU instance
        Memory_free(&memory);
        CPU_free(&cpu);



        return 0;
}

