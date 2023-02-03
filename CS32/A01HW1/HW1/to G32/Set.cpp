#include "Set.h"

Set::Set() {
    m_size = 0;
}

bool Set::empty() const {
    return m_size == 0;
}
int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if(this->size() == DEFAULT_MAX_ITEMS || this->contains(value)) return false;
    int split_index = 0;
    for (int i = 0; i < this->size(); i++) {
        if (this->m_container[split_index] == value) {
            return false;
        }
        else if (this->m_container[split_index] < value) {
            split_index++;
        }
        else {
            break;
        }
    }
    
    for (int i = this->size(); i > split_index ; i--) {
        m_container[i] = m_container[i-1];
    }
    m_container[split_index] = value;
    this->m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    int split_index = 0;
    bool found_value = false;
    for (int i = 0; i < m_size; i++) {
        if (this->m_container[i] == value) {
            split_index = i;
            found_value = true;
            break;
        }
    }
    if (found_value) {
        if (split_index != DEFAULT_MAX_ITEMS) {
            for (int i = split_index; i < m_size - 1; i++) {
                this->m_container[i] = this->m_container[i + 1];
            }
        }
        this->m_size--;
    }
    return found_value;
}
// Remove the value from the set if it is present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const{
    for (int i = 0; i < m_size; i++) {
        if (this->m_container[i] == value) return true;
    }
    return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const{
    if (i >= 0 && i < this->size()) {
        value = this->m_container[i];
        return true;
    }
    return false;
}
// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.

void Set::swap(Set& other) {
    ItemType container_temp[DEFAULT_MAX_ITEMS];
    for (int i = 0; i < this->m_size; i++) {
        container_temp[i] = this->m_container[i];
    }

    int size_temp = this->m_size;
    
    for (int i = 0; i < other.m_size; i++) {
        this->m_container[i] = other.m_container[i];
    }
    this->m_size = other.m_size;

    other.m_size = size_temp;
    
    for (int i = 0; i < size_temp; i++) {
        other.m_container[i] = container_temp[i];
    }
}
// Exchange the contents of this set with the other one.

void Set::dump() {
    std::cerr << "size: ";
    std::cerr << m_size << std::endl;
    for (int i = 0; i < size(); i++) {
        std::cerr << "No.   " << i << " " << std::endl;
        std::cerr << m_container[i] << std::endl;
    }
    std::cerr << "======================" << std::endl;
}
// Print test

