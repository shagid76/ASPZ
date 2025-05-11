#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 4096    

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *pattern  = argv[1];
    const char *filename = argv[2];
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return EXIT_FAILURE;
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof line, fp)) {
        if (strstr(line, pattern))
            fputs(line, stdout);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}