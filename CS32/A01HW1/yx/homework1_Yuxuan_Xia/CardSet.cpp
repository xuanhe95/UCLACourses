
#include "CardSet.h"

CardSet::CardSet() {}

bool CardSet::add(unsigned long cardNumber) {
    return m_cards.insert(cardNumber);
}

int CardSet::size() const {
    return m_cards.size();
}

void CardSet::print() const {
    unsigned long x;
    for (int i = 0; i < this->size(); i++) {
        m_cards.get(i, x);
        cout << x << endl;
    }
}
