#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "ItemToPurchase.h"

/* 
   To compile: gcc main.c ShoppingCart.c ItemToPurchase.c
   To run: ./a.out
 */

typedef struct ShoppingCart {
    char customerName[50];
    char currentDate[20];
    ItemToPurchase cartItems[10];
    int cartSize;
} ShoppingCart;

ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart);
ShoppingCart RemoveItem(char itemName[], ShoppingCart cart);
ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart);
int GetNumItemsInCart(ShoppingCart cart);
int GetCostOfCart(ShoppingCart cart);
void PrintTotal(ShoppingCart cart);
void PrintDescriptions(ShoppingCart cart);
void PrintMenu(ShoppingCart cart);

#endif