#include <iostream>
#include <string>
using namespace std;

int main() {
	const double LOW = 55000, MID = 70000, HIGH = LOW + MID;	//bounds of tax rates.
	const double LOW_RATE = 0.04, SPECIAL_RATE = 0.05, MID_RATE = 0.07, HIGH_RATE = 0.093;	//tax rates
	const double CHILD_DISCOUNT = 200;	//discount for per child.

	string name, occupation;
	double income, tax = 0; //taxable tax and total tax.
	int children;

	cout.setf(ios::fixed);
	cout.precision(2);	//set precision of double numbers.

	cout << "Enter your name: " << endl;
	getline(cin, name);
	
	cout << "Enter your taxable income: " << endl;
	cin >> income;
	cout << "Enter your occupation: " << endl;
	cin.ignore(10000, '\n');
	getline(cin, occupation);
	cout << "Enter your children: " << endl;
	cin >> children;

	

	if (income <= LOW){	//if income lower than first bound.
		tax += income * LOW_RATE;
	}
	else if (income <= HIGH){	//if income lower than second bound.
		tax += LOW * LOW_RATE;
		if (occupation == "nurse" || occupation == "teacher") {
			tax += (income - LOW) * SPECIAL_RATE;
		}
		else {
			tax += (income - LOW) * MID_RATE;
		}
	}
	else{	//beyound bounds.
		tax += LOW * LOW_RATE;
		if (occupation == "nurse" || occupation == "teacher") tax += MID * SPECIAL_RATE;
		else tax += MID * MID_RATE;
		tax += (income - HIGH) * HIGH_RATE;
	}

	if (income < HIGH) {	//if income less than high bound.
		tax -= children * CHILD_DISCOUNT;
		tax = (tax < 0) ? 0 : tax; //make sure that total tax not less than 0.
	}

	cout << "Name: " << name << endl;
	cout << "Taxable income: " << income << endl;
	cout << "Occupation: " << occupation << endl;
	cout << "Number of children: " << children << endl;
	cout << "---" << endl;

	if (name == "") cout << "You must enter a name" << endl;
	else if (income < 0) cout << "The taxable income must not be negative" << endl;
	else if (occupation == "") cout << "You must enter an occupation" << endl;
	else if (children < 0) cout << "The number of children must not be negative" << endl;
	else cout << name << " would pay $" << tax <<endl;

}



