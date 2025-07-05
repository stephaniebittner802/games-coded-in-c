/*
 solitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* 
   To compile: gcc solitairePoker.c
   To run: ./a.out
 */

//do not remove
#include "include.code"

// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);

void getnewcards();
void getcards();
int score();
void scoresheet();
void nameScore(int a);

int cards[5] = {0};
int scoreNumbers[10] = {0};
int cardlist[10][5];

int main(int argc, char ** argv) {
    seed(argc, argv);
    instructions();

    for(int round = 0; round < 10; round++){
        shuffle();
        getnewcards();
        printf("Select up to three cards to replace[1-5] and press enter\n");
        char replace[10];
        fgets(replace, 10, stdin);
        int count = 0;
        while(1){
            for(int i = 0; i < strlen(replace); i++){
                if(isdigit(replace[i])){
                    count++;
                }
            }
            if(count <= 3 && count >= 1){
                for(int i = 0; i < strlen(replace); i++){
                    if(isdigit(replace[i])){
                        cards[(replace[i]-'0') - 1] = nextcard();
                    }
                }
                break;
            } else if(count == 0){
                break;
            } else {
                printf("Please do not change more than three cards.");
            }
        }
        for(int k = 0; k < 5; k++){
            cardlist[round][k] = cards[k];
        }
        getcards();
        scoreNumbers[round] = score();
        printf("Hand %d: Score:    %d\n\n", round + 1, scoreNumbers[round]);
    }
    scoresheet();
    return 0;
}


void getnewcards(){
    for(int i = 0; i < 5; i++){
        cards[i] = nextcard();
        printf("%s-%s\t", suitNames[getsuit(cards[i])], rankNames[getrank(cards[i])]);

    }
    printf("\n");
}
void getcards(){
    for(int i = 0; i < 5; i++){
        printf("%s-%s\t", suitNames[getsuit(cards[i])], rankNames[getrank(cards[i])]);
    }
    printf("\n");
}

int score(){
    int result;
    result = royalflush(cards);
    if(result == 0){
        result = straightflush(cards);
        if(result == 0){
            result = fourofkind(cards);
            if(result == 0){
                result = straightflush(cards);
                if(result == 0){
                    result = fullhouse(cards);
                    if(result == 0){
                        result = flush(cards);
                        if(result == 0){
                            result = straight(cards);
                            if(result == 0){
                                result = threekind(cards);
                                if(result == 0){
                                    result = twopair(cards);
                                    if(result == 0){
                                        result = pair(cards);
                                        if(result == 0){
                                            result = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

void scoresheet(){
    int total = 0;
    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");
    for(int i = 0; i < 10; i++){
        printf("Hand %2d: Score: %5d ", i + 1, scoreNumbers[i]);
        nameScore(scoreNumbers[i]);
        printf(" [");
        for(int k = 0; k < 5; k++){
        printf("%2d%8s-%-6s\n", cardlist[i][k], suitNames[getsuit(cardlist[i][k])], rankNames[getrank(cardlist[i][k])]);
        }
        printf("]\n");
        total += scoreNumbers[i];
    }
    //printf("\n");
    printf("==============================================================================\n");
    printf("Total points:      %d \n", total);
    printf("==============================================================================\n");
}

void nameScore(int a){
    if(a == 50){
        printf("%-13s", "ROYAL FLUSH");
    }
    if(a == 45){
        printf("%-13s", "STRAIGHT FLUSH");
    }
    if(a == 40){
        printf("%-13s", "QUADS");
    }
    if(a == 32){
        printf("%-13s", "FULL HOUSE");
    }
    if(a == 26){
        printf("%-13s", "FLUSH");
    }
    if(a == 17){
        printf("%-13s", "STRAIGHT");
    }
    if(a == 11){
        printf("%13s", "TRIPS");
    }
    if(a == 7){
        printf("%-13s", "TWO PAIR");
    }
    if(a == 3){
        printf("%-13s", "PAIR");
    }
    if(a == 1){
        printf("%-13s", "HIGHCARD");
    }

}

// Function to get the suit of a card
enum suits getsuit(int card){
    if (card >= 0 && card <= 12) {
        return CLUB;
    } else if (card >= 13 && card <= 25) {
        return DIAMOND;
    } else if (card >= 26 && card <= 38) {
        return HEART;
    } else if (card >= 39 && card <= 51) {
        return SPADE;
    }
    return 0;
}

// Function to get the rank of a card
enum ranks getrank(int card){
    if(card % 13 == 0){
        return ACE;
    } else if(card % 13 == 1){
        return TWO;
    } else if(card % 13 == 2){
        return THREE;
    } else if(card % 13 == 3){
        return FOUR;
    } else if(card % 13 == 4){
        return FIVE;
    } else if(card % 13 == 5){
        return SIX;
    } else if(card % 13 == 6){
        return SEVEN;
    } else if(card % 13 == 7){
        return EIGHT;
    } else if(card % 13 == 8){
        return NINE;
    } else if(card % 13 == 9){
        return TEN;
    } else if(card % 13 == 10){
        return JACK;
    } else if(card % 13 == 11){
        return QUEEN;
    } else if(card % 13 == 12){
        return KING;
    }
    return 0;
}

// Function to evaluate the poker hand
enum hands eval(int hand[]){
    //"UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    //"FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand
    return 0;
}

// Function to check for a royal flush
int royalflush(int hand[]){
    int clubs = 0;
    int diamonds = 0;
    int hearts = 0;
    int spades = 0;
    for(int i = 0; i < 5; i++){
        if ((hand[i] >= 9 && hand[i] <= 12) || hand[i] == 0) {
            clubs++;
        } else if ((hand[i] >= 22 && hand[i] <= 25) || hand[i] == 13) {
            diamonds++;
        } else if ((hand[i] >= 35 && hand[i] <= 38) || hand[i] == 26) {
            hearts++;
        } else if ((hand[i] >= 48 && hand[i] <= 51) || hand[i] == 39) {
            spades++;
        }
    }
    if(clubs == 5 || spades == 5 || diamonds == 5 || hearts == 5){
        return 50; //50 points
    }
    return 0;
}

// Function to check for a straight flush
int straightflush(int hand[]){
    //bubblesort
    int temp;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5 - i - 1; j++){
            if(hand[j] > hand[j+1]){
                temp = hand[j];
                hand[j] = hand[j+1];
                hand[j+1] = temp;
            }
        }
    }
    for(int i = 0; i < 4; i++){
        if(hand[i+1] != hand[i] + 1){
            return 0;
        }
    }
    return 45; //45 points
}

// Function to check for a flush
int flush(int hand[]){
    int clubs = 0;
    int diamonds = 0;
    int hearts = 0;
    int spades = 0;
    for(int i = 0; i < 5; i++){
        if (hand[i] >= 0 && hand[i] <= 12) {
            clubs++;
        } else if (hand[i] >= 13 && hand[i] <= 25) {
            diamonds++;
        } else if (hand[i] >= 26 && hand[i] <= 38) {
            hearts++;
        } else if (hand[i] >= 39 && hand[i] <= 51) {
            spades++;
        }
        if(clubs == 5 || diamonds == 5 || hearts == 5 || spades == 5){
            return 26;
        }
    }
    return 0;
}

// Function to check for a straight
int straight(int hand[]){
    int arr[13] = {0};
    int consec = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;
    }
    for(int i = 0; i < 13; i++){
        if(arr[i] >= 1){
            for(int j = i+1; j < i+5; j++){
                if(arr[j] != 1){
                    return 0;
                }
            }
            break;
        }
    }
    return 17;
}

// Function to check for four of a kind
int fourofkind(int hand[]){
    int arr[13] = {0};//rank
    int four = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;

    }
    for(int i = 0; i < 13; i++){
        if(arr[i] == 4){
            four++;
        }
    }
    if(four == 1){
        return 40;
    }

    return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){
    int arr[13] = {0};
    int three = 0;
    int two = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;
    }
    for(int i = 0; i < 13; i++){
        if(arr[i] == 2){
            two++;
        }
        if(arr[i] == 3){
            three++;
        }
    }
    if(two == 1 && three == 1){
        return 32;
    }

    return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){
    int arr[13] = {0};
    int three = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;
    }
    for(int i = 0; i < 13; i++){
        if(arr[i] == 3){
            three++;
        }
    }
    if(three == 1){
        return 11;
    }
    return 0;
}

// Function to check for two pairs
int twopair(int hand[]){
    int arr[13] = {0};
    int two = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;
    }
    for(int i = 0; i < 13; i++){
        if(arr[i] == 2){
            two++;
        }
    }
    if(two == 2){
        return 7;
    }
    return 0;
    return 0;
}

// Function to check for a pair
int pair(int hand[]){
    int arr[13] = {0};
    int two = 0;
    for(int i = 0; i < 5; i++){
        arr[hand[i] % 13]++;
    }
    for(int i = 0; i < 13; i++){
        if(arr[i] == 2){
            two++;
        }
    }
    if(two == 1){
        return 3;
    }
    return 0;
}