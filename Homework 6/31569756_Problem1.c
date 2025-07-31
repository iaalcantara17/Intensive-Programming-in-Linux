#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

struct node *revList(struct node *head)
{
    struct node *rev = NULL, *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        tmp->next = rev;
        rev = tmp;
    }
    return rev;
}

int main(void)
{
    int i = 1, num;
    struct node *head = NULL, *tail = NULL, *cur;
    
    while (1)
    {
        cur = (struct node *)malloc(sizeof(struct node));
        if (!cur)
            break;
        printf("Input data for node %d : ", i);
        if (scanf("%d", &num) == EOF)
        {
            free(cur);
            break;
        }
        i++;
        cur->val = num;
        cur->next = NULL;
        if (!head)
            head = cur;
        else
            tail->next = cur;
        tail = cur;
    }
    
    printf("\nData entered in the list are:");
    for (cur = head; cur; cur = cur->next)
        printf("\nData = %d", cur->val);
    
    head = revList(head);
    printf("\nThe list in reverse are :");
    while (head)
    {
        printf("\nData = %d", head->val);
        cur = head;
        head = head->next;
        free(cur);
    }
    
    printf("\n");
    return 0;
}

