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
