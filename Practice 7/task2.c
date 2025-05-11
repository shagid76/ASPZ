#define _XOPEN_SOURCE 700   
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TIME_FMT "%b %e %H:%M"

static void perms_to_string(mode_t mode, char out[11])
{
    const char *rwx = "rwx";
    out[0] = S_ISDIR(mode)  ? 'd' :
             S_ISLNK(mode)  ? 'l' :
             S_ISCHR(mode)  ? 'c' :
             S_ISBLK(mode)  ? 'b' :
             S_ISSOCK(mode) ? 's' :
             S_ISFIFO(mode) ? 'p' : '-';
    for (int i = 0; i < 9; ++i)
        out[i + 1] = (mode & (1 << (8 - i))) ? rwx[i % 3] : '-';
    if (mode & S_ISUID) out[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID) out[6] = (mode & S_IXGRP) ? 's' : 'S';
    if (mode & S_ISVTX) out[9] = (mode & S_IXOTH) ? 't' : 'T';
    out[10] = '\0';
}

int main(void)
{
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }
    struct dirent *de;
    char perm[11], timebuf[64], linktarget[PATH_MAX + 1];
    while ((de = readdir(dir))) {
        struct stat st;
        if (lstat(de->d_name, &st) == -1) {
            fprintf(stderr, "lstat(%s): %s\n", de->d_name, strerror(errno));
            continue;
        }
        perms_to_string(st.st_mode, perm);
        struct passwd *pw = getpwuid(st.st_uid);
        struct group  *gr = getgrgid(st.st_gid);
        struct tm *tm = localtime(&st.st_mtime);
        strftime(timebuf, sizeof timebuf, TIME_FMT, tm);
        printf("%s %2lu %-8s %-8s %8ld %s %s",
               perm,
               (unsigned long)st.st_nlink,
               pw ? pw->pw_name : "-",
               gr ? gr->gr_name : "-",
               (long)st.st_size,
               timebuf,
               de->d_name);
        if (S_ISLNK(st.st_mode)) {
            ssize_t n = readlink(de->d_name, linktarget, sizeof linktarget - 1);
            if (n != -1) {
                linktarget[n] = '\0';
                printf(" -> %s", linktarget);
            }
        }
        putchar('\n');
    }
    closedir(dir);
    return EXIT_SUCCESS;
}