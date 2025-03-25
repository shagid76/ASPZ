#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = NULL;
    int count = 3;

    while (count--) {
        if (!ptr) {
            ptr = malloc(10);
            if (!ptr) {
                perror("malloc");
                exit(1);
            }
        }

        strcpy(ptr, "hello");
        printf("ptr: %s\n", (char *)ptr);

        free(ptr);
        ptr = NULL; 
    }
    return 0;
}
