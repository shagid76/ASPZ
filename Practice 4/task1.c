#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t low = 1;
    size_t high = (size_t)1 << 63; 
    size_t mid;
    void *ptr;

    printf("Searching for maximum allocatable memory block...\n");

    while (low < high) {
        mid = low + (high - low) / 2;

        ptr = malloc(mid);
        if (ptr) {
            free(ptr);
            low = mid + 1; 
        } else {
            high = mid; 
        }
    }

    size_t max_alloc = low - 1;
    printf("Maximum allocatable block with malloc(): %zu bytes (%.2f GB)\n",
           max_alloc, max_alloc / (1024.0 * 1024.0 * 1024.0));

    return 0;
}
