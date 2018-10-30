#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Prototyping my overloaded input handlers
int myInput(int input, string prompt);
double myInput(double input, string prompt);
char myInput(char input, string prompt);
string myInput(string input, string prompt);

//This generates a menu from my string vector
int menuSelection(int input, string prompt, vector<string> MyMenu);


//The following input functions achieve these goals
//Prompt the user with the string given in the parameter
//Check the datatype of the input of the user to match the variable datatype in the function
//If good, continue, if bad, clear the error, ignore the buffer until the next line.
//Rinse, repeat.

//This function handles verifying the datatype for int cin
int myInput (int input, string prompt)
{
	static bool isNotAcceptable = false;

	do
	{
		

		if (cin.fail() || isNotAcceptable)
		{
			cout << "\nThe entry was not a valid type.\nPlease attempt to enter a new numerical value.\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
			isNotAcceptable = false;
		}

		cout << prompt;
		cin >> input;

		if (cin.get() != '\n')
			isNotAcceptable = true;

	} while (cin.fail() || isNotAcceptable);

	return input;
}

//This function handles verifying the datatype for double cin
double myInput(double input, string prompt)
{
	do
	{

		if (cin.fail())
		{
			cout << "\nThe entry was not a valid type.\nPlease attempt to enter a new numerical value.\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}

		cout << prompt;
		cin >> input;

	} while (cin.fail());

	return input;
}

//This function handles verifying the datatype for char cin
char myInput(char input, string prompt)

{
	do
	{

		if (cin.fail())
		{
			cout << "\nThe entry was not a valid type.\nPlease attempt to enter a new character input.\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}

		cout << prompt;
		cin >> input;

	} while (cin.fail());

	return input;
}

//This function handles verifying the datatype for string input
string myInput(string input, string prompt)
{
	do
	{

		if (cin.fail())
		{
			cout << "\nThe entry was not a valid type.\nPlease attempt to retry your entry.\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}

		cout << prompt;
		cin >> input;

	} while (cin.fail());

	return input;
}

//This function is for determining if the using would like to run the program again and returns a bool
bool continueFunc(char input,string prompt)

{
	bool userChoice = false;
	bool isAcceptable = true;

	cout << "\n\nProgram completed!\n";

	do 
	{
		input = myInput(input, prompt);

		//Character inputs of Y, y, N,n are accepted to determine if the user would like to run the program again
		if (input == 'Y' || input == 'y')
		{
			userChoice = true;
			isAcceptable = true;
		}
		else if (input == 'N' || input == 'n')
		{

			cout << "\n\nThanks for using the our products by ZachInc!\n\n";
			isAcceptable = true;
		}
		else
		{
			cout << "\nThis is not an acceptable input.\n\n";
			isAcceptable = false;
			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (!isAcceptable);


	return userChoice;
}


//This function will construct a simple menu from our customized vector string at the beginning of each program
int menuSelection(int input, string prompt, vector<string> MyMenu)

{

	string starString = "";
	cout << "\nPlease select from the following options. \n\n";
	cout << starString.assign(33, '*') << endl; //Menu separation

	for (int i = 0; i < MyMenu.size(); i++)
		cout << i + 1 << ": " << MyMenu[i] << "\n\n";//This will iterate through our menu no matter the size of the vector

	cout << starString.assign(33, '*') << endl; //Menu separation

	input = myInput(input, prompt);//This allows us to select a menu item through an integer

	if (input > MyMenu.size() || input < 1) //If the input is out of bounds an error is thrown
	{
		cout << "\n\nYou have entered an invalid menu selection. Try again. \n\n";
		input = menuSelection(input, prompt, MyMenu); //recursion is used to loop this function until a correct input is made
	}

	return input;

}

/*

Playing with stuff for later
void funcSelection(int userMenu, double userValue)

{

	switch (userMenu)
	{
	case menu1:
		sinhFunc(userValue);
		break;

	case menu2:
		coshFunc(userValue);
		break;

	case menu3:
		sqrtFunc(userValue);
		break;

	case menu4:
		logFunc(userValue);
		break;

	case menu5:
		lnFunc(userValue);
		break;

	default://Not sure how a user could reach this state. If they do, the program will exit.
		cout << "Invalid menu selection. How did you even get here? Please restart the program.\n\n";
		exit(0);
	}
}
*/

/*
struct Menu
{
	vector <string> menu;

	Menu()
	{
		for (int i = 0; i < ; i++)
			menu.push_back(i)
	}

	void Display()
	{
		cout << "\n\n";
		for (int i = 0; i < menu.size(); i++)
		{
			cout << i + 1 << ": " << menu[i] << "\n\n";
		}
	}

	int Size()
	{
		return menu.size();
	}

};
*/