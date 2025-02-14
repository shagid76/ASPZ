#include <stdio.h>

void secondsToTime(int seconds){
      int inputValue = seconds; 
      int hours = seconds / 3600;
      seconds %= 3600;
      int minutes = seconds / 60;
      seconds %= 60;
      if (hours < 0 || minutes < 0 || seconds < 0) {
        printf("%d секунд еквівалентно %d годинам %d хвилинам %d секундам.\n", inputValue, hours, minutes, seconds);
    } else {
        printf("%d секунд еквівалентно %d годинам %d хвилинам %d секундам.\n", inputValue, hours, minutes, seconds);
    }
    }

int main(){
    int seconds;
    printf("Введіть кількість секунд ");
    scanf("%d", &seconds);
    secondsToTime(seconds);
    return 0;
}
