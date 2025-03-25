#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t initial_size = 1024;
    void *ptr = malloc(initial_size);
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    strcpy(ptr, "hello");
    printf("Before realloc: %s\n", (char *)ptr);

 
    size_t huge_size = (size_t)1 << 62;


    // ptr = realloc(ptr, huge_size);  // Небезпечно

    void *tmp = realloc(ptr, huge_size);
    if (!tmp) {
        printf("realloc failed! Keeping original pointer.\n");
        free(ptr); 
        return 1;
    }

    ptr = tmp; 
    printf("Realloc succeeded\n");

    free(ptr);
    return 0;
}
