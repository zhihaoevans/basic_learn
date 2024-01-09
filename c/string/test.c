#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
*/

int main(int argc, char* argv[])
{
	const char *str = "ge2/2";
	char temp_str[16];
	char *c;

	strcpy(temp_str, str);

	c = strchr(temp_str, '/');

	*(c + 1) = '0' + (atoi(c + 1) ^ 1);

	printf("%s\n", NULL);

	return 0;
}
