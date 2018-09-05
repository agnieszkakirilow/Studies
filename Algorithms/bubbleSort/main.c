#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

int main(void)
{
    int unsorted[SIZE] = {9, 7, 1, 3, 6, 2, 0, 4, 8, 5};
    int start;
    bool again = true;

    for(start = 0; (start < SIZE) && again; start++)
    {
        again = false;
        int i;
        for (i = SIZE - 1 ; i > start; i-- )
        {
            if (unsorted[i] < unsorted[i-1])
            {
                int tmp = unsorted[i-1];
                unsorted[i-1] = unsorted[i];
                unsorted[i] = tmp;
                again = true;
            }
        }
    }

    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", unsorted[i]);
    }

    return 0;
}

