/* Program for adding user inputted numbers

Written by Dieter Brehm, 2020

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* input loop */
int* readInput(int* inputs) {
    // initialize a integer for tracking the loop
    int i;
    // initialize a char array to put user info in
    char inputRaw[8];
    for (i = 0; i < 20 + 1; i++ ) {        
        int val = atoi(inputRaw);
        // check if number is too big or weird

        // check if not a possible integer
        // atoi should return 0 if it fails
        // if (val == 0) {
        //     break;
        // }

        // check if the array is too small 
        if (i >= 20) {
            break;
        }

        // check if user entered ctrl-d
        // I see here that fgets modifies the inputraw
        // array even in a check.
        if (fgets(inputRaw, 8, stdin) == NULL) {
            break;
        }

        // put the value in the array
        inputs[i] = val;
    }
}

int sum(int* inputs, int length) {
    // https://riptutorial.com/c/example/1125/array-length indicates
    // that it is necessary to pass length seperately from the pointer to
    // the array, as sizeof won't work properly otherwise.
    // TODO: test this assumption.
    int i;
    int result = 0;
    for (i = 0; i < length; i++) {
        result += inputs[i];
    }
    return result;
} 


int main() {
    // define an array to store numbers in
    // TODO: we may need to do a copy-and-expand detection
    int inputArray[20] = {};
    int result;
    // read user input until exited by user, modifying input array
    readInput(inputArray);

    result = sum(inputArray, sizeof(inputArray) / sizeof(inputArray[0]));
    printf("the result is %d\n", result);
    return 0;
}