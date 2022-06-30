#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Lab2_header.h"
#include <string.h>
int main()
{
	double res;
	char* s = NULL;
	do {
		printf("Enter your expression:\n");
		s = get_str();
		if (s) {
			printf("Your expression:\n");
			puts(s);
			res = stack_process(s);
			printf("Result : %lf\n", res);
		}
	} while (s);
	if (!s) {
		printf("End of programm\n");
	}
	return 0;
}

