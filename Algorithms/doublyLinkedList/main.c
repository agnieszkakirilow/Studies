#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct person
{
    int age;
    char name[20];
    struct person *next;
    struct person *prev;
};

struct person *first = NULL;
struct person *next = NULL;
struct person *prev = NULL;
struct person *last = NULL;

void append(int a, char *n);
void show();
struct person *find(int a);
void removeNode(int a);
void reverseShow();


int main()
{
    append(10, "Marek");
    append(15, "Jarek");
    append(17, "Krystek");
    append(12, "Igor");
    show();
    removeNode(17);
    show();
    append(13, "Wicio");
    append(6, "Ania");
    reverseShow();
}

void append(int a, char *n)
{
   struct person *tmp = (struct person*)malloc(sizeof(struct person));
   tmp->next = tmp->prev = NULL;
   tmp->age = a;
   strcpy(tmp->name, n);

   if(first == NULL)
   {
       first = last = tmp;
   }
   else
   {
       tmp->prev = last;
       last->next = tmp;
       last = tmp;
       last->next = NULL;
   }

}

void show()
{
   struct person *tmp = first;
   printf("age      name\n");
   while(tmp != NULL)
   {
       printf("%3d%10s\n",tmp->age, tmp->name);
       tmp = tmp->next;
   }
}

struct person *find(int a/*count*/)
{
   struct person *tmp = first;
   bool found = false;
   while(tmp->next != NULL)
   {
       if(tmp->age = a)
       {
           found = true;
           break;
       }
       tmp = tmp->next;
       if(found)
       {
           printf("%s is %d\n", tmp->name, a);
       }
       else
       {
           printf("No one on a list is %d\n", a);
           tmp = NULL;
       }
       return tmp;
   }
}

void removeNode(int a)
{
    struct person *tmp = first;
    struct person *prev = first;
    if (tmp != NULL && tmp->age == a)
    {
        first = first->next;
        first->prev = NULL;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->age != a)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        return;
    }
    prev->next = tmp->next;
    tmp->next->prev = prev;
    free(tmp);
}

void reverseShow()
{
   struct person *tmp = last;
   printf("age      name\n");
   while (tmp != NULL)
   {
       printf("%3d%10s\n",tmp->age, tmp->name);
       tmp = tmp->prev;
   }
}
