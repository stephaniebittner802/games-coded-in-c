#include <stdio.h>
#include <string.h>
#include "ShoppingCart.h"
#include "ItemToPurchase.h"

ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart) {
    if (cart.cartSize < 10) { //Condition: Is the cart full?
        //cart.cartItems[cart.cartSize] = item; //Jumps to last index of the cart & adds item afterwar
        cart.cartItems[cart.cartSize].itemPrice = item.itemPrice;
        cart.cartItems[cart.cartSize].itemQuantity = item.itemQuantity;
        strcpy(cart.cartItems[cart.cartSize].itemName, item.itemName);
        strcpy(cart.cartItems[cart.cartSize].itemDescription, item.itemDescription);
        cart.cartSize++;
    } else {
        printf("Cart is full. Cannot add more items.\n");
    }
    return cart;
}

ShoppingCart RemoveItem(char itemName[], ShoppingCart cart) {
    int i = 0;
    int exists = 0; //0 if DNE 1 if item that is supposed to be deleted exists
    while (i < cart.cartSize) {
        if (strcmp(cart.cartItems[i].itemName, itemName) == 0) {
            exists = 1;
            break;
        }
        i++;
    }

    if (exists) {
        while (i < cart.cartSize - 1) {
            cart.cartItems[i] = cart.cartItems[i + 1];
            i++;
        }
        cart.cartSize--;
    } else {
        printf("Item not found in cart. Nothing removed.\n");
    }

    return cart;
}

ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart) {
    int i = 0;
    int exists = 0;
    while (i < cart.cartSize) {
        if (strcmp(cart.cartItems[i].itemName, item.itemName) == 0) {
            exists = 1;
            break;
        }
        i++;
    }

    if (exists) {
        if(item.itemPrice > 0){
        cart.cartItems[i].itemPrice = item.itemPrice;
        }
        if(item.itemQuantity > 0){
        cart.cartItems[i].itemQuantity = item.itemQuantity;
        }
        if(strcmp(item.itemName, "none") != 0){
        strcpy(cart.cartItems[i].itemName, item.itemName);
        }
        if(strcmp(item.itemDescription, "none") != 0){
        strcpy(cart.cartItems[i].itemDescription, item.itemDescription);
        }
    } else {
        printf("Item not found in cart. Nothing modified.\n");
    }
    return cart;
}

int GetNumItemsInCart(ShoppingCart cart) {
    int sumItems = 0;
    for (int i = 0; i < cart.cartSize; i++) {
        sumItems += cart.cartItems[i].itemQuantity;
    }
    return sumItems;
}

int GetCostOfCart(ShoppingCart cart) {
    int contentCost = 0;
    for (int i = 0; i < cart.cartSize; i++) {
        contentCost += cart.cartItems[i].itemQuantity * cart.cartItems[i].itemPrice;
    }
    return contentCost;
}

void PrintTotal(ShoppingCart cart) {
    
    printf("%s's Shopping Cart - %s\n", cart.customerName, cart.currentDate);
    printf("Number of Items: %d\n\n", GetNumItemsInCart(cart));
    
    if (cart.cartSize == 0) {
        printf("SHOPPING CART IS EMPTY\n");
    }
    for (int i = 0; i < cart.cartSize; i++) {
        PrintItemCost(cart.cartItems[i]);
    }

    printf("\nTotal: $%d\n", GetCostOfCart(cart));
    
}

void PrintMenu(ShoppingCart cart) {
    char option = 'a';
    do {
        if(option == 'a' || option == 'r' || option == 'c' || option == 'i' || option == 'o'){
            printf("\nMENU\n");
            printf("a - Add item to cart\n");
            printf("r - Remove item from cart\n");
            printf("c - Change item quantity\n");
            printf("i - Output items' descriptions\n");
            printf("o - Output shopping cart\n");
            printf("q - Quit\n");
            printf("\n");
        }
        printf("Choose an option:\n");
        scanf(" %c", &option);

        ItemToPurchase item;
        item.itemPrice = -1;
        item.itemQuantity = -1;
        char itemName[50];

        if(option == 'a') {
            printf("ADD ITEM TO CART\n");
            printf("Enter the item name:\n");
            scanf(" %[^\n]s", item.itemName);

            printf("Enter the item description:\n");
            scanf(" %[^\n]s", item.itemDescription);

            printf("Enter the item price:\n");
            scanf("%d", &item.itemPrice);

            printf("Enter the item quantity:\n");
            scanf("%d", &item.itemQuantity);

            cart = AddItem(item, cart);
        } else if(option == 'r'){
            printf("REMOVE ITEM FROM CART\n");
            printf("Enter name of item to remove:\n");
            scanf(" %[^\n]s", itemName);
            cart = RemoveItem(itemName, cart);
        } else if(option == 'c'){
            printf("CHANGE ITEM QUANTITY\n");
            printf("Enter the item name:\n");
            scanf(" %[^\n]s", item.itemName);

            printf("Enter the new quantity:\n");
            scanf("%d", &item.itemQuantity);

            cart = ModifyItem(item, cart);
        } else if(option == 'i'){
            printf("OUTPUT ITEMS' DESCRIPTIONS\n");
            PrintDescriptions(cart);
        } else if(option == 'o'){
            printf("OUTPUT SHOPPING CART\n");
            PrintTotal(cart);
            //PrintTotal(cart);
        } else if(option == 'q'){
            break;
        }
    } while (option != 'q');
}

void PrintDescriptions(ShoppingCart cart) {
    printf("%s's Shopping Cart - %s\n\n", cart.customerName, cart.currentDate);
    printf("Item Descriptions\n");

    for (int i = 0; i < cart.cartSize; i++) {
        PrintItemDescription(cart.cartItems[i]);
    }
}