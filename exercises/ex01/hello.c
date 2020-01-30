#include <stdio.h>

int main() {
	int x = 5;
	int y = x + 1;
	printf("Hello, World!%i\n", y);
	return 0;
}


/* Comments on experimentation and optimization
	 1. Adding X
	 Adding x adds the lines
	 
	15 | movl	$5, -8(%rbp)
	20 | movl	%eax, -12(%rbp) ## 4-byte spill (increased)

	to the output assembly compared to the assembly
	output without the integer. I think that the added
	line 15, the movl $5 -8(%rbp), is the equivalent of
	the `int x = 5` line.

	2. Optimizated with O2

	Adding the optimization flag removes a lot from the
	original assembly output, and furthermore, doesn't include
	an indication of the integer x line at all. So I think it 
	realized it exists and removed it!

	3a. Printing X (unoptimized)

	comparing the printing of x versus just adding it in an 
	unoptimized setting, the lines of interest are:

	16 | movl	-8(%rbp), %esi
	20 | xorl	%esi, %esi
	22 | movl	%esi, %eax

	instead of using the item %ecx, it is replaced with %eci.

	3b. Printing X (optimized)

	Optimizing that sequence does as above in 2., but this time, 
	because it is actually used, the int x representation remains.
	This time, only the movl utilizes the %esi text, and the other %'s 
	use %eax.

	4a. Printing y (unoptimized)

	When adding one to x and assigning it to y, then printing that,
	we see the following changes:

	17 | addl	$1, %eax
	18 | movl	%eax, -12(%rbp)
	19 | movl	-12(%rbp), %esi

	addl is presumably the assembly instruction for adding numbers. 
	I think that the movl lines perform the assignment to y.

	4b. Printing y (optimized)

	It performs the previously made optimizations common to all
	the iterations of the program, and notably, skips the addition step,
	and goes straight to 6 instead of having 5 and adding 1 to it and 
	performing a new assignment.
 */
