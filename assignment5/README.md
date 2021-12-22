# Assignment 5

## Problem:

Using system calls, fork(), wait(), open(), close(), read() and write(), write a C program to read a simple two-term arithmetic expression (x op y, where x and y are real values and op is one of +, - * or /) as a string, evaluates it, then prints it out . Your program should follow the sequential steps, given below.

* Prompts the message "This program is simple calculator",
* Gets in an infinite loop then
1. Writes the message "Enter an expression, e.g., 134.5 + 456> ",

2. Use "read()" to read the whole input line as a string.

3. Forks and
* the parent writes the message "Created a child to perform task, waiting...", then calls wait() to wait for its child.
* the child process calls the function childFunction(char *) and never returns.

4. The child, through childFunction(char *line),
* writes the message "I am a child working for my parent"
* extracts the two values and operator (it is not necessary that there is a blank to separate the operator from operands, e.g. 23+11 or 23 + 11 are both valid),
* in case of input error, the child calls exit(55),
* opens a file called result.txt, for writing and truncates it, to get rid of old contents,
* writes the value of the expression in result.txt, then closes the file.
* calls exit(0)

5. Once the child terminates, the parent checks the returned status value and if it is 55, writes on the screen "Wrong expression" and goes back to 1.

6. Otherwise, the parent opens file result.txt for reading, reads the value (type double), prints it on the screen, closes result.txt and goes back to 1.

**Important:** All reads/writes must be done using read()/write()