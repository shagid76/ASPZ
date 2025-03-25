#include <stdio.h>

int counter = 0;

void recurse() {
    counter++;
    recurse();
}

int main() {
    recurse();
    return 0;
}	
