#include <stdio.h>
#include "ShoppingCart.h"
#include "ItemToPurchase.h"
#include <string.h>

int main() {
    char customerName[50];
    char currentDate[20];
    char option = 'a';

    printf("Enter Customer's Name:\n");
    scanf(" %[^\n]s", customerName);

    printf("Enter Today's Date:\n");
    scanf(" %[^\n]s", currentDate);

    printf("\n");
    printf("Customer Name: %s\n", customerName);
    printf("Today's Date: %s\n", currentDate);

    ShoppingCart cart;
    cart.cartSize = 0;
    //MakeItemBlank(&(cart.cartItems[0]));
    strcpy(cart.customerName, customerName);
    strcpy(cart.currentDate, currentDate);

        PrintMenu(cart);

    return 0;
}