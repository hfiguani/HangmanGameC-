// CIT-120 2HB Final Project
// Developing Hangman game
// By Hafed Figuani
// Last modification: 12/08/2016

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <Windows.h>
#include <MMSystem.h>
#include <ctime>
#include "HangmanGame.h"
using namespace std;

int main()
{
	system("color F0");
	system("title Hangman game by Hafed Figuani");

	int i, j, guessesNum, winsNum = 0, nbrOfGamesPlayed = 0;
	double winRate;
	char ltr;
	bool incremented;
	string  line, userName, result, dateTime, partialWrd, secretWord;
	vector<string> words, users;
	vector <char> guesses, partialWord;
	ifstream inputFile;
	ofstream outputFile;

	GameHeader();
	cout << "Do you want to play Hangman game? ";
	ltr = getYorN();
	if (ltr == 'N') {
		cout << "\nDon\'t you love this game?\n";
		system("pause");
		return 0;
	}
	cout << "Please enter your name: "; // Get user name
	userName = getValidUserName();

	openFile(inputFile, "Log/_Users.txt");// check if the user already exist in the log
	while (getline(inputFile, line))
		users.push_back(line);
	inputFile.close();

	while (ltr == 'Y')
	{
		if (find(users.begin(), users.end(), userName) != users.end()) // if user exists in the log
		{
			openFile(inputFile, "Log/" + userName + ".txt");
			getline(inputFile, userName, '\n');
			getline(inputFile, dateTime, '\n');
			inputFile >> result >> nbrOfGamesPlayed >> winsNum >> winRate >> secretWord >> partialWrd; /// get user statistics
			inputFile.close();

			cout << "\nHello " << userName << ",\n"  // dislpay user statistics
				<< "  You last played the game on " << dateTime << " and you " << result << ".\n"
				<< "  You played a total of " << nbrOfGamesPlayed << " time" << (nbrOfGamesPlayed == 1 ? "" : "s") << " and won " << winsNum << " time" << (winsNum == 1 ? "" : "s") << ".\n"
				<< "  Your average win rate is " << winRate << "%.\n"
				<< "  The secret word was \"" << secretWord << "\" and you got " << (result == "won" ? "it right." : partialWrd);
		}
		else   // if new user append the name to users list
			users.push_back(userName);

		inputFile.open("Words/Words.txt"); // get random word
		while (getline(inputFile, line))
			words.push_back(line);
		inputFile.close();
		srand(unsigned(time(0)));
		secretWord = trimTrailingWhiteSpace(words[rand() % words.size()]);

		cout << "\n\nThe word to find is:\n";
		partialWord.clear();
		guesses.clear();
		for (i = 0; i < secretWord.length(); i++) // display blanks 
		{
			partialWord.push_back('-');
			cout << partialWord[i];
		}
		cout << "\nHow many times you want to guess: "; // get the number of unsucesseful guesses
		guessesNum = getPositiveNumber();
		for (j = guessesNum; j >= 1; j--)
		{
			if (j <= 3)
				system("color CF");
			cout << "\n" << j << ") Guess a letter: ";  // get a letter from player
			ltr = getAvailableLetter(guesses);
			partialWrd = "";
			incremented = false;
			for (i = 0; i < secretWord.length(); i++)  // if letter is correct, the chance is not counted
			{
				if (secretWord[i] == ltr) {
					partialWord[i] = ltr;
					if (incremented == false)
					{
						j++;
						incremented = true;
					}
				}
				partialWrd += partialWord[i];
			}
			cout << partialWrd;
			guesses.push_back(ltr);

			if (secretWord.compare(partialWrd) == 0) // compare the secret word and the so far word if equal end game
			{
				cout << "\n\nYou won,\n";
				PlaySound(TEXT("Sounds/win.wav"), NULL, SND_SYNC);// add linker input winmm.lib
				result = "won";
				winsNum++;
				break;
			}
			if (j == 1) {    // if last chance end game
				cout << "\n\nYou lose,\n";
				PlaySound(TEXT("Sounds/lose.wav"), NULL, SND_SYNC);
				result = "lose";
			}
		}
		cout << "The secret word was \"" << secretWord << "\".\n";
		system("color F0");
		dateTime = currentDateTime();// set statistics variables
		nbrOfGamesPlayed++;
		winRate = winsNum * 100 / nbrOfGamesPlayed;

		createFile(outputFile, "Log/" + userName + ".txt"); // output statistics to user's file
		outputFile << userName << endl << dateTime << endl << result << endl << nbrOfGamesPlayed << endl << winsNum << endl << winRate << endl << secretWord << endl << partialWrd;
		outputFile.close();

		createFile(outputFile, "Log/_Users.txt"); // output users to _Users file
		for (i = 0; i < users.size(); i++)
			outputFile << users[i] << endl;
		outputFile.close();

		cout << "\n\n\t**************************************************\n\n ";
		cout << "Do you want to play again? ";
		ltr = getYorN();
		if (ltr == 'N') {
			cout << "\nDon\'t you love Hangman Game?\n";
			system("pause");
		}
	}
	return 0;
}
