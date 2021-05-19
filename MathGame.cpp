//Math Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//function prototypes
void credits(); //display name of the program
void validateName(string& name); //gets name of the user and validates it
void menu(); //display menu options
void validateUserResponse(char& userChoice); //gets user's choice from the menu
string validateUserAnswer(); // gets user's answer to the problem
bool checkUserAnswer(string answer, int correctAnswer); //check if the user typed the correct answer to the problem
void updateStats(bool correctAnswer, double& earning, int& correct, int& wrong); //update the user status
void displayStats(string& userName, double& earning, int& correct, int& wrong); //display the user status
/*retrieves player statistics from external txt file when the game starts, assuming the player is a returning player,
  else create a text file to store the stats*/
void retrieveStats(string& userName, double& earning, int& correct, int& wrong);
void saveStats(string& userName, double& earning, int& correct, int& wrong); // saves all the data to the file named by user's name
//4 functions below generate a certain type of math problem and displays it.
void generateAddition(bool& correct);
void generateSubtraction(bool& correct);
void generateMultiplication(bool& correct);
void generateDivision(bool& correct);

int main()
{
	credits(); //displays the what the program is
	//checks intention to execute the program
	cout << "y/Y to continue, any other char to exit" << endl;
	string input;
	getline(cin, input);
	int inputLength = input.length();
	if (input != "y" && input != "Y")
	{
		return 0;
	}

	system("cls");
	//gets user's name
	string userName;
	validateName(userName);

	system("cls"); //clears the console

	double earning;
	int correct;
	int wrong;
	//gets the user data if it exists, creates one otherwise
	retrieveStats(userName, earning, correct, wrong);

	bool running = true; //bool value to check whether to keep running the program

	while (running)
	{
		menu(); //displays menu options

		char userChoice;
		validateUserResponse(userChoice); //gets the user choice from the menu
		system("cls");
		bool wasCorrect = false;
		switch (userChoice) //executes user's choice
		{
		case '1':
			generateAddition(wasCorrect);
			system("cls");
			updateStats(wasCorrect, earning, correct, wrong);
			break;
		case '2':
			generateSubtraction(wasCorrect);
			system("cls");
			updateStats(wasCorrect, earning, correct, wrong);
			break;
		case '3':
			generateMultiplication(wasCorrect);
			system("cls");
			updateStats(wasCorrect, earning, correct, wrong);
			break;
		case '4':
			generateDivision(wasCorrect);
			system("cls");
			updateStats(wasCorrect, earning, correct, wrong);
			break;
		case '5':
			displayStats(userName, earning, correct, wrong);
			break;
		default:
			running = false; /*because the user input from the menu is validated by the validateUserResponse function,
							   (userChoice can only be 1,2,3,4,5,n or N)
							   default will be executed only if the input is n or N */
		}
	}
	saveStats(userName, earning, correct, wrong); //saves the data to the file and ends the program
	return 0;
}

void credits()
{
	cout << "***********************\n" << "***********************\n" << "***********************" << endl;
	cout << "******           ******" << endl;
	cout << "******TheMathGame******" << endl;
	cout << "******  By Jin   ******" << endl;
	cout << "******  Park     ******" << endl;
	cout << "******           ******" << endl;
	cout << "***********************\n" << "***********************\n" << "***********************" << endl;
	cout << endl;
}


void validateName(string& name)
{
	char space = ' ';
	string input;
	bool valid = false;
	while (!valid)
	{
		cout << "Enter your first name and press <ENTER>" << endl;
		getline(cin, input);
		int inputLength = input.length();
		if (inputLength == 0)
			cout << "This is not a name" << endl;
		for (int i = 0; i < inputLength; i++)
		{
			//if the user typed a space or non - alphabet character(s), print error message
			if (input[i] == space || isalpha(input[i]) == 0)
			{
				cout << "This is not a name" << endl;
				i = inputLength;
			}
			//if every character is valid, validation is done
			if (i == inputLength - 1)
			{
				valid = true;
			}
		}
	}
	name = input;
}

void menu()
{
	cout << "******CHOOSE A PROBLEM*******" << endl;
	cout << "****************************\n" << "****************************" << endl;
	cout << "******                ******" << endl;
	cout << "****** 1. ADD         ******" << endl;
	cout << "****** 2. SUBTRACT    ******" << endl;
	cout << "****** 3. MULTIPLY    ******" << endl;
	cout << "****** 4. DIVIDE      ******" << endl;
	cout << "****** 5. STATS       ******" << endl;
	cout << "****** n/N to QUIT    ******" << endl;
	cout << "******                ******" << endl;
	cout << "****************************\n" << "****************************\n" << endl;

}

void validateUserResponse(char& userChoice)
{
	string input;
	bool valid = false;
	while (!valid)
	{
		getline(cin, input);
		//if the input is not one of the menu options, prints error message 
		if (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "n" && input != "N")
			cout << "This is not a valid menu option" << endl;
		else
		{
			valid = true;
		}
	}
	userChoice = input[0];
}

void updateStats(bool correctness, double& earning, int& correct, int& wrong)
{
	if (correctness) //if correct, increments number of correct problems and updates the earning +0.05
	{
		correct++;
		earning += 0.05;
		cout << "***********RIGHT!***********" << endl << endl;
	}
	else //otherwise(wrong), increments number of wrong problems and updates the earning -0.03
	{
		wrong++;
		earning -= 0.03;
		cout << "***********WRONG!***********" << endl << endl;
	}
}

void displayStats(string& userName, double& earning, int& correct, int& wrong)
{
	//prints the four data, user's name, total earning, number of correct problems, and number of wrong problems
	cout << "************************************\n************************************\n************************************" << endl;
	cout << "******                      ********" << endl;
	cout << "******" << userName << "                  ********" << endl;
	cout << "******Total Earnings $" << earning << "  ********" << endl;
	cout << "******Total Correct " << correct << "       ********" << endl;
	cout << "******Total Incorrect " << wrong << "     ********" << endl;
	cout << "******                      ********" << endl;
	cout << "************************************\n************************************\n************************************" << endl;
	cout << endl;
	system("pause");
	system("cls");
}

void retrieveStats(string& userName, double& earning, int& correct, int& wrong)
{
	ifstream inputFile;
	inputFile.open(userName + ".txt");
	//if the file named by the user's name doesn't exist, all numerical datas are set to 0
	if (inputFile.fail())
	{
		earning = 0.00;
		correct = 0;
		wrong = 0;
	}
	else //if the file exists, reads data from the file
	{
		inputFile >> userName;
		inputFile >> earning;
		inputFile >> correct;
		inputFile >> wrong;
	}
	inputFile.close();
}

void saveStats(string& userName, double& earning, int& correct, int& wrong)
{
	//creates a file named by the user's name and stores all 4 datas to the file
	ofstream outputFile;
	outputFile.open(userName + ".txt");
	outputFile << userName << endl;
	outputFile << earning << endl;
	outputFile << correct << endl;
	outputFile << wrong << endl;
	outputFile.close();

}

void generateAddition(bool& correct)
{
	unsigned seed = time(0);
	srand(seed); //seeding by the current time
	//generate two random numbers
	int num1 = rand() % 10 + 1; // minimum = 1, maximum = 10
	int num2 = rand() % 10 + 1;
	cout << "******ADDITION******" << endl;
	cout << "********************\n" << "********************" << endl;
	cout << "***** " << num1 << " + " << num2 << "=?" << " ******" << endl;
	cout << "********************\n" << "********************" << endl;

	int correctAnswer = num1 + num2; //the correct answer
	string userInput = validateUserAnswer(); //gets user input and validates it
	bool correctOrWrong = checkUserAnswer(userInput, correctAnswer); //checks if it's correct or wrong
	correct = correctOrWrong;
}

void generateSubtraction(bool& correct)
{
	unsigned seed = time(0);
	srand(seed);
	int num1 = rand() % 10 + 1; // minimum = 1, maximum = 10
	int num2 = rand() % 10 + 1;
	//if the random number, num2 is greater than num1, the subtraction will have negative integer as the correct answer
	//switches num1 and num2 if num2 is greater than num1 to avoid this situation
	if (num1 < num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	cout << "******SUBTRACTION******" << endl;
	cout << "***********************\n" << "***********************" << endl;
	cout << "***** " << num1 << " - " << num2 << "=?" << " *********" << endl;
	cout << "***********************\n" << "***********************" << endl;

	int correctAnswer = num1 - num2;
	string userInput = validateUserAnswer();
	bool correctOrWrong = checkUserAnswer(userInput, correctAnswer);
	correct = correctOrWrong;

}

void generateMultiplication(bool& correct)
{
	unsigned seed = time(0);
	srand(seed);
	int num1 = rand() % 10 + 1; // minimum = 1, maximum = 10
	int num2 = rand() % 10 + 1;

	cout << "******MULTIPLICATION******" << endl;
	cout << "**************************\n" << "**************************" << endl;
	cout << "***** " << num1 << " X " << num2 << "=?" << " ************" << endl;
	cout << "**************************\n" << "**************************" << endl;

	int correctAnswer = num1 * num2;
	string userInput = validateUserAnswer();
	bool correctOrWrong = checkUserAnswer(userInput, correctAnswer);
	correct = correctOrWrong;
}

void generateDivision(bool& correct)
{
	unsigned seed = time(0);
	srand(seed);
	int diviser = rand() % 10 + 1; // minimum = 1, maximum = 10
	//to make sure that the division doesn't have a remainder,
	//creates the dividend by multiplying two integers (one of them is the diviser)
	int dividend = diviser * (rand() % 10 + 1);

	cout << "******DIVISION******" << endl;
	cout << "********************\n" << "********************" << endl;
	cout << "***** " << dividend << " / " << diviser << "=?" << " ******" << endl;
	cout << "********************\n" << "********************" << endl;

	int correctAnswer = dividend / diviser;
	string userInput = validateUserAnswer();
	bool correctOrWrong = checkUserAnswer(userInput, correctAnswer);
	correct = correctOrWrong;
}

string validateUserAnswer()
{
	bool valid = false;
	string input;
	while (!valid)
	{
		getline(cin, input);
		for (int i = 0; i < input.length(); i++)
		{
			if (isdigit(input[i]) == 0) //if the user typed any character other than a number, prints error messages
			{
				i = input.length();
				cout << "This is not a positive integer";
				cout << "Enter a number!" << endl;
			}
			if (i == input.length() - 1)
				valid = true;
		}

	}
	return input;
}

bool checkUserAnswer(string userAnswer, int correctAnswer)
{
	//checks if the user's answer and the correct answer for the problem are the same
	if (atoi(userAnswer.c_str()) == correctAnswer)
	{
		return true;
	}
	else
	{
		return false;
	}
}

