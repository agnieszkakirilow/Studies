#include <stdio.h>
#include <stdbool.h>
#define SIZE 8

int mergeSort(int *tab, int begin, int end);
int merge(int *tab, int begin, int middle, int end);

int main(void)
{
    int unsorted[SIZE] = {2, 5, 1, 3, 8, 7, 6, 4};
    int begin = 0;
    int end = SIZE -1;
    printf("My unsorted tab: ");
    for(int i = 0; i <= end; i++)
    {
        printf("%d, ",unsorted[i]);
    }
    mergeSort(unsorted, begin, end);
    printf("\nMy sorted tab: ");
    for(int i = 0; i <= end; i++)
    {
        printf("%d, ",unsorted[i]);
    }
}

int mergeSort(int *tab, int begin, int end)
{
    if(end-begin > 0)
    {
        int middle = (begin + end)/2;
        mergeSort(tab, begin, middle);
        mergeSort(tab, middle + 1, end);
        merge(tab, begin, middle, end);
    }
}

int merge(int *tab, int begin, int middle, int end)
{
    int sizeLeft = middle - begin + 1;
    int sizeRight = end - middle;
    int *leftTab = (int*)malloc(sizeLeft*sizeof(int));
    int *rightTab = (int*)malloc(sizeRight*sizeof(int));

    int i = 0;
    for(i = 0; i < sizeLeft; i++)
    {
        leftTab[i] = tab[begin + i];
    }
    for(i=0; i < sizeRight; i++)
    {
        rightTab[i] = tab[middle + 1 + i];
    }

    for(i = begin; i < sizeLeft + sizeRight; i++)
    {
        tab[i] = 0;
    }

    int iLeft = 0;
    int iRight = 0;
    int iTab = 0;
    while(iLeft < sizeLeft && iRight < sizeRight  )//tab not empty
    {
        if(leftTab[iLeft] < rightTab[iRight] )
        {
            tab[begin + iTab] = leftTab[iLeft];
            iLeft ++;
        }
        else
        {
            tab[begin + iTab] = rightTab[iRight];
            iRight++;
        }
        iTab++;
    }
    while(iLeft < sizeLeft)
    {
        tab[begin + iTab] = leftTab[iLeft];
        iLeft++;
        iTab++;
    }
    while(iRight < sizeRight)
    {
        tab[begin + iTab] = rightTab[iRight];
        iRight++;
        iTab++;
    }
    free(leftTab);
    free(rightTab);
}





