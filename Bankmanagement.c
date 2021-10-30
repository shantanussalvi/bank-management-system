/* Project - Bank Management System 

Project By: Sairaaj Surve - 60003200079
            Shantanu Salvi- 60003200025

Can do the following: 
1.Display Details Of an Account
2.Withdraw From an Account
3.Deposit to an Account
4.Create a new Account
5.Delete an existing Account

Information in stored in the order :
Account Number
Name
Balance

Corresponding Pin-Codes are Stored in Password.txt

Compiled on *GCC COMPILER*
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Structure contaning information of accounts*/

struct Account
{
    char ID[50];
    char Name[50];
    double balance;
};

/* Returns position of the Account number string passed as argument in Info.txt */

int position(char iD[50])
{   

    FILE *ptr;
    ptr = fopen("Info.txt","r+"); // Opnes Info.txt
    char garbage[50]; // For comparing with Account Number
    int pos = 0; // Store positon of Account Number

    fseek(ptr,0,SEEK_SET); // Takes cursor in file to first position

    while(1) // Finds the postion of Account Number
    {       
        fscanf(ptr,"%s",&garbage);
        if(!(strcmp(garbage,iD)))
        {   
            break;
        }
        pos++;
    }
    fclose(ptr);
    return pos;
}

/*  Function returns the number of lines in Info.txt file  */

int line()
{
    FILE *ptr;
    ptr = fopen("Info.txt", "r"); // Opens Info.txt
    int n = 1;
    char c;
    for(c = getc(ptr); c != EOF; c = getc(ptr)) //Loops through all charecters in the file
    { 
        if(c == '\n') // Whenever character is a newline no. of line is incremented
        {
            n++;
        }
    }
    fclose(ptr); // Closes Info.txt

    return n;
}

/*  Function returns the number of lines in Password.txt file  */

int pinLine()
{
    FILE *ptr;
    ptr = fopen("Password.txt", "r"); // Opens Password.txt
    int n = 1;
    char c;
    for(c = getc(ptr); c != EOF; c = getc(ptr)) //Loops through all charecters in the file
    { 
        if(c == '\n') // Whenever character is a newline no. of line is incremented
        {
            n++;
        }
    }
    fclose(ptr); // Closes Password.txt

    return n;
}

/* Reads Info.txt and fills the array with data */

void assign(struct Account Arr[50])
{
    FILE *ptr;

    ptr = fopen("Info.txt","r"); // Opens Info.txt

    int lines = line(); // Counts number of lines 

    int i = 0,j=0;

    while(j<lines/3) // Gets three lines in one loop
    {
        fscanf(ptr,"%s",&Arr[i].ID);
        fscanf(ptr,"%s",&Arr[i].Name);
        fscanf(ptr,"%lf",&Arr[i].balance);
        i++;
        j++;
    }

    fclose(ptr);
}

/* Displays the Account structure */

void display(struct Account Acc) 
{
    printf("Account Number : %s\n",Acc.ID);
    printf("Info Of Account Holder : %s\n",Acc.Name);
    printf("Balance : %0.2f\n",Acc.balance);
    
}

/* Resolves an issue where changes on last entry adds an extra blank space in Info.txt */

void endCorrection()
{
    FILE *ptr,*tempPtr;
    ptr = fopen("Info.txt","r+"); // Opnes Info.txt
    tempPtr = fopen("Temp.txt","w+"); // Opens Temp.txt

    char garbage[50]; // Temporary variable to copy strings

    int lines = line(); // Number of lines in Info.txt
    
    fseek(ptr,0,SEEK_SET); // Takes cursor in file to first position
    if(lines % 3 != 0) // Only gets executed when there is an extra line
    {
        for(int i = 0 ; i < lines - 1 ; i ++) // Copies all the contents except the last blank line
        {
            fscanf(ptr,"%s",&garbage); 
            
            fputs(garbage,tempPtr);
            if(i != lines - 2 )fputs("\n",tempPtr); // Does not print last line for second last (last non blank) line
            
        }
        fclose(ptr); 
        fclose(tempPtr); 
        remove("Info.txt"); 
        rename("Temp.txt","Info.txt"); 
        return;
    }

    fclose(ptr); 
    fclose(tempPtr);
    remove("Temp.txt");
}


/* Modifies the Info.txt while withdrawing and depositing */

void modifyBalance(double Balance , char iD[50])
{   
    FILE *ptr,*tempPtr;
    ptr = fopen("Info.txt","r+"); // Opnes Info.txt
    tempPtr = fopen("Temp.txt","w+"); // Opens Temp.txt

    char garbage[50]; // For comparing with Account Number
    int pos = position(iD); // Store positon of Account Number

    int lines = line(); // Number of lines in Info.txt

    fseek(ptr,0,SEEK_SET);  // Takes cursor in file to first position

    for(int k = 0 ; k < lines ; k++) // Copies the contents of Info.txt to Temp.txt
    {
        fscanf(ptr,"%s",&garbage); // Inputs one line into garbage variable
        if( k == pos + 2) // Hits balance of required Account Number
        {
            sprintf(garbage, "%0.2f", Balance); // Converts Balance double to a string
            fputs(garbage,tempPtr); //  Inserts new Balance in place of old
            fputs("\n",tempPtr); // Prints New line in Info.txt
            continue;
        }
        fputs(garbage,tempPtr); // Inserts the line from Info.txt into Temp.txt
        if(k != lines - 1)fputs("\n",tempPtr); // Prints New line in Info.txt
        
            
    }
    
    fclose(ptr); // Closes Info.txt
    fclose(tempPtr); // Closes Temp.txt

    remove("Info.txt"); // Deletes Info.txt (with old balance)
    rename("Temp.txt","Info.txt"); // Renames Temp.txt (with new balance)

    endCorrection();
    
}

/* Resolves an issue where changes on last entry adds an extra blank space in Password.txt */

void pinEndCorrection()
{
    FILE *ptr,*tempPtr;
    ptr = fopen("Password.txt","r+"); // Opnes Password.txt
    tempPtr = fopen("Temp2.txt","w+"); // Opens Temp2.txt

    char garbage[50]; // Temporary variable to copy strings

    for(int i = 0 ; i < pinLine() - 1 ; i ++) // Copies all the contents except the last blank line
        {
            fscanf(ptr,"%s",&garbage); 
            
            fputs(garbage,tempPtr);
            if(i != pinLine() - 2 )fputs("\n",tempPtr); // Does not print last line for second last (last non blank) line
            
        }

    fclose(ptr); // Closes  Password.txt
    fclose(tempPtr); // Closes Temp2.txt

    remove("Password.txt"); // Deletes  Password.txt 
    rename("Temp2.txt","Password.txt"); // Renames Temp.txt 

}


void deletePin(int pos)
{
    FILE *ptr,*tempPtr;
    ptr = fopen("Password.txt","r+"); // Opnes Password.txt
    tempPtr = fopen("Temp2.txt","w+"); // Opens Temp2.txt

    char garbage[50]; // Temporary variable to copy strings

    fseek(ptr,0,SEEK_SET);  // Takes cursor in file to first position

    for(int k = 0 ; k < pinLine(); k++) // Copies the contents of Password.txt to Temp2.txt
    {
        fscanf(ptr,"%s",&garbage); // Inputs one line into garbage variable
        if( k == pos) 
        {
            // Does not Copy the Pin we want to delete
            continue;
        }
        fputs(garbage,tempPtr); // Inserts the line from Password.txt into Temp2.txt
        if(k != pinLine() - 1)fputs("\n",tempPtr); // Prints New line in Temp2.txt

    }

    fclose(ptr); // Closes Password.txt
    fclose(tempPtr); // Closes Temp2.txt

    remove("Password.txt"); // Deletes Password.txt 
    rename("Temp2.txt","Password.txt"); // Renames Temp2.txt 

}


/* Deletes an account */

void delete(char iD[50])
{

    FILE *ptr,*tempPtr;
    ptr = fopen("Info.txt","r+"); // Opnes Info.txt
    tempPtr = fopen("Temp.txt","w+"); // Opens Temp.txt

    char garbage[50]; // For comparing with Account Number
    int pos = position(iD); // Store positon of Account Number

    int lines = line(); // Number of lines in Info.txt

    fseek(ptr,0,SEEK_SET);  // Takes cursor in file to first position

    for(int k = 0 ; k < lines ; k++) // Copies the contents of Info.txt to Temp.txt
    {
        fscanf(ptr,"%s",&garbage); // Inputs one line into garbage variable
        if( k == pos || k == pos + 1 || k == pos + 2) 
        {
            // Does not Copy contents of the Account we want to delete
            continue;
        }
        fputs(garbage,tempPtr); // Inserts the line from Info.txt into Temp.txt
        if(k != lines - 1)fputs("\n",tempPtr); // Prints New line in Info.txt

    }

    fclose(ptr); // Closes Info.txt
    fclose(tempPtr); // Closes Temp.txt

    remove("Info.txt"); // Deletes Info.txt 
    rename("Temp.txt","Info.txt"); // Renames Temp.txt 
    endCorrection();

}

/* Creates new Account and its Pin-Code */

void createAcc(char iD[50])
{
    char name[50];
    double deposit;
    FILE *ptrs, *passptr;
    passptr = fopen("Password.txt", "r+"); 
    ptrs = fopen("Info.txt", "r+"); // appends the file
    fseek(ptrs,0,SEEK_SET); // Takes cursor in file to first position
    int pos = 0; // Store positon of Account Number
    int l = line();
    char garbage[50]; 
    
    while(EOF) // Finds the postion of Account Number
    {      
         
        fscanf(ptrs,"%s",&garbage);
        if(!(strcmp(garbage,iD)))
        {   
            break;
        }
        
        pos++;
        if(pos == l){
            break;
        }
    }
    if(pos == l) // if there is no already existing account ID
    { 
        int pin;
        fseek(ptrs,0,SEEK_END); // moves cursor in file to end position

        fseek(passptr,0,SEEK_END);

        fprintf(ptrs,"\n%s", iD); // prints account number in the file

        printf("Enter new pin : ");
        scanf("%d", &pin);
        fprintf(passptr, "\n%d", pin); // prints pin in password file

        printf("Enter account holder's name : "); 
        scanf("%s", &name);
        fprintf(ptrs,"\n%s",name); //prints account holder name in the file

        printf("Enter Deposit : ");
        scanf("%lf", &deposit);
        fprintf(ptrs, "\n%0.2lf", deposit); //prints deposit in the file
        printf("Account Succesfully Created!\n");
        
    }
    else // if account does exists
    {
        printf("Account already exists!!\n");
    }
    fclose(ptrs);
    fclose(passptr);
}

/* Returns the index of account in the Structure Account Array */
/* Returns -1 if does not exists */ 

int accountIndex(struct Account Arr[50], char temp[50])
{
    for(int i = 0 ; i < line()/3 ; i++)
    {
        if(!(strcmp(Arr[i].ID,temp)))
        {
            return i;
        }
    }
    return -1; 

}

/* checks the pin entered by user is correct or not */

int pin(char iD[50]){
    int p, pass;
    char garbage[50];
    printf("Enter pin : ");
    scanf("%d", &p);
    int pos = position(iD); // gives position of account number
    FILE *ps;
    ps = fopen("Password.txt", "r"); // reads file Password.txt
    for(int i = 0; i < pos / 3; i++){  
    
        fscanf(ps,"%s", &garbage); 
    }
    fscanf(ps, "%d", &pass); // stores the pin of the account

    if(p == pass) // if pin entered matches
    {     
        fclose(ps);
        return 1; 
    }
    else{
        printf("Pin is incorrect. Enter correct pin\n");
    }
    fclose(ps);
    return 0;
}



void main()
{   
    FILE *ptr,*passPtr;
    ptr = fopen("Info.txt","r+");
    if(ptr == NULL) ptr = fopen("Info.txt","w+"); // creates the file if does not exists
    fclose(ptr);

    struct Account Arr[50];
    char temp[50];
    int choice;
    int index;
    double tempAmount;
    int p;

    passPtr = fopen("Password.txt","r");
    if(passPtr == NULL)
    {
        printf("MISSING FILES\n");
        return;
    }
    fclose(passPtr);

    while(1)
    {   
        assign(Arr);

        printf("1.Account Details\n");
        printf("2.Deposit\n");
        printf("3.Withdraw\n");
        printf("4.Create Account\n");
        printf("5.Delete Account\n");
        printf("6.Number Of Account\n");
        printf("7.Quit\n");
        printf("What do you want to do : ");
        scanf("%d",&choice);

        if(choice == 6)
        {   
            system("cls");
            printf("Currently There Are %d Accounts Active!\n",line()/3);
            system("pause");
            system("cls");
            continue;
        }

        if(choice == 7)
        {
            system("cls");
            printf("THANK YOU");
            return;
        }

        else if(choice > 7 || choice < 1)
        {
            printf("Invalid input. Try again!\n");
            system("pause");
            system("cls");
            continue;
        }

        system("cls");
        printf("Enter Account Number : ");
        scanf("%s",&temp);
        

        index = accountIndex(Arr,temp);

        if(index == - 1 && choice != 4)
        {
            printf("Account does not exists\n");
            system("pause");
            continue;
        }

        switch (choice)
        {
        case 1:
            p = pin(temp);
            if(p == 1){
                display(Arr[index]);
            }
            system("pause");
            system("cls");
            break;

        case 2:
            p = pin(temp);
            if(p == 1){
                printf("Enter Amount you want to deposit : ");
                scanf("%lf",&tempAmount);
                modifyBalance(Arr[index].balance + tempAmount , Arr[index].ID);
                printf("Transaction Succesful!\n");
            }
            system("pause");
            system("cls");
            break;

        case 3:
            p = pin(temp);
            if(p == 1){
                printf("Enter Amount you want to withdraw : ");
                scanf("%lf",&tempAmount);
                if(tempAmount > Arr[index].balance)
                {
                    printf("Insufficient Balance\n");
                    system("pause");
                    system("cls");
                    break;
                }
                modifyBalance(Arr[index].balance - tempAmount , Arr[index].ID);
                printf("Transaction Succesful!\n");
            }
            system("pause");
            system("cls");
            break;

        case 4:
            createAcc(temp);
            system("pause");
            system("cls");
            break;

        case 5:
            p = pin(temp);
            if(p == 1){
                deletePin(index);
				delete(Arr[index].ID);
                printf("Account Succesfully Closed!\n");
            }
            if(pinLine() != (line()/3) )pinEndCorrection();
            
            system("pause");
            system("cls");
            break;

        default:
            break;
        }
    }
}