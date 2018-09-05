#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct tree
{
   int data;
   struct tree *left;
   struct tree *right;
};

struct tree *root = NULL;


void insert(int x);
void delete(int x);
void show(struct tree *current);
void delCur(struct tree *current);

int main()
{
    insert(30);
    insert(20);
    insert(40);
    insert(10);
    insert(25);
    insert(32);
    insert(50);
    insert(5);
    insert(12);
    insert(22);
    insert(28);
    insert(29);
    insert(31);
    insert(35);
    insert(45);
    insert(55);
    show(root);
    printf("\n\n\n");
    delete(30);
    show(root);
}

void insert(int x)
{
    struct tree *tmp = (struct tree *)malloc(sizeof(struct tree));
    tmp->right = NULL;
    tmp->left = NULL;
    tmp->data = x;
    struct tree *parent = root;

    if(root == NULL)
    {
        root = tmp;
    }
    else
    {
        struct tree *current = root;
        while(current != NULL)//is not pointing to null
        {
            parent = current;
            if(tmp->data > current->data)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        if(tmp->data > parent->data)
        {
            parent->right = tmp;
        }
        else
        {
            parent->left = tmp;
        }
    }

}


void delete(int x)
{
    struct tree* current = root;
    struct tree *parent = NULL;
    struct tree *tmp;
    while(current)
    {
        if(current->data == x)
        {
            break;
        }
        parent = current;
        if(parent->data > x)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
     }

     if(current)
     {
       if(current->left == NULL && current->right == NULL)//no children
       {
           if(current == parent->right)
           {
               parent->right = NULL;
           }
           else
           {
               parent->left = NULL;
           }
           free(current);
       }
       else if(current->left != NULL && current->right == NULL)//one left child
       {
           if(parent->right == current)
           {
               parent->right = current->left;
           }
           else
           {
               parent->left = current->left;
           }
           free(current);
       }
       else if(current->left == NULL && current->right != NULL)//one right child
       {
           if(parent->right == current)
           {
               parent->right = current->right;
           }
           else
           {
               parent->right = current->right;
           }
           free(current);
       }
       else if(current->left != NULL && current->right != NULL)//two children
       {
           parent = current;
           tmp = current->right;
           while(tmp->left)
           {
               parent = tmp;
               tmp = tmp->left;
           }
            current->data = tmp->data;
            if(parent == current)
            {
                 parent->right = tmp->right;
            }
            else
            {
                parent->left = tmp->right;
            }
            free(tmp);
           }
     }
}

void show(struct tree *cur)
{
    if(cur->left)
    {
        show(cur->left);
    }
    printf("%d\n",cur->data);
    if(cur->right)
    {
        show(cur->right);
    }
}


