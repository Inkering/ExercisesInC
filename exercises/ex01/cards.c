/*
 * A program for card counting.
 * Initially sourced from the Head First C text book
 * Added to and improved by Dieter Brehm
 */
#include <stdio.h>
#include <stdlib.h>

/* input_card function
	 taking an array of characters, parse the value of a card based on the
	 first character and turn the value to iterate our card count by
	 based on our card counting rules
*/
int input_card(char * card_name) {
	int val = 0;
	switch (card_name[0]) {
	case 'K':
	case 'Q':
	case 'J':
		val = 10;
		break;
	case 'A':
		val = 11;
		break;
	default:
		val = atoi(card_name);
		if ((val < 1) || (val > 10)) {
			puts("I don't understand that value!");
			return 0;
			/* continue; */
		}
	}
	return val;
}

/* increment_count function
	 take the current count and new card value as integers
	 and return the incremented count according to our
	 defined rules
*/
int increment_count(int val, int count) {
	if ((val > 2) && (val < 7)) {
		count++;
	} else if (val == 10) {
		count--;
	}
	return count;
}

/* Execute the program */
int main()
{
	char card_name[3];
	int count = 0;
	while (card_name[0] != 'X') {
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		if (card_name[0] == 'X') {
			continue;
		}
		int val = input_card(card_name);
		int count = increment_count(val, count);
		printf("Current count: %i\n", count);
	}
	return 0;
}
