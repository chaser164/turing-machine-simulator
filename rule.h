/*
Rule interface for Turing Machine implementation 2024.

Author: Chase R

*/

#ifndef  __RULE_H__
#define __RULE_H__

#include <stdio.h> // size_t, FILE


typedef struct rule {
    char *curr_state;
    char *next_state;
    char curr_symbol;
    char next_symbol;
    char dir;
} rule;

/*
* creates a rule
*/
rule *rule_create();

/*
* reads in a rule from in file, one at a time (TODO)
*/
rule *rule_read(FILE *input);

/*
* prints all of a rules attributes to the specified output
*/
void rule_print(const rule *r, FILE *output);

/*
* getters
*/
const char *get_curr_state(const rule *r);
const char *get_next_state(const rule *r);
const char get_curr_symbol(const rule *r);
const char get_next_symbol(const rule *r);
const char get_dir(const rule *r);

/*
* setters
*/
void set_curr_state(rule *r, const char *state);
void set_next_state(rule *r, const char *state);
void set_curr_symbol(rule *r, const char symbol);
void set_next_symbol(rule *r, const char symbol);
void set_dir(rule *r, const char dir);

/*
* frees a rule from memory
*/
void rule_destroy(rule *r);


#endif
