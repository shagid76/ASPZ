#define _XOPEN_SOURCE 700        
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int dir_filter(const struct dirent *d)
{
    if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
        return 0;                             
    if (d->d_type == DT_DIR)
        return 1;
    if (d->d_type == DT_UNKNOWN) {
        struct stat st;
        return (stat(d->d_name, &st) == 0 && S_ISDIR(st.st_mode));
    }
    return 0;
}

int main(void)
{
    struct dirent **list;
    int n = scandir(".", &list, dir_filter, alphasort); 
    if (n < 0) {
        perror("scandir");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; ++i) {
        puts(list[i]->d_name);
        free(list[i]);         
    }
    free(list);
    return EXIT_SUCCESS;
}