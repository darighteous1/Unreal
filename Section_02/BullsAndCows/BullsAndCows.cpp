/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

int main();

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBullsAndCows(FBullCowCount);
bool PlayerWantsToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

// the entry point for our application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (PlayerWantsToPlayAgain());

	return 0;
}


void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";

	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		PrintBullsAndCows(BullCowCount);
	}

	PrintGameSummary();
	return;
}

// loop continually until the user enters a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n";
			break;
		case EGuessStatus::Contains_Invalid_Symbols:
			std::cout << "Please use only lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}

		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);

	return Guess;
}


void PrintBullsAndCows(FBullCowCount BullCowCount)
{
	// print the guess back to them
	std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
	std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done! You win!!!\n";
	}
	else
	{
		std::cout << "Oh noes! Better luck next time!\n";
	}
}

bool PlayerWantsToPlayAgain()
{
	std::cout << "Do you want to play another game with the same word? (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}