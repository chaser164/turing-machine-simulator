# Turing Machine Implementation

*Chase Reynders*

## Overview

This project implements a [Turing Machine](https://en.wikipedia.org/wiki/Turing_machine) by reading rules into a dynamic array and performing the rules on a tape, printing out the final tape output.

Since it is impossible to represent an infinitely long tape in memory, the tape is finite in length, and if rule sets cause the Turing Machine's head to traverse beyond the tape's limits, an error is returned.

Errors are also raised when no rule matches the current state-symbol combination as well as when an invalid direction (not 'R' or 'L') is supplied.

## Usage

run `make all` to compile.

```
./Turing <rule set file path> <tape file path> <init state string> <init head location (index of tape)>
```

To simplify the implementation, there are only 2 valid halting states: `HALT` and `halt`.

For example, run
```
./Turing rules/reverse.txt tapes/tape_1.txt q1 0
```
to reverse a binary string.

## Rule Sets

Rule sets encode the Turing Machine. They are stored in `rules/`.

### even_zeros.txt

This rule set determines if the total count of zeros in the tape is even or odd. it returns 0 if even, 1 if odd. This rule set is expecting a single, contiguous chunk of non-blank characters where
$${\displaystyle \Gamma } = \{-, 0, 1\}$$ 
and '-' represents a blank character. The initial state is `q1`, and the program is expecting the head to start to the left of the chunk of 1s and 0s.

### reverse.txt

This rule set reverses the input tape. The expected input tape is a single, contiguous chunk of 1s and 0s padded by blanks (represented as '-'). Ensure that there is sufficient blank padding to the left of the binary chunk, since the reversal works by copying the character in backwards order before the start of the chunk on the tape. The initial state is `q1`, and the program is expecting the head to start to the left of the chunk of 1s and 0s.
