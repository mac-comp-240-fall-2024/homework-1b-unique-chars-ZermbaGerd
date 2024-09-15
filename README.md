[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/gF_qPi1k)
# Unique Characters in a String

## Overview and Guidelines

This is a classic problem that has been posed many times (including for the
dreaded coding interview by employers). The problem is this:

**Given a string of characters, which are encoded in ascii, determine if the string contains all unique characters.**

There are many solutions in various languages, some of which are
straightforward, but at the same time may be inefficient. Others may perform
fairly well, but are rather incomplete (they don't cover all ascii characters
that are easy to check). Perhaps the most vexing issue with many proposed
solutions is that they do not handle cases when a string contains characters it
does not expect. The web is filled with examples that are too simple and not
exhaustive. Writing and using code like this has consequences. **Your goal** is
to use what you learn about how ascii characters are encoded as bits, and
therefore numbers. The problem can be solved using the numerical representation
of all possible characters and some special unsigned long integers that you
treat as 'bit vectors' (described further below).

The 128 fundamental ascii characters are found in the file provided called
`ascii_table.txt`. This is purely a reference and is not designed to be part of
your code solution.

Complete all the tasks listed below, and be sure to check the assignment rubric 
to make sure your solution matches what we are looking for. 

Be sure to commit and push your changes frequently: having a copy of the code
that is **not** on the server is safest, and easiest when you need help. See
Homework 0 for guidance on staging, committing, and pushing your code.

### Assignment Rubric

- In `hasUniqueChars.c` (16 pts):
    - Student name and description of file at the top of the file
    - Clean coding style (indentation, spacing, readability, good variable names, etc.)
    - Function `hasUniqueChars` has a good quality comment
    - Function `hasUniqueChars` implemented correctly according to instructions below
    - All debugging statements have been commented out or removed
- In `test.c` (16 pts):
    - Student name and description of file at the top of the file
    - Clean coding style (indentation, spacing, readability, good variable names, etc.)
    - Every test in `main` has a comment that describes what it tests  (3 pts)
    - Includes thorough tests that use `assert`:
        - all printable characters
        - strings with and without duplicate characters
        - strings with multiple spaces (spaces do not count as duplicates)
        - edge cases at the end of the allowable range
        - some non-printing characters
    - All debugging statements have been commented out or removed


### Starter Code

- `Makefile`
    - We have provided a Makefile for you; it creates an executable called `hasUniqueChars`.
- `binary_convert.c`, `binary_convert.h` 
    - these files create printable binary representations of integers. You will not need to change these files.
- `hasUniqueChars.c`
    - this file contains a function to check if a string has duplicated characters. You will 
    complete the function `hasUniqueChars`. This file also contains two helper 
    functions that you will not need to change: the `seeBits` function is used
    to visualize a binary sequence, the `checkInvalid` function checks for
   non-printing characters.

- `test.c`
    - The main program, that will contain your exhaustive tests of the `hasUniqueChars`
   function.


### Execution

The graders should be able to do the following to build and run your code *without errors*:

    make clean
    make
    ./hasUniqueChars

## Tasks to Complete

### Task 1: Complete `hasUniqueChars.c`

#### First step, adding good comments and other simple items

The `hasUniqueChars.c` file has TODO comment that reinforce the instructions in 
this section. Read and implement all TODO comments. Remember
that it is good style to **remove** TODO comments once you have completed them.

Right away, modify the top-of-file comment, and the comment for `hasUniqueChars`
and any other easy TODOs.

#### Complete the function `hasUniqueChars` in `hasUniqueChars.c`

```
bool hasUniqueChars(char * inputStr)
```

This function should do the following:
- Take in an input string, `inputStr`, of any length, provided as an array of
  chars. 
    - The characters in the array could be any ASCII value.
        - Examine the file `ascii_table.txt` to see the full listing of ASCII characters and their integer equivalents. 
        - Note that the first column of characters listed in `ascii_table.txt`, as 
        well as the last character, DEL, are _non-printing characters_. See the Helpful Notes
        at the end of this README for more information about including non-printing
        characters in a string.
    - Treat individual characters as **integers** for this assignment (it is easiest!). The
    `checkInvalid` function is a good example of how to do this.

- Check if a non-printing character (is in the string, and print an error message and exit the 
  program if one occurs. The `checkInvalid` function does this for you.
- Otherwise, the function should return a `bool` (see [documentation on the C library stdbool.h](https://en.wikibooks.org/wiki/C_Programming/stdbool.h).
- The return value should be `true` if every character, ignoring spaces, only occurs once in the input string, and false otherwise.
- The space character is the only ascii character that can be repeated in the
  input string and still result in hasUniqueChars returning true.


#### Tracking unique characters

The trick to an efficient solution to the unique characters problem (one that runs
in O(n) time), is an efficient data structure for keeping track of which characters
have been seen so far, as we iterate over the characters in the string.

We will use a "bit vector" as our efficient data structure: each bit will represent 
whether or not we have seen a given ASCII character. If the bit is 0 then we have not
yet seen that specific character, and if it is 1 then we have seen it. 
We can manipulate our bit vectors with bitwise operators: 
bitwise AND (`&`), bitwise OR (`|`), bitwise XOR (`^`), and bitwise NOT (`~`)).

The bit vector will be implemented as an `unsigned long` integer, or rather two of them.
The `hasUniqueChars` function defines two variables to serve as bit vectors:

```
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 
```

We need two `unsigned long` ints, because each long int on our 64-bit Intel architectures
is 8 bytes, or 64 bits long. Thus one long can only track 64 characters, and we have 95 characters to track. Two long ints have more than enough capacity for our purposes.

As the function loops over the characters, it should:
- Determine whether the character is tracked by `checkBitsA_z` or by `checkBitsexcl_amp`
- Determine which bit in the bit vector represents this character, and use bitwise 
operations to check if the character has already been seen
    - As a part of this, you will need to create another `unsigned long` integer that is
all zeros, except that it has a 1 in the correct bit for the current character
- If so, then the current character is a duplicate, so the loop should quit early and the function return false
- Otherwise, it should use bitwise operations to set the bit to 1, as we have now seen the character once


#### Use arithmetic on `char` variables

Any `char` variable, such as the one called `nextChar` in the code, can be
treated like an integer and used in mathematical expressions in C
using + or -. Thus, you can easily determine the index into a bit vector for
each character you encounter by doing math on the character.

#### Mapping characters onto bits

For any ASCII characters whose numeric value is between 65 and 126
(inclusive), the bit vector `checkBitsA_z` can be used to mark whether a character
has been seen already. The mapping of should look like this:

|index of bit in checkBitsA_z | ascii char | char value|
|-----------------------------|------------|-----------|
|0 | A | 65 |
|1 | B | 66 |
|...|...|...|
|25| Z | 90 |
|...|...|...|
|61 | ~ | 126 |

Notice that bits 62 and 63 will not be needed. What this means is that if given
an input string "AB}", then after checking each of the three characters,
`checkBitsA_z` should look like this in binary (spaces have been added after
every 4 bits for readability):

    0001 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

Bit 0 of `checkBitsA_z` is on the right in the above depiction, and got set to 1
for the A in the input string. Bit 63 of `checkBitsA_z` is on the left (not
used, so will always stay 0).


For any So 

The other bit vector, `checkBitsexcl_amp`, can be used for the characters whose
decimal values range from 33 to 64. 
For any ASCII characters whose numeric value is between 33 and 64
(inclusive), the bit vector `checkBitsexcl_amp` can be used to mark whether a character
has been seen already. More bits of this vector will remain
unused: 32 through 63. The mapping of should look like this:

|index of bit in checkBitsexcl_amp | ascii char | char value|
|-----------------------------|------------|-----------|
|0 | ! | 33 |
|1 | " | 34 |
|...|...|...|
|31| @ | 64 |


#### Tools you may use for the function `hasUniqueChars`

- Use any of the following bitwise operators to make checks in the loop:
```
    << >> & | ~ ^
```

You will not need all of these.

- You are also free to use any other operators that work on numerical
   variables, such as `+`, `-`, `\*`, `<`, `>`.

- You may also use relational operators in if statements (`!`, `&&`, `||`).

- You might be tempted to use any functions in the C library ctype.h, but this
   strategy will likely make your code more complicated. You should just treat
   nextChar as an integral value.


### Task 3: Complete the `test.c` file

The `test.c` file has TODO comment that reinforce the instructions in 
this section. Read and implement all TODO comments. Remember
that it is good style to **remove** TODO comments once you have completed them.

Right away, modify the top-of-file comment, and any other easy TODOs.

Examine the `main` function: it includes a few sample tests of `hasUniqueChars`
to get you started. Make sure you understand how they work, and how to set up strings
(more information is in Helpful Notes below).

Complete enough tests to **fully** check your `hasUniqueChars` function (see the
rubric above). This means **complete and exhaustive** testing, using examples that should return true,
those that should return false, and those that should fail and exit the program.
**Use asserts for each test.**


## Helpful notes

### Declaring and creating strings

These examples are taken from [this C tutorial
site](http://www.crasseux.com/books/ctutorial/Initializing-strings.html), with
some additional comments and bug fixes- beware that not all examples online are
correct!

There are three examples of how to declare and initialize strings in C given in
the main() of text.c. They are:

```
  /* Example 1 */
  char string1[] = "A string declared as an array.\n";

  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";

  /* Example 3 */
  char string3[128];   // can copy in up to 127 characters
                       // chose 128 because it is a multiple of 8 bytes
  strcpy(string3, "A string constant copied in.\n");
  
  printf ("%s", string1);
  printf ("%s", string2);
  printf ("%s", string3);
  
```

What follows are an explanation of each one.

```
/* Example 1 */
  char string1[] = "A string declared as an array.\n";
```

This is often the best way to declare and initialize a string that should keep a
constant value and not change. The character array is declared explicitly. There
is no size declaration for the array; just enough memory is allocated for the
string, because the compiler knows how long the string constant is. The compiler
stores the string constant in the character array and adds a null character (\0)
to the end. This works well if you don't intend to change the string and wish to
treat it as a constant.

```
  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";
```

The second of these initializations is a pointer to an array of characters. Just
as in the first example, the compiler calculates the size of the array from the
string constant and adds a null character. The compiler then assigns a pointer
to the first character of the character array to the variable string2.

Note: Most string functions will accept strings declared in either of these two
ways. Consider the `printf` statements at the end of the example program above --
the statements to print the variables `string1` and `string2` are identical.

```
  /* Example 3 */
  char string3[128];
  strcpy(string3, "A string constant copied in.\n");
```
  
Declaring a string in this way is useful when you don't know what the string
variable will contain, but have a general idea of the length of its contents (in
this case, the string can be a maximum of 128 characters long). The drawback is
that you will either have to use some kind of string function like `strcpy` to assign the
variable a value, as the next line of code does, or you will have to assign the 
elements of the array the hard way, character by character. (See string.h library functions for more
information on the function `strcpy`.)

### Escape sequences

Some special ascii non-printing characters need to be represented in a character
string using what is called an *escape sequence*. Please read about this on the
[Wikipedia page](https://en.wikipedia.org/wiki/Escape_sequences_in_C) devoted to
describing them. 
