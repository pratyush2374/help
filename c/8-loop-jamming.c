#include <stdio.h>
#include <time.h>

int main()
{
    int array1[] = {10, 20, 30};
    int array2[] = {20, 10, 30};
    int array3[] = {40, 40, 10};

    clock_t t1, t2, t3;

    t1 = clock();

    for (int i = 0; i < 10000000; i++)
    {
        int sum = 0;

        for (int x = 0; x < 3; x++)
        {
            sum += array1[x];
        }

        for (int x = 0; x < 3; x++)
        {
            sum += array2[x];
        }

        for (int x = 0; x < 3; x++)
        {
            sum += array3[x];
        }

        if (sum != 210)
        {
            printf("false\n");
        }
    }

    t2 = clock();

    for (int i = 0; i < 10000000; i++)
    {
        int sum = 0;

        for (int x = 0; x < 3; x++)
        {
            sum += array1[x];
            sum += array2[x];
            sum += array3[x];
        }

        if (sum != 210)
        {
            printf("false\n");
        }
    }

    t3 = clock();

    printf("Before loop jamming: %.3f ms\n",
           (double)(t2 - t1) * 1000.0 / CLOCKS_PER_SEC);
    printf("After loop jamming: %.3f ms\n",
           (double)(t3 - t2) * 1000.0 / CLOCKS_PER_SEC);

    return 0;
}
