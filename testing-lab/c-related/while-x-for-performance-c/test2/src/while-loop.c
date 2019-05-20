#include <stdio.h>
#include <time.h>

#define NUM_REPS 1e+2
#define LOOP_SIZE 1e+10

int main() {
    unsigned long int i, j = 0;
    clock_t t;

    for (i = 0; i < NUM_REPS; i++) {
        t = clock();
        j = 0;
        while (j++ < LOOP_SIZE);
        t = clock() - t;
        
        printf("%f\n", t / (1.0 * CLOCKS_PER_SEC));
    }
}
