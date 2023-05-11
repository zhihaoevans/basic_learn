#include <unistd.h>

int main(void) {
    execl("/bin/ls", "ls", NULL);
    return 0;
}
