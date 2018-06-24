/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>	
#include "FBullCowGame.h"

#include <fstream>
#include <stdlib.h>

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void display_members();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
char AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse across plays

// the entry point for our application
int main()
{
	char bPlayAgain = 'y';
	PrintIntro();
	while(1)
	{
		if (bPlayAgain == 'y')
		{
			PlayGame();
			bPlayAgain = AskToPlayAgain();
		}
		else if (bPlayAgain == 'c')
		{
			BCGame.ChangeHiddenWord();
			PlayGame();
			bPlayAgain = AskToPlayAgain();
		}
		else
			break;
	}
	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Written by Rashil Gandhi, with inspiration from Udemy.com.\n\n";
	display_members();
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	// until the game is not won and there are still tries left
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " and Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Okay); // Loop continually until the user gives a valid guess
	return Guess;
}

char AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? Or change the hidden word(c)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return Response[0];
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Congratulations!\n\n";
	else
		std::cout << "Too bad.\n\n";
	return;
}

void display_members()
{
	FText getcontent;
	std::ifstream openfile("banner.txt");
	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			getline(openfile, getcontent);
			std::cout << getcontent << std::endl;
		}
	}
}