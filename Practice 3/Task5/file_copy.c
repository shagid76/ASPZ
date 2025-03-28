#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 10 * 1024 * 1024 

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    const char *source_file = argv[1];
    const char *dest_file = argv[2];

    FILE *source = fopen(source_file, "rb");
    if (!source) {
        printf("Cannot open file %s for reading\n", source_file);
        return 1;
    }

    struct stat st;
    if (stat(source_file, &st) == 0 && st.st_size > MAX_FILE_SIZE) {
        printf("File size exceeds the limit\n");
        fclose(source);
        return 1;
    }

    FILE *dest = fopen(dest_file, "wb");
    if (!dest) {
        printf("Cannot open file %s for writing\n", dest_file);
        fclose(source);
        return 1;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            printf("Error writing to file %s\n", dest_file);
            fclose(source);
            fclose(dest);
            return 1;
        }
    }

    fclose(source);
    fclose(dest);
    printf("File copied successfully from %s to %s\n", source_file, dest_file);
    return 0;
}