/*
	 dtee, pronounced dee-tee
	 A tee copy by Dieter Brehm, 2020

	 USAGE:
	 dtee -a file.txt, given a piped in stdin

	 Softsys Questions:
	 3. REFLECT

	 I think that it took awhile to wrap my head around the libraries available to
	 me. Once copious googling led me to getline, I felt as I was on the right path.
	 My first thought was to choose a fixed size for a particular line, but I wasn't
	 sure about the bounds for what people are typically pipping from one source to
	 another. C's getline function gets around this by handling dynamic allocation of
	 increased line sizes.

	 4. SOLUTION COMPARISON

	 Looking at Apple's chosen implementation, it uses more robust handling of
	 arugments with the getopt() function, allowing it to handle arbitary cases
	 without a lot of checks beyond a switch statement. It also doesn't use as
	 high level file reading commands, instead choosing to use read() and raw byte
	 numbers (8 KiB bytes at a time!)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	chunk of code for writing any found
	standard input to a given file pointer.
 */
void writeContents(FILE *fileOutput) {
  // * check file?
  // * write all of found stdin until it's NULL
  // * close the file?
  // * print the output too

	size_t len = 0;
	char *line = NULL;

	// same as size_t but it is signed (can be negative)
	ssize_t nread;

	// structure seen in getline manpage
	// use getline to find the right number of bytes to write,
	// and modify line to contain the line we want to write.
	// at each loop, we're only writing one line, so the
	// number of elements to write passed to fwrite is 1.
	// we tell fwrite to stream output to our file pointer.
  while ((nread = getline(&line, &len, stdin)) != -1) {
		printf("%s", line);
		fwrite(line, nread, 1, fileOutput);
	}
}

int main(int argc, char* argv[]) {

	FILE* toWrite;

	if (argc == 3) {
		if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "--append") == 0) {
			exit(EXIT_FAILURE);
		} else if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--append") == 0) {
			// if -a or --append passed correctly
			// open file in append mode
			toWrite = fopen(argv[2], "a");
		} else {
			// if 3 arguments but invalid third
			// TODO: is this case redundent compared to the first?
			exit(EXIT_FAILURE);
		}
	} else if ( argc == 2) {
		// if no -a flag passed,
		// open file in overwrite mode
		toWrite = fopen(argv[1], "w");
	}

	// check if the file read correctly
	if (toWrite == NULL) {
		perror("file open err: ");
		exit(EXIT_FAILURE);
	}

	// write stdin to our file
	writeContents(toWrite);

	// close the file
	fclose(toWrite);

	return 0;
}
