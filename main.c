#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void create_db();
void delete_db();
void create_account(char first_name[],char last_name[],char account_no[],char mail[],int balance,int pin,char city[]);
void close_account(char account_no[]);
void deposit(char account_no[],int amount);

struct account
{
    char first_name[20];
    char last_name[20];
    char account_no[11];
    char mail[40];
    int balance;
    int pin;
    char city[15];
};

struct account user;

int main(int arg_count,char* arguments[])
{
    if(strcmp(arguments[1],"create_db")==0)
    {
        create_db();
    }

    if(strcmp(arguments[1],"delete_db")==0)
    {
        delete_db();
    }

    if(strcmp(arguments[1],"create_account")==0)
    {
        //arguments=program_name,create_account,first_name,last_name,mobile,email,balance,password,city
        //total arguments=9
        if(arg_count==9)
        {
            create_account(arguments[2],arguments[3],arguments[4],arguments[5],atoi(arguments[6]),atoi(arguments[7]),arguments[8]);
        }
        else
        {
            printf("invalid arguments");
        }
    }

    if(strcmp(arguments[1],"close_account")==0)
    {
        if(arg_count==3)
        {
            close_account(arguments[2]);
        }
        else
        {
            printf("invalid arguments");
        }
    }

    if(strcmp(arguments[1],"deposit")==0)
    {
        if(arg_count==4)
        {
            deposit(arguments[2],atoi(arguments[3]));
        }
        else
        {
            printf("invalid arguments");
        }
    }
    return 0;
}

void create_db()
{
    FILE *new_file;

    new_file=fopen("accounts.txt","w");
    fclose(new_file);

    printf("database created");
}

void delete_db()
{
    remove("accounts.txt");

    printf("database deleted");
}

void create_account(char first_name[],char last_name[],char account_no[],char mail[],int balance,int pin,char city[])
{
    int account_exist=FALSE;

    FILE *accounts;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0)
        {
            account_exist=TRUE;
        }
    }
    fclose(accounts);

    if(account_exist==FALSE)
    {
        accounts=fopen("accounts.txt","a");
        fprintf(accounts,"%s %s %s %s %d %d %s\n",first_name,last_name,account_no,mail,balance,pin,city);
        fclose(accounts);
        printf("account created");
    }
    else
    {
        printf("account exists");
    }
}

void close_account(char account_no[])
{
    int account_found=FALSE;
    FILE *accounts,*temp;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0)
        {
            account_found=TRUE;
        }
    }
    fclose(accounts);

    if(account_found==TRUE)
    {
        accounts=fopen("accounts.txt","r");
        temp=fopen("temp.txt","w");

        while(!feof(accounts))
        {
            fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
            if(strcmp(user.account_no,account_no)!=0)
            {
                fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,user.balance,user.pin,user.city);
            }
        }

        fclose(accounts);
        fclose(temp);
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
        printf("account closed");
    }
    else
    {
        printf("account not found");
    }
}

void deposit(char account_no[],int amount)
{
    int account_found=FALSE;
    FILE *accounts,*temp;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0)
        {
            account_found=TRUE;
        }
    }
    fclose(accounts);

    if(account_found==TRUE)
    {
        accounts=fopen("accounts.txt","r");
        temp=fopen("temp.txt","w");

        while(!feof(accounts))
        {
            fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
            if(strcmp(user.account_no,account_no)!=0)
            {
                fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,user.balance,user.pin,user.city);
            }
            else
            {
                fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,(user.balance+amount),user.pin,user.city);
            }
        }

        fclose(accounts);
        fclose(temp);
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
        printf("amount deposited");
    }
    else
    {
        printf("account not found");
    }
}
