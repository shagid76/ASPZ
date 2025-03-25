#include <stdio.h>
#include <stdlib.h>

int main() {
    //realloc(NULL, size)
    printf("Calling realloc(NULL, 100)...\n");
    void *ptr = realloc(NULL, 100);
    if (ptr == NULL) {
        printf("realloc(NULL, 100) failed (like malloc failure)\n");
        return 1;
    } else {
        printf("realloc(NULL, 100) succeeded, ptr = %p\n", ptr);
    }

    //realloc(ptr, 0)
    printf("Calling realloc(ptr, 0)...\n");
    void *new_ptr = realloc(ptr, 0);
    if (new_ptr == NULL) {
        printf("realloc(ptr, 0) returned NULL (ptr was freed)\n");
    } else {
        printf("realloc(ptr, 0) returned non-NULL pointer: %p (still must free)\n", new_ptr);
        free(new_ptr);
    }

    return 0;
}
