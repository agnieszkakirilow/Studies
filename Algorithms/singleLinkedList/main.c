#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



struct person
{
   int age;
   char name[20];
   struct person *next;//pointer next pointing at object of type person
};

struct person *first = NULL;
struct person *last = NULL;

void append(int x, char *n);
void show();
int length();
void addAfter(struct person *current, int newAge, char *newName);
struct person* find(int x);
void removeNode(int x);
void addAtBegin(int x, char *n);

int main()
{
    append(5, "pawel");
    append(2, "adam");
    append(10, "piotr");
    append(8, "aga");
    show();
    find(15);
    find(8);
    find(5);
    find(2);
    length();
    addAfter(find(10), 30, "Marcin");
    removeNode(10);
    addAtBegin(7, "wojtek");
    show();
}

void append(int x, char *n)
{
    struct person *tmp = (struct person *)malloc(sizeof(struct person));
    tmp->next = NULL;
    tmp->age = x;
    strcpy(tmp->name, n);

    if(first == NULL)
    {
        first = last = tmp;
    }
    else
    {
        struct person *p;
        p = first;

        while(p->next != NULL)//another node is there
        {
            p = p->next; //move to next node
        }
        p->next = tmp; //add new node
    }
}

void show()
{
    struct person *tmp = first;
    while(tmp != NULL)
    {
        printf("%d, %s\n", tmp->age, tmp->name);
        tmp = tmp->next;
    }
}

struct person *find(int x)
{
    struct person *tmp = first;
    bool found = false;
    while(tmp != NULL)
    {
        if (tmp->age == x )
        {
            found = true;
            break;
        }
        tmp = tmp->next;
    }
    if (found == true)
    {
        printf("%s is %d\n", tmp->name, x);
    }
    else
    {
        printf("No one on a list is %d\n", x);
        tmp = NULL;
    }
    return tmp;
}

int length()
{
    int count = 0;
    struct person* tmp = NULL;
    tmp = first;

    while(tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    printf("There are %d items on a list\n",count);
    return count;
}

void removeNode(int x)
{
    struct person* tmp = first;
    struct person* prev = first;

    if (tmp != NULL && tmp->age == x)// If head node itself holds the key to be deleted
    {
        first = first->next;   // Change head
        free(tmp);             // tmp holds first node address
        return;
    }
    // Search for the key to be deleted, keep track of the previous node as we need to change 'prev->next'
    while (tmp != NULL && tmp->age != x)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    // If key was not present in linked list
    if (tmp == NULL)
    {
        return;
    }
    prev->next = tmp->next;    // Unlink the node from linked list

    free(tmp);  // Free memory
}

void addAfter(struct person* current, int newAge, char *newName)
{
    struct person *tmp = (struct person *)malloc(sizeof(struct person));
    tmp->age = newAge;
    strcpy(tmp->name, newName);

    tmp->next = current->next;
    current->next = tmp;
}

void addAtBegin(int x, char *n)
{
    struct person *new = (struct person *)malloc(sizeof(struct person));
    new->age = x;
    strcpy(new->name, n);

    new->next = first;
    first=new;
}
