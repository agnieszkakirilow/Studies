#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <string.h>

#define STACK_SIZE 5

typedef struct Stack
{
    int top;
    int buffer[STACK_SIZE];
} Stack;

sem_t semProducer;
sem_t semConsumer;

void* sharedMemory(int size)
{
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;
    return mmap(NULL, size, protection, visibility, 0, 0);
}

int push_pop(int val, Stack* stack)
{
    if (stack->top == STACK_SIZE)
    {
        return -1;
    }
    else
    {
        stack->top++;
        stack->buffer[stack->top] = val;
    }
    return 1;
}

int pop_front(Stack* stack)
{
    if (stack->top == -1)
    {
        return -1;
    }
    else
    {
        printf("%d\n", stack->buffer[stack->top]);
        stack->top--;
    }
    return 1;
}

void producer(void* shmem)
{
    Stack stack;
    for(int i = 1; i < 10; i++)
    {
        printf("producer\n");
        sem_wait(&semProducer);
        memcpy(&stack, shmem, sizeof(stack));
        if (push_pop(i, &stack) == -1)
        {
            printf("stack is full\n");
        }
        memcpy(shmem, &stack, sizeof(stack));
        printf("producer end\n");
        sem_post(&semConsumer);
    }
}

void consumer(void* shmem)
{
    Stack stack;
    for(int i = 1; i < 10; i++)
    {
        printf("consumer\n");
        sem_wait(&semConsumer);
        memcpy(&stack, shmem, sizeof(stack));
        if (pop_front(&stack) == -1)
        {
            printf("stack is empty\n");
        }
        memcpy(shmem, &stack, sizeof(stack));
        printf("consumer end\n");
        sem_post(&semProducer);
    }
}

int main(int argc, char** argv) 
{
    sem_init(&semProducer, true, 1);
    sem_init(&semConsumer, true, 0);
    
    Stack stack;
    stack.top = -1;
    
    void* sharedMem = sharedMemory(sizeof(stack));
    
    memcpy(sharedMem, &stack, sizeof(stack));
    
    int pid = fork();
    
    if(pid == 0)
    {
        producer(sharedMem);
    }
    else
    {
        consumer(sharedMem);
    }

    return (EXIT_SUCCESS);
}

