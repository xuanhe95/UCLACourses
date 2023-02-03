#include "CardSet.h"

CardSet::CardSet() {
    this->m_set = Set();
}
bool CardSet::add(unsigned long cardNumber) {
    return this->m_set.insert(cardNumber);
}
int CardSet::size() const {
    return this->m_set.size();
}
void CardSet::print() const {
    unsigned long value;
    for (int i = 0; i < this->m_set.size(); i++) {
        this->m_set.get(i, value);
        std::cout << value << std::endl;
    }
}

