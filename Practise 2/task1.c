#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));

    time_t max = (time_t)((1ULL << (sizeof(time_t) * 8 - 1)) - 1);
    printf("Максимальне значення time_t: %lld\n", (long long)max);

    char *time_str = ctime(&max);
    if (time_str == NULL) {
        printf("ctime() повернула NULL (некоректне значення часу)\n");
    } else {
        printf("time_t переповниться: %s", time_str);
    }
    return 0;
}
