#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set ss;
    std::cerr << "A";
    assert(ss.insert("roti"));
    std::cerr << "A";
    assert(ss.insert("pita"));
    std::cerr << "A";
    assert(ss.size() == 2);
    std::cerr << "A";
    assert(ss.contains("pita"));
    std::cerr << "A";
    ItemType x = "laobing";
    std::cerr << "A";
    assert(ss.get(0, x) && x == "pita");
    std::cerr << "A";
    assert(ss.get(1, x) && x == "roti");
    std::cerr << "A";
    ss.dump();
}

int main()
{
    test();
    std::cerr << "K";
    cout << "Passed all tests" << endl;
    std::cerr << "K";
}