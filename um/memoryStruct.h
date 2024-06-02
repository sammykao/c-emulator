/***************************************************************
 *
 *                     memoryStruct.h
 *
 *     Assignment: UM
 *     Authors:  Sammy Kao & Luke Randolph
 *     Date:     04/04/2024
 *
 *     This file provides the definition of the Memory struct.
 *
 ***************************************************************/

#ifndef MEMORYSTRUCT_INCLUDED
#define MEMORYSTRUCT_INCLUDED

#include <seq.h>

/* Definition of Memory struct */
struct Memory {
        Seq_T segments;        /* Sequence to hold segments */
        Seq_T unmapped_ids;    /* Sequence to hold unmapped IDs */
        int counter;           /* Counter variable */
};

#endif