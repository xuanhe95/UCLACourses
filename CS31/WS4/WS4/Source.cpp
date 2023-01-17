#include <iostream>
using namespace std;

/***
string stateCodes[] = {
	"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MA",
	"MD", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
	"SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
};
char partyCodes[2];
***/

string reverseString(string);
string reverseWord(string);


int main() {
	cout << reverseString("Let's take LeetCode contest");
}

string reverseString(string text) {
	int len = 0;
	int s = 0;
	string ret = "";
	for (int i = 0; i < text.size(); i++) {
		if (text.at(i) == ' ') {
			ret += reverseWord(text.substr(s, len + 1).c_str());
			len = 0;
			s = i+1;
		}
		else len++;
	}
	return ret.substr( 1, ret.size() - 1).c_str();
}

string reverseWord(string word) {
	string ret = "";
	for (int i = word.size() - 1; i >= 0; i--) {
		ret += word.at(i);
	}
	return ret;
}