#pragma once
#include <iostream>
#include "FBullCowGame.h"
#include <map>
#include <string>

//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5}, {7,6}, {8,7}, {9,8}, {10,8} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

void FBullCowGame::ChangeHiddenWord()
{
	long long int pin = 9810837435;
	long long int inpin;
	std::cout << "\nPlease enter the pin: ";
	std::cin >> inpin;
	if (inpin == pin)
	{
		std::cout << "\nPin authorised. Please enter the new hidden word: ";
		FString hw;
		std::cin >> hw;
		MyHiddenWord = hw;
		system("cls");
		return;
	}
	else
	{
		std::cout << "\nThe pin entered is not correct. Continuing with the previous hidden word...\n\n";
		return;
	}

}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
		return EGuessStatus::Not_Isogram;
	else if (!IsLowercase(Guess))
		return EGuessStatus::Not_Lowercase;
	else if (GetHiddenWordLength() != Guess.length())
		return EGuessStatus::Wrong_Length;
	else
		return EGuessStatus::Okay;
}

// receives valid guess, increments try, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming they are both same

	// loop through all the letters in the hidden word
	for (int32 MWChar = 0; MWChar < WordLength; MWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MWChar])
			{
				if (GChar == MWChar)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) // treat 0 and 1 letterwords as isograms
		return true;
	TMap<char, bool> LetterSeen; // setup the map	
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed cases
		if (LetterSeen[Letter] == true)		// if the letter is in the map
			return false;						// we do not have an isogram
		else								// otherwise
			LetterSeen[Letter] = true;			// add the letter to the map as seen
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
		if (!islower(Letter))
			return false;
	return true;
}
