#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);
int countBool(const string s, const Set& trueValues, const Set& falseValues, bool& result);
int order(char o);
bool isOperand(char c);
int operandStatus(char c, const Set& trueValues, const Set& falseValues);
void print(stack<char> s);

// Evaluate a boolean expression
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values sets), then postfix is set to the postfix
//   form of the expression.  If not, postfix might or might not be
//   changed, result is unchanged, and the function returns 1.
//
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters:
//
//      If every operand letter in the expression appears in either
//      trueValues or falseValues but not both, then result is set to the
//      result of evaluating the expression (using for each letter in the
//      expression the value true if that letter appears in trueValues or
//      false if that letter appears in false values) and the function
//      returns 0.
//
//      Otherwise, result is unchanged and the value the function returns
//      depends on these two conditions:
//        at least one letter in the expression is in neither the
//            trueValues nor the falseValues sets; and
//        at least one letter in the expression is in both the
//            trueValues and the falseValues set.
//      If only the first condition holds, the function returns 2; if
//      only the second holds, the function returns 3.  If both hold
//      the function returns either 2 or 3 (and the function is not
//      required to return the same one if called another time with the
//      same arguments).



int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
	stack<char> s;
	string post;

	for (int i = 0; i < infix.size(); i++) {
		char c = infix.at(i);
		if (c == '(') {
			if (i == infix.size() - 1) return 1;
			else if (isOperand(infix.at(i + 1)) || infix.at(i + 1) == '!' || infix.at(i + 1) == '(') {
				s.push(c);
			}
			else return 1;
		}
		else if (c == ')') {
			while (s.top() != '(') {
				post += s.top();
				s.pop();
			}
			s.pop();
		}
		else if (isOperand(c)) post += c;
		else if (c == ' ') continue;
		else if (order(c) != -1) {
			while (!s.empty() && order(c) < order(s.top())) {
				post += s.top();
				s.pop();
			}
			s.push(c);
			//print(s);
		}
		else return 1;	// non-valid input
	}

	while (!s.empty()) {
		post += s.top();
		s.pop();
	}
	postfix = post;
	return countBool(post, trueValues, falseValues, result);
}

void print(stack<char> s) {
	stack<char> temp;

	while (!s.empty()) {
		cerr << s.top() << endl;
		temp.push(s.top());
		s.pop();
	}
	while (!temp.empty()) {
		s.push(temp.top());
		temp.pop();

	}
	cerr << "=========" << endl;
}

int countBool(const string st, const Set& trueValues, const Set& falseValues, bool& result) {
	if (st == "") return 1;
	bool rst = true;
	bool firstOperator= false;
	stack<bool> s;

	for (int i = 0; i < st.size(); i++) {
		char c = st.at(i);
		if (!isOperand(c) && c != '!') {
			if (!firstOperator) {
				rst = s.top();
				s.pop();
				firstOperator = true;
			}
			if (s.empty()) return 1;
			else if (c == '&') {
				rst = rst && s.top();
				s.pop();
			}
			else if (c == '|') {
				rst = rst || s.top();
				s.pop();
			}
		}
		else if (c == '!') {
			s.top() = !s.top();
		}
		else {
			if (operandStatus(c, trueValues, falseValues) == 0) s.push(true);
			else if (operandStatus(c, trueValues, falseValues) == 1) s.push(false);
			else return operandStatus(c, trueValues, falseValues);
		}
	}
	if (st.size() == 1 && isOperand(st.at(0))) {
		result = s.top();
		return 0;
	}
	if (!s.empty()) return 1;
	else {
		result = rst;
		return 0;
	}
}


int operandStatus(char c, const Set& trueValues, const Set& falseValues) {
	if (trueValues.contains(c) && falseValues.contains(c)) return 3;
	else if (!trueValues.contains(c) && !falseValues.contains(c)) return 2;
	else if (trueValues.contains(c)) return 0;
	else return 1;
}


int order(char o) {
	if (o == '(') return 0;
	if (o == '!') return 5;
	if (o == '&') return 4;
	if (o == '|') return 3;
	return -1;
}

bool isOperand(char c) {
	return islower(c);
}


int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("()z", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("n+y", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x" && answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cout << "Passed all tests" << endl;
}