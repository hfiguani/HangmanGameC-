#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

string trimTrailingWhiteSpace(string str) {
	int i;
	for (i = str.length() - 1; i >= 0; i--)
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			break;
	return str.substr(0, i + 1);
}

string getValidUserName() {
	char illegalCharacters[] = { '/','?','<','>','\\',':','*','|','#','$','%','\'','\"','=','{','}','.','+','@' };
	string str;
	int i, j;
	bool isIllegal = false;

	cin >> ws; getline(cin, str);
	str = trimTrailingWhiteSpace(str);
	for (i = 0; i < str.length(); i++)
		for (j = 0; j < 19; j++)
			if (str[i] == illegalCharacters[j])
				isIllegal = true;

	while (isIllegal == true) {
		cout << "Invalid user name. Try again: ";
		cin >> ws; getline(cin, str);
		str = trimTrailingWhiteSpace(str);
		isIllegal = false;
		for (i = 0; i < str.length(); i++)
			for (j = 0; j < 19; j++)
				if (str[i] == illegalCharacters[j])
					isIllegal = true;
	}
	return str;
}

char getLetter() {
	char c;
	cin >> c; cin.ignore(80, '\n');
	while (c > 'z' || c < 'A' || (c < 'a' && c > 'Z'))
	{
		cout << c << " is NOT a letter! please enter a letter :";
		cin >> c; cin.ignore(80, '\n');
	}
	return c;
}

char getLowerCaseLetter() {
	char c = getLetter();
	while (c <= 'Z' && c >= 'A')
	{
		cout << "\t      " << c << " is NOT a lower case letter. Try again :";
		c = getLetter();
	}
	return c;
}

char getAvailableLetter(vector <char> vec) {
	char ltr = getLowerCaseLetter();
	while (find(vec.begin(), vec.end(), ltr) != vec.end()) // check if letter is already tried
	{
		cout << "You already guessed the letter \"" << ltr << "\". Try again: ";
		ltr = getLowerCaseLetter();
	}
	return ltr;
}

char getYorN() {
	char c;
	cin >> c; cin.ignore(80, '\n');
	while (c != 'n' && c != 'N' && c != 'Y' && c != 'y')
	{
		cout << "Please type Y or N. Try again: ";
		cin >> c; cin.ignore(80, '\n');
	}
	if (c == 'n' || c == 'N')
		return 'N';
	else
		return 'Y';
}

void GameHeader() {
	cout << "\n"
		<< "\t   ************************************************************************         \n"
		<< "\t   *   Introduction to Computer Science and Object Oriented Programming   *         \n"
		<< "\t   *                           Final Project                              *         \n"
		<< "\t   *                      Hangman Game Development                        *         \n"
		<< "\t   *                           by H. Figuani                              *         \n"
		<< "\t   ************************************************************************         \n\n\n";
}

double getNumber() {
	double num;
	while (!(cin >> num)) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Numbers only please.Try again : ";
	}
	return num;
}

int getWholeNumber() {
	double num = getNumber();
	while (num != int(num)) {
		cout << "Whole numbers only please.Try again : ";
		num = getNumber();
	}
	return int(num);
}

int getPositiveNumber() {
	int num = getWholeNumber();
	while (num <= 0)
	{
		cout << "Positive numbers only please.Try again : ";
		num = getWholeNumber();
	}
	cin.ignore(80, '\n');
	return num;
}

string currentDateTime() {
	time_t  now = time(NULL);
	struct tm  nowLocal;
	stringstream datetime, minutes;
	localtime_s(&nowLocal,&now);
	(nowLocal.tm_min < 10 ? minutes << "0" << nowLocal.tm_min : minutes << nowLocal.tm_min);
	datetime << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_mday << "/" << nowLocal.tm_year + 1900 << " at " << nowLocal.tm_hour << ":" << minutes.str();
	return  datetime.str();
	// c++ Preprocessor _CRT_SECURE_NO_WARNINGS
}

void createFile(ofstream &outputFile, string fileName) {
	outputFile.open(fileName.c_str());
	while (outputFile.fail())
	{
		cout << "\nFailed to create file: " << fileName << ", Try again.";
		outputFile.open(fileName.c_str());
	}
}

void openFile(ifstream &inputFile, string fileName) {
	inputFile.open(fileName.c_str());
	while (inputFile.fail())
	{
		cout << "Failed to open file: " << fileName << ", Try again.\n";
		inputFile.open(fileName.c_str());
	}
}