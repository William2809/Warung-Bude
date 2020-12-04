#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_ELEMENT = 25;
//linked list
struct NodeOrder
{
    char dishName[255];
    int totalPrice;
    NodeOrder *nextOrder, *prevOrder;
} * headOrder, *tailOrder, *currOrder;

//hash table
struct Node1
{
    char name[255];
    int totalPrice;
    NodeOrder *order;
    Node1 *next;
} * head1[MAX_ELEMENT], *tail1[MAX_ELEMENT];

//linked list
NodeOrder *createNodeOrder(char *dishName)
{
    NodeOrder *temp = (NodeOrder *)malloc(sizeof(NodeOrder));
    strcpy(temp->dishName, dishName);
    temp->nextOrder = temp->prevOrder = NULL;
    return temp;
}

//hash table
Node1 *createNode1(char *name)
{
    Node1 *temp = (Node1 *)malloc(sizeof(Node1));
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}

//hash table
unsigned long DJB2(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    // printf("%llu\n", hash);
    return hash % MAX_ELEMENT;
}

//hash table
void insert(char *str)
{
    int index = DJB2(str);

    if (head1[index])
    {
        Node1 *temp = createNode1(str);
        tail1[index]->next = temp;
        tail1[index] = temp;
    }
    else
    {
        head1[index] = tail1[index] = createNode1(str);
    }
}

//hash table
bool searchCust(char *customerName)
{
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (head1[i])
        {
            Node1 *curr1 = head1[i];
            while (curr1)
            {
                if (strcmp(curr1->name, customerName) == 0)
                {
                    return true;
                }
                curr1 = curr1->next;
            }
        }
    }
    return false;
}

void searchIndex(int index)
{
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (head1[i])
        {
            Node1 *curr1 = head1[i];
            while (curr1)
            {
                if (i == index)
                {
                    printf("Name: %s\n", curr1->name);
                    int food = 0;
                    while (curr1->order)
                    {
                        food++;
                        printf("[%d]. %s\n", food, curr1->order->dishName);
                        curr1->order = curr1->order->nextOrder;
                    }
                    if (food > 0)
                    {
                        printf("Total: %d\n", head1[i]->totalPrice);
                        printf("Please enter to continue...");
                        getchar();
                        return;
                    }
                    else
                    {
                        return;
                    }
                }
                curr1 = curr1->next;
            }
        }
    }
    return;
}

bool searchIndex1(int index)
{
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (head1[i])
        {
            Node1 *curr1 = head1[i];
            while (curr1)
            {
                if (i == index)
                {
                    return true;
                }
                curr1 = curr1->next;
            }
        }
    }
    return false;
}

//hash table
void view()
{
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        // printf("%d ", i);
        if (head1[i])
        {
            Node1 *curr1 = head1[i];
            while (curr1)
            {
                if (curr1->name)
                {
                    printf("[%d]. %s\n", i, curr1->name);
                }
                curr1 = curr1->next;
            }
        }
    }
}

//  TOTAL ORDER

//hash table
void pushOrder(char *customerName, char *dishName, int payment)
{
    int flag = 0;
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (head1[i])
        {
            Node1 *curr1 = head1[i];
            while (curr1)
            {
                if (strcmp(curr1->name, customerName) == 0)
                {
                    head1[i]->totalPrice = payment;
                    flag = 1;
                    break;
                }
                curr1 = curr1->next;
            }
            if (flag == 1)
            {
                if (!(curr1->order))
                {
                    curr1->order = createNodeOrder(dishName);
                }
                else
                {
                    while (curr1->order->nextOrder)
                    {
                        curr1->order = curr1->order->nextOrder;
                    }
                    curr1->order->nextOrder = createNodeOrder(dishName);
                }
                break;
            }
        }
    }
}

// bool viewOrderPay(int index)
// {
//     int ctrindex = 0;
//     for (int i = 0; i < MAX_ELEMENT; i++)
//     {
//         // printf("%d ", i);
//         if (head1[i])
//         {
//             Node1 *curr1 = head1[i];
//             while (curr1)
//             {
//                 ctrindex++;
//                 if (ctrindex == index)
//                 {
//                     printf("%s\n", curr1->name);
//                     if (!curr1->order)
//                     {
//                         printf("You have not ordered anything\n");
//                         return false;
//                     }
//                     else
//                     {
//                         int food = 0;
//                         while (curr1->order)
//                         {
//                             food++;
//                             printf("[%d]. %s\n", food, curr1->order->dishName);
//                             curr1->order = curr1->order->nextOrder;
//                         }
//                         printf("Total: %d\n", head1[i]->totalPrice);
//                         printf("Please enter to continue...");
//                         getchar();
//                         return true;
//                     }
//                 }
//                 curr1 = curr1->next;
//             }
//         }
//     }
//     return false;
// }
