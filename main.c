#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void create_db();
void delete_db();

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
