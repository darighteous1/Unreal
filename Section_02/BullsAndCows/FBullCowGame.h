#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Contains_Invalid_Symbols
};

enum class EResetStatus
{
	OK,
	No_Hidden_Word
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	void UpdateCurrentTry();
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	bool bGameIsWon;
};