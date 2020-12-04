#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu();
void addDish();
void removeDish();
void addCustomer();

void cls()
{
    for (int i = 0; i < 40; i++)
    {
        puts("");
    }
}

void exit()
{
    cls();
    char exit[255];
    FILE *fp = fopen("exitlogo.txt", "r");
    while (fscanf(fp, "%[^\n]\n", exit) != EOF)
    {
        printf("%s\n", exit);
    }
}

void systemAndDate()
{
#ifdef _WIN64
    printf("Windows 64-bit");
#elif _WIN32
    printf("Windows 32-bit");
#elif __APPLE__ || __MACH__
    printf("Mac OSX");
#elif __linux__
    printf("Linux");
#elif __FreeBSD__
    printf("FreeBSD");
#elif __unix || __unix__
    printf("Unix");
#else
    printf("Other");
#endif
    puts("");
    time_t tanggal;
    time(&tanggal);
    printf("%s", asctime(localtime(&tanggal)));
}

struct Node
{
    char dishName[255];
    int price;
    int quantity;
    Node *next, *prev;
} * head, *tail, *curr;

Node *createNode(char *dishName, int price, int quantity)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    strcpy(temp->dishName, dishName);
    temp->price = price;
    temp->quantity = quantity;
    temp->next = temp->prev = NULL;
    return temp;
}

void pushHead(char *dishName, int price, int quantity)
{
    Node *temp = createNode(dishName, price, quantity);

    if (!head)
    {
        head = tail = temp;
    }
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail(char *dishName, int price, int quantity)
{
    Node *temp = createNode(dishName, price, quantity);

    if (!head)
    {
        head = tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(char *dishName, int price, int quantity)
{
    Node *temp = createNode(dishName, price, quantity);
    pushTail(dishName, price, quantity);
}

void popHead()
{
    if (head && head == tail)
    {
        head = tail = NULL;
        free(head);
    }
    else
    {
        Node *newHead = head->next;

        head->next = newHead->prev = NULL;
        free(head);
        head = newHead;
    }
}

void popTail()
{
    if (head && head == tail)
    {
        head = tail = NULL;
        free(head);
    }
    else
    {
        Node *newTail = tail->prev;
        tail->prev = newTail->next = NULL;
        free(tail);
        tail = newTail;
    }
}

void popMid(char *dishName)
{

    if (!head)
    {
        return;
    }
    else if (strcmp(head->dishName, dishName) == 0)
    {
        popHead();
    }
    else if (strcmp(tail->dishName, dishName) == 0)
    {
        popTail();
    }
    else
    {
        curr = head;

        while (curr && strcmp(curr->dishName, dishName) == 0)
        {
            curr = curr->next;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr->prev = curr->next = NULL;
        free(curr);
    }
}

void printLinkedList()
{
    printf("       Bude's Menu\n");
    printf("==========================================\n\n");
    curr = head;
    int no = 1;
    printf("%-5s %-15s %-10s %-8s\n", "No.", "Name", "Quantity", "Price");
    while (curr)
    {
        printf("%d     %-15s %03d       Rp%-8d\n", no, curr->dishName, curr->quantity, curr->price);
        curr = curr->next;
        no++;
    }
    printf("==========================================\n");
}

bool search(char *dishName)
{
    curr = head;
    //    printf("%s", dishName);
    while (curr)
    {
        if (strcmp(curr->dishName, dishName) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int searchOrder(char *dishName, int total)
{
    curr = head;
    //    printf("%s", dishName);
    while (curr)
    {
        if (strcmp(curr->dishName, dishName) == 0)
        {
            if (total > curr->quantity)
            {
                return 0;
            }
            else
            {
                curr->quantity -= total;
                return total * curr->price;
            }
        }
        curr = curr->next;
    }
    return 0;
}

int checkOrder(char *dishName, int len, char *customerName)
{
    int flag = 0;
    for (int i = 0; i < len; i++)
    {
        if (dishName[i] == 'x' && dishName[i + 1] >= '0' && dishName[i + 1] <= '9')
        {
//            printf("YAAA\n");
            int counter = 0, ctrBack = 0;
            for (int j = i; dishName[j] != '\0'; j++)
            {
                ctrBack++;
            }
            int dishNameLen = len - ctrBack - 1;
            if (dishNameLen <= 0)
            {
                return -1;
            }
            for (int j = i + 2; dishName[j] != '\0'; j++)
            {
                counter++;
            }
            int total = 0;
            for (int j = i + 1; dishName[j] != '\0'; j++)
            {
                int temp = dishName[j] - '0';
                for (int k = 0; k < counter; k++)
                {
                    temp *= 10;
                }
                total += temp;
                counter--;
            }
            char tempDishName[255];
            strcpy(tempDishName, dishName);
            tempDishName[dishNameLen] = '\0';
            int totalPayment = searchOrder(tempDishName, total);
            if (totalPayment > 0)
            {
                pushOrder(customerName, dishName, totalPayment);
//                printf("FOUND THE MENU\n");
            }
            else
            {
//                printf("NOT FOUND THE MENU\n");
                return -1;
            }
//            printf("total: %d\n", total);
        }
    }
}
