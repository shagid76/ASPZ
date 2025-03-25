#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    size_t gb = 1024L * 1024L * 1024L; // 1 GB
    size_t total = 0;
    size_t limit = 128;

    while (total < limit) {
        void *ptr = malloc(gb);
        if (!ptr) {
            printf("malloc failed after %zu GB\n", total);
            break;
        }

        memset(ptr, 0, gb);

        printf("Allocated %zu GB\n", total + 1);
        total++;
    }
    return 0;
}
