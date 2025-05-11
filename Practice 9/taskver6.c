#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int is_system_user(const char* home, const char* shell) {
    if (strncmp(home, "/home", 5) != 0) {
        return 1;
    }

    if (
        strcmp(shell, "/sbin/nologin") == 0 ||
        strcmp(shell, "/bin/false") == 0 ||
        strcmp(shell, "/usr/sbin/nologin") == 0 ||
        strcmp(shell, "") == 0
    ) {
        return 1;
    }

    return 0;
}

int main() {
    FILE* fp = fopen("/etc/passwd", "r");
    if (!fp) {
        perror("Не вдалося відкрити /etc/passwd");
        return 1;
    }

    char line[MAX_LINE];

    printf("%-20s %-30s %-20s %-10s\n", "Ім'я користувача", "Домашній каталог", "Shell", "Системний?");
    printf("==============================================================================================\n");

    while (fgets(line, sizeof(line), fp)) {
        char* username = strtok(line, ":");
        strtok(NULL, ":");
        strtok(NULL, ":"); 
        strtok(NULL, ":"); 
        strtok(NULL, ":");
        char* home = strtok(NULL, ":");
        char* shell = strtok(NULL, ":\n");

        if (username && home && shell) {
            int system = is_system_user(home, shell);
            printf("%-20s %-30s %-20s %-10s\n", username, home, shell, system ? "Так" : "Ні");
        }
    }

    fclose(fp);
    return 0;
}