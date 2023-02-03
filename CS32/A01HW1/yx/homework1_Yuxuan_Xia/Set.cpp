#include <iostream>
#include "Set.h"

Set::Set(){
    m_count = 0;
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
    if (m_count < DEFAULT_MAX_ITEMS && !this->contains(value)) {
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
    int temp = other.m_count;
    other.m_count = this->m_count;
    this->m_count = temp;
    
    int large_count;
    if (other.m_count > this->m_count) {
        large_count = other.m_count;
    }
    else {
        large_count = this->m_count;
    }
    
    for (int i = 0; i < large_count; i++) {
        ItemType temp = this->m_array[i];
        this->m_array[i] = other.m_array[i];
        other.m_array[i] = temp;
    }
}

void Set::dump() const {
    for (int i = 0; i < m_count; i++) {
        cerr << i << ": " << m_array[i] << endl;
    }
}
