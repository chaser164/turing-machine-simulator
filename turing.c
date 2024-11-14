/*
Driver for Turing Machine Implementation 2024.

Author: Chase R
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine.h"

#define MAX_ITER 1000

int main(int argc, char **argv)
{  
    // Ensure correct number of CLA
    if (argc != 5)
    {
        fprintf(stderr, "Usage: ./Turing <rule set file> <tape file> <init state> <init head location>\n");
        return 1;
    }
    FILE *rule_file = fopen(argv[1], "r");
    FILE *tape_file = fopen(argv[2], "r");
    // Ensure valid infile path
    if (rule_file == NULL || tape_file == NULL)
    {
        fprintf(stderr, "ERROR: At least one of the supplied files are NULL\n");
        return 1;
    }
    
    machine *m = machine_create(rule_file, tape_file, argv[3], atoi(argv[4]));
    printf("Input Tape:\n%s\n\n", machine_tape(m));
    // Iterate through the turing machine acording to rulesets, keeping track of any errors that occur.
    for(int i = 0; i < MAX_ITER; i++)
    {
        // Update, and quit program if error encountered
        if (update(m))
        {
            machine_destroy(m);
            return 1;
        }
        if (strcmp(m->state, "HALT") == 0 || strcmp(m->state, "halt") == 0)
        {
            printf("Output Tape:\n%s\n\n", machine_tape(m));
            machine_destroy(m);
            return 0;
        }
    }
    fprintf(stderr, "%d iterations reached; stopping", MAX_ITER);
    machine_destroy(m);
    return 1;
}
