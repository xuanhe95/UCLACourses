#include <iostream>
#include "newSet.h"

Set::Set(){
    m_array = new ItemType[DEFAULT_MAX_ITEMS];
    m_count = 0;
    m_size = DEFAULT_MAX_ITEMS;
}

Set::Set(int size) {
    m_array = new ItemType[size];
    m_count = 0;
    m_size = size;
}

Set::~Set() {
    delete [] m_array;
}

Set::Set(const Set&s)  {
    m_size = s.m_size;
    m_count = s.m_count;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = s.m_array[i];
    }
}

Set& Set::operator=(const Set&s)  {
    if (this != &s){
        m_size = s.m_size;
        m_count = s.m_count;
        delete[] m_array;
        m_array = new ItemType[m_size];
        if (m_count > 0) {
            for (int i = 0; i < m_count; i++) {
                m_array[i] = s.m_array[i];
            }
        }
    }
    return *this;
}

bool Set::empty() const {
    if (m_count == 0) {
        return true;
    }
    else {
        return false;
    }
}

int Set::size() const {
    return m_count;
}

bool Set::contains(const ItemType &value) const {
    for (int i = 0; i < m_count; i++) {
        if (value == m_array[i]) {
            return true;
        }
    }
    return false;
}

bool Set::insert(const ItemType &value) {
    if (m_count < m_size && !this->contains(value)) {
        if (m_count == 0) {
            m_array[0] = value;
        }
        else if (m_array[m_count - 1] < value) {
            m_array[m_count] = value;
        }
        else {
            for (int i = 0; i < m_count; i++) {
                if (m_array[i] > value) {
                    for (int j = m_count - 1; j >= i; j--) {
                        m_array[j + 1] = m_array[j];
                    }
                    m_array[i] = value;
                    break;
                }
            }
        }
        m_count++;
        return true;
    }
    return false;
}

bool Set::erase(const ItemType &value) {
    if (this->contains(value)) {
        for (int i = 0; i < m_count; i++) {
            if (value == m_array[i]) {
                for (int j = i; j < m_count - 1; j++) {
                    m_array[j] = m_array[j + 1];
                }
                m_count--;
                return true;
            }
        }
    }
    return false;
}

bool Set::get(int i, ItemType &value) const {
    if (i >= 0 && i < m_count ) {
        value = m_array[i];
        return true;
    }
    return false;
}

void Set::swap(Set &other){
    Set temp = *this;
    *this = other;
    other = temp;
}

void Set::dump() const {
    for (int i = 0; i < m_count; i++) {
        cerr << i << ": " << m_array[i] << endl;
    }
}
