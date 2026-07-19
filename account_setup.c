#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    int accNo;
    char name[50];
    int pin;
    float balance;
};

void createAccount();
void displayAccounts();

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("      HSR BANK - ACCOUNT SETUP\n");
        printf("\n");
        printf("1. Create New Account\n");
        printf("2. View All Accounts\n");
        printf("3. Exit\n");
        printf("--------------------\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            printf("\nThank You!\n");
            return 0;

        default:
            printf("\nInvalid Choice!\n");
        }
    }
}

void createAccount()
{
    FILE *fp;
    struct Account a;
    struct Account temp;

    fp = fopen("bank.dat", "ab+");

    if (fp == NULL)
    {
        printf("Unable to Open File.\n");
        return;
    }

    int lastAccNo = 1000;

    rewind(fp);

    while (fread(&temp, sizeof(struct Account), 1, fp))
    {
        lastAccNo = temp.accNo;
    }

    a.accNo = lastAccNo + 1;

    printf("\nEnter Customer Name : ");
    scanf(" %[^\n]", a.name);

    do
    {
        printf("Enter 4 Digit PIN : ");
        scanf("%d", &a.pin);

        if (a.pin < 1000 || a.pin > 9999)
            printf("PIN must be 4 digits.\n");

    } while (a.pin < 1000 || a.pin > 9999);

    do
    {
        printf("Enter Opening Balance : ");
        scanf("%f", &a.balance);

        if (a.balance < 0)
            printf("Balance Cannot be Negative.\n");

    } while (a.balance < 0);

    fwrite(&a, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\n\n");
    printf("Account Created Successfully!\n");
    printf("Account Number : %d\n", a.accNo);
    printf("Customer Name  : %s\n", a.name);
    printf("\n");
}

void displayAccounts()
{
    FILE *fp;
    struct Account a;

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found.\n");
        return;
    }

    printf("\n---------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-10s\n", "Acc No", "Name", "PIN", "Balance");
    printf("---------------------------------------------------\n");

    while (fread(&a, sizeof(struct Account), 1, fp))
    {
        printf("%-10d %-20s %-10d %.2f\n",
               a.accNo,
               a.name,
               a.pin,
               a.balance);
    }

    printf("---------------------------------------------------\n");

    fclose(fp);
}