#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
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
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        full.insert(std::to_string(i));
    }

    assert(full.size() == 160);
    assert(!full.insert("K"));
    assert(full.contains("4"));
    assert(full.erase("4"));
    assert(!full.contains("4"));
    assert(full.insert("K"));
    assert(full.contains("K"));
    assert(full.size() == 160);

    ItemType value;
    ItemType& vx = value;
    assert(!full.get(160, vx));
    assert(full.get(159, vx));
    assert(vx == "K");
    assert(full.get(0, vx));
    assert(vx == "0");

    Set miniFull(4);
    assert(miniFull.size() == 0);
    assert(miniFull.insert("A"));
    assert(miniFull.insert("0"));
    assert(miniFull.insert(""));
    assert(miniFull.size() == 3);
    assert(!miniFull.insert(""));
    assert(miniFull.insert("AKA"));
    assert(!miniFull.insert("B"));
    assert(!miniFull.insert(""));

    assert(miniFull.size() == 4);
    assert(!miniFull.erase("B"));
    assert(miniFull.erase("AKA"));
    assert(miniFull.size() == 3);

    assert(miniFull.insert("B"));
    assert(miniFull.get(0, vx));
    assert(vx == "");
    assert(!miniFull.get(4, vx));
    assert(miniFull.get(3, vx));
    assert(vx == "B");

    full.swap(miniFull);
    assert(full.size() == 4);
    assert(miniFull.size() == DEFAULT_MAX_ITEMS);
    assert(miniFull.contains("5") && full.contains("B"));



    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { "01868980", "5018956", "1375626", "1233455", "53", "31" };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++) {
        assert(b.insert(v[k]));
    }

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5]) && b.insert(v[5]));




    cout << "Passed all tests NEW Set" << endl;

}

/*
int main() {
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { 1868980, 5018956, 1375626, 1233455, 53, 31 };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++) {
        assert(b.insert(v[k]));
    }

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5]) && b.insert(v[5]));

    cout << "Passed all tests new Set" << endl
}
*/

/*


int main()
{
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { 123, 10, 89, 98, 126, 22};

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++) 
        assert(b.insert(v[k]));

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));

    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    b.insert(v[3]);

    assert(!a.insert(v[5]) && b.insert(v[5]));
}
*/