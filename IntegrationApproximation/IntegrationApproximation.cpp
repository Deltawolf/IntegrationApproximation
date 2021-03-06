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
#include "Zach.h" //Relative path to source files


using namespace std;



//Core functions for int main not in header
void constructMenu(vector<string> &menuItems); 
void funcSelection(int userMenu, double userRange1, double userRange2, int userIntervals);

//Represents the menu choices the user can make. Resize enum based on the size of the menu used 
enum menuChoice { menu1 = 1, menu2 = 2, menu3 = 3, menu4 = 4, menu5 = 5 };


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
//Initalize variables
	bool userContinue = false;
	bool invalidInput = false;

	double userRange1 = NULL;
	double userRange2 = NULL;

	int userIntervals = NULL;
	int userMenu = NULL;

	char continueInput = NULL;

	vector <string> menuItems;


//Fills our vector with items using pushback command	
	constructMenu(menuItems);

//User manuals on back order
	cout << "Welcome to Integration.exe! Here, we will only integrate one function as listed in your user manual!\n\n";

//Loop will execute again only if the user would like to choose multiple options
	do
	{

		//Prompt the user with supplied string to select a menu item with an integer. If datatype incorrect, function loops. 
		userMenu = menuSelection(userMenu, "\nPlease select which type of integration to display: \n", menuItems);

	/*

		This loop will test the users input for the follow:
			1. b >= a before integrating
			2. That n != 0 (We will not be dividing by 0 today)
			3. That a is a non-negative number

		If invalid, the user will receive a non-descriptive error to fix their inputs.
		Section loops until user can enter a valid input.
		Subintervals will be defined for all menu selections that are not the "Farris Special"
		
	*/
		do
		{
			invalidInput = false;

			//myInput prompt's the user with the string supplied, and then tests the user's input vs the datatype of the first parameter given. Loops until correct
			userRange1 = myInput(userRange1, "\nPlease enter the start of your integration range: \n");
			userRange2 = myInput(userRange2, "\nPlease enter the end of your integration range: \n"); 

			if (userMenu != menu1) //Not used in the Farris Special
				userIntervals = myInput(userIntervals, "\nPlease enter the number of subdivisions (must be integer): \n"); 
			if (userMenu == menu1)
				userIntervals = 1; //Default value to avoid dividing by 0 in changeX since user will not be prompted for an interval

			if ((userRange2 <= userRange1) || (userIntervals == 0) || (userRange1 < 0))
			{
				invalidInput = true;
				cout << "\n\nYour range or selected subdivisions are not acceptable. Please try entering them again.\n\n";
			}

		} while (invalidInput);

		
	//Execute the selected integral operation based on the menu selection, range from a to b, and subintervals selected by the user
		funcSelection(userMenu, userRange1, userRange2, userIntervals);
	
	//Prompt the user to use the program again. If true, loop. If false, exit. Character value accepted as y,Y,n,N. Loop if incorrect value supplied.
		userContinue = continueFunc(continueInput, "Would you like to integrate again?: ");

	} while (userContinue);

}

//Menu is constructed with the following strings, in order.
void constructMenu(vector<string> &menuItems)
{
	menuItems.push_back("Dr. Farris Special");
	menuItems.push_back("Exact Integration");
	menuItems.push_back("Midpoint Approximation");
	menuItems.push_back("Trapezoidal Approximation");
	menuItems.push_back("Simpson's Approximation");

}

//This is the hard coded function that we are approximating
double integralFunction(double x) 
{
	return 1 + 7 * sqrt(x) + 2/((x+1)*(x+1));
}

//This is the hard coded exact integral that we will complete the range for if selected directly or with Farris Special
double integratedFunction(double x)
{
	return 14 * sqrt(x*x*x) / 3 + x - 2 / (x + 1);
}

//This function will return the results of our exact integration
void exactN2Gration(double userRange1, double userRange2)
{
	cout << "\nThe definite integral of your function between " << userRange1 <<" and " << userRange2 <<" is: "<< integratedFunction(userRange2) - integratedFunction(userRange1) << "\n\n";
}

//This function will use a rectangular midpoint approximation to return the approximate area under the function
//DeltaX*(Fx0+DeltaX/2 + Fx1+DeltaX/2 + Fx2+DeltaX/2...Fxn -DeltaX/2)
void midN2Gration(double userRange1, double userRange2, int userIntervals, int userMenu = menu3)
{
	double sum = 0.0;
	double changeX = (userRange2 - userRange1) / userIntervals;
	if (userMenu = menu1) //if Farris Special, then we are using a predetermined interval per program spec.
		changeX = 0.01;
	for (double i = userRange1 + changeX/2; i <= userRange2 - changeX/2; i += changeX)
		sum += integralFunction(i);

	sum *= changeX;
	
	cout << "\nThe approximate integral of your function between " << userRange1 << " and " << userRange2 << " is: " << sum << "\n\n";
}

//This function will use a trapezoidal approximation to return the approximate area under the function
//1 / 2 * DeltaX*(Fx0 + 2Fx1 + 2Fx2... Fn)
void trapezoidN2Gration(double userRange1, double userRange2, int userIntervals)
{
	double changeX = (userRange2 - userRange1) / userIntervals; //(b-a)/n
	double sum = integralFunction(userRange1) + integralFunction(userRange2); //Fx0 + Fxn

	//Fx1 through Fxn-1
	for (double i = userRange1 + changeX; i <= userRange2 - changeX; i += changeX)
		sum += 2*integralFunction(i);

	sum *=(1.0 / 2.0)*changeX;

	cout << "\nThe approximate integral of your function between " << userRange1 << " and " << userRange2 << " is: " << sum << "\n\n";
}

//This function will use Simpson's Rule to return the approximate area under the function
//1/3*DeltaX*(Fx0 + 4Fx1 + 2Fx2... Fxn)
void simpsonN2Gration(double userRange1,double userRange2,int userIntervals)
{
	int counter = 0;
	double changeX = (userRange2 - userRange1) / userIntervals; //(b-a)/n
	double sum = integralFunction(userRange1) + integralFunction(userRange2); //Fx0 + Fxn

	//Fx1 through Fxn-1
	for (double i = userRange1 + changeX;  i <= userRange2 - changeX; i += changeX)
	{
		// If n is even, multiply by 4, if n is odd, multiply by 2
		(counter % 2 == 0) ? sum += 4 * integralFunction(i) : sum += 2 * integralFunction(i); 
		counter++;
	}

	//Multiply Summation by 1/3 and DeltaX per formula
	sum *= (1.0 / 3.0)*changeX;

	cout << "\nThe approximate integral of your function between " << userRange1 << " and " << userRange2 << " is: " << sum << "\n\n";
}

//This returns the midpoint rectangular approximation and the exact integration to the specs of the project (Graded portion)
void farrisN2Gration(double userRange1, double userRange2, int userIntervals,  int userMenu)
{

	midN2Gration(userRange1, userRange2, userIntervals, userMenu); //1 is used to not divide by 0 until changeX can be redefined to the user spec
	exactN2Gration(userRange1, userRange2);

}

//This executes the given function based on the user's specified range, interval, and parameters
//Menu items are in order of our constructMenu() function. If item order is changed there, this must change accordingly.
void funcSelection(int userMenu, double userRange1, double userRange2,int userIntervals)

{

	switch (userMenu)
	{
	case menu1:
		farrisN2Gration(userRange1, userRange2, userIntervals, userMenu);
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