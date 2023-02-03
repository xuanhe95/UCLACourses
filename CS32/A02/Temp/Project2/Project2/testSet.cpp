#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	Set s1;
	assert(s1.empty());
	ItemType x = "arepa";
	assert(!s1.get(42, x) && x == "arepa"); // x unchanged by get failure
	s1.insert("chapati");
	assert(s1.size() == 1);
	assert(s1.get(0, x) && x == "chapati");
	s1.insert("ahapati");
	assert(s1.size() == 2);
	assert(s1.get(0, x) && x == "ahapati");

	Set s2;
	s2.insert("zill");
	s2.insert("fill");
	s2.insert("bill");

	assert(s2.contains("bill"));
	s2.erase("bill");
	assert(s2.contains("fill"));
	assert(!s2.insert("fill"));
	s2.insert("cool");

	assert(!s2.contains("bill"));
	assert(s2.contains("fill"));
	assert(!s2.insert("fill"));
	s2.insert("");

	assert(s2.get(0, x) && x == "");

	swap(s1, s2);
	assert(s1.contains("") && !s2.contains("cool") && s2.contains("chapati"));
	assert(s1.size() == 4 && s2.size() == 2);

	assert(!s1.erase("nill"));
	assert(s1.erase("fill"));
	assert(s1.size() == 3);
	assert(!s1.contains("fill"));
	assert(!s1.contains("chapati"));

	Set full;
	for (int i = 0; i < 160; i++) {
		full.insert(std::to_string(i));
	}

	assert(full.size() == 160);
	assert(full.contains("4"));
	assert(full.erase("4"));
	assert(!full.contains("4"));
	assert(full.insert("K"));
	assert(full.contains("K"));
	assert(full.size() == 160);

	ItemType value;
	ItemType& v = value;
	assert(!full.get(160, v));
	assert(full.get(159, v));
	assert(v == "K");
	assert(full.get(0, v));
	assert(v == "0");

	cout << "Passed all tests Set" << endl;
}