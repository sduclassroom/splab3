#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    char *name[] = {"sh","sum01txt","log.txt",NULL};
    if (execvp(name[0], name) < 0) {
        printf("*** ERROR: exec failed\n");
        exit(1);
    }
    return 0;
}
