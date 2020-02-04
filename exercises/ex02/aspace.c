/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void printLocal() 
{
    int var3 = 5;
    printf("Address of var3 (new local) is %p\n", &var3);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    char *s = "Hello, World";

   

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);

    void *m = malloc(128);
    printf ("m points to %p\n", m);

    printLocal();

    void *n1 = malloc(21);
    void *n2 = malloc(21);

    printf ("21 byte n1 points to %p\n", n1);
    printf ("21 byte n2 points to %p\n", n2);

    return 0;
}
