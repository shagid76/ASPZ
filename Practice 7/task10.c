#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DEFAULT_COUNT 10          

static double rnd01(void)
{
    return (double)rand() / (double)RAND_MAX;
}

static double rnd0n(double n)
{
    return rnd01() * n;
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));    
    double n        = 1.0;         
    int    how_many = DEFAULT_COUNT;

    if (argc >= 2) {
        n = atof(argv[1]);         
        if (n <= 0.0) {
            fprintf(stderr, "n має бути > 0\n");
            return EXIT_FAILURE;
        }
    }
    if (argc >= 3) {
        how_many = atoi(argv[2]);   
        if (how_many <= 0) {
            fprintf(stderr, "кількість має бути > 0\n");
            return EXIT_FAILURE;
        }
    }
    for (int i = 0; i < how_many; ++i) {
        double x = (n == 1.0) ? rnd01() : rnd0n(n);
        printf("%f\n", x);
    }

    return EXIT_SUCCESS;
}