#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void die(const char *msg) { perror(msg); exit(EXIT_FAILURE); }

static void drop_to(uid_t uid)
{
    if (seteuid(uid) == -1) die("seteuid");
}

static int can_open(const char *path, int flags)
{
    int fd = open(path, flags);
    if (fd == -1) return 0;
    close(fd);
    return 1;
}

int main(void)
{
    char *sudo_uid_s = getenv("SUDO_UID");
    char *sudo_gid_s = getenv("SUDO_GID");
    if (!sudo_uid_s || !sudo_gid_s) {
        fprintf(stderr,
                "Запустіть програму через sudo, щоб мати root-привілеї "
                "і знати UID звичайного користувача.\n");
        return EXIT_FAILURE;
    }
    uid_t user_uid = (uid_t)strtoul(sudo_uid_s, NULL, 10);
    gid_t user_gid = (gid_t)strtoul(sudo_gid_s, NULL, 10);

    char tmpl[] = "/tmp/demo.XXXXXX";
    drop_to(user_uid);                        
    int tmpfd = mkstemp(tmpl);
    if (tmpfd == -1) die("mkstemp");
    const char *msg = "hello\n";
    write(tmpfd, msg, strlen(msg));
    close(tmpfd);
    printf("Створено файл: %s  (власник = UID %u)\n\n",
           tmpl, (unsigned)user_uid);

    struct scenario {
        const char *label;
        uid_t owner;
        gid_t group;
        mode_t mode;
    } cases[] = {
        { "own 600",             user_uid, user_gid, 0600 },
        { "own 644",             user_uid, user_gid, 0644 },
        { "own 666",             user_uid, user_gid, 0666 },
        { "root 600",            0,        0,        0600 },
        { "root 644",            0,        0,        0644 },
        { "root 666",            0,        0,        0666 },
        { "root 004 (o+r)",      0,        0,        0004 },
        { "root 006 (o+rw)",     0,        0,        0006 },
    };

    const size_t N = sizeof(cases) / sizeof(cases[0]);

    printf("%-12s │ %-13s │ %-4s │ %-4s\n",
           "Сценарій", "chmod / chown", "read", "write");
    puts("─────────────┼───────────────┼──────┼──────");

    for (size_t i = 0; i < N; ++i) {
        drop_to(0);                                   
        if (chown(tmpl, cases[i].owner, cases[i].group) == -1)
            die("chown");
        if (chmod(tmpl, cases[i].mode) == -1)
            die("chmod");

        drop_to(user_uid);

        int r_ok = can_open(tmpl, O_RDONLY);
        int w_ok = can_open(tmpl, O_WRONLY | O_APPEND);

        drop_to(0);                                  

        printf("%-12s │ %04o %-7s │  %-3s │  %-3s\n",
               cases[i].label,
               cases[i].mode,
               (cases[i].owner == 0) ? "(root)" : "(own)",
               r_ok ? "yes" : "no",
               w_ok ? "yes" : "no");
    }
    unlink(tmpl);
    return EXIT_SUCCESS;
}