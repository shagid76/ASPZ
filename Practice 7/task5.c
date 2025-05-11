#define _XOPEN_SOURCE 700    
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void list_dir(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "listtree: %s: %s\n", path, strerror(errno));
        return;
    }

    struct dirent *de;
    char  buf[PATH_MAX];

    while ((de = readdir(dir))) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        snprintf(buf, sizeof buf, "%s/%s", path, de->d_name);
        puts(buf);
        struct stat st;
        if (stat(buf, &st) == 0 && S_ISDIR(st.st_mode))
            list_dir(buf);
    }
    closedir(dir);
}

int main(void)
{
    list_dir(".");  
    return EXIT_SUCCESS;
}