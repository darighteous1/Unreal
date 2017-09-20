#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map


int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

FBullCowGame::FBullCowGame() { Reset(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (! IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (! IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; // TODO write method
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

void FBullCowGame::UpdateCurrentTry() { MyCurrentTry++; }

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	UpdateCurrentTry();
	FBullCowCount BullCownCount;

	// loop through all letters in the hidden word
	int32 WordLength = GetHiddenWordLength();

	for (int32 HiddenWordChar = 0; HiddenWordChar < WordLength; HiddenWordChar++)
	{
		// compare letters against the guess
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)
		{
			// if they match
			if (MyHiddenWord[HiddenWordChar] == Guess[GuessChar])
			{
				if (HiddenWordChar == GuessChar)
				{
					BullCownCount.Bulls++; // increment bulls if they are in the same place
				}
				else
				{
					BullCownCount.Cows++; // increment cows if not
				}
			}
		}
	}

	bGameIsWon = BullCownCount.Bulls == WordLength;

	return BullCownCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> SeenLetter;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (! SeenLetter[Letter])
		{
			SeenLetter[Letter] = true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (! islower(Letter))
		{
			return false;
		}
	}

	return true;
}
