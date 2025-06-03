#include <stdio.h>
#include <unistd.h>

int main() {
    int seconds = 10; 

    while (seconds > 0) {
        printf("Залишилось часу: %d секунд\n", seconds);
        sleep(1);
        seconds--;
    }

    printf("Подія відбулась!\n");
    return 0;
}