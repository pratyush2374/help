#include <stdio.h>
#include <time.h>

int main()
{
    int array1[5];

    clock_t t1, t2, t3;

    t1 = clock();

    for (int i = 0; i < 10000000; i++)
    {
        for (int x = 0; x < 5; x++)
        {
            array1[x] = x;
        }
    }

    t2 = clock();

    for (int i = 0; i < 10000000; i++)
    {
        array1[0] = 0;
        array1[1] = 1;
        array1[2] = 2;
        array1[3] = 3;
        array1[4] = 4;
    }

    t3 = clock();

    printf("Time before loop unrolling: %.3f ms\n",
           (double)(t2 - t1) * 1000.0 / CLOCKS_PER_SEC);

    printf("Time after loop unrolling: %.3f ms\n",
           (double)(t3 - t2) * 1000.0 / CLOCKS_PER_SEC);

    return 0;
}
