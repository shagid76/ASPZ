#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/user.h>
#include <errno.h>

void log_crash_info(pid_t pid, int status) {
    if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        printf("[ptrace] Process %d terminated by signal %d (%s)\n", pid, sig, strsignal(sig));
        struct user_regs_struct regs;
        if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == 0) {
            printf("RIP: 0x%llx\n", (unsigned long long)regs.rip);
            printf("RSP: 0x%llx\n", (unsigned long long)regs.rsp);
        } else {
            perror("ptrace(GETREGS)");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return 1;
    }

    pid_t child = fork();
    if (child == 0) {
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
            perror("ptrace TRACEME");
            exit(1);
        }
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    }

    int status;
    while (1) {
        waitpid(child, &status, 0);
        if (WIFEXITED(status)) {
            printf("Process %d exited normally with code %d\n", child, WEXITSTATUS(status));
            break;
        }
        if (WIFSIGNALED(status)) {
            log_crash_info(child, status);
            break;
        }
        if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            ptrace(PTRACE_CONT, child, NULL, sig);
        }
    }
    return 0;
}