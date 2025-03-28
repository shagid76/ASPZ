#include <stdio.h>

void recursive_function(int count) {
    int buffer[1000];
    printf("Recursion depth: %d\n", count);
    recursive_function(count + 1);
}

int main() {
    printf("Starting recursive function...\n");
    recursive_function(1);  
    return 0;
}