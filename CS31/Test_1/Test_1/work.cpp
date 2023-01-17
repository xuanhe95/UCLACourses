#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "How many hours did you work?" << endl;
	double hours;
	cin >> hours;

	cout << "What is your hourly rate of pay?" << endl;
	double payRate;
	cin >> payRate;

	cout << "Hours worked is " << hours << endl;
	cout << "Pay rate is " << payRate << endl;

	double salary = hours * payRate;
	cout << "Your salary is $" << salary << endl;

	cout.setf(ios::fixed);
	cout.precision(2);	//fixed in two digits after the point.

	cout << salary * 0.10 << " will be withheld." << endl << endl;
	cin.ignore(10000, '\n');

	cout << "What's your name? ";
	string name;
	getline(cin, name);

	cout << "How old are you? ";
	int age;
	cin >> age;

	cin.ignore(10000, '\n');

	cout << "What is your quest? ";
	string quest;
	getline(cin, quest);

	cout << "Hello, brave " << name << "!" << endl;
	cout << "You want to " << quest << endl;
	cout << "If you live, next year you will be " << age + 1 << endl;

}