#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void create_db();
void delete_db();
void create_account(char first_name[],char last_name[],char account_no[],char mail[],int balance,int pin,char city[]);

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
    SYSTEMTIME time;
    GetLocalTime(&time);

    FILE *accounts;
    accounts=fopen("accounts.txt","a");
    fprintf(accounts,"%s %s %s %s %d %d %s\n",first_name,last_name,account_no,mail,balance,pin,city);
    fclose(accounts);

    printf("account created");
}
