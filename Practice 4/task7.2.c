#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sbar {
    int id;
    char name[32];
};

int main() {
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) { perror("calloc"); return 1; }

    strcpy(ptr[0].name, "original");
    ptr[0].id = 42;

    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray");
        free(ptr);
        return 1;
    }

    printf("ID: %d, Name: %s\n", newptr[0].id, newptr[0].name);
    free(newptr);
    return 0;
}
