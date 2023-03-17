#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isOperand(char x) {
   return (x >= 'a' && x <= 'z');
}

bool isOperator(char x) {
   return (x == '&' || x == '|' || x == '!' );
}

bool isBiOperator(char x) {
   return (x == '&' || x == '|');
}

int precedence(char x) {
    switch (x){
        case '&':
            return 2;
        case '|':
            return 1;
        case '!':
            return 3;
        default:
            return 0;
    }
}

bool valid(string infix) {
    stack<char> parentheses;
    int numOperand = 0;
    if (infix.size() != 0){
        string infix2 = "";
        for (int i = 0; i < infix.size(); i++){
            if (infix[i] != ' '){
                infix2 += infix[i];
            }
        }
        for (int i = 0; i < infix2.size() ; i++){
            if (!isOperator(infix2[i]) && !isOperand(infix2[i]) && infix2[i] != '(' && infix2[i] != ')'){
                return false;
            }
            if (isBiOperator(infix2[i])) {
                if (i < 1 || i >= infix2.size() - 1 || isOperator(infix2[i - 1]) || isBiOperator(infix2[i - 1])){
                    return false;
                }
            }
            else if (infix2[i] == '!'){
                if (isBiOperator(infix2[i + 1])){
                    return false;
                }
            }
            else if (isOperand(infix2[i])){
                numOperand ++;
                if (i != infix2.size() - 1) {
                    if (isOperand(infix2[i + 1]) || infix2[i + 1] == '('){
                        return false;
                    }
                }
            }
            else if (infix2[i] == '(') {
                if (i != infix2.size() - 1) {
                    if (infix2[i + 1] == ')'){
                        return false;
                    }
                }
                parentheses.push('(');
            }
            else if (infix2[i] == ')') {
                if (parentheses.empty()){
                    return false;
                }
                parentheses.pop();
            }
        }
        if (!parentheses.empty()){
            return false;
        }
        if (numOperand == 0){
            return false;
        }
        return true;
    }
    return false;
}

void convert(string infix, string& postfix) {
    postfix = "";
    stack<char> operatorStack;
    for (int i = 0; i < infix.size(); i ++) {
        char chr = infix[i];
        if (isOperand(chr)) {
            postfix += chr;
        }
        else if (chr == '(') {
            operatorStack.push(chr);
        }
        else if (chr == ')'){
            while (operatorStack.top() != '('){
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (isOperator(chr)){
            while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(chr) <= precedence(operatorStack.top())){
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(chr);
        }
    }
    while (!operatorStack.empty()){
        postfix += operatorStack.top();
        operatorStack.pop();
    }
}

void evaluate(string postfix, bool& result, const Set& trueValues, const Set& falseValues) {
    stack<bool> boolOperandStack;
    for (int i = 0; i < postfix.size(); i ++){
        char chr = postfix[i];
        if (isOperand(chr)){
            boolOperandStack.push(trueValues.contains(chr));
        }
        else{
            if (chr == '!'){
                bool boolOperand = boolOperandStack.top();
                boolOperandStack.pop();
                boolOperand = !boolOperand;
                boolOperandStack.push(boolOperand);
            }
            else{
                bool boolOperand2 = boolOperandStack.top();
                boolOperandStack.pop();
                bool boolOperand1 = boolOperandStack.top();
                boolOperandStack.pop();
                if (chr == '&'){
                    if (boolOperand1 && boolOperand2){
                        result = true;
                    }
                    else {
                        result = false;
                    }
                }
                else if (chr == '|') {
                    if (boolOperand1 || boolOperand2){
                        result = true;
                    }
                    else {
                        result = false;
                    }
                }
                boolOperandStack.push(result);
            }
        }
    }
    result = boolOperandStack.top();
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    if (!valid(infix)){
        return 1;
    }
    convert(infix, postfix);
    for (int i = 0; i < infix.size(); i++){
        if (isOperand(infix[i])){
            if (trueValues.contains(infix[i]) && falseValues.contains(infix[i])){
                return 3;
            }
            if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i])){
                return 2;
            }
        }
    }
        evaluate(postfix, result, trueValues, falseValues);
        return 0;
}

int main()
{
    
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
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
    assert(evaluate("F  |  !f & (t&n) ", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
                           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);

    
/*
    string trueChars  = "ucla";
    string falseChars = "nsx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    string pf;
    bool answer;
    

    assert(evaluate("u", trues, falses, pf, answer) == 0 &&  answer);
    assert(evaluate("u&c&l&a & !(u&s&c)", trues, falses, pf, answer) == 0  &&  answer);
    assert(evaluate("(n)", trues, falses, pf, answer) == 0   &&  !answer);
      assert(evaluate("a&(s)", trues, falses, pf, answer) == 0   &&  !answer);
        assert(evaluate("a & !s", trues, falses, pf, answer) == 0  &&  answer);
        assert(evaluate("!(n|u)", trues, falses, pf, answer) == 0 &&  !answer);
        assert(evaluate("!n|u", trues, falses, pf, answer) == 0   &&  answer);
        assert(evaluate("a|n&n", trues, falses, pf, answer) == 0  &&  answer);
        assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", trues, falses, pf, answer) == 0 &&  answer);
        assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", trues, falses, pf, answer) == 0 &&  answer);
        assert(evaluate("a&!(s|u&c|n)|!!!(s&u&b)", trues, falses, pf, answer) == 2 &&  answer);
*/
    
    cout << "Passed all tests" << endl;
 
}
 

