#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to print the player's hand of cards
void printHand(const char *hand[], int handSize) {
    printf("Your hand: ");
    for (int i = 0; i < handSize; i++) {
        printf("[%d] %s ", i, hand[i]);  // Display card index and card value
    }
    printf("\n");
}

// Function to draw a card from the deck and add it to the player's or computer's hand
void drawCard(const char *deck[], int *deckSize, const char **hand, int *handSize, int numCards) {
    for (int i = 0; i < numCards && *deckSize > 0 && *handSize < 20; i++) {
        hand[*handSize] = deck[*deckSize - 1];  // Take the last card from the deck
        (*handSize)++;  // Increase hand size
        (*deckSize)--;  // Decrease deck size
    }
}

// Function to check if a card is playable based on the top card
int isPlayable(const char *card, const char *topCard) {
    // A card is playable if it matches the color or number or is a special card (+2, +4)
    return (card[0] == topCard[0] || card[1] == topCard[1] || strcmp(card, "+4") == 0 || strcmp(card, "+2") == 0);
}

// Function to handle special cards (+2, +4, Reverse)
void handleSpecialCards(const char *card, const char *deck[], int *deckSize, const char **opponentHand, int *opponentHandSize, int *direction) {
    if (strcmp(card, "+2") == 0) {
        printf("The opponent must draw 2 cards!\n");
        drawCard(deck, deckSize, opponentHand, opponentHandSize, 2);  // Opponent draws 2 cards
    } else if (strcmp(card, "+4") == 0) {
        printf("\nThe opponent must draw 4 cards!\n");
        drawCard(deck, deckSize, opponentHand, opponentHandSize, 4);  // Opponent draws 4 cards
    } else if (strcmp(card, "RRev") == 0) {
        *direction = -(*direction);  // Reverse the direction of play
        printf("The direction of play has reversed!\n");
    }
}

int main(void) {
    // Define the card sets for red, green, blue, yellow, and wild cards
    const char *red[] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R+2", "R+2", "RRev"};
    const char *green[] = {"G0", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "G+2", "G+2", "GRev"};
    const char *blue[] = {"B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B+2", "B+2", "BRev"};
    const char *yellow[] = {"Y0", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9", "Y+2", "Y+2", "YRev"};
    const char *wild[] = {"+4", "+4"};  // Wild cards

    const char *deck[54];  // Total deck of cards
    const char *playerHand[20];  // Player's hand
    const char *computerHand[20];  // Computer's hand
    int deckSize = 54;  // Initial size of the deck
    int playerHandSize = 7;  // Player starts with 7 cards
    int computerHandSize = 7;  // Computer starts with 7 cards
    const char *topCard;  // The current top card
    int direction = 1;  // 1 for normal direction (left to right), -1 for reversed direction

    srand(time(NULL));  // Seed the random number generator

    // Populate the deck with the respective color and wild cards
    for (int i = 0; i < 13; i++) {
        deck[i] = red[i];
        deck[i + 13] = green[i];
        deck[i + 26] = blue[i];
        deck[i + 39] = yellow[i];
    }
    deck[52] = wild[0];  // Wild cards (+4)
    deck[53] = wild[1];  // Wild cards (+4)

    // Shuffle the deck by swapping random pairs of cards
    for (int i = 0; i < 54; i++) {
        int j = generateRandomNumber(0, 53);
        const char *temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    // Deal 7 cards to the player and computer
    for (int i = 0; i < 7; i++) {
        playerHand[i] = deck[i];
        computerHand[i] = deck[i + 7];
    }
    deckSize -= 14;  // 14 cards have been dealt
    topCard = deck[14];  // Set the top card to be the 15th card in the shuffled deck

    // Game loop: continue until either the player or the computer runs out of cards
    while (playerHandSize > 0 && computerHandSize > 0) {
        printf("\n----------------------------------\n");
        printf("\nTop card: %s\n", topCard);  // Display the top card
        printHand(playerHand, playerHandSize);  // Print the player's hand
        printf("Computer has %d cards.\n", computerHandSize);

        // Player's turn
        int playerChoice = -1;
        printf("Choose a card to play (0-%d) or draw (-1): ", playerHandSize - 1);

        // Validate input
        while (scanf("%d", &playerChoice) != 1 || (playerChoice != -1 && (playerChoice < 0 || playerChoice >= playerHandSize))) {
            // Clear invalid input
            while (getchar() != '\n');  // clear the buffer
            printf("Invalid input! Please choose a valid card (0-%d) or draw (-1): ", playerHandSize - 1);
        }

        // Handle the player's card choice
        if (playerChoice == -1) {
            drawCard(deck, &deckSize, playerHand, &playerHandSize, 1);  // Player draws a card
            printf("\n----------------------------------\n");
            printf("You drew a card!\n");
        } else if (isPlayable(playerHand[playerChoice], topCard)) {
            topCard = playerHand[playerChoice];  // Player plays a valid card
            printf("\n----------------------------------\n");
            printf("You played %s\n", topCard);
            handleSpecialCards(topCard, deck, &deckSize, computerHand, &computerHandSize, &direction);  // Handle special cards
            for (int i = playerChoice; i < playerHandSize - 1; i++) {
                playerHand[i] = playerHand[i + 1];  // Shift the remaining cards
            }
            playerHandSize--;  // Decrease hand size after playing a card
        }

        // Check if the player has won
        if (playerHandSize == 0) {
            printf("\nYou won!\n");
            break;
        }

        // Computer's turn
        int computerChoice = -1;
        for (int i = 0; i < computerHandSize; i++) {
            if (isPlayable(computerHand[i], topCard)) {
                computerChoice = i;  // Computer finds a playable card
                break;
            }
        }

        // If the computer can play a card, it does; otherwise, it draws a card
        if (computerChoice >= 0) {
            topCard = computerHand[computerChoice];  // Computer plays a valid card
            printf("Computer played %s", topCard);
            handleSpecialCards(topCard, deck, &deckSize, playerHand, &playerHandSize, &direction);  // Handle special cards
            for (int i = computerChoice; i < computerHandSize - 1; i++) {
                computerHand[i] = computerHand[i + 1];  // Shift the remaining cards
            }
            computerHandSize--;  // Decrease hand size after playing a card
        } else {
            drawCard(deck, &deckSize, computerHand, &computerHandSize, 1);  // Computer draws a card
            printf("Computer drew a card!");
        }

        // Check if the computer has won
        if (computerHandSize == 0) {
            printf("\nComputer won!");
            break;
        }
    }

    return 0;  // End of game
}
