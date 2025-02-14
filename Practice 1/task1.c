#include <stdio.h>

void secondsToTime(int seconds){
      int hours = seconds / 3600;
      seconds %= 3600;
      int minutes = seconds / 60;
      seconds %= 60;
      printf("%d hours %d minutes %d seconds", hours, minutes, seconds);
    }

int main(){
    int inputSeconds;
    printf("Input seconds number ");
    scanf("%d", &inputSeconds);
    secondsToTime(inputSeconds);
    return 0;
}

