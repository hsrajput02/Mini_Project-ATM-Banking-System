#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Account
{
    int accNo;
    char name[50];
    int pin;
    float balance;
};

struct Account accounts[MAX];
int totalAccounts = 0;

/* Function Declarations */
void loadAccounts();
void saveAccounts();
void mainMenu();

int login();
void userMenu(int index);
void balanceInquiry(int index);
void depositMoney(int index);
void withdrawMoney(int index);

void transferMoney(int index);
void changePin(int index);
void miniStatement(int index);

int main()
{
    loadAccounts();
    mainMenu();
    return 0;
}

void mainMenu()
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("ATM BANKING SYSTEM\n");
        printf("__________________\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("-----------------\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int index = login();

            if (index != -1)
                userMenu(index);

            break;
        }

        case 2:
            printf("\nThank You For Using HSR BANK ATM.\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }
}

void saveAccounts()
{
    FILE *fp;
    int i;

    fp = fopen("bank.dat", "wb");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    for (i = 0; i < totalAccounts; i++)
    {
        fwrite(&accounts[i],
               sizeof(struct Account),
               1,
               fp);
    }

    fclose(fp);
}

void loadAccounts()
{
    FILE *fp;

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("\nCustomer Database Not Found!\n");
        return;
    }

    totalAccounts = 0;

    while (fread(&accounts[totalAccounts],
                 sizeof(struct Account),
                 1,
                 fp))
    {
        totalAccounts++;
    }

    fclose(fp);
}

int login()
{
    int accNo, pin;
    int i;
    int attempts = 3;
    int found = -1;

    printf("\n------- LOGIN -------\n");

    printf("Enter Account Number : ");
    scanf("%d", &accNo);

    for (i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accNo == accNo)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Account Not Found.\n");
        return -1;
    }

    while (attempts > 0)
    {
        printf("Enter PIN : ");
        scanf("%d", &pin);

        if (accounts[found].pin == pin)
        {
            printf("\nLogin Successful.\n");
            return found;
        }

        attempts--;

        if (attempts > 0)
            printf("Wrong PIN! Attempts Left : %d\n", attempts);
    }

    printf("\nToo Many Failed Attempts.\n");

    return -1;
}

void userMenu(int index)
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("      HSR BANK ATM\n");
        printf("_________________________\n");
        printf("Welcome! %s\n", accounts[index].name);
        printf("-------------------------\n");
        printf("1. Balance Inquiry\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Change PIN\n");
        printf("6. Mini Statement\n");
        printf("7. Logout\n");
        printf("----------------------\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            balanceInquiry(index);
            break;

        case 2:
            depositMoney(index);
            break;

        case 3:
            withdrawMoney(index);
            break;

        case 4:
            transferMoney(index);
            break;

        case 5:
            changePin(index);
            break;

        case 6:
            miniStatement(index);
            break;

        case 7:
            saveAccounts();
            printf("\nLogged Out Successfully.\n");
            return;

        default:
            printf("\nInvalid Choice!\n");
        }
    }
}

void balanceInquiry(int index)
{
    printf("\n-------------------------\n");
    printf("Account Number : %d\n", accounts[index].accNo);
    printf("Name           : %s\n", accounts[index].name);
    printf("Balance        : %.2f\n", accounts[index].balance);
    printf("-------------------------\n");
}

void depositMoney(int index)
{
    float amount;

    printf("\nEnter Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Invalid Amount!\n");
        return;
    }

    accounts[index].balance += amount;

    saveAccounts();

    printf("Amount Deposited Successfully.\n");
    printf("Current Balance : %.2f\n", accounts[index].balance);
}

void withdrawMoney(int index)
{
    float amount;

    printf("\nEnter Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Invalid Amount!\n");
        return;
    }

    if (amount > accounts[index].balance)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    accounts[index].balance -= amount;

    saveAccounts();

    printf("Please Collect Your Cash.\n");
    printf("Remaining Balance : %.2f\n", accounts[index].balance);
}

void transferMoney(int index)
{
    int accNo, i;
    float amount;

    printf("\nEnter Receiver Account Number : ");
    scanf("%d", &accNo);

    if (accNo == accounts[index].accNo)
    {
        printf("Cannot transfer to same account.\n");
        return;
    }

    for (i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accNo == accNo)
        {
            printf("Enter Amount : ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid Amount.\n");
                return;
            }

            if (amount > accounts[index].balance)
            {
                printf("Insufficient Balance.\n");
                return;
            }

            accounts[index].balance -= amount;
            accounts[i].balance += amount;

            saveAccounts();

            printf("Transfer Successful.\n");
            return;
        }
    }

    printf("Receiver Account Not Found.\n");
}

void changePin(int index)
{
    int oldPin, newPin;

    printf("Enter Current PIN : ");
    scanf("%d", &oldPin);

    if (oldPin != accounts[index].pin)
    {
        printf("Incorrect PIN.\n");
        return;
    }

    printf("Enter New 4 Digit PIN : ");
    scanf("%d", &newPin);

    if (newPin < 1000 || newPin > 9999)
    {
        printf("PIN must be 4 digits.\n");
        return;
    }

    if (oldPin == newPin)
    {
        printf("New PIN cannot be same as old PIN.\n");
        return;
    }

    accounts[index].pin = newPin;

    saveAccounts();

    printf("PIN Changed Successfully.\n");
}

void miniStatement(int index)
{
    printf("\n___________________________\n");
    printf("        MINI STATEMENT\n");
    printf("______________________________\n");
    printf("Account No : %d\n", accounts[index].accNo);
    printf("Name       : %s\n", accounts[index].name);
    printf("Balance    : %.2f\n", accounts[index].balance);
    printf("-----------------------\n");
}
