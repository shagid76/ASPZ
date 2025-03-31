#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

#define MAX_ROLLS 1000
#define FILE_NAME "dice_rolls.txt"
#define MAX_FILE_SIZE 1024 * 1024  

void handle_sigxfsz(int signum) {
    printf("File size limit reached. Stopping write operation.\n");
    exit(EXIT_FAILURE);
}

int main() {
    signal(SIGXFSZ, handle_sigxfsz);

    struct rlimit lim;

    if (getrlimit(RLIMIT_FSIZE, &lim) != 0) {
        perror("Failed to get file size limit");
        return 1;
    }

    printf("Current file size limit: soft = %ld, hard = %ld\n",
           (long)lim.rlim_cur, (long)lim.rlim_max);

    lim.rlim_cur = MAX_FILE_SIZE;
    if (setrlimit(RLIMIT_FSIZE, &lim) != 0) {
        perror("Failed to set file size limit");
        return 1;
    }

    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("Cannot open file");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < MAX_ROLLS; i++) {
        int diceThrow = (rand() % 6) + 1;
        fseek(file, 0, SEEK_END); 
        long file_size = ftell(file);

        if (file_size >= MAX_FILE_SIZE) {
            printf("File size exceeded maximum limit. Stopping write operation.\n");
            break;
        }

        fprintf(file, "Throw %d: %d\n", i + 1, diceThrow);
    }

    fclose(file);

    return 0;
}