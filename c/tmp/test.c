#include <stdio.h>

//test comment
int main(int argc, char* argv[])
  {
	int ffd;
	(void)ffd;  // Suppress unused warning
	(void)argc; // Suppress unused warning
	(void)argv; // Suppress unused warning
    printf("Hello, world!\n");
    return 0;
  }
