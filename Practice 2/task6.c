#include <stdio.h>
#include <stdlib.h>

static size_t recursion_depth = 0;

void test_recurse(void) {
    int local_var = 0;
    recursion_depth++;
    printf("Depth: %zu, address of local_var: %p\n",
           recursion_depth, (void*)&local_var);
    test_recurse();
}

int main(void) {
    test_recurse();
    return 0;
}