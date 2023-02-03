#include <iostream>
#include <cassert>
#include "Set.h"
#include "CardSet.h"

int main() {
    CardSet cs1;
    cs1.add(12345678);
    cs1.print();
    cs1.add(28902);
    cs1.print();
    assert(cs1.size() == 2);
    
    CardSet cs2 = cs1;
    cs1.add(137905);
    assert(cs1.size() == 3);
    assert(cs2.size() == 2);
    cs1.print();
    cs2.print();
    
    cout << "Passed all tests" << endl;
}
