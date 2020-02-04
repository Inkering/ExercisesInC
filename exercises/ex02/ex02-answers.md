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