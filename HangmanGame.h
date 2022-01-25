#pragma once
#include <fstream>
#include <string>
using namespace std;

char getLetter();
char getLowerCaseLetter();
char getYorN();
int getWholeNumber();
int getPositiveNumber();
double getNumber();
string currentDateTime();
string trimTrailingWhiteSpace(string str);
void GameHeader();
void openFile(ifstream &inputFile, string fileName);
void createFile(ofstream &outputFile, string fileName);
string getValidUserName();
char getAvailableLetter(vector <char> vec);

