/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT


Exercise answers:

1. Diagramming

Parent

fork ----------> child 0

fork ----------> child 1

fork ----------> child 2

Parent Hello

wait <---------- child 0 exit

child 0 exit msg

wait <---------- child 1 exit

child 1 exit msg

wait <---------- child 2 exit

child 2 exit msg

elasped time

2. Static, Heap, global sharing:

By adding a variable (which we think might be independent to each process) of
each type, and then modifying in each process, we can see if the differences compound.
cmd line printout:

Creating child 0.
Creating child 1.
Creating child 2.
Hello from child 0.
31 31 31 1Hello from the parent.
Child 12268 exited with error code 0.
Hello from child 1.
31 31 31 1Child 12269 exited with error code 1.
Hello from child 2.
31 31 31 1Child 12270 exited with error code 2.
Elapsed time = 2.002334 seconds.

As seen from the 4 sets of numbers shown throughout, differences do NOT compound! woo!

3. answer to rss question: the rss feed process won't reply (return) when execkle is called.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

// values for testing child behaviour
int someg = 30;

static int somes = 30;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, int* somem, int* someh)
{
    sleep(i);
    printf("Hello from child %d.\n", i);

		// change values to see if changes compound
		// across threads
		someg += 1;
		somes += 1;
		(*somem) += 1;
		(*someh) += 1;

		// print child process variables
		// we certainly expect them to be indepedendent to the processes
		printf("%d %d %d %d", someg, somes, *somem, *someh);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;
		int somem = 30;
		int* someh = malloc(sizeof(int));

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
					child_code(i, &somem, someh);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
