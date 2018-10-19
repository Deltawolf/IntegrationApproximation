/*
Zach Shore
ENGR 210
Integration
Due OCT 30

f(x) = 1+7*sqrt(x) + 2/(x+1)^2
DeltaX = 0.01
A<B
A is positive

Approx and Exact Integration
*/


#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "..\..\..\MyHeaders\Zach.h"


using namespace std;



//Core functions for int main
void constructMenu(vector<string> &menuItems); 
void funcSelection(int userMenu, double userRange1, double userRange2, int userIntervals);

//If operations menu expands, change this value to reflect the number of available options.
//Edit enum inside of funcSelection() to reflect new items as well.

//Functions available to menu selection.

enum menuChoice { menu1 = 1, menu2 = 2, menu3 = 3, menu4 = 4, menu5 = 5 };
//named menuFunc for each entry to avoid ambiguous naming error I encountered with the math functions


/*
**************************
Main
**************************

1. The program accepts a value from the user.
2. The program will select a menu selection from the user.
3. A mathematical operation is performed through function selection switch.
4. The user is prompted if they would like to use the program again.

*/



int main()
{
	bool userContinue = false;
	bool invalidInput = false;
	double userRange1 = NULL;
	double userRange2 = NULL;
	int userIntervals = NULL;
	int userMenu = NULL;
	char continueInput = NULL;

	vector <string> menuItems;
	
	constructMenu(menuItems);

	cout << "Welcome to Integration.exe! Here, we will only integrate one function as listed in your user manual!\n\n";


	do
	{
		do
		{
			invalidInput = false;
			userRange1 = myInput(userRange1, "\nPlease enter the start of your integration range: \n");
			userRange2 = myInput(userRange2, "\nPlease enter the end of your integration range: \n");
			userIntervals = myInput(userIntervals, "\nPlease enter the number of subdivisions (must be integer): "); //Not used in the Ferris Special
			if ((userRange2 <= userRange1) || (userIntervals == 0) || (userRange1 < 0))
			{
				invalidInput = true;
				cout << "\n\nYour range or selected subdivisions are not acceptable. Please try entering them again.\n\n";
			}

		} while (invalidInput);

		userMenu = menuSelection(userMenu, "\nPlease select which type of integration to display: \n", menuItems);

		funcSelection(userMenu, userRange1, userRange2, userIntervals);

		userContinue = continueFunc(continueInput, "Would you like to integrate again?");

	} while (userContinue);

}

void constructMenu(vector<string> &menuItems)
{
	menuItems.push_back("Dr. Ferris Special");
	menuItems.push_back("Exact Integration");
	menuItems.push_back("Midpoint Approximation");
	menuItems.push_back("Trapezoidal Approximation");
	menuItems.push_back("Simpson's Approximation");

}


double integralFunction(double x) 
{
	return 1 + 7 * sqrt(x) + 2/((x+1)*(x+1));
}

double integratedFunction(double x)
{
	return 14 * sqrt(x*x*x) / 3 + x - 2 / (x + 1);
}


void exactN2Gration(double userRange1, double userRange2)
{
	cout << "\nThe definite integral of your function between " << userRange1 <<" and " << userRange2 <<" is: "<< integratedFunction(userRange2) - integratedFunction(userRange1) << "\n\n";
}

void midN2Gration(double userRange1, double userRange2, int userIntervals, bool ferris = false)
{
	double sum = 0.0;
	double changeX = (userRange2 - userRange1) / userIntervals;
	if (ferris)
		changeX = 0.01;
	for (double i = userRange1 + changeX/2; i <= userRange2 - changeX/2; i += changeX)
		sum += integralFunction(i);

	sum *= changeX;
	
	cout << "\nThe approximate integral over the given range is: " << sum << "\n\n";
}

void trapezoidN2Gration(double userRange1, double userRange2, int userIntervals)
{
	double changeX = (userRange2 - userRange1) / userIntervals;
	double sum = integralFunction(userRange1) + integralFunction(userRange2);
	for (double i = userRange1 + changeX; i <= userRange2 - changeX; i += changeX)
		sum += 2*integralFunction(i);

	sum *=(1.0 / 2.0)*changeX;

	cout << "\nThe approximate integral over the given range is: " << sum << "\n\n";
}

void simpsonN2Gration(double userRange1,double userRange2,int userIntervals)
{
	int counter = 0;
	double changeX = (userRange2 - userRange1) / userIntervals;
	double sum = integralFunction(userRange1) + integralFunction(userRange2);
	for (double i = userRange1 + changeX;  i <= userRange2 - changeX; i += changeX)
	{
		(counter % 2 == 0) ? sum += 4 * integralFunction(i) : sum += 2 * integralFunction(i);
		counter++;
	}
	sum *= (1.0 / 3.0)*changeX;

	cout << "\nThe approximate integral over the given range is: " << sum << "\n\n";
}

void ferrisN2Gration(double userRange1, double userRange2)
{

	midN2Gration(userRange1, userRange2, 0, true);
	exactN2Gration(userRange1, userRange2);

}

void funcSelection(int userMenu, double userRange1, double userRange2,int userIntervals)

{

	switch (userMenu)
	{
	case menu1:
		ferrisN2Gration(userRange1, userRange2);
		break;

	case menu2:
		exactN2Gration(userRange1, userRange2);
		break;

	case menu3:
		midN2Gration(userRange1, userRange2, userIntervals);
		break;

	case menu4:
		trapezoidN2Gration(userRange1, userRange2, userIntervals);
		break;

	case menu5:
		simpsonN2Gration(userRange1, userRange2, userIntervals);
		break;

	default://Not sure how a user could reach this state. If they do, the program will exit.
		cout << "Invalid menu selection. How did you even get here? Please restart the program.\n\n";
		exit(0);
	}
}