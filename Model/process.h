#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu()
{
    cls();
    systemAndDate();
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");

    int num;
    while (1)
    {
        printf(">> ");
        scanf("%d", &num);
        if (num >= 1 && num <= 8)
        {
            break;
        }
    }
    switch (num)
    {
    case 1:
        cls();
        addDish();
        break;
    case 2:
        cls();
        removeDish();
        break;
    case 3:
        cls();
        addCustomer();
        break;
    case 4:
        cls();
        searchCustomer();
        break;
    case 5:
        cls();
        viewWarteg();
        break;
    case 6:
        cls();
        orderDish();//kalau indexnya sama masih ga ngerti ko
        break;
    case 7:
        cls();
        payment();
        break;
    case 8:
        exit();//exitnya bermasalah ko, logonya gamau keprint
        break;
    }
}

void addDish()
{
    char dishName[255];
    int price;
    int quantity;
    //insert dish name
    getchar();
    while (1)
    {
        strcpy(dishName, "");
        printf("Insert the name of the dish[Lowercase letters]: ");
        scanf("%[^\n]", dishName);
        getchar();
        int flag = 0;

        for (int i = 0; dishName[i] != '\0'; i++)
        {
            flag = 0;
            if ((dishName[i] >= 'a' && dishName[i] <= 'z') || dishName[i] == ' ')
            {
                flag = 0;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int len = strlen(dishName);
            if (len < 1)
            {
                continue;
            }
            break;
        }
    }

    //insert the price
    while (1)
    {
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();
        if (price >= 1000 && price <= 50000)
        {
            break;
        }
    }

    //insert the quantity
    while (1)
    {
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity);
        getchar();
        if (quantity >= 1 && quantity <= 999)
        {
            break;
        }
    }

    pushTail((char *)dishName, price, quantity);
    printf("The dish has been added!\n");
    printf("Press enter to continue...");
    getchar();
    menu();
}

void removeDish()
{
    char dishName[255];
    strcpy(dishName, "");
    printLinkedList();
    getchar();
    while (1)
    {
        printf("Insert dish's name to be deleted: ");
        scanf("%[^\n]", dishName);
        getchar();
        int flag = 0;
        for (int i = 0; dishName[i] != '\0'; i++)
        {
            flag = 0;
            if (dishName[i] >= 'A' && dishName[i] <= 'Z')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            continue;
        }
        else
        {
            int len = strlen(dishName);
            if (len < 1)
            {
                continue;
            }
        }
        if (search(dishName) == true)
        {
            break;
        }
    }

    popMid(dishName);

    printf("The dish has been removed!\n");
    printf("Press enter to continue...");
    getchar();
    menu();
}

void addCustomer()
{
    char customerName[255];
    getchar();
    while (1)
    {
        strcpy(customerName, "");
        printf("Insert the customer's name [Without Space]: ");
        scanf("%[^\n]", customerName);
        getchar();
        int flag = 0;
        for (int i = 0; customerName[i] != '\0'; i++)
        {
            if (customerName[i] == ' ')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int len = strlen(customerName);
            if (len < 1)
            {
                continue;
            }
            break;
        }
    }
    insert((char *)customerName);
    puts("");
    printf("Customer has been added!\n\n");
    printf("Press enter to continue...");
    getchar();
    menu();
}

void searchCustomer()
{
    char customerName[255];
    printf("Insert the customer's name to be searched: ");
    getchar();

    while (1)
    {
        strcpy(customerName, "");
        scanf("%[^\n]", customerName);
        getchar();
        int flag = 0;
        for (int i = 0; customerName[i] != '\0'; i++)
        {
            if (customerName[i] == ' ')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int len = strlen(customerName);
            if (len < 1)
            {
                continue;
            }
            break;
        }
    }
    if (searchCust((char *)customerName) == true)
    {
        printf("%s is present.\n", customerName);
    }
    else
    {
        printf("%s is not present.\n", customerName);
    }

    printf("Press enter to continue...");
    getchar();
    menu();
}

void viewWarteg()
{
    getchar();
    printf("Customer's List\n");
    // getchar();
    view();
    printf("Press enter to continue...");
    getchar();
    menu();
}

void orderDetail(char *customerName)
{
    int amount;
    printf("Insert the amount of dish: ");
    scanf("%d", &amount);
    getchar();
    char dishName[255];
    for (int i = 0; i < amount; i++)
    {
        printf("[%d] Insert the dish's name and quantity: ", i + 1);
        scanf("%[^\n]", dishName);
        getchar();
        int len = strlen(dishName);
        if (checkOrder(dishName, len, customerName) != -1)
        {

            printf("SUCCESS\n");
        }
        else
        {
            printf("NOT SUCCESS\n");
            i--;
        }
    }
}

void orderDish()
{
    char customerName[255];
    // printf("Insert the customer's name: ");
    getchar();

    while (1)
    {
        printf("Insert the customer's name: ");
        strcpy(customerName, "");
        scanf("%[^\n]", customerName);
        getchar();
        int flag = 0;
        for (int i = 0; customerName[i] != '\0'; i++)
        {
            if (customerName[i] == ' ')
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            int len = strlen(customerName);
            if (len < 1)
            {
                continue;
            }
            if (searchCust((char *)customerName) == true)
            {
                orderDetail(customerName);
            }
            else
            {
                continue;
            }
            break;
        }
    }
    printf("Order Success!\n");
    printf("Press enter to continue...");
    getchar();
    menu();
}

void payment()
{
    int customerIndex;
    while (1)
    {
        printf("Insert the customer's index: ");
        scanf("%d", &customerIndex);
        getchar();
        if (searchIndex1(customerIndex) == true)
        {
            searchIndex(customerIndex);
            menu();
            break;
        }
    }
    return;
}
