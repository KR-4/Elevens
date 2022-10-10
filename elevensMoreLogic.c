#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Declaring variables
char RANKS[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
char SUITS[4][1] = {"D", "C", "H", "S"};

// Define a card struct
struct card{
                int cardValue;
                char cardName[4];
                bool isDealt;
                string rank;
                string suit_symbol;
            };

//Creating the 40 cards in the deck
struct card cards[52];

//Function Prototypes
void printIntroduction();
void chooseGameMode();
int randomNum(int range);
void initializeDeck();
void initializeGrid();
void printGrid();
void userSelectCards();
bool checkIfInGrid(char cardSelected[]);
int findIndex(char cardSelected[]);
bool checkIfValidChoice(int numCardsSelected);
int findInGrid(int cardSelectedIndex);
void changeCards();
bool checkIfPlayable();
int yesOrNo();
void resetValues();

int main()
{

}

// Print the introduction
void printIntroduction()
{

}

// Ask the user to choose single player or multiplayer
// Ask the user to choose between 11s and 13s
void chooseGameMode()
{

}

// Ask the user to choose the game mode
void chooseGameMode()
{

}

// Return a random integer within the range passed
int randomNum(int range)
{
    return 0;
}

// Assign a value and rank to each of the 40 cards
void initializeDeck()
{

}

// Initialize the current grid
void initializeGrid()
{

}

// Print the current grid
void printGrid()
{

}

// Take card choices from users
void userSelectCards()
{

}

// Check if the chosen card is in the current grid
bool checkIfInGrid(char cardSelected[])
{
    return false;
}

// Return the index (in the cards array) of the card name chosen
int findIndex(char cardSelected[])
{
    return 0;
}

// Check if the user entered a valid choice
bool checkIfValidChoice(int cardsSelected)
{
    return false;
}

// Returns position of card in grid array
int findInGrid(int cardSelectedIndex)
{
    return 0;
}

// Changes 2 cards if the user made a numerical combination
// Or changes 3 cards if the user chose a Jack, Queen, King combination
void changeCards()
{

}

// Returns a boolean depending on if there is a possible combination in the current grid
bool checkIfPlayable()
{
    return false;
}

// ask the user to enter 'yes' or 'no', and return integer based on response
int yesOrNo()
{
    return 0;
}

// reset all values
void resetValues()
{

}