#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define MEMORY_SIZE (1024 * 1024 * 10)

int main() {
    void *ptr = malloc(MEMORY_SIZE);
    if (ptr == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    if (mlock(ptr, MEMORY_SIZE) != 0) {
        perror("mlock failed");
        free(ptr);
        return 1;
    }

    printf("Successfully locked %d MB of memory.\n", MEMORY_SIZE / (1024 * 1024));
    void *ptr2 = malloc(MEMORY_SIZE);
    if (ptr2 == NULL) {
        perror("Failed to allocate memory");
        free(ptr);
        return 1;
    }

    if (mlock(ptr2, MEMORY_SIZE) != 0) {
        perror("mlock failed on second memory allocation");
    } else {
        printf("Successfully locked second block of memory.\n");
    }
    
    free(ptr);
    free(ptr2);
    return 0;
}