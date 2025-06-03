#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid = wait(&status);

    if (WIFEXITED(status)) {
        printf("Exited with code %d\n", WEXITSTATUS(status));
    }

    return 0;
}