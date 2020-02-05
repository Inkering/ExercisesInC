# Exercise 2 Answers

*2-3-20 Dieter Brehm*

## The Address Space
1. aspace output
when I compile aspace, the outpt on the terminal is:

    ```bash
    Address of main is 0x1057dfe60
    Address of var1 is 0x1057e1018
    Address of var2 is 0x7ffeea4207e8
    p points to 0x7f8971c01800
    s points to 0x1057dff3c
    ```

2. malloc research and reading aspace\
From the tutorialspoint article, malloc seems to allow us to dedicate
a certain space of memory (which we can choose the length of), and then
gives us a pointer to that space. I think that it would be pretty
important to free this data when we no longer need it, because we lose
the concept of scoping when we use this as far as I understand it.  
\
From reading through the aspace code, I see that it assigns 5 to the variable
var2, makes a pointer to 128 bytes of space, and a char array that says hello
world. Then it prints the memory addresses of each object, and where the pointers
point to.

3. The virtual address space\
-------------  STACK  -------------  
\
the char array "Hello, World"  
the pointer s which points to the char array memory
the pointer p which points to the malloc'd heap memory
\
--------------  HEAP  -------------  
\
where p points to, the malloc.
\
------------  GLOBALS  ------------  
\
var1  
main
\
-----------  CONSTANTS  -----------
\
\
--------------  CODE  -------------
\
the code is in here!

4. heap growth tests\
Adding another malloc of the same size, the heap addresses grow up.

    ```bash
    p points to 0x7fc898401800
    m points to 0x7fc898401880
    ```

5. local growth tests\
The address differences are
\
    ```bash
    Address of var2 is 0x7ffee8bd77b8
    Address of var3 (new local) is 0x7ffee8bd776c
    ```
    In decimal,  
    ```
    var2: 140732803151800
    var3: 140732803151724
    ```
    it grows down!

6. randomly chosen size allocation\
Making two allocations of a randomly chosen byte size. n1 was created first, n2 second

    ```bash
    21 byte n1 points to 0x7ff035c01900
    21 byte n2 points to 0x7ff035c01920
    ```
    in decimal this is:
    ```
    n1: 140669670660352
    n2: 140669670660384
        --------------- -
    res:            -32
    res in hex:     -20
    ```

## Stack Allocated data

1. exploring `stack.c`\
The program prints the location of an array defined in foo, and also in bar. Finally, in
main, the contents of the most recent usage of the array are printed. However, I can 
immediately see that this isn't going to work as intended. Firstly, when the variables in 
function foo() go out of scope, the reference to the array variable will be uttely released 
from the stack when it goes out of scope.

2. Compiling stack (unmodified)\
When compiling it, the output when run is:
    ```
    address of stack memory associated with local variable
      'array' returned
    ```
3. Running it\
When running the stack program, even with warnings, it shows:
    ```
    0x7ffeeda1c830
    0x7ffeeda1c830
    0
    48
    -308164512
    32766
    -308164736
    ```
    Many of these values just look like random numbers from my computer's stack, particularly the large ones.

4. Commenting out print statements\
When commenting out the print statements in foo() and bar(), we get:
    ```
    0
    48
    -394426272
    32766
    -394426496
    ```
    and the warning is the same as in 2.
    Here we are only attempting to print the array contents, which is done, although the
    data shown is pretty ridiculous, as determined before.

5. Comments in the file.\
Okay! Moved to the stack file!