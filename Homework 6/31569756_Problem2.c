#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

void bSort(struct node **head)
{
    if (!(*head))
        return;
    struct node *end = NULL;
    while ((*head)->next != end)
    {
        struct node **cur = head;
        while ((*cur)->next != end)
        {
            struct node *a = *cur;
            struct node *b = a->next;
            if (a->val > b->val)
            {
                a->next = b->next;
                b->next = a;
                *cur = b;
            }
            cur = &((*cur)->next);
        }
        end = *cur;
    }
}

int main(void)
{
    struct node *head = NULL, *tail = NULL, *nd;
    while (1)
    {
        nd = (struct node *)malloc(sizeof(struct node));
        if (!nd)
            break;
        printf("Enter your number: ");
        if (scanf("%d", &nd->val) == EOF)
        {
            free(nd);
            break;
        }
        nd->next = NULL;
        if (!head)
            head = nd;
        else
            tail->next = nd;
        tail = nd;
    }
    
    bSort(&head);
    struct node *cur = head;
    while (cur)
    {
        printf("\n%d", cur->val);
        cur = cur->next;
    }
    
    cur = head;
    while (cur)
    {
        struct node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    
    printf("\n");
    return 0;
}

