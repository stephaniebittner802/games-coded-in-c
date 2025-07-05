
# C Games Collection

This repository contains a collection of interactive games built in C, including:

1. **YahtC**: A dice game inspired by Yahtzee. Players roll dice, select which to reroll, and then score their hands based on various combinations such as "Full House," "Flush," and "Straight."

2. **Solitaire Poker**: A solitaire-style poker game. The goal is to achieve the best possible poker hand. The game includes multiple rounds where cards can be replaced, and it evaluates the player's hand for different poker hands such as "Royal Flush" and "Four of a Kind."

3. **Online Shopping Cart**: A simulation of an online shopping cart. Users can add items, remove them, modify quantities, and view a detailed list of items with their prices and quantities. The program keeps track of the total cost of the cart and provides different operations, e.g., item descriptions and total calculation.

## Playing the Games:
- **YahtC**:
  - Roll dice up to three times.
  - Choose dice to reroll.
  - Score based on combinations like "5 of a kind" or "Full House."

- **Solitaire Poker**:
  - Shuffle and deal cards.
  - Replace up to three cards in each round.
  - Score based on poker hands and display results after each round.

- **Online Shopping Cart**:
  - Add, remove, or modify items in the cart.
  - Calculate total cost based on item prices and quantities.
  - Print item descriptions and total cart value.

## Compilation and Running:
1. To compile and run **YahtC**:
   ```bash
   gcc yahtC.c -o yahtC
   ./yahtC
   ```
2. To compile and run **Solitaire Poker**:
   ```bash
   gcc solitairePoker.c -o solitairePoker
   ./solitairePoker
   ```
3. To compile and run **Online Shopping Cart**:
   ```bash
   gcc main.c ShoppingCart.c ItemToPurchase.c -o shoppingCart
   ./shoppingCart
   ```

