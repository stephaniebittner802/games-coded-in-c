#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 
   To compile: gcc yahtC.c
   To run: ./a.out
 */

int roll();
int rollRound();
int score(char[]);
void scoresheet();

int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;
int r5 = 0;
int r6 = 0;
int r7 = 0;


void seed(int argc, char ** argv){
    srand(time(NULL)); // Initialize random seed
    if (argc>1){
        int i;
        if (1 == sscanf(argv[1],"%d",&i)){
            srand(i);
        }
    }
}
void instructions(){
    printf("\n\n\n\n"
           "\t**********************************************************************\n"
           "\t*                         Welcome to YahtC                            *\n"
           "\t**********************************************************************\n"
           "\tYahtC is a dice game (very) loosely modeled on Yahtzee\n"
           "\tBUT YahtC is not Yahtzee.\n\n"
           "\tRules:\n"
           "\t5 dice are rolled\n"
           "\tThe user selects which dice to roll again.\n"
           "\tThe user may choose to roll none or all 5 or any combination.\n"
           "\tAnd then the user selects which dice to roll, yet again.\n"
           "\tAfter this second reroll the turn is scored.\n\n"
           "\tScoring is as follows:\n"
           "\t\t*\t50 points \t5 of a kind scores 50 points.\n"
           "\t\t*\t45 points \tNo pairs (all unique) scores 45 points.\n"
           "\t\t*\t40 points \t4 of a kind scores 40 points.\n"
           "\t\t*\t30 points \t3 of a kind scores 30 points.\n"
           "\t\t*\tTotal Dice\tOtherwise score the dice total.\n\n"
           "\tTo indicate nothing to reroll the user will input 0\n"
           "\tThis should end the players turn.\n"
           "\tOtherwise the user will indicate which dice to reroll by position\n"
           "\t135 would indicate to reroll the first, third and last die.\n"
           "\tThe numbers do not have to be given in order\n"
           "\tThe game ends after 7 turns.\n"
           "\t**********************************************************************\n\n\n");
           }
int main(int argc, char ** argv){
    seed(argc, argv);
    instructions();
    r1 = rollRound();
    r2 = rollRound();
    r3 = rollRound();
    r4 = rollRound();
    r5 = rollRound();
    r6 = rollRound();
    r7 = rollRound();
    scoresheet();
    return 0;
}


int roll(){
   int x = (rand()%6)+1;
   return x;
}

char fiveStr[5];
void fiveRolls(char fiveR[]) {
   for(int i = 0; i < 5; i++){
      fiveR[i] = roll() + '0';
      fiveStr[i] = fiveR[i];
   }
   fiveStr[5] = '\0';
}

int x;
int rollRound(){
   fiveRolls(fiveStr);
   printf("First Roll = %s\n", fiveStr);
   printf("Select dice to reroll:");
   scanf("%d", &x);
   int diceBackwards[5] = {0};
   int j = 0;
   if(x > 0){
      while(x > 0){
         diceBackwards[j] = x%10;
         x /= 10;
         j++;
      }
      for(int i = 4; i >= 0; i--){
         if(diceBackwards[i] != 0){
            fiveStr[diceBackwards[i] - 1] = roll() + '0';
         }
      }
      printf("second: %s\n", fiveStr);
      printf("Select dice to reroll:");
      scanf("%d", &x);
      j = 0;
      if(x > 0){
         for(int i = 0; i < 5; i++){ //reset array
            diceBackwards[i] = 0;
         }
         while(x > 0){
            diceBackwards[j] = x%10;
            x /= 10;
            j++;
         }
         for(int i = 4; i >= 0; i--){
            if(diceBackwards[i] != 0){
               fiveStr[diceBackwards[i] - 1] = roll() + '0';
            }
         }
      }
   }
   printf("final: %s\n", fiveStr);
   return score(fiveStr);
}

int score(char fiveStr[]){
   int one = 0;
   int two = 0;
   int three = 0;
   int four = 0;
   int five = 0;
   int six = 0;
   int k;
   int uno = 0;
   for(int i = 0; i < 5; i++){
      if(fiveStr[i] == '1'){
         one++;
      }
      if(fiveStr[i] == '2'){
         two++;
      }
      if(fiveStr[i] == '3'){
         three++;
      }
      if(fiveStr[i] == '4'){
         four++;
      }
      if(fiveStr[i] == '5'){
         five++;
      }
      if(fiveStr[i] == '6'){
         six++;
      }
   }
   if(one == 1){
      uno++;
   }
   if(two == 1){
      uno++;
   }
   if(three == 1){
      uno++;
   }
   if(four == 1){
      uno++;
   }
   if(five == 1){
      uno++;
   }
   if(six == 1){
      uno++;
   }
   if(one == 5 || two == 5 || three == 5 || four == 5 || five == 5 || six == 5){
      k = 50;
   } else if(uno == 5){
      k = 45;
   } else if(one == 4 || two == 4 || three == 4 || four == 4 || five == 4 || six == 4){
      k = 40;
   } else if(one == 3 || two == 3 || three == 3 || four == 3 || five == 3 || six == 3){
      k = 30;
   } else {
      k = one + 2 * two + 3 * three + 4 * four + 5 * five + 6 * six;
   }
   printf("score for %s is %d\n", fiveStr, k);
   printf("\n");
   return k;
}

void scoresheet(){
   printf("----------\n");
   printf("SCORESHEET\n");
   printf("----------\n");
   printf("Turn 1: %d\n", r1);
   printf("Turn 2: %d\n", r2);
   printf("Turn 3: %d\n", r3);
   printf("Turn 4: %d\n", r4);
   printf("Turn 5: %d\n", r5);
   printf("Turn 6: %d\n", r6);
   printf("Turn 7: %d\n", r7);
   printf("==========\n");
   printf("Total: %d\n", r1 + r2 + r3 + r4 + r5 + r6 + r7);
}