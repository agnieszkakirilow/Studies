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
void show(struct tree* cur, struct tree* parent, int level, char side);
void delCur(struct tree *current, struct tree *parent);

int main()
{
    insert(30);
    insert(20);
    insert(40);
    insert(10);
    insert(25);
    insert(32);
    insert(50);

    show(root, 0, 1, 'o');
    printf("\n\n\n");

    printf("delete 10\n");
    delete(10);
    show(root, 0, 1, 'o');
    printf("\n\n\n");

    printf("insert 10\n");
    insert(10);
    show(root, 0, 1, 'o');
    printf("\n\n\n");

    printf("delete 20\n");
    delete(20);
    show(root, 0, 1, 'o');
    printf("\n\n\n");
}

void insert(int x)
{
    struct tree *tmp = (struct tree *)malloc(sizeof(struct tree));
    tmp->right = NULL;
    tmp->left = NULL;
    tmp->data = x;
    struct tree* parent = root;

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

void delCur(struct tree *current, struct tree *parent)
{
    struct tree* tmp = current;

    if(current->right == NULL)//no right child
    {
        current=current->left;
    }
    else if(current->left == NULL)//no left child
    {
        current = current->right;
    }
    else//children present
    {
        tmp = current->left;

        while(tmp->right)
        {
            parent = tmp;
            tmp = tmp->right;
        }
        current->data = tmp->data;
        if(parent = current)
        {
            parent->left = tmp->left;
        }
        else
        {
            parent->right = tmp->left;
        }
    }
    printf("free\n");
    if(parent->left == tmp)
    {
        parent->left = NULL;
    }
    else
    {
        parent->right = NULL;
    }
    free(tmp);
}
void delete(int x)
{
    struct tree* current = root;
    struct tree* parent = NULL;

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
        delCur(current, parent);
    }
}

void show(struct tree *cur, struct tree *parent, int level, char side)
{
    if(cur->left)
    {
        show(cur->left, cur, level+1, 'l');
    }
    if(parent != 0)
    {
        printf("(%p)lvl:%d, s:%c   %d, parent(%p): %d\n", cur, level, side, cur->data, parent, parent->data);
    }
    else
    {
         printf("(%p)lvl:%d, s:%c   %d, no parent\n", cur, level, side, cur->data);
    }
    if(cur->right)
    {
        show(cur->right, cur, level+1, 'r');
    }
}


