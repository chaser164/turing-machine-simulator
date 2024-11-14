/*
machine.c implementation for Turing Machine Implementation 2024.

Author: Chase R
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "machine.h"
#include "rule.h"
#include "rule_list.h"

/*
* given arraylist and file specifying rules, populate arraylist with rule struct instances
*/
void populate_list(FILE *infile, rule_list *r_list)
{
    // while valid rules are found in the file, read them in
    for (int i = 0; 1; i++) 
    {
        rule *r = rule_read(infile);
        if (r == NULL) {
            break;
        }
        rule *inserted_rule = list_insert(r_list, r, i);
        // If we receive a non-NULL rule, we must destroy it; it wasn't inserted successfully
        if (inserted_rule != NULL)
        {
            rule_destroy(inserted_rule);
        }
    }
    fclose(infile);
}

/*
* collect tape contents from infile, skipping '\n'
*/
char *get_tape_contents(FILE *input)
{
    // Count number of characters (except newline) in the file
    size_t num_chars = 0;
    for (char c = fgetc(input); c != EOF; c = fgetc(input))
    {
        if (c != '\n') 
        {
            num_chars++;
        }
    }
    // Reset file stream pointer
    fseek(input, 0, SEEK_SET);
    char *tape = malloc((num_chars + 1) * sizeof(char));
    // Read in tape, skipping newlines
    size_t idx = 0;
    for (char c = fgetc(input); c != EOF; c = fgetc(input))
    {
        if (c != '\n') 
        {
            tape[idx++] = c;
        }
    }
    tape[idx] = '\0';
    return tape;
}

machine *machine_create(FILE *rule_file, FILE *tape_file, char *state, size_t head_loc)
{
    rule_list *r_list = list_create();
    populate_list(rule_file, r_list);
    char *tape = get_tape_contents(tape_file);
    machine *new_machine = malloc(sizeof(machine));
    new_machine->r_list = r_list;
    new_machine->tape = tape;
    new_machine->tape_length = strlen(tape);
    new_machine->head_loc = head_loc;
    new_machine->state = state;
    return new_machine;
}

void machine_print(machine *m, FILE *output)
{
    fprintf(output, "STATE: %s\n\n", m->state);
    fprintf(output, "HEAD LOCATION: %zu\n\n", m->head_loc);
    fprintf(output, "TAPE: %s (%zu chars)\n\n", m->tape, m->tape_length);
    fprintf(output, "RULE SET:\n");
    print_list(m->r_list, output);
}

int update(machine *m)
{
    // Dummy rule for finding relevant rule in rule set
    rule dummy_rule = {m->state, NULL, m->tape[m->head_loc], ' ', ' '};
    rule *dummy_rule_ptr = &dummy_rule;
    size_t rule_idx = list_index_of(m->r_list, dummy_rule_ptr);
    // Ensure existing rule
    if (rule_idx >= m->r_list->length) 
    {
        fprintf(stderr, "No matching rule for (%s, %c)\n", dummy_rule_ptr->curr_state, dummy_rule_ptr->curr_symbol);
        return 1;
    }
    rule *rule = list_access(m->r_list, rule_idx);
    // Ensure appripriate direction value
    if (rule->dir != 'L' && rule->dir != 'R')
    {
        fprintf(stderr, "Invalid direction %c\n", rule->dir);
        return 1;
    }
    // Ensure sufficient tape length
    if ((rule->dir == 'L' && m->head_loc == 0) || 
    (rule->dir == 'R' && m->head_loc >= m->tape_length - 1))
    {
        fprintf(stderr, "Insufficient tape length for rule set\n");
        return 1;
    }
    // Update tape
    m->tape[m->head_loc] = rule->next_symbol;
    // Update head location
    if (rule->dir == 'R')
    {
        m->head_loc++;
    } else
    {
        m->head_loc--;
    }
    // Update state
    m->state = rule->next_state;
    return 0;
}

char *machine_tape(machine *m)
{
    return m->tape;
}

void machine_destroy(machine *m)
{
    // Free allocated memory
    list_destroy(m->r_list);
    free(m->tape);
    // Free the machine itself
    free(m);
    return;
}
