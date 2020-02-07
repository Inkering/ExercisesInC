/* Program for adding user inputted numbers

Written by Dieter Brehm, 2020

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* readInput(int* inputs) {
/* Function for collecting user input of numbers until
 * they 
 */

    // initialize a integer for tracking the loop
    int i;
    // initialize a char array to put user info in
    char inputRaw[8];
    for (i = 0; i < 20 + 1; i++ ) {        
        // check if number is too big or weird
        // subject one from length check for end terminator
        if (strlen(inputRaw) == 8 -1) {
            fprintf(stderr,"the number inputted is too big!");
            return 0;
        }

        // check if the array is too small 
        if (i >= 20) {
            fprintf(stderr,"too many elements aded!");
            return 0;
        }

        // check if user entered ctrl-d
        // I see here that fgets modifies the inputraw
        // array even in a check.
        if (fgets(inputRaw, 8, stdin) == NULL) {
            break;
        }

        // convert from string to int
        int val = atoi(inputRaw);

        // check if we got a valid integer
        if (val == 0 && strncmp(inputRaw, "0\n", 3)) {
            fprintf(stderr,"not a value integer!");
            return 0;
        }
        
        // put the value in the array
        inputs[i] = val;
    }
    return 0;
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

    // calculated the summation of the inputted numbers
    result = sum(inputArray, sizeof(inputArray) / sizeof(inputArray[0]));
    
    printf("the result is %d\n", result);
    return 0;
}