/*
rule_list.c implementation for Turing Machine Implementation 2024

Author: Chase R
*/

#include "rule.h"
#include "rule_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

/**
 * Check if the actual number of rules in the array is "too large"; if it is,
 *  increase the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * If the array capacity was changed, print to stderr the string "Expand to ",
 *  followed by the new capacity of the list and a newline. Here is a possible
 *  print statement:
 *
 *     fprintf(stderr, "Expand to %zu\n", new_capacity);
 *
 * If the capacity was not changed, do nothing.
 */
void list_expand_if_necessary(rule_list *rules)
{
    if (list_length(rules) >= rules->capacity)
    {
        size_t new_capacity = rules->capacity * RESIZE_FACTOR;
        rules->capacity = new_capacity;
        rules->rule_arr = realloc(rules->rule_arr, new_capacity * sizeof(rule*));
        fprintf(stderr, "Expand to %zu\n", new_capacity);
    }
    return;
}

/**
 * Check if the actual number of rules in the array is "too small"; if it is,
 *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * If the array capacity was changed, print to stderr the string "Contract to "
 *  followed by the new capacity of the list. Here is a possible print
 *  statement:
 *
 *     fprintf(stderr, Contract to %zu\n, new_capacity);
 *
 * If the capacity was not changed, do nothing.
 *
 * The capacity of the array must never fall below INITIAL_CAPACITY!
 */
void list_contract_if_necessary(rule_list *rules)
{
    if ((list_length(rules) * RESIZE_FACTOR < rules->capacity / RESIZE_FACTOR) && rules->capacity > INITIAL_CAPACITY)
    {
        size_t new_capacity = rules->capacity / RESIZE_FACTOR;
        rules->capacity = new_capacity;
        rules->rule_arr = realloc(rules->rule_arr, new_capacity * sizeof(rule*));
        fprintf(stderr, "Contract to %zu\n", new_capacity);
    }
    return;
}

rule_list *list_create()
{
    rule_list *new_list = malloc(sizeof(rule_list));
    new_list->rule_arr = malloc(INITIAL_CAPACITY * sizeof(rule*));
    new_list->length = 0;
    new_list->capacity = INITIAL_CAPACITY;
    return new_list;
}

size_t list_index_of(rule_list *rules, rule *r)
{
    for (int i = 0; i < list_length(rules); i++)
    {
        // Check curr state and curr symbol, return index if matches
        if (strcmp(get_curr_state(list_access(rules, i)), get_curr_state(r)) == 0)
        {
            if (get_curr_symbol(list_access(rules, i)) == get_curr_symbol(r))
            {
                return i;
            }
        }
    }
    return list_length(rules);
}

// PRECONDITION: idx ≤ ∣rules∣
rule *list_insert(rule_list *rules, rule *r, size_t idx)
{
    // Ensure name isn't already in the ArrayList
    if (list_index_of(rules, r) < list_length(rules))
    {
        return r;
    }
    
    list_expand_if_necessary(rules);
    // Increase list length
    rules->length++;
    // shift contents at idx and everything to the right of idx one to the right
    for (int i = list_length(rules) - 1; i > idx; i--)
    {
        rules->rule_arr[i] = list_access(rules, i - 1);
    }
    // Insert rule into list
    rules->rule_arr[idx] = r;
    return NULL; 
}

rule *list_remove(rule_list *rules, rule *r)
{
    // Ensure name is in the ArrayList
    int idx = list_index_of(rules, r);
    if (idx < list_length(rules))
    {
        rule *removed_rule = list_access(rules, idx);
        // Shift all pointers to the left
        for (int i = idx; i < list_length(rules) - 1; i++)
        {
            rules->rule_arr[i] = list_access(rules, i + 1);
        }
        // Decrease length
        rules->length--;
        list_contract_if_necessary(rules);
        return removed_rule;
    }
    return NULL;
}

rule *list_access(rule_list *rules, size_t idx)
{
    if (idx >= list_length(rules))
    {
        return NULL;
    }
    return rules->rule_arr[idx];
}

size_t list_length(rule_list *rules)
{
    return rules->length;
}


// Prints each rule to the provided outfile, one name per line
void print_list(rule_list *rules, FILE *outfile)
{
    for (int i = 0; i < list_length(rules); i++)
    {
        // Print rule
        rule_print(list_access(rules, i), outfile);
        // Extra newline
        fprintf(outfile, "\n");
    }
}

void list_destroy(rule_list *rules)
{
    // Destroy each rule
    for (int i = 0; i < list_length(rules); i++)
    {
        rule_destroy(list_access(rules, i));
    }
    // Free array
    free(rules->rule_arr);
    // Free ArrayList
    free(rules);
}
