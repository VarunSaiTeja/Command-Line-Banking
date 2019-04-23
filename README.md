# Command-Line-Banking
A banking software works with command line arguments

Your (user) moile number will be assigned as his/her account number

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
To close account

(application name) close_account (account_no) (pin)

"Command Line Banking" close_account 9010075670 1000
___
To check account balance

(application name) balance (account_no) (pin)

"Command Line Banking" balance 9010075670 1000
___
To deposit amount

(application name) deposit (account_no) (amount)

"Command Line Banking" deposit 9010075670 5000
___
To withdraw amount

(application name) withdraw (account_no) (amount) (pin)

"Command Line Banking" withdraw 9010075670 5000 1000
___
To transfer amount

(application name) transfer (sender_account_no) (receiver account_no) (amount) (sender pin)

"Command Line Banking" transfer 9010075670 9123456789 5000 1000
___
