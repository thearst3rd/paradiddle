# Paradiddle

Paradiddle is an esoteric programming language created by me, Terry Hearst. The language is based on only the two characters R and L, which symbolize hitting a drum stroke with your right or left hand in rudimental percussion.

# The Language

The only two valid characters in Paradiddle are the capital letters R and L. All other charaters are ignored. Each R or L is called a "stroke". The program is read as pairs of two strokes in a row, called a "pair". Each pair can either be a diddle (aka RR or LL) or a single (RL or LR).

The program must start with a single. Then, the program counts how many diddles are read after that until another single (or EOF). The combination of the single and following diddles is called a roll. For example, `RLRRLLRRLLRRLL` would be a roll of length 6, because after the initial single there are 6 diddles. `RLRR` would be 1, `LRLLRRLL` would be 3, and so on. The length of each roll determines what operation, or "op" is executed. The list of operations is listed in the table below.

The memory model of Paradiddle is a stack. At the start of the program it is empty, and as the program goes on ops can 'push' values onto the stack and 'pop' values off of the stack.

Op  | Name | Function
--- | ---- | --------
1   | push | Push the next op to the stack. Do NOT execute the next op.
2   | add  | Pop b and a off the stack, then push a + b.
3   | sub  | Pop b, a off the stack, then push a - b. Note: Order matters.
4   | mul  | Pop b, a off the stack, then push a * b
5   | div  | Pop b, a off the stack, then push a / b
6   | num  | Pop n off the stack, then output the decimal number n.
7   | char | Pop n off the stack, then output the n as a char.
8   | dup  | Duplicate the top value of the stack.
9   | pop  | Pop a value from the stack and discard it.


# Running the Interpreter

The program is run with the "paradiddle" command in the command line. To run the program, type "paradiddle" followed by the name of the file. Example:

`paradiddle hello.rlrr`

### Command Line Arguments

Additional command line arguments are the following:

`-strict`: Enables strict mode, which means the program must start with R, and every pair of two strokes must logically follow the last pair, as in the starting stroke following a diddle must alternate from the starting stroke of that diddle, and the starting stroke after a single must match the starting stroke of the single. For example, `RLRRLLRR` is valid, but `LRLLLLRR` is not.
