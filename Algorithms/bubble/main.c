#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

int data[SIZE] = {4, 8, 1, 6, 2, 10, 7, 3, 9, 5};

void show()
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main()
{
    int a;
    for(a = 0; a < 5; a++)
    {
        if (a == 2)
        {
            continue;
        }
        printf("%d", a);
        printf("hihi %d\n", a);
    }

    printf("\n");

    for (a = 0; a < 5; a++)
    {
        if (a == 2)
        {
            break;
        }
        printf("%d", a);
    }

    printf("\n\n\n\n\n\n");

    int i, j, n = SIZE;

    for(i = 0; i < n - 1; i++)
    {
        for(j = n - 1; j > i; --j)
        {
            if (data[j] < data[j - 1])
            {
                int tmp = data[j - 1];
                data[j - 1] = data[j];
                data[j] = tmp;
            }
        }
    }

    show();

    return 0;
}
