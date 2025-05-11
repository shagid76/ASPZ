#define _GNU_SOURCE         
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SZ   (64 * 1024)         
#define MAX_F    1024                 

struct filecnt {
    char   path[PATH_MAX];
    size_t count;
};

static struct filecnt table[MAX_F];
static size_t tsize = 0;

static struct filecnt *lookup(const char *p)
{
    for (size_t i = 0; i < tsize; ++i)
        if (strcmp(table[i].path, p) == 0) return &table[i];

    if (tsize == MAX_F) return NULL;             
    strncpy(table[tsize].path, p, PATH_MAX - 1);
    table[tsize].path[PATH_MAX - 1] = '\0';
    table[tsize].count = 0;
    return &table[tsize++];
}

static uid_t pid_owner(pid_t pid)
{
    char fn[64];
    snprintf(fn, sizeof fn, "/proc/%d/status", pid);

    FILE *fp = fopen(fn, "r");
    if (!fp) return (uid_t)-1;

    char *line = NULL;
    size_t cap = 0;
    uid_t uid = (uid_t)-1;

    while (getline(&line, &cap, fp) != -1)
        if (strncmp(line, "Uid:", 4) == 0) {      
            uid = (uid_t)strtoul(line + 5, NULL, 10);
            break;
        }
    free(line);
    fclose(fp);
    return uid;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s <dir> <threshold>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir = argv[1];
    const size_t THR = strtoul(argv[2], NULL, 10);
    if (THR == 0) { fputs("threshold must be >0\n", stderr); return EXIT_FAILURE; }

    uid_t myuid = getuid();

    int fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    if (fd < 0) { perror("inotify_init1"); return EXIT_FAILURE; }

    int wd = inotify_add_watch(fd, dir, IN_OPEN);
    if (wd < 0) { perror("inotify_add_watch"); return EXIT_FAILURE; }

    printf("permwatch: watching %s (uid=%u), threshold=%zu\n", dir, myuid, THR);

    char buf[BUF_SZ] __attribute__((aligned(__alignof__(struct inotify_event))));
    for (;;) {
        ssize_t len = read(fd, buf, sizeof buf);
        if (len < 0) {
            if (errno == EAGAIN) { usleep(10000); continue; }
            perror("read"); break;
        }

        for (char *ptr = buf; ptr < buf + len; ) {
            struct inotify_event *ev = (struct inotify_event *)ptr;
            ptr += sizeof *ev + ev->len;

            if (!(ev->mask & IN_OPEN) || (ev->mask & IN_ISDIR)) continue;

            uid_t owner = pid_owner(ev->pid);
            if (owner == (uid_t)-1 || owner == myuid) continue;     

            char path[PATH_MAX];
            snprintf(path, sizeof path, "%s/%s", dir, ev->len ? ev->name : "");
            struct filecnt *fc = lookup(path);
            if (!fc) continue;                                       

            if (++fc->count == THR) {
                struct stat st;
                if (stat(path, &st) == 0) {
                    mode_t newmode = st.st_mode | S_IRGRP | S_IROTH;
                    if (chmod(path, newmode) == 0)
                        printf("  +r for others: %s (count=%zu)\n", path, fc->count);
                    else
                        perror("chmod");
                }
            }
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}