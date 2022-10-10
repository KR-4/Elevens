#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


// Declaring variables
char RANKS[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
char SUITS[4][1] = {"D", "C", "H", "S"};
string SUIT_SYMBOL[4] = {"♦", "♣", "♥", "♠"};
bool playAgain = true;
int grid[9];
int numPlayers;
int gameMode;
char firstCardSelected[4];
int firstCardSelectedIndex;
char secondCardSelected[4];
int secondCardSelectedIndex;
char thirdCardSelected[4];
int thirdCardSelectedIndex;
int numCardsSelected;
int gridIndex;
int score;
int roundNum = 1;
int playerOneScore;
int playerTwoScore;

// Define a card object
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
    // Print the introduction
    printIntroduction();

    // Ask the user to choose what variant of the game they wish to play
    chooseGameMode();
    printf("\nOK, LET'S PLAY!\n");

    // Call the initializeDeck() function to create a deck of 52 cards
    initializeDeck();

    // Populate the grid array with the indexes of 9 different cards
    initializeGrid();

    // Enter this loop when the user wants to play the game
    while(playAgain)
    {
        // checkIfPlayable() function checks if there are any possible combinations in the current grid of cards
        while(checkIfPlayable())
        {
            printf("\n\nRound %i\n", roundNum);
            printf("5 ");
            sleep(1);
            printf("4 ");
            sleep(1);
            printf("3 ");
            sleep(1);
            printf("2 ");
            sleep(1);
            printf("1 ");
            sleep(1);
            printf("GO! \n");
            sleep(1);

            // Execute if the user chose to play multiplayer
            if(numPlayers == 2)
            {
                // All odd numbered rounds are Player One's turns
                if(roundNum % 2 == 1)
                {
                    printf("It is Player One's turn!\n");
                }else // Even numbered rounds are Player Two's turns
                {
                    printf("It is Player Two's turn!\n");
                }
            }

            // Print the current 3x3 grid of cards
            printGrid();

            // Take the user's chosen cards and store their indexes
            userSelectCards();

            // Replace the cards the user chose with new cards
            changeCards();

            // If the user chose multiplayer, print the score of the current player (either player 1 or 2)
            // If the user chose single player, print their score
            if(numPlayers == 2)
            {
                if(roundNum % 2 == 1)
                {
                    printf("\n************************\n Player One's Score: %i \n************************\n", playerOneScore);
                }else
                {
                    printf("\n************************\n Player Two's Score: %i \n************************\n", playerTwoScore);
                }
            }else
            {
                printf("\n************\n Score: %i \n************\n", score);
            }
            roundNum++;
        }

        printf("\n\nRound %i\n", roundNum);
        printf("5 ");
        sleep(1);
        printf("4 ");
        sleep(1);
        printf("3 ");
        sleep(1);
        printf("2 ");
        sleep(1);
        printf("1 ");
        sleep(1);
        printf("GO! \n");
        sleep(1);
        // Print the current grid one last time
        printGrid();
        printf("\nLooks like you ran out of combinations!\n");
        sleep(1);

        // If multiplayer chosen, print the final scores of each player
        // If single player chosen, print final score
        if(numPlayers == 2)
        {
            printf("\nThank you for playing!\n");
            printf("Player One's final score was: %i\n", playerOneScore);
            printf("Player Two's final score was: %i\n", playerTwoScore);
        }else // Single player score
        {
            printf("\nThank you for playing!\nYour final score was: %i\n", score);
        }

        // Ask the users if they want to play again or not
        printf("Do you want to play again? (Enter Yes or No)\n");
        int play = -1;
        do
        {
            // yesOrNo() returns an integer depending on the user's response
            // Returns 1 for yes and 0 for no
            play = yesOrNo();
        }while(play == -1);

        // If play is equal to 1, the user wants to play again
        if(play == 1)
        {
            // Reset all the scores to 0 and isDealt to false
            resetValues();
            initializeGrid();
            printf("\nOk, great! Let's play again!\n");
            chooseGameMode();
        }else // play must be equal to 0 and the user wants to quit
        {
            printf("\nThank you for playing ElevensMore!\n");
            printf("We hope you enjoyed playing!\n");
            printf("Have a good day!\n");
            playAgain = false;
            break;
        }
    }
}

// Prints the introduction statements, along with the rules of the game
void printIntroduction()
{
    printf("****************************************************************************************************\n");
    printf("\nWELCOME TO ELEVENSMORE!\n\n");
    sleep(1);
    printf("In this game, you will have to make one of two different types of combinations to win the round\n");
    printf("The first type of combination involves choosing a Jack, Queen and King combination.\n");
    printf("The second type of combination involves choosing two cards that add up to a certain sum.\n");
    printf("If you cannot make either of these two combinations, you have lost.\n\n");
    sleep(2);
    printf("If you choose to play the elevens game mode, the two cards must add up to 11.\n");
    printf("If you choose to play the thirteens game mode, the two cards must add up to 13.\n\n");
    sleep(2);
    printf("You can also choose to play single player or multiplayer.\n\n");
    sleep(2);
    printf("When choosing cards, enter the rank first, then the suit.\n");
    printf("For example, if you want to choose Ace of Spades, you would enter AS\n\n");
    printf("Good luck and have fun!\n");
    printf("\n****************************************************************************************************\n");
    sleep(2);
}

// Ask the user to choose single/multiplayer and 11s/13s
void chooseGameMode()
{
    // Prompt the user to enter if they want to play single player or multiplayer
    printf("\nDo you want to play single player or multiplayer (up to two people total)?");
    do
    {
        printf("\nEnter 1 for single player and 2 for multiplayer:\n");
        scanf("%i", &numPlayers);
        if(numPlayers == 1 || numPlayers == 2)
        {
            break;
        }
    }while(true);

    // Ask the user if they want to play the elevens or thirteens game mode
    do
    {
        printf("\nNow, do you want to play 11s or 13s? (11 for elevens and 13 for thirteens)\n");
        scanf("%i", &gameMode);
        if(gameMode == 11 || gameMode == 13)
        {
            break;
        }
    }while(true);
}

// Take a integer range as a parameter
// Return a random integer within that range
int randomNum(int range)
{
    return (rand()%range);
}

// Assign a value and rank to each of the 52 cards
void initializeDeck()
{
    int y = 0;
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            // Initialize card if it is a 10
            if(i == 9)
            {
                // Assign the rank to the card
                cards[y].cardName[0] = RANKS[i][0];
                cards[y].cardName[1] = RANKS[i][1];
                // Assign the suit to the card
                cards[y].cardName[2] = SUITS[j][0];
            }else // All other ranks in the deck
            {
                // Assign the rank to the card
                cards[y].cardName[0] = RANKS[i][0];
                // Assign the suit to the card
                cards[y].cardName[1] = SUITS[j][0];
            }

            // Assign the card value
            cards[y].cardValue = i + 1;

            // Set the boolean isDealt to false,
            // Since the card has not been dealt yet
            cards[y].isDealt = false;

            // Assign the rank and suit symbol separately
            // Simplifies when printing cards in grid
            cards[y].rank = RANKS[i];
            cards[y].suit_symbol = SUIT_SYMBOL[j];

            y++;
        }
    }
}

// Initialize the current grid
void initializeGrid()
{
    // srand allows for an argument seed to be passed (seed is where computer starts generating the random numbers from)
    // Since time is always changing, argument seed will never be the same; a different sequence of numbers will always be generated
    srand(time(NULL));

    int index;
    for(int i = 0; i < 9; i++)
    {
            do
            {
                // Get a random card from the deck
                index = randomNum(52);
            }while(cards[index].isDealt);

            // Assign the index of the card in the cards array to the grid array
            // Therefore, the grid array will hold 9 indexes of cards
            grid[i] = index;

            // Set the boolean isDealt to true, since the card is dealt
            cards[index].isDealt = true;
    }
}

// Print the current grid
void printGrid()
{
    // Index in grid array of first card to be printed in that row
    int firstIndex = 0;
    // Index in grid array of second card to be printed in that row
    int secondIndex = 1;
    // Index in grid array of third card to be printed in that row
    int thirdIndex = 2;


    int counter;
    int limit;

    for(int j = 0; j < 3; j++)
    {
        // Printf("%s   ", cards[grid[k]].cardName);
        printf("┌───────┐   ┌───────┐   ┌───────┐\n");

        // The limit for the current row is from the first card to the third card
        limit = firstIndex + 3;

        // Check within each row if the current card has a rank of 10
        // (since it must be printed with one less whitespace character)
        for(counter = firstIndex; counter < limit; counter++)
        {
            if(cards[grid[counter]].cardValue == 10)
            {
                printf("│%s     │   ", cards[grid[counter]].rank);
            }else
            {
                printf("│%s      │   ", cards[grid[counter]].rank);
            }
        }
        printf("\n");
        printf("│       │   │       │   │       │\n");//2

        // Print the the suits of each card in the current row
        printf("│   %s   │   │   %s   │   │   %s   │\n", cards[grid[firstIndex]].suit_symbol,
                                                            cards[grid[secondIndex]].suit_symbol,
                                                            cards[grid[thirdIndex]].suit_symbol);
        printf("│       │   │       │   │       │\n");
        printf("│       │   │       │   │       │\n");
        printf("└───────┘   └───────┘   └───────┘\n");
        firstIndex += 3;
        secondIndex += 3;
        thirdIndex += 3;
    }
}

// Take card choices from user(s) and ensure that it is a valid combination
void userSelectCards()
{
    bool validChoice = false;

    //Enter and continue in this while loop until the user makes a valid choice
    while(!validChoice)
    {
        // Prompt the user for their first card choice
        do
        {
            printf("\nPlease choose your first card: ");
            scanf("%s", firstCardSelected);

            if(!checkIfInGrid(firstCardSelected))
            {
                printf("\n* That's not in the grid! *\n");
            }
        }while(!checkIfInGrid(firstCardSelected));
        // Assign the index of the chosen card to the integer firstCardSelectedIndex
        firstCardSelectedIndex = findIndex(firstCardSelected);

        // Prompt the user for their second card choice
        do
        {
            printf("\nPlease choose your second card: ");
            scanf("%s", secondCardSelected);

            if(!checkIfInGrid(secondCardSelected))
            {
                printf("\n* That's not in the grid! *\n");
            }
        }while(!checkIfInGrid(secondCardSelected));
        // Assign the index of the chosen card to the integer secondCardSelectedIndex
        secondCardSelectedIndex = findIndex(secondCardSelected);

        // Check if the user's choice of 2 cards is a valid combination
        if(checkIfValidChoice(2))
        {
            // Set the number of cards selected to 2
            numCardsSelected = 2;

            // When in multiplayer mode:
            if(numPlayers == 2)
            {
                // Depending on the turn, increment that player's score
                if(roundNum % 2 == 1)
                {
                    playerOneScore++;
                }else
                {
                    playerTwoScore++;
                }
            }else // Increment the single player's score
            {
                score++;
            }
            break;
        }

        // If cards are J, Q, K: the indexes from 40 to 51
        if(firstCardSelectedIndex > 39 && secondCardSelectedIndex > 39)
        {
            // Prompt the user for their third card choice
            do
            {
                printf("\nPlease choose your third card: ");
                scanf("%s", thirdCardSelected);

                if(!checkIfInGrid(thirdCardSelected))
                {
                printf("\n* That's not in the grid! *\n");
                }
            }while(!checkIfInGrid(thirdCardSelected));
            // Assign the index of the chosen card to the integer thirdCardSelectedIndex
            thirdCardSelectedIndex = findIndex(thirdCardSelected);

            // Check if the user entered a Jack, Queen, King combination
            if (checkIfValidChoice(3))
            {
                // Set the number of cards selected to 3
                numCardsSelected = 3;

                // When in multiplayer mode:
                if(numPlayers == 2)
                {
                    // Depending on the turn, increment that player's score by 2
                    if(roundNum % 2 == 1)
                    {
                        playerOneScore += 2;
                    }else
                    {
                        playerTwoScore += 2;
                    }
                }else // Increment the single player's score
                {
                    score += 2;
                }
                printf("\nROYAL COMBO!\n");
                break;
            }
        }else
        {
            printf("Oops, I don't think that combination works! Try again!\n\n");
        }
    }

    if(checkIfPlayable())
    {
        // Prints random congratulatory message to user
        if(numCardsSelected != 3)
        {
            int greeting = randomNum(4);
            switch(greeting)
            {
                case 0:
                    printf("\nGood choice!\n");
                    break;
                case 1:
                    printf("\nClassic combo!\n");
                    break;
                case 2:
                    printf("\nI like it!\n");
                    break;
                case 3:
                    printf("\nKeep up the good work!\n");
                    break;
            }
        }
    }
}

// Check if the card passed as a parameter is in the current grid
bool checkIfInGrid(char cardSelected[])
{
    for(int i = 0; i < 9; i++)
    {
        if(strcmp(cardSelected, cards[grid[i]].cardName) == 0)
        {
            return true;
        }
    }
    return false;
}

// Return the index of the inputted card name
int findIndex(char cardSelected[])
{
    for(int i = 0; i < 9; i++)
    {
        if(strcmp(cardSelected, cards[grid[i]].cardName) == 0)
        {
            return grid[i];
        }
    }
    return -1;
}

// Check if the user entered a valid choice
bool checkIfValidChoice(int cardsSelected)
{
    // If the user selected two cards:
    if (cardsSelected == 2)
    {
        // Check if firstCardSelected and secondCardSelected add up to selected gameMode sum
        if((cards[firstCardSelectedIndex].cardValue + cards[secondCardSelectedIndex].cardValue) == gameMode)
        {
            return true;
        }
    }else // cardsSelected must be equal to 3
    {
        // Check is firstCardSelected, secondCardSelected and thirdCardSelected are a Jack, Queen and King
        // Get the cardValue for each card selected and check if the sum is equal to 36 (J=11, Q=12, K=13)
        if((cards[firstCardSelectedIndex].cardValue +
            cards[secondCardSelectedIndex].cardValue +
            cards[thirdCardSelectedIndex].cardValue) == 36)
        {
            return true;
        }
    }
    return false;
}

// Returns position of card in grid array
int findInGrid(int cardSelectedIndex)
{
    for(int i = 0; i < 9; i++)
    {
        if(grid[i] == cardSelectedIndex)
        {
            return i;
        }
    }
    return -1;
}

// Changes either 2 or 3 cards depending on what the user has chosen
void changeCards()
{
    int index;

    // Change the first card chosen by the user
    do
    {
        index = randomNum(52);
    }while(cards[index].isDealt);
    // Replace the grid position of the previous card with the new card
    grid[findInGrid(firstCardSelectedIndex)] = index;
    // Set the boolean isDealt to true, since the card is dealt
    cards[index].isDealt = true;


    // Change the second card chosen by the user
    do
    {
        index = randomNum(52);
    }while(cards[index].isDealt);
    // Replace the grid position of the previous card with the new card
    grid[findInGrid(secondCardSelectedIndex)] = index;
    // Set the boolean isDealt to true, since the card is dealt
    cards[index].isDealt = true;

    // If the user has chosen 3 cards:
    if (numCardsSelected == 3)
    {
        // Repeat previous replacement process for third card
        do
        {
            index = randomNum(52);
        }while(cards[index].isDealt);
        grid[findInGrid(thirdCardSelectedIndex)] = index;
        cards[index].isDealt = true;
    }
    cards[index].isDealt = true;
}

// Returns a boolean depending on if there are any possible combinations in the current grid of cards
bool checkIfPlayable()
{
    // Check for a numerical combination that adds up to 11
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(((cards[grid[i]].cardValue + cards[grid[j]].cardValue) == gameMode) && grid[i] < 40 && grid[j] < 40)
            {
                return true;
            }
        }
    }

    // Check for Jack, Queen, King combination
    bool isJack;
    bool isQueen;
    bool isKing;
    for(int i = 0; i < 9; i++)
    {
        // If the card's index is between 40 and 43 inclusive, it is a Jack
        if(grid[i] > 39 && grid[i] < 44)
        {
            isJack = true;
        }
        // If the card's index is between 44 and 47 inclusive, it is a Queen
        else if(grid[i] > 43 && grid[i] < 48)
        {
            isQueen = true;
        }
        // If the card's index is between 48 and 51 inclusive, it is a King
        else if(grid[i]>47 /*&& grid[i]<44  --> might not need*/)
        {
            isKing = true;
        }
    }

    // Check if there is a Jack, Queen and King all present in the current grid
    if(isJack && isQueen && isKing)
    {
        return true;
    }

    return false;
}

// Ask the user to enter 'yes' or 'no', and return integer based on response
int yesOrNo()
{
    char yes_or_no[3];
    scanf("%s", yes_or_no);

    // If the user enters yes, return 1
    if((strcmp(yes_or_no, "yes") == 0) ||
       (strcmp(yes_or_no, "Yes") == 0) ||
       (strcmp(yes_or_no, "YES") == 0) ||
       (strcmp(yes_or_no, "Y") == 0) ||
       (strcmp(yes_or_no, "y") == 0))
    {
        return 1;
    }else if((strcmp(yes_or_no, "no") == 0) ||
             (strcmp(yes_or_no, "No") == 0) ||
             (strcmp(yes_or_no, "NO") == 0) ||
             (strcmp(yes_or_no, "N") == 0) ||
             (strcmp(yes_or_no, "n") == 0)) // If the user enters no, return 0
    {
        return 0;
    }else
    {
        printf("re-enter\n");
    }
    return -1;
}

// Reset values
void resetValues()
{
    // Set scores back to 0
    score = 0;
    playerOneScore = 0;
    playerTwoScore = 0;

    // Set boolean isDealt to false for all cards in deck
    for (int i = 0; i < 52; i++)
    {
        cards[i].isDealt = false;
    }

    // Set round number back to 1
    roundNum = 1;
}