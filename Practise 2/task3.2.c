#include <stdio.h>
#include <stdlib.h>

int global_var = 1;         
static int static_var = 2;  
const int const_var = 3;    
int uninit_var;             

int main() {
    int local_var = 4;      /
    int *heap_var = malloc(sizeof(int)); 
    *heap_var = 5;

    printf("Text (code):         %p (main)\n", (void*)main);
    printf("Global (.data):      %p\n", (void*)&global_var);
    printf("Static (.data):      %p\n", (void*)&static_var);
    printf("Const (.rodata):     %p\n", (void*)&const_var);
    printf("Uninit (.bss):       %p\n", (void*)&uninit_var);
    printf("Local (stack):       %p\n", (void*)&local_var);
    printf("Heap (malloc):       %p\n", (void*)heap_var);

    free(heap_var);
    return 0;
}
