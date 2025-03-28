#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

#define MAX_NUM_49 7
#define MAX_NUM_36 6
#define MAX_CPU_TIME 2

int numbers_49[MAX_NUM_49];
int numbers_36[MAX_NUM_36];

void handle_sigxcpu(int signum) {
    printf("\nCPU time limit exceeded. Stopping the lottery simulation.\n");
    exit(EXIT_FAILURE);
}

void generate_unique_numbers(int *numbers, int max_num, int max_value) {
    int count = 0;
    while (count < max_num) {
        int num = rand() % max_value + 1;
        int is_unique = 1;

        for (int i = 0; i < count; i++) {
            if (numbers[i] == num) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            numbers[count] = num;
            count++;
        }
    }
}

int main() {
    signal(SIGXCPU, handle_sigxcpu);
    struct rlimit lim;
    lim.rlim_cur = MAX_CPU_TIME;
    lim.rlim_max = MAX_CPU_TIME;

    if (setrlimit(RLIMIT_CPU, &lim) != 0) {
        perror("Failed to set CPU time limit");
        return 1;
    }

    srand(time(NULL)); 

    generate_unique_numbers(numbers_49, MAX_NUM_49, 49);
    generate_unique_numbers(numbers_36, MAX_NUM_36, 36);

    printf("Lottery Numbers (7 from 49):\n");
    for (int i = 0; i < MAX_NUM_49; i++) {
        printf("%d ", numbers_49[i]);
    }
    printf("\n");

    printf("Bonus Numbers (6 from 36):\n");
    for (int i = 0; i < MAX_NUM_36; i++) {
        printf("%d ", numbers_36[i]);
    }
    printf("\n");

    return 0;
}