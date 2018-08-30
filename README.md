# Command-Line-Banking
A banking software works with command line arguments

When trying to pass arguments via cmd to application

if application name is one word then no need to specify double quotes, otherwise specify application name with double quotes

arguments[0] assigns to application name (array index elements starts with 0), so arguments we passing to application starts with 1
___
To create database

(application name) create_db

"Command Line Banking" create_db
___
To delete database

(application name) delete_db

"Command Line Banking" delete_db
___
To create new account

(application name) create_account (first_name) (last_name) (mobile_no) (email) (balance) (security_pin) (city)

"Command Line Banking" create_account Varun Teja 9010075670 varun@gmail.com 500 1000 Darsi
___
