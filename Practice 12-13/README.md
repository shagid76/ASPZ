# Практична робота №12-13 
# Звіт
# Завдання (6 варіант)
Розробіть програму, яка замінює стандартний механізм логування ядра при падінні процесу, використовуючи ptrace для збирання розширеної інформації.
# Реалізація
Ця програма створює дочірній процес за допомогою fork, у якому виконується передана користувачем програма з використанням execvp, а також активується режим трасування ptrace через PTRACE_TRACEME. Батьківський процес очікує на зміну стану дитини за допомогою waitpid у циклі. Якщо дитина завершилася нормально, програма виводить код її завершення і завершує роботу. Якщо дитина отримала сигнал, наприклад, при падінні, програма визначає тип сигналу і за допомогою ptrace отримує значення регістрів процесора, зокрема RIP і RSP, які виводить на екран для детальної діагностики. Якщо дитина зупинилася через сигнал, батьківський процес передає цей сигнал назад дитині, продовжуючи її виконання. Таким чином, програма замінює стандартний лог падіння процесу, надаючи розширену інформацію за допомогою ptrace, що дозволяє краще аналізувати причини аварій і внутрішній стан процесу в момент його зупинки.
# Ключові частини коду:
Використання ptrace(PTRACE_TRACEME) в дочірньому процесі
```bash
if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
    perror("ptrace TRACEME");
    exit(1);
}
```
Дозволяє батьківському процесу контролювати дочірній. Обов’язковий виклик перед execvp().

Запуск цільової програми
```bash
execvp(argv[1], &argv[1]);
```
Виконує передану користувачем програму для відстеження. Якщо execvp не спрацює — програма завершується з помилкою.

Основний цикл очікування і контролю за процесом
```bash
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
```
Контролює життєвий цикл дочірнього процесу. Реагує на зупинки, сигнали і завершення.

Функція логування при аварійному завершенні
```bash
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
```
Виводить сигнал, яким завершився процес, і регістри процесора (інструкція та стек).
# Успішний запуск
```bash
yarik@FreeBSD:~/ASPZ/Practice 12-13 $ gcc -Wall task1.c -o task1
yarik@FreeBSD:~/ASPZ/Practice 12-13 $ ./task1
Process 12346 exited normally with code 0
```

# Запуск з помилкою(segmentation fault) 
```bash
yarik@FreeBSD:~/Practice 12-13 $ gcc -Wall task1.c -o task1
yarik@FreeBSD:~/Practice 12-13 $ ./task1 ./crasher
[ptrace] Process 12345 terminated by signal 11 (Segmentation fault)
RIP: 0x4006a3
RSP: 0x7ffd8e1b9c28
```
