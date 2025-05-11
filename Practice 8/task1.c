#define _GNU_SOURCE            
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define CHUNK 4096             

int main(void)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); return 1; }

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    char buf[CHUNK];
    memset(buf, 'A', sizeof buf);

    size_t total = 0;
    while (1) {
        ssize_t n = write(pipefd[1], buf, sizeof buf);
        if (n == -1) {
            if (errno == EAGAIN) break;     
            perror("write"); return 1;
        }
        total += (size_t)n;
    }
    printf("Записано у pipe до заповнення: %zu байт\n", total);

    ssize_t want   = CHUNK;
    ssize_t really = write(pipefd[1], buf, want);

    if (really == -1 && errno == EAGAIN)
        printf("Друге write(): буфер повний, записано 0 байт (EAGAIN)\n");
    else if (really >= 0 && really < want)
        printf("Друге write(): запитано %zd, записано %zd (короткий запис)\n",
               want, really);
    else
        printf("Несподіваний результат: %zd\n", really);

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}