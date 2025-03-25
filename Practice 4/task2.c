#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
    int xa = 100000;
    int xb = 100000; 

    int num = xa * xb;
    printf("num = %d\n", num);

    void* ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc failed\n");
    } else {
        printf("malloc succeeded: allocated %d bytes\n", num);
        free(ptr);
    }

    xa = INT_MAX;
    xb = 4; 

    num = xa * xb;
    printf("num (overflowed) = %d\n", num);

    ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc failed after overflow\n");
    } else {
        printf("malloc succeeded: allocated %d bytes (unexpected!)\n", num);
        free(ptr);
    }

    return 0;
}
