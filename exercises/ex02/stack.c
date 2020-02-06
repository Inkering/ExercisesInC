/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

// define a constant called SIZE with value 5
#define SIZE 5

// define a function which returns an int pointer
int *foo() {
    // declare an integer and an int array of size 5
    int i;
    int array[SIZE];

    // print the address(?) of the array
    // printf("%p\n", array);

    // loop through indeces 
    for (i=0; i<SIZE; i++) {
        // put the value 42 in every index of the array
        array[i] = 42;
    }
    // wait is this the right return type.
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

// 1. exploring `stack.c`\
// The program prints the location of an array defined in foo, and also in bar. Finally, in
// main, the contents of the most recent usage of the array are printed. However, I can 
// immediately see that this isn't going to work as intended. Firstly, when the variables in 
// function foo() go out of scope, the reference to the array variable will be uttely released 
// from the stack when it goes out of scope.

// 2. Compiling stack (unmodified)\
// When compiling it, the output when run is:
//     ```
//     address of stack memory associated with local variable
//       'array' returned
//     ```
// 3. Running it\
// When running the stack program, even with warnings, it shows:
//     ```
//     0x7ffeeda1c830
//     0x7ffeeda1c830
//     0
//     48
//     -308164512
//     32766
//     -308164736
//     ```
//     Many of these values just look like random numbers from my computer's stack, particularly the large ones.

// 4. Commenting out print statements\
// When commenting out the print statements in foo() and bar(), we get:
//     ```
//     0
//     48
//     -394426272
//     32766
//     -394426496
//     ```
//     and the warning is the same as in 2.
//     Here we are only attempting to print the array contents, which is done, although the
//     data shown is pretty ridiculous, as determined before.
