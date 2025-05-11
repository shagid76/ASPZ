#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PAGE_LINES 20           

static void page_stream(FILE *fp, const char *name)
{
    char   *line = NULL;
    size_t  cap  = 0;
    ssize_t nread;
    unsigned long lines_out = 0;
    while ((nread = getline(&line, &cap, fp)) != -1) {
        fwrite(line, 1, (size_t)nread, stdout);
        ++lines_out;
        if (lines_out % PAGE_LINES == 0) {
            fputs("--More--", stdout);
            fflush(stdout);

            int c = getchar();
            (void)c;              
            fputs("\r        \r", stdout);
        }
    }
    free(line);
    if (ferror(fp))
        fprintf(stderr, "mymore: read error on %s: %s\n",
                name, strerror(errno));
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [file ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        const char *fname = argv[i];
        FILE *fp = (strcmp(fname, "-") == 0) ? stdin : fopen(fname, "r");
        if (!fp) {
            fprintf(stderr, "mymore: cannot open %s: %s\n",
                    fname, strerror(errno));
            continue;                  
        }
        page_stream(fp, fname);

        if (fp != stdin)
            fclose(fp);
    }
    return EXIT_SUCCESS;
}