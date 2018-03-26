// Homework 07

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <fstream>

// Declaring Struct "Card"

struct Card {
    std::string cardSuit;
    std::string cardValue;
    int numValue;
};

// Declaring Function PrintCard that takes in Card Struct

void PrintCard(Card& card) {
    std::cout << card.cardValue << " of " << card.cardSuit;
}

// Declaring GetRandCard Function that Returns a Card

Card GetRandCard(Card cardArray[], int arraySize) {
    int number = std::rand() % arraySize;
    return cardArray[number];
}

// Declaring IsSame Function That Says If Two Cards Are Same Value or Not

bool IsSame(Card& cardOne, Card& cardTwo) {
    int pointValue;
    int pointValueTwo;
    pointValue = cardOne.numValue;
    pointValueTwo = cardTwo.numValue;
    if(pointValue == pointValueTwo)
        return true;

    return false;

}

// Declaring IsWinner function That Determines Which Card Is Greater

bool IsWinner(Card& cardOne, Card& cardTwo) {
    int pointValue;
    int pointValueTwo;
    pointValue = cardOne.numValue;
    pointValueTwo = cardTwo.numValue;
    if(pointValue > pointValueTwo)
        return true;

    return false;
}

// Declaring LoadCards Function That

void LoadCards(Card cardArray[], Card cardArrayTwo[], int arraySize, std::ifstream &fileInput) {
    for (int i = 0; i < arraySize; i++)
    {
        // Get line of text
        std::string lineOfText;
        std::getline(fileInput, lineOfText);
        std::stringstream mySS(lineOfText);
        // extract string value from arrays
        std::string StringValue;
        mySS >> StringValue;
        cardArray[i].cardValue = StringValue;
        cardArrayTwo[i].cardValue = StringValue;
        // extract of
        std::string of;
        mySS >> of;
        // extract suit and int value
        std::string StringSuit;
        mySS >> StringSuit;
        cardArray[i].cardSuit = StringSuit;
        cardArrayTwo[i].cardSuit = StringSuit;
        int IntValue;
        mySS >> IntValue;
        cardArray[i].numValue = IntValue;
        cardArrayTwo[i].numValue = IntValue;



        // get rid of stuff in the stream
        fileInput.clear();
    }


}



int main() {

    // initialize random number generator
    srand(time(0));

    // constant integer for #cards in game
    const int numberOfCards = 52;

    // card arrays for each player
    Card playerOneArray[numberOfCards];
    Card playerTwoArray[numberOfCards];

    // asking for player names
    std::string playerOne;
    std::string playerTwo;
    std::cout << "What is Player 1's name: ";
    std::cin >> playerOne;
    std::cout << "What is Player 2's name: ";
    std::cin >> playerTwo;

    // ask user for card file name
    std::string fileName;
    std::cout << "Enter card file name: ";
    std::cin >> fileName;

    // Open FileStream Txt File
    std::ifstream cardFile;
    cardFile.open(fileName.c_str());
    if (cardFile.is_open())
    {
        //load the cards
        LoadCards(playerOneArray, playerTwoArray, numberOfCards, cardFile);

        //initialize point counters
        int playerOnePoints = 0;
        int playerTwoPoints = 0;

        bool continueGame = true;

        //main game loop
        while(continueGame) {
            std::cout << playerOne << ": " << playerOnePoints << std::endl;
            std::cout << playerTwo << ": " << playerTwoPoints << std::endl;

            //get one card for each player
            Card playerOneCard = GetRandCard(playerOneArray, numberOfCards);
            Card playerTwoCard = GetRandCard(playerTwoArray, numberOfCards);

            //print each players cards
            std::cout << playerOne << " drew ";
            PrintCard(playerOneCard);
            std::cout << std::endl;

            std::cout << playerTwo << " drew ";
            PrintCard(playerTwoCard);
            std::cout << std::endl;

            //check the result
            if(IsSame(playerOneCard, playerTwoCard)){
                std::cout << "Draw!";
            } else {
                //if the cards are not the same, you need to call is winner only once
                if(IsWinner(playerOneCard, playerTwoCard)){
                    playerOnePoints += 1;
                    std::cout << playerOne << " wins this round." << std::endl;
                } else {
                    playerTwoPoints += 1;
                    std::cout << playerTwo << " wins this round." << std::endl;
                }
            }

            //ask user if he wants to play another round
            std::cout << "Would you like to play again? (Y/N)" << std::endl;
            std::string answer;
            std::cin >> answer;
            if(answer == "N" || answer == "n"){
                continueGame = false;
            }
        }

        //check to see who is the winner and print the result
        if(playerOnePoints > playerTwoPoints){
            std::cout << playerOne << " is the winner with " << playerOnePoints << " points!" << std::endl;
        } else if(playerOnePoints < playerTwoPoints) {
            std::cout << playerTwo << " is the winner with " << playerTwoPoints << " points!" << std::endl;
        } else {
            std::cout << "The match ends in a draw! Both players have: " << playerOnePoints << " points!" << std::endl;
        }

    } else {
        std::cout << "File not found.";
        return 1;
    }

    return 0;
}

