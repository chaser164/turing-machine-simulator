/*
Machine interface for Turing Machine implementation 2024.

Author: Chase R

*/

#ifndef  __MACHINE_H__
#define __MACHINE_H__

#include "rule_list.h"
#include "rule.h"
#include <stdio.h>

typedef struct machine_t {
    rule_list *r_list;
    char *tape;
    size_t tape_length;
    char *state;
    size_t head_loc;
} machine;

/*
* creates a machine from rule set file, tape file, init state, and init head loc
*/
machine *machine_create(FILE *rule_file, FILE *tape_file, char *state, size_t head_loc);

/*
* Prints the tape and the rule set to specified output file
*/
void machine_print(machine *m, FILE *output);

/*
* Updates the machine. If there is no valid matching state, invalid direction supplied,
* or tape is insufficient length, returns 1. valid update returns 0.
*/
int update(machine *m);

/*
* Getter for the tape field of the machine
*/
char *machine_tape(machine *m);

/*
* destroys the machine in allocated memory
*/
void machine_destroy(machine *m);

#endif
