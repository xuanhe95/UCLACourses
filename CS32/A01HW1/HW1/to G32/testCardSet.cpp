#include "Set.h"
#include "CardSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    CardSet s;
    ItemType x = 501896731;
    assert(s.add(x));
    assert(s.add(186866120));
    assert(s.add(137562644));
    assert(s.add(139414466));
    assert(!s.add(186866120));
    assert(s.size() == 4);

    CardSet cs1;
    cs1.add(12345678);
    cs1.add(28902);
    assert(cs1.size() == 2);

    CardSet cs2 = cs1;
    cs1.add(137905);
    assert(cs1.size() == 3);
    assert(cs2.size() == 2);
    cs1.print();
    cs2.print();

    CardSet full;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        full.add(i * 100);
    }
    assert(!full.add(0));
    assert(!full.add(100));
    assert(!full.add(1000));
    assert(full.size() == DEFAULT_MAX_ITEMS);
    full.print();

    cout << "Passed all tests Card Set" << endl;
}