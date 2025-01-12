/*
Cliffansyah Yahya
CS 216
3/12/2024

Description: This program simulates and manages a soft drink machine, information of each drink type
should be stored in a structure that has data members to contain the drink name, drink price, and
number of drinks of that type currently in the machine

the class should have 2 public member functions
a. displayChoices (displays menu of drink names and prices)
b. buyDrink (handles a sale)

class should have at least 2 private member functions
a. inputMoney (called by buydrink to accept, validate and return to buyDrink the amount of money input)
b. dailyReport (called by the destructor to report how many of each drink type remain in the machine
at the end of the day and the money collected total)
c. use additional functions for modularity

the program that uses the class should have a main processing loop which calls the displayChoices
class member function and allows the patron to either pick a drink or quit the program.

if patron selects drink, the buyDrink class member function is called to handle the sale

this function should be passed the patron's drink choice.

buyDrink function:
a. call the inputMoney function, passing it the patron's drink choice
b. if the patron does not want the transaction, return all of the money inputted.
c. if the machine is out of soda, display a message that states "sold out" and return the
inputted money
d. if the machince has the soda and enough money was entered, complete sale by updating the quantity
on hand and money collected information, calculating the change that is left for the patron, and delivering
the soda displaying the message " Enjoy your beverage "

input validation
a. only accept valid menu choices. do not distribute a beverage if the money inserted is short of
the price of the selected drink.

exercise14(Drink Machine Simulator) on page 590.

Drink Name      Cost    Number in Machine
Cola            1.00       20
Root beer       1.00       20
Orange soda     1.00       20
Grape soda      1.00       20
Bottled water   1.50       20


*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//function prototype
//double validateLessThanZero(double validation);

class sodaMachine 
{
	/*
	the class should have 2 public member functions

		b.buyDrink(handles a sale)
	*/
public:
	//constructors 
	sodaMachine() : moneyCollected(0) 
	{
		drinkTypes[0] = { "Cola", 1.00, 20 };
		drinkTypes[1] = { "Root beer", 1.00, 20 };
		drinkTypes[2] = { "Orange soda", 1.00, 20 };
		drinkTypes[3] = { "Grape soda", 1.00, 20 };
		drinkTypes[4] = { "Bottled water", 1.50, 20 };
	}

	//a.displayChoices(displays menu of drink names and prices)
	void displayChoices() 
	{
		//displays the choices of sodas
		cout << setw(15) << left << "Drink Name" << setw(10) << "Cost" << setw(20) << "Number in Machine" << endl;
		cout << "------------------------------------------" << endl;
		
		//for loop for organizing and aligning the menu
		for (int i = 0; i < 5; ++i) 
		{
		cout << setw(15) << left << drinkTypes[i].drinkName << setw(10) << fixed << setprecision(2) << drinkTypes[i].drinkPrice
		<< setw(20) << drinkTypes[i].drinkQuantity << endl;
			
		}
		cout << " " << endl;
	}

	void buyDrink(int choice) 
		{ //loop for input outside of the choices provided
		if (choice < 1 || choice > 5) 
		{
			cout << "Invalid choice." << endl;
			return;
		}

		// reference of variable drinkinformation to the array of drinkTypes
		// if you leave the & operator, the daily report quantity doesnt seem to count
		drinkInformation& drinkInfo = drinkTypes[choice - 1];
		//assigns price to drinkInfo drinkPrice structure
		double price = drinkInfo.drinkPrice;
		//assigns quantity to drinkInfo drinkQuantity structure
		int quantity = drinkInfo.drinkQuantity;

		//loop for if there is no more of a certain drink type in the machine
		if (quantity <= 0) 
		{
			cout << "Sold out " << endl;
			return;
		}

		//input validation in inputMoney
		double money_inserted = inputMoney(price); 
		if (money_inserted < price) 
		{
			//returns money if not enough money was inserted
			cout << "Transaction canceled. Returning money." << endl;
			return;
		}

		// change function for the money inserted that is greater than price
		double change = money_inserted - price;
		//decrement for quantity if customer buys a drink
		drinkInfo.drinkQuantity--;
		//adds the price of a sold drink to money collected
		moneyCollected = moneyCollected + price;

		//if change is present, this if statement displays it
		if (change > 0) 
		{
			cout << "Here is your change: $" << fixed << setprecision(2) << change << endl;
		}
		cout << "Here is your beverage " << endl;
		cout << " " << endl;
	}

	// Destructor to display daily report
	// provides information on money collected and soda information
	// after use
	~sodaMachine() 
	{
		dailyReport();
	}



	/*
	class should have at least 2 private member functions

	*/
private:
	/*
	information of each drink type should be stored in a structure that has data
	members to contain the drink name, drink price, and
	number of drinks of that type currently in the machine
	*/
	struct drinkInformation 
	{
		string drinkName;
		double drinkPrice;
		int drinkQuantity;
	};

	//array for drink information, 5 drink types
	//store money collected in variable
	drinkInformation drinkTypes[5];
	double moneyCollected;

	//a. (PRIVATE) inputMoney(called by buydrink to accept, validate and return to buyDrink the amount of money input)
	double inputMoney(double drinkPrice) 
	{
		double money;
		//while loop for input validation
		while (true) 
		{
			cout << "Insert money: $ " << fixed << setprecision(2);
			cin >> money;
			if (cin.fail()) 
		{ 
				//input validation in inputMoney to be used in buyDrink
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Cannot be accepted. Enter a valid amount." << endl;
		}
			else if (money < drinkPrice) 
		{	
				//tells the user the amount was less than the price
				cout << "Not enough money." << endl;
		}
			else 
			{
				//returns money for processing to daily report
				return money;
			}
		}
	}

	// b. dailyReport(called by the destructor to report how many of each drink type remain in the machine
	// at the end of the day and the money collected total)
	void dailyReport() 
	{
		cout << "Daily Report: \n";
		//for loop for updated information on each drink type
		for (int i = 0; i < 5; i++) 
		{
			// i + 1 so it doesnt use 0 for index
			cout << i + 1 << ". " << drinkTypes[i].drinkName << ": " 
				<< drinkTypes[i].drinkQuantity << " remaining " << endl;
		}
		//displays the money collected total
		cout << "Money collected total: $" << fixed << setprecision(2) << moneyCollected << endl;
	}

};



	int main() 
	{
		// machine is variable of sodamachine
		// allows main function to use sodaMachine class
		// member functions and variables
		sodaMachine machine;
		cout << " " << endl;
		cout << "	   Soda Machine	"  << endl;
		cout << "------------------------------------------" << endl;
		
		//create infinite loop until a break statement
		while (true) 
		{
			//displays choices from the sodamachine class variable
			machine.displayChoices();

			int drinkChoice;
			cout << "Choose a drink type (1-5) or type 0 to exit and check inventory of machine: ";
			cin >> drinkChoice;

			if (drinkChoice == 0) 
			{
				break;
			}
			// takes care of the sale process in buyDrink
			machine.buyDrink(drinkChoice);
		}




		return 0;
	}



	
