    /*
1.Display(DONE)
2.Withdraw(DONE)
3.Deposit(DONE)
4.Create(Optional)
5.Delete(Optional)
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Account
{
    char ID[50];
    char Name[50];
    double balance;
};

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

/* Reads Info.txt and fills the array with data */

void assign(struct Account Arr[10])
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
    printf("Info Of Account Holder : %s\n",Acc.Name);
    printf("Account Number : %s\n",Acc.ID);
    printf("Balance : %0.2f\n",Acc.balance);
}

/* Modifies the Info.txt while withdrawing and depositing */

/*void modifyBalance(double Balance , char iD[50])
{   
    FILE *ptr,*tempPtr;
    ptr = fopen("Info.txt","r+"); // Opnes Info.txt
    tempPtr = fopen("Temp.txt","w+"); // Opens Temp.txt

    char garbage[50]; // For comparing with Account Number
    int pos = 0; // Store positon of Account Number

    int lines = line();

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

    fseek(ptr,0,SEEK_SET);  // Takes cursor in file to first position

    for(int k = 0 ; k < lines ; k++) // Copies the contents of Info.txt to Temp.txt
    {
        fscanf(ptr,"%s",&garbage); // Inputs one line into garbage variable
        if( k == pos + 2) // Hits balance of required Account Number
        {
            sprintf(garbage, "%f", Balance); // Converts Balance double to a string
            fputs(garbage,tempPtr); //  Inserts new Balance in place of old
            fputs("\n",tempPtr); // Prints New line in Info.txt
            continue;
        }
        fputs(garbage,tempPtr); // Inserts the line from Info.txt into Temp.txt
        fputs("\n",tempPtr); // Prints New line in Info.txt
            
    }
    
    fclose(ptr); // Closes Info.txt
    fclose(tempPtr); // Closes Temp.txt

    remove("Info.txt"); // Deletes Info.txt (with old balance)
    rename("Temp.txt","Info.txt"); // Renames Temp.txt (with new balance)
    
}*/

//creates account 

void create_acc(double Balance , char iD[50])
{
    char ac[50], name[50];
    double deposit;
    FILE *ptrs;
    ptrs = fopen("Info.txt", "a+"); // appends the file
    printf("Enter Account number:\n");
    scanf("%s", &ac);
    fseek(ptrs,0,SEEK_SET); // Takes cursor in file to first position
    int pos = 0; // Store positon of Account Number
    int l = line();
    char garbage[50]; 
    
    while(EOF) // Finds the postion of Account Number
    {      
         
        fscanf(ptrs,"%s",&garbage);
        if(!(strcmp(ac,iD)))
        {   
            break;
        }
        
        pos++;
        if(pos == l){
            break;
        }
    }
    if(pos == l){ // if there is no already existing account ID
        fseek(ptrs,0,SEEK_END); // moves cursor in file to end position
        fprintf(ptrs,"\n%s", ac); // prints account number in the file
        printf("Enter account holder's name: \n"); 
        scanf("%s", &name);
        fprintf(ptrs,"\n%s",name); //prints account holder name in the file
        printf("Enter Deposit: ");
        scanf("%lf", &deposit);
        fprintf(ptrs, "\n%lf", deposit); //prints deposit in the file
    }
    else{
        printf("Account already exists!!");
    }
    fclose(ptrs);
}

void main()
{
    struct Account Arr[10];


    assign(Arr);

   // display(Arr[1]);

    double f = 25.8;

    /*modifyBalance(Arr[1].balance-f,Arr[1].ID);
    assign(Arr);
    display(Arr[1]);  */

    create_acc(Arr[1].balance-f,Arr[1].ID);
}
