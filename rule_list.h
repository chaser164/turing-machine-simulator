/*
Rule list interface for Turing Machine Implementation 2024.

Author: Chase R

*/

#ifndef __RULE_LIST_H__
#define  __RULE_LIST_H__

#include "rule.h"
#include <stdio.h> // size_t


typedef struct rule_list_struct {
    rule **rule_arr;
    size_t length;
    size_t capacity;
} rule_list;

/*
* creates a list of rules
*/
rule_list *list_create();

/*
* Returns index of rule if it matches the curr state and curr symbol of the supplied rule
* Otherwise, returns length of list
*/
size_t list_index_of(rule_list *rules, rule *r);

/*
* Inserts into arraylist
* If the rule is already contained in the array list, the rule ptr is returned to the caller
* PRECONDITION: idx ≤ ∣rules∣
* Returns NULL upon successful insertion
*/
rule *list_insert(rule_list *rules, rule *r, size_t idx);

/*
* Removes rule with corresponding curr state and curr symbol
* removed rule ptr is returned upon successful removal
* NULL is returned with failed removal (i.e. rule to remove not in list)
*/
rule *list_remove(rule_list *rules, rule *r);

/*
* Returns rule ptr at the given idx
* Returns NULL if out of bounds
*/
rule *list_access(rule_list *rules, size_t idx);

/*
* getter for length of list
*/
size_t list_length(rule_list *rules);

/*
* Prints each rule by repeatedly calling rule_print()
*/
void print_list(rule_list *rules, FILE *outfile);

/*
* Frees each rule and the rule_list itself
*/
void list_destroy(rule_list *rules);

#endif
