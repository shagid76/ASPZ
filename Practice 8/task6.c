#define _GNU_SOURCE         
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static void child_loop(int fd, int loops)
{
    char buf[64];
    pid_t me = getpid();

    for (int i = 0; i < loops; ++i) {
        int len = snprintf(buf, sizeof buf, "%d.%d\n", (int)me, i);
        lseek(fd, 0, SEEK_END);
        if (write(fd, buf, len) != len) {
            perror("write");
            _exit(1);
        }
    }
    _exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 4 ||
       !(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-n") == 0)) {
        fprintf(stderr,
                "Використання: %s [-a|-n] <Nproc> <Loops>\n"
                "   -a  O_APPEND  (коректно)\n"
                "   -n  NO_APPEND (можливе взаємне змішання)\n",
                argv[0]);
        return 1;
    }

    int use_append = (strcmp(argv[1], "-a") == 0);
    int N          = atoi(argv[2]);     
    int loops      = atoi(argv[3]);     

    unlink("out.txt");                   

    int flags = O_WRONLY | O_CREAT | (use_append ? O_APPEND : 0);
    int fd = open("out.txt", flags, 0644);
    if (fd == -1) { perror("open"); return 1; }

    printf("PID parent = %d  (%s)\n", (int)getpid(),
           use_append ? "O_APPEND" : "NO_APPEND");
    for (int p = 0; p < N; ++p)
        if (fork() == 0)
            child_loop(fd, loops);

    while (wait(NULL) > 0);

    close(fd);
    puts("Запис завершено. Перевіряємо файл…");

    FILE *fp = fopen("out.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    char *line = NULL; size_t cap = 0; long long bad = 0, total = 0;
    while (getline(&line, &cap, fp) != -1) {
        ++total;
        if (strchr(line, '\n') == NULL) ++bad;    
    }
    free(line); fclose(fp);

    printf("Всього рядків: %lld, пошкоджених: %lld\n",
           total, bad);
    puts("Перегляньте out.txt, щоб побачити змішані/подвоєні фрагменти.");
    return 0;
}