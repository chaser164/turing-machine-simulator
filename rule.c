/*
rule.c implementation for Turing Machine Implementation 2024.

Author: Chase R
*/

#include "rule.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


rule *rule_create()
{
    rule *new_rule = malloc(sizeof(rule));
    // Malloc for strings, which require additional dynamic allocation
    new_rule->curr_state = malloc(50 * sizeof(char));
    new_rule->next_state = malloc(50 * sizeof(char));
    return new_rule;
}

rule *rule_read(FILE *input)
{
    // Initial state
    rule *new_rule = rule_create();
    size_t idx = 0;
    for (char c = fgetc(input); c != ','; c = fgetc(input))
    {
        if (c == '\n' || c == EOF) {
            rule_destroy(new_rule);
            return NULL;
        }
        new_rule->curr_state[idx++] = c;
    }
    new_rule->curr_state[idx] = '\0';
    // Initial symbol
    new_rule->curr_symbol = fgetc(input);
    // Clean up until comma
    idx = 0;
    for (char c = fgetc(input); c != ','; c = fgetc(input))
    {
        if (c == '\n' || c == EOF) {
            rule_destroy(new_rule);
            return NULL;
        }
        continue;
    }
    // Next state
    idx = 0;
    for (char c = fgetc(input); c != ','; c = fgetc(input))
    {
        if (c == '\n' || c == EOF) {
            rule_destroy(new_rule);
            return NULL;
        }
        new_rule->next_state[idx++] = c;
    }
    new_rule->next_state[idx] = '\0';
    // Next symbol
    new_rule->next_symbol = fgetc(input);
    // Clean up until comma
    idx = 0;
    for (char c = fgetc(input); c != ','; c = fgetc(input))
    {
        if (c == '\n' || c == EOF) {
            rule_destroy(new_rule);
            return NULL;
        }
        continue;
    }
    // direction
    new_rule->dir = fgetc(input);
    // Clean up until newline
    idx = 0;
    for (char c = fgetc(input); c != '\n'; c = fgetc(input))
    {
        continue;
    }
    return new_rule;
}

void rule_print(const rule *r, FILE *output)
{
    fprintf(output, "current state: %s\n", get_curr_state(r));
    fprintf(output, "next state: %s\n", get_next_state(r));
    fprintf(output, "current symbol: %c\n", get_curr_symbol(r));
    fprintf(output, "next symbol: %c\n", get_next_symbol(r));
    fprintf(output, "direction: %c\n", get_dir(r));
    return;
}

const char *get_curr_state(const rule *r)
{
    return r->curr_state;
}

const char *get_next_state(const rule *r)
{
    return r->next_state;
}

const char get_curr_symbol(const rule *r)
{
    return r->curr_symbol;
}

const char get_next_symbol(const rule *r)
{
    return r->next_symbol;
}

const char get_dir(const rule *r)
{
    return r->dir;
}

void set_curr_state(rule *r, const char *state)
{
    strcpy(r->curr_state, state);
    return;
}

void set_next_state(rule *r, const char *state)
{
    strcpy(r->next_state, state);
    return;
}

void set_curr_symbol(rule *r, const char symbol)
{
    r->curr_symbol = symbol;
    return;
}

void set_next_symbol(rule *r, const char symbol)
{
    r->next_symbol = symbol;
    return;
}

void set_dir(rule *r, const char dir)
{
    r->dir = dir;
    return;
}

// int rule_compare(rule *a, rule *b)
// {
//     return strcmp(a->curr_state, b->curr_state);
// }

void rule_destroy(rule *r)
{
    free(r->curr_state);
    free(r->next_state);
    free(r);
}
