CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: Turing

clean:
	rm -f *.o Turing

Turing : turing.o machine.o rule.o rule_list.o
	$(CC) $(CFLAGS) -o $@ $^

turing.o : turing.c rule_list.c rule_list.h rule.c rule.h
machine.o : machine.c machine.h rule_list.c rule_list.h rule.c rule.h
rule_list.o : rule_list.c rule_list.h rule.c rule.h
rule.o : rule.c rule.h