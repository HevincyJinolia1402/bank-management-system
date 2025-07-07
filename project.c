// bank management system

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void main_menu();
void new_account();
void update_account();
void transaction();
void check_account();
void remove_account();
void customer_details();
void close_application();

struct date
{
    int month, day, year;
};

struct date get_dates(struct date dt);

struct customer
{
    char name[50];
    int acc_no, age;
    char address[100];
    int atype;
    float amount;
    double phone_no;
    struct date deposit_date;
    struct date withdraw_date;
} add, update, check, del, txn;

int main_exit; // global variable

int main()
{
    char password[20], pass_match[20] = "1234";

    system("cls");

    printf("enter the password to login \n");
    scanf("%s", password);

    if (strcmp(password, pass_match) == 0)
    {
        printf("\n password matched \n");
        main_menu();
    }
    else
    {
        printf("\n wrong password \n");
        printf("\n option : \n 1 - try again \n 0 - exit \n\n");
        scanf("%d", &main_exit);
    }

    if (main_exit == 1)
    {
        system("cls");
        main();
    }
    else
    {
        system("cls");
        exit(0);
    }
}

void main_menu()
{
    int choice;
    system("cls");

    printf("\n welcome to banking management system \n");
    printf("\n banking options : \n");

    printf("1.Create your account \n2.Update account \n3.Transactions \n4.Check account \n5.remove account \n6.View customer details \n7.exit");
    printf("\n please enter your choice : \n");
    scanf("%d", &choice);

    system("cls");

    switch (choice)
    {
    case 1:
        new_account();
        break;
    case 2:
        update_account();
        break;
    case 3:
        transaction();
        break;
    case 4 :
         check_account();
         break;
    case 5 :
         remove_account();
         break;
    case 6 :
         customer_details();
         break;
    case 7:
        exit(0);
        break;
    default:
        printf("invalid option");
        break;
    }
    new_account();
}

void new_account()
{
    FILE *ptr;
    int choice;

    ptr = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "a"); // a-> append the data

    printf("\n enter the account number : \t");
    scanf("%d", &add.acc_no);

    printf("\n enter the name : \t");
    scanf("%s", add.name);

    printf("\n enter your age : \t");
    scanf("%d", &add.age);

    printf("\n enter the address : \t");
    scanf("%s", add.address);

    printf("\n enter the account type : \t1.savings \t2.fixed deposit \t");
    scanf("%d", &add.atype);

    printf("\n enter the phone number : \t");
    scanf("%lf", &add.phone_no);

    printf("\n enter the amount : \t");
    scanf("%f", &add.amount);

    struct date dt = get_dates(dt);

    add.deposit_date.day = dt.day;
    add.deposit_date.month = dt.month;
    add.deposit_date.year = dt.year;

    fprintf(ptr, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, add.address, add.atype, add.amount, add.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);
    fclose(ptr);

    system ("cls");
    printf("\nAccount created successfully!");

    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}

struct date get_dates(struct date dt)
{
    time_t currenttime;
    struct tm *ltime;

    time(&currenttime);

    ltime = localtime(&currenttime);

    dt.day = ltime->tm_mday;
    dt.month = ltime->tm_mon + 1;
    dt.year = ltime->tm_year + 1900;

    return dt;
}
void update_account()
{
    // update the records - 1.address  2.phone no
    FILE *old, *newrec;
    int record_found = 0;

    old = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "r"); // r -> read
    newrec = fopen("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "w");   // w -> write

    printf("\n enter the account number : \t");
    scanf("%d", &update.acc_no);
    while (fscanf(old, "%d %s %s %d %f %lf %d/%d/%d \n ", &add.acc_no, add.name, add.address, &add.atype, &add.amount, &add.phone_no, &add.deposit_date.month, &add.deposit_date.day, &add.deposit_date.year) != EOF)
    {
        if (add.acc_no == update.acc_no)
        {
            record_found = 1;

            printf("enter new address :");
            scanf("%s", update.address);

            printf("enter new phone number :");
            scanf("%lf", &update.phone_no);

            fprintf(newrec, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, update.address, add.atype, add.amount, update.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);

            printf("\nAccount updated successfully!");
        }
        else
        {
            fprintf(newrec, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, add.address, add.atype, add.amount, add.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");
    rename("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");

    if (record_found == 0)
    {
        system("cls");
        printf("\n record not found !");
    }
    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}

void transaction()
{
    FILE *old, *newrec;
    int record_found = 0;

    old = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "r"); // r -> read
    newrec = fopen("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "w");       // w -> write

    printf("\n enter the account number :");
    scanf("%d", &update.acc_no);
    while (fscanf(old, "%d %s %s %d %f %lf %d/%d/%d \n ", &add.acc_no, add.name, add.address, &add.atype, &add.amount, &add.phone_no, &add.deposit_date.month, &add.deposit_date.day, &add.deposit_date.year)!= EOF)
        
    {
        if (add.acc_no == update.acc_no)
        {
            record_found = 1;
            printf("\n enter the choice 1.deposit  2.withdraw");

            int choice;
            scanf("%d", &choice);
            float deposit_amount = 0;
            float withdraw_amount = 0;
            if (choice == 1)
            {
                printf("\nenter deposit amount :");
                scanf("%f", &deposit_amount);

                update.amount = add.amount + deposit_amount;
            }
            else if (choice == 2)
                
            {
                printf("\nenter withdraw amount :");
                scanf("%f", &withdraw_amount);

                if (add.amount < withdraw_amount)
                {
                    printf("\n insufficient balance");
                    main_menu();
                }
                else
                {
                    update.amount = add.amount - withdraw_amount;
                }
            }

            fprintf(newrec, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, add.address, add.atype, update.amount, add.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);

            printf("\nAccount updated successfully!");
        }
        else
        {
            fprintf(newrec, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, add.address, add.atype, add.amount, add.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");
    rename("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");

    if (record_found == 0)
    {
        system("cls");
        printf("\n record not found !");
    }
    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}

void check_account()
{
    FILE *ptr;
    int record_found = 0;
    ptr = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "r");

    system("cls");

    printf("enter the account number : ");
    scanf("%d", &check.acc_no);

    while (fscanf(ptr, "%d %s %s %d %f %lf %d/%d/%d \n ", &add.acc_no, add.name, add.address, &add.atype, &add.amount, &add.phone_no, &add.deposit_date.month, &add.deposit_date.day, &add.deposit_date.year)!= EOF)

    {
        if (add.acc_no == check.acc_no)
        {
            system("cls");
            printf("record found : \n");
            record_found = 1;

            printf("\n account no : %d", add.acc_no);
            printf("\n account name : %d", add.name);

            if (add.atype == 1)
                printf("\n account type : %d - savings", add.atype);

            else if (add.atype == 2)
            printf("\n account type : %d - current", add.atype);
            printf("account balance : %.2f", add.amount);
            printf("\n phone : %.01f", add.phone_no);
            printf("\n deposit date : %d - %d - %d", add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);
            break;
        }
    }
    fclose(ptr);

    if (record_found == 0)
    {
        system("cls");
        printf("\n record not found !");
    }
    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}
void remove_account()
{    
        FILE *old, *newrec;
    int record_found = 0;

    old = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "r"); // r -> read
    newrec = fopen("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "w");       // w -> write

    printf("\n enter the account number : \t");
    scanf("%d", &del.acc_no);
    while (fscanf(old, "%d %s %s %d %f %lf %d/%d/%d \n ", &add.acc_no, add.name, add.address, &add.atype, &add.amount, &add.phone_no, &add.deposit_date.month, &add.deposit_date.day, &add.deposit_date.year) != EOF)
    {
        if (add.acc_no == del.acc_no)
        {
            record_found = 1;
            continue;
        }
        else
        {
            fprintf(newrec, "%d %s %s %d %f %lf %d/%d/%d \n ", add.acc_no, add.name, add.address, add.atype, add.amount, add.phone_no, add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");
    rename("C:\\Users\\User\\Documents\\CProgramming\\new.txt", "C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt");

    if (record_found == 0)
    {
        system("cls");
        printf("\n record not found !");
    }
    else
    {
        system("cls");
        printf("\n record deleted successfully");
    }

    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}
void customer_details()
{
    FILE *ptr;
    int record_found = 0;
    ptr = fopen("C:\\Users\\User\\Documents\\CProgramming\\bank_records.txt", "r");

    system("cls");

    while (fscanf(ptr, "%d %s %s %d %f %lf %d/%d/%d \n ", &add.acc_no, add.name, add.address, &add.atype, &add.amount, &add.phone_no, &add.deposit_date.month, &add.deposit_date.day, &add.deposit_date.year) != EOF)

        {
            record_found = 1;

            printf("\n account no : %d", add.acc_no);
            printf("\n account name : %d", add.name);  

            if (add.atype == 1)
            {
                printf("\n account type : %d - savings", add.atype);
            }
            else if (add.atype == 2)
            {
            printf("\n account type : %d - current", add.atype);
            }

            printf("account balance : %.2f", add.amount);
            printf("\n phone : %.01f", add.phone_no);
           printf("\n deposit date : %d - %d - %d", add.deposit_date.month, add.deposit_date.day, add.deposit_date.year);

           printf("\n ***************\n");
        }
    
    fclose(ptr);

    if (record_found == 0)
    {
        system("cls");
        printf("\n record not found !");
    }
    printf("\nenter option  1.main menu  2.exit");
    scanf("%d", &main_exit);
    system("cls");

    if (main_exit == 1)
    {
        main_menu();
    }
    else if (main_exit == 2)
    {
        exit(0);
    }
    else
    {
        printf("invalid option");
    }
}
