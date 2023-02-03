#ifndef newSet_hpp
#define newSet_hpp

#include <iostream>
using namespace std;

using ItemType = string;
const int DEFAULT_MAX_ITEMS = 160;

class Set
{
  public:
    Set();         // Create an empty set (i.e., one whose size() is 0).
    
    Set(int size);
    
    Set(const Set&s);
    
    Set& operator=(const Set&s);
    
    ~Set();

    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if value is not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
     
    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
    
    void dump() const;
    
    
private:
    ItemType* m_array;
    int m_count;
    int m_size;
};

#endif
