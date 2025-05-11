#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char  buf[4096];              
    size_t n;                   
    FILE *from_rwho = popen("rwho", "r");
    if (!from_rwho) {
        perror("popen(rwho)");
        return EXIT_FAILURE;
    }

    FILE *to_more  = popen("more", "w");
    if (!to_more) {
        perror("popen(more)");
        pclose(from_rwho);
        return EXIT_FAILURE;
    }

    while ((n = fread(buf, 1, sizeof(buf), from_rwho)) > 0) {
        if (fwrite(buf, 1, n, to_more) != n) {
            perror("fwrite → more");
            break;
        }
    }

    pclose(from_rwho);
    pclose(to_more);
    return EXIT_SUCCESS;
}