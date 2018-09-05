#include <stdio.h>
#define CAPACITY 5

int stack[CAPACITY];
int top = -1;
int push_pop(int element);
int pop_front();
void traverse();

int main()
{
    pop_front();
    push_pop(3);
    push_pop(4);
    push_pop(6);
    push_pop(2);
    push_pop(8);
    push_pop(9);
    pop_front();
    push_pop(9);
    traverse();
    return 0;
}

int push_pop(int element)
{
    if(top == CAPACITY -1)
    {
        printf("Stack is full. You cannot add %d\n", element);
        return -1;
    }
    else
    {
        top++;
        stack[top] = element;
        printf("Element %d added - top is %d\n", element, top);
        return 0;
    }
}

int pop_front()
{
    int element;
    if(top == -1)
    {
        printf("Stack is empty. You cannot pop.\n");
        return -1;
    }
    else
    {
        element = stack[top];
        top--;
        printf("Element %d deleted - top is %d\n", element, top);
        return 0;
    }
}

void traverse()
{
    int i;
    if(top == -1)
    {
        printf("No elements to display\n");
    }
    else
    {
        printf("Stack elements are:");
        for(i = 0; i <= top; i++)
        {
            printf("%d  ",stack[i]);
        }
    }
}
