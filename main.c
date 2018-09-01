#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void create_db();
void delete_db();
void create_account(char first_name[],char last_name[],char account_no[],char mail[],int balance,int pin,char city[]);
void close_account(char account_no[],int pin);
void deposit(char account_no[],int amount);
void withdraw(char account_no[],int amount,int pin);
void transfer(char sender_account_no[],char receiver_account_no[],int amount,int pin);
void balance(char account_no[],int pin);
void log_at(char account_no[],int pin);

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
        if(arg_count==4)
        {
            close_account(arguments[2],atoi(arguments[3]));
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
            if(atoi(arguments[3])>0)
            {
                deposit(arguments[2],atoi(arguments[3]));
            }
            else
            {
                printf("invalid amount");
            }
        }
        else
        {
            printf("invalid arguments");
        }
    }

    if(strcmp(arguments[1],"withdraw")==0)
    {
        if(arg_count==5)
        {
            if(atoi(arguments[3])>0)
            {
                withdraw(arguments[2],atoi(arguments[3]),atoi(arguments[4]));
            }
            else
            {
                printf("invalid amount");
            }
        }
        else
        {
            printf("invalid arguments");
        }
    }

    if(strcmp(arguments[1],"transfer")==0)
    {
        if(arg_count==6)
        {
            if(atoi(arguments[4])>0)
            {
                transfer(arguments[2],arguments[3],atoi(arguments[4]),atoi(arguments[5]));
            }
            else
            {
                printf("invalid amount");
            }
        }
        else
        {
            printf("invalid arguments");
        }
    }

    if(strcmp(arguments[1],"balance")==0)
    {
        if(arg_count==4)
        {
            balance(arguments[2],atoi(arguments[3]));
        }
        else
        {
            printf("invalid arguments");
        }

    }

    if(strcmp(arguments[1],"log_at")==0)
    {
        if(arg_count==4)
        {
            log_at(arguments[2],atoi(arguments[3]));
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

        if(strcmp(user.mail,mail)==0)
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

void close_account(char account_no[],int pin)
{
    int account_found=FALSE;
    int pin_correct=FALSE;
    FILE *accounts,*temp;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0 || strcmp(user.mail,account_no)==0)
        {
            strcpy(account_no,user.account_no);
            account_found=TRUE;
            if(user.pin==pin)
            {
                pin_correct=TRUE;
            }
        }
    }
    fclose(accounts);

    if(account_found==TRUE && pin_correct==TRUE)
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
        if(account_found==FALSE)
        {
            printf("account not found");
        }
        else
        {
            printf("incorrect pin");
        }
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
        if(strcmp(user.account_no,account_no)==0 || strcmp(user.mail,account_no)==0)
        {
            strcpy(account_no,user.account_no);
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

void withdraw(char account_no[],int amount,int pin)
{
    int account_found=FALSE;
    int sufficient=FALSE;
    int pin_correct=FALSE;
    FILE *accounts,*temp;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0 || strcmp(user.mail,account_no)==0)
        {
            strcpy(account_no,user.account_no);
            if(user.pin==pin)
            {
                pin_correct=TRUE;
            }
            account_found=TRUE;
            if(user.balance>=amount)
            {
                sufficient=TRUE;
            }
        }
    }
    fclose(accounts);

    if(account_found==TRUE)
    {
        if(sufficient==TRUE && pin_correct==TRUE)
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
                    fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,(user.balance-amount),user.pin,user.city);
                }
            }

            fclose(accounts);
            fclose(temp);
            remove("accounts.txt");
            rename("temp.txt","accounts.txt");
            printf("amount withdrawn");
        }
        else
        {
            if(pin_correct==FALSE)
            {
                printf("incorrect pin");
            }
            else
            {
                if(sufficient==FALSE)
                {
                    printf("insufficient amount");
                }
            }
        }
    }
    else
    {
        printf("account not found");
    }
}

void transfer(char sender_account_no[],char receiver_account_no[],int amount,int pin)
{
    int sender_account_found=FALSE;
    int receiver_account_found=FALSE;
    int sufficient=FALSE;
    int pin_correct=FALSE;
    FILE *accounts,*temp;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);

        if(strcmp(user.account_no,sender_account_no)==0 || strcmp(user.mail,sender_account_no)==0)
        {
            strcpy(sender_account_no,user.account_no);
            sender_account_found=TRUE;
            if(user.pin==pin)
            {
                pin_correct=TRUE;
            }
            if(user.balance>=amount)
            {
                sufficient=TRUE;
            }
        }

        if(strcmp(user.account_no,receiver_account_no)==0 || strcmp(user.mail,receiver_account_no)==0)
        {
            strcpy(receiver_account_no,user.account_no);
            receiver_account_found=TRUE;
        }
    }
    fclose(accounts);

    if(sender_account_found==TRUE && receiver_account_found==TRUE)
    {
        if(sufficient==TRUE && pin_correct==TRUE)
        {
            accounts=fopen("accounts.txt","r");
            temp=fopen("temp.txt","w");

            while(!feof(accounts))
            {
                fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
                if(strcmp(user.account_no,sender_account_no)!=0 && strcmp(user.account_no,receiver_account_no)!=0)
                {
                    fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,user.balance,user.pin,user.city);
                }
                else
                {
                    if(strcmp(user.account_no,sender_account_no)==0)
                    {
                        fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,(user.balance-amount),user.pin,user.city);
                    }

                    if(strcmp(user.account_no,receiver_account_no)==0)
                    {
                        fprintf(temp,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,(user.balance+amount),user.pin,user.city);
                    }
                }
            }

            fclose(accounts);
            fclose(temp);
            remove("accounts.txt");
            rename("temp.txt","accounts.txt");
            printf("amount transferred");
        }
        else
        {
            if(pin_correct==FALSE)
            {
                printf("incorrect pin");
            }
            else
            {
                printf("insufficient amount");
            }
        }
    }
    else
    {
        if(sender_account_found==FALSE && receiver_account_found==FALSE)
        {
            printf("sender and receiver account not found");
        }
        else
        {
            if(sender_account_found==FALSE)
            {
                printf("sender account not found");
            }

            if(receiver_account_found==FALSE)
            {
                printf("receiver account not found");
            }
        }
    }
}

void balance(char account_no[],int pin)
{
    int account_found=FALSE;
    int pin_correct=FALSE;
    int amount;
    FILE *accounts;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0 || strcmp(user.mail,account_no)==0)
        {
            strcpy(account_no,user.account_no);
            account_found=TRUE;
            if(user.pin==pin)
            {
                pin_correct=TRUE;
                amount=user.balance;
            }
            else
            {
                printf("incorrect pin");
            }
        }
    }
    fclose(accounts);

    if(pin_correct==TRUE)
    {
        printf("%d",amount);
    }

    if(account_found==FALSE)
    {
        printf("account not found");
    }
}

void log_at(char account_no[],int pin)
{
    int pin_correct=FALSE;
    int account_found=FALSE;
    FILE *accounts;

    accounts=fopen("accounts.txt","r");
    while(!feof(accounts))
    {
        fscanf(accounts,"%s %s %s %s %d %d %s\n",user.first_name,user.last_name,user.account_no,user.mail,&user.balance,&user.pin,user.city);
        if(strcmp(user.account_no,account_no)==0 || strcmp(user.mail,account_no)==0)
        {
            strcpy(account_no,user.account_no);
            account_found=TRUE;
            if(user.pin==pin)
            {
                pin_correct=TRUE;
            }
        }
    }
    fclose(accounts);

    if(account_found==TRUE)
    {
        if(pin_correct==TRUE)
        {
            printf("success");
        }
        else
        {
            printf("failed");
        }
    }
    else
    {
        printf("account not found");
    }
}
