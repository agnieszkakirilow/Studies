#include <stdio.h>

int main()
{
    int unsorted[10] = {3,7,5,1,8,2,9,4,6,10};
    int i,j;
    int tmp;
    for(i = 1; i < 10; i++)
    {
        tmp = unsorted[i];
        j = i - 1;
        while(j >= 0 && unsorted[j] > tmp)
        {
            unsorted[j+1] = unsorted[j];
            j = j-1;
        }
        unsorted[j+1] = tmp;
    }
    for(i = 0; i <10; i++)
    {
        printf("%d", unsorted[i]);
    }
    return 0;
}
