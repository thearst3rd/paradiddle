# Paradiddle

Paradiddle is an esoteric programming language created by me, Terry Hearst. The language is based on only the two characters R and L, which symbolize hitting a drum stroke with your right or left hand in rudimental percussion.

I created this language for fun in my free time. It is by no means finished, as I plan to add ops to control program flow and allow for loops and conditionals and such. I'll try not to mess with the existing ops to retain compatibility. We'll see.

Since I programmed it's original implementation in Lua, I've grown in the field of computer science and decided to write a cleaner implementation in C++ that could be run as an executable. I hope some fellow percussionists (or anyone else) out there will find this entertaining, and if not slightly amusing. Thank you.

# The Language

The only two valid characters in Paradiddle are the capital letters R and L. All other charaters are ignored. Each R or L is called a "stroke". The program is read as pairs of two strokes in a row, called a "pair". Each pair can either be a diddle (aka RR or LL) or a single (RL or LR).

The program must start with a single. Then, the program counts how many diddles are read after that until another single (or EOF). The combination of the single and following diddles is called a roll. For example, `RLRRLLRRLLRRLL` would be a roll of length 6, because after the initial single there are 6 diddles. `RLRR` would be 1, `LRLLRRLL` would be 3, and so on. The length of each roll determines what operation, or "op" is executed. The list of operations is listed in the table below.

The memory model of Paradiddle is a stack. At the start of the program it is empty, and as the program goes on ops can 'push' values onto the stack and 'pop' values off of the stack.

## Op Table

Op  | Name | Function
--- | ---- | --------
1   | push | Push the next op to the stack. Do NOT execute the next op.
2   | add  | Pop b then a off the stack, then push a + b.
3   | sub  | Pop b then a off the stack, then push a - b. *Note: Order matters.*
4   | mul  | Pop b then a off the stack, then push a * b.
5   | div  | Pop b then a off the stack, then push a / b. *Note: Order matters.*
6   | num  | Pop a value off the stack then output it as a decimal number.
7   | char | Pop a value off the stack then output it as a char.
8   | dup  | Duplicate the top value of the stack.
9   | pop  | Pop a value from the stack and discard it.

*Note*: If the program encounters an unknown op, it will simply ignore it.

## Programming Conventions

Paradiddle code files have the extension `.rlrr`.

The first pair in the program should be `RL`. Then, all following pairs should follow the given rules:

1. If a pair is a single - `RL` or `LR` - then the next pair should begin with the same stroke as the single did. For example: `...RLRR...` and `...LRLL...`.
2. If a pair is a diddle - `RR` or `LL` - then the next pair should being with the *opposite* stroke as the diddle. For example: `...RRLLRRLL...`

Following these rules, there will always be a unique set of strokes for any given set of intended ops. Note that this is just a convension. Unless running in strict mode (with the `-strict` parameter), you can have any combination of RL, LR, RR, and LL as you want as long as they yield the correct ops. But as a convention, try to stick to the rules above.

If you would like to make your program multiline, try to follow these guidelines:

1. Keep every roll on a new line.
2. If there is a push op, the next line after should be indented indicating that is a numerical value rather than a command.

For all of my conventions, feel free to look at the example programs to get a feel for Paradiddle code.
 
# The Implementation

## Building the Program

If you have gcc and make, simply run `make` in the root directory. Otherwise, compile the program with your favorite compiler. There aren't that many files, you can figure it out.

## Running the Interpreter

The program is run with the "paradiddle" command in the command line. To run the program, type "paradiddle" followed by the name of the file. Example:

`paradiddle hello.rlrr`

### Command Line Arguments

Additional command line arguments are the following:

`-strict`: Runs the program in strict mode. The program must follow the programming conventions stated above that refer to with what stroke a pair is allowed to start.
