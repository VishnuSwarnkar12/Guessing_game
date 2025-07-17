#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

const char* ACCOUNT_FILE = "account.dat";

void create_acc();
void deposit_money();
void withdraw_money();
void check_balance();

typedef struct {
   char name[100];
   int acc_no;
   float bal;
}Account;

int main(){
 int choice;
    while(1){
        printf("\n***Banking Management System*** ");
        printf("\n 1. Create Account ");
        printf("\n 2. Deposit Money ");
        printf("\n 3. Withdraw Money");
        printf("\n 4. Check Balance  ");
        printf("\n 5. Exit ");
        printf("\n Enter Your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
              create_acc();
              break;
            case 2:
              deposit_money();
            
              break;
            case 3:
              withdraw_money();
              break;
            case 4:
              check_balance();
              break;
            case 5:
              printf("\n Closing the Bank. Thanks for your visit.");
              return 0;
              break;        
            default:
              printf("\n invalid choice");
              break;  
        }
        
    }


    return 0;

}

void create_acc(){
  Account acc;
  FILE *file = fopen(ACCOUNT_FILE,"ab+");
  if (file == NULL) {
    printf("\n Unable to open file!!");
    return;
  }
  char c;
  do {
    c = getchar();
  } while(c != '\n' && c != EOF );
  printf("\n Enter your name : ");
  fgets(acc.name, sizeof(acc.name), stdin);
  int ind = strcspn(acc.name, "\n");
  acc.name[ind] = '\0';
  printf("\n Enter your account number ");
  scanf("%d",&acc.acc_no);
  acc.bal = 0;
  fwrite(&acc, sizeof(acc), 1, file);
  fclose(file);
  printf("\n Account created successfully  \n");

}

void deposit_money(){
  FILE *file = fopen(ACCOUNT_FILE,"rb+");
    if (file == NULL) {
    printf("\n Unable to open file!!");
    return;
  }
 int acc_no;
 float money;
 Account acc_to_read;
  printf("\nEnter your Account no. : ");
   scanf("%d",&acc_no);
  printf("\n Enter amount to deposit : ");
   scanf("%f",&money);
  
   while(fread(&acc_to_read, sizeof(acc_to_read),1,file)) {
      if(acc_to_read.acc_no == acc_no){
        acc_to_read.bal += money;
        fseek(file, - sizeof(acc_to_read), SEEK_CUR);
        fwrite(&acc_to_read, sizeof(acc_to_read),1,file);
        fclose(file);

        printf("\n Successfully Deposited Rs. %.2f  Current Account balance is : %.2f\n ",money,acc_to_read.bal);
        
        return ;
      }
   }

   fclose(file);
   printf("Money could not be deposited because Account no. %d not found in records",acc_no);
}

void withdraw_money(){
 FILE *file = fopen(ACCOUNT_FILE,"rb+");
 if( file == NULL) {
  printf("\n unable to open file \n");
  return ;
 }
 int acc_no;
 float money;
 Account acc_to_read;
 printf("\n Enter your account no.");
  scanf("%d",&acc_no);
 printf("\n Enter amount you wish to withdraw : ");
  scanf("%f",&money);

  while(fread(&acc_to_read, sizeof(acc_to_read),1,file) != EOF) {
    if(acc_to_read.acc_no == acc_no) {
      if(acc_to_read.bal >= money) {
        acc_to_read.bal -= money;
        fseek(file, -sizeof(acc_to_read), SEEK_CUR);
        fwrite(&acc_to_read, sizeof(acc_to_read), 1, file);
        printf("\nSuccessfully withdrawn Rs.%.2f Remaining balance: Rs.%.2f",money,acc_to_read.bal);
      } else {
        printf("\n Insufficient balance !!");
      }
      fclose(file);
      return ;
    }
  }
  fclose(file);
  printf("Money could not be withdrawn because Account no. %d not found in records",acc_no);
}

void check_balance(){

 
    FILE *file = fopen(ACCOUNT_FILE,"rb");
    if (file == NULL) {
    printf("\n Unable to open file!!");
    return;
  }

    int acc_no;
    Account acc_read;

 printf("\n Enter your account number ");
  scanf("%d",&acc_no);

  while(fread(&acc_read, sizeof(acc_read), 1 , file)){
    if(acc_read.acc_no == acc_no) {
        printf("your current account balance is rs. %.2f ",acc_read.bal);
        fclose(file);
        return;
    }
  }
  fclose(file);
  printf("\n Account no. %d was not found!!\n", acc_no);
}
