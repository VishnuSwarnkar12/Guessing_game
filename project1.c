#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand(time(NULL));
    int random , guess;
    int NOG = 0;
    printf("welcom to the world of guessing numbers...\n");
    random = rand() % 100 +1;// generating random no.
    
    
    do{
        printf("enter a number between 1 to 100 \n");
        scanf("%d",&guess);
        NOG++;

        if( guess < random){

            printf("guess a larger number..\n");
        } else if(guess > random){
            printf("guess a smaller number..\n");
        }else {
            printf("congraulations !!! you have successfully guessed the number in %d attempts.\n",NOG);
        }
       
    }while(guess != random);

    printf("\n Bye Bye This game was a copy");
    return 0;
}