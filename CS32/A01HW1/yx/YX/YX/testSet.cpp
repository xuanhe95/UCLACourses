
/*
#include "Set.h"
#include <iostream>
#include <cassert>
   using namespace std;

   int main()
   {
       Set s1;
       assert(s1.empty());
       ItemType x = 9876543;
       assert( !s1.get(42, x)  &&  x == 9876543); // x unchanged by get failure
       s1.insert(123456789);
       assert(s1.size() == 1);
       assert(s1.get(0, x)  &&  x == 123456789);
       s1.insert(389);
       s1.dump();
       
       Set s2;
       s2.insert(98734013);
       s2.insert(7462);
       s2.insert(0);
       assert(s2.contains(0));
       s2.erase(0);
       assert(s2.contains(7462));
       s2.insert(7462);
       s2.insert(14895739042);
       assert(!s2.contains(0));
       assert(s2.contains(7462));
       assert(!s2.insert(7462));
       s2.insert(7489052);
       
       swap(s1, s2);
       assert(s1.contains(98734013) && !s2.contains(98734013) && s2.contains(123456789));
       assert(s1.size() == 4 && s2.size() == 2);
        
       cout << "Passed all tests" << endl;
   }
*/


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
    assert( !s1.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
    s1.insert("chapati");
    assert(s1.size() == 1);
    assert(s1.get(0, x)  &&  x == "chapati");
    s1.insert("ahapati");
    assert(s1.size() == 2);
    assert(s1.get(0, x)  &&  x == "ahapati");
    
    Set s2;
    s2.insert("zill");
    s2.insert("fill");
    s2.insert("bill");
    assert(s2.contains("bill"));
    s2.erase("bill");
    assert(s2.contains("fill"));
    s2.insert("fill");
    s2.insert("cool");
    assert(!s2.contains("bill"));
    assert(s2.contains("fill"));
    assert(!s2.insert("fill"));
    s2.insert("");
    assert(s2.get(0, x)  &&  x == "");
    
    swap(s1, s2);
    assert(s1.contains("") && !s2.contains("cool") && s2.contains("chapati"));
    assert(s1.size() == 4 && s2.size() == 2);

    cout << "Passed all tests" << endl;
}




