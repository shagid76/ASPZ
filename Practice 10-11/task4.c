#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    int num_children = 5;
    
    for (int i = 1; i <= num_children; ++i) {
        child_pid = fork();
        
        if (child_pid == 0) {
            printf("Child process %d\n", i);
            exit(0); 
        } else if (child_pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    for (int i = 0; i < num_children; ++i) {
        wait(NULL);
    }
    
    printf("All child processes have finished.\n");
    return 0;
}