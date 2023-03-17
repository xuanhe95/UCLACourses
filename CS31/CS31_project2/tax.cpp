#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    string occupation;
    double income;
    int children;
    double tax;
    
    cout << "Name: ";
    getline(cin, name);
    cout << "Taxable income: ";
    cin >> income;
    cin.ignore(10000, '\n');
    cout << "Occupation: ";
    getline(cin, occupation);
    cout << "Number of children: ";
    cin >> children;
    cout << "---" << endl;
    
    if (name.length() == 0) {
        cout << "You must enter a name" << endl;
    } else if (income < 0) {
        cout << "The taxable income must not be negative" << endl;
    } else if (occupation.length() == 0) {
        cout << "You must enter an occupation" << endl;
    } else if (children < 0) {
        cout << "The number of children must not be negative" << endl;
    } else {
        
        if (income <= 55000) {
            tax = income * 0.04;
        } else if (income <= 125000) {
            if (occupation == "nurse" || occupation == "teacher") {
                tax = 55000 * 0.04 + (income - 55000) * 0.05;
            } else {
                tax = 55000 * 0.04 + (income - 55000) * 0.07;
            }
        } else {
            if (occupation == "nurse" || occupation == "teacher") {
                tax = 55000 * 0.04 + 70000 * 0.05 + (income - 125000) * 0.093;
            } else {
                tax = 55000 * 0.04 + 70000 * 0.07 + (income - 125000) * 0.093;
            }
        }
        
        if (income < 125000) {
            tax = tax - 200 * children;
        }
        
        if (tax < 0) {
            tax = 0;
        }
        
        cout.setf(ios::fixed);
        cout.precision(2);
        
        cout << name << " would pay $" << tax << endl;
    }
    
}
