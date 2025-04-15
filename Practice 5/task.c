#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(void){
    while (1) {
        char *ptr = (char *)malloc(1);

        if (!ptr) {
            fprintf(stderr, "Не вдалось виділити пам'ять\n");
            return 1;
        }
    
        usleep(100);
    }
    return 0;
}