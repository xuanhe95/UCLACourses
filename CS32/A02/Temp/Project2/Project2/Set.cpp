// Set.cpp

#include "Set.h"

Set::Set()
	: m_sdll(*new SortedDoubleLinkedList())
{}

bool Set::insert(const ItemType& value)
{
	return m_sdll.insert(value);	// insert the value to the linked list
}

bool Set::erase(const ItemType& value)
{
	return m_sdll.remove(value);	// remove the value from the linked list
}

bool Set::get(int i, ItemType& value) const
{
	return m_sdll.get(i, value);	// get the value from the linked list
}

void Set::swap(Set& other)
{
	SortedDoubleLinkedList temp;	// preserve the linked list from original Set
	temp = m_sdll;
	m_sdll = other.m_sdll;			// set other's linked list to the original Set
	other.m_sdll = temp;			// set the preserved linked list to the other Set
}
/*
int Set::findFirstAtLeast(const ItemType& value) const
{
	int begin = 0;
	int end = m_size;
	while (begin < end)
	{
		int mid = (begin + end) / 2;
		if (value < m_data[mid])
			end = mid;
		else if (m_data[mid] < value)
			begin = mid + 1;
		else
			return mid;
	}
	return begin;
}
*/

Set::Set(const Set& other) {
	m_sdll = other.m_sdll;
}
Set& Set::operator=(const Set& other) {
	if (this != &other) {
		Set temp(other);
		swap(temp);
	}
	return *this;
}

void Set::dump() const {
	m_sdll.dump();
}

void unite(const Set& s1, const Set& s2, Set& result) {
	ItemType x;
	result = s1;
	for (int i = 0; i < s2.size(); i++) {
		s2.get(i, x);
		result.insert(x);
	}
}

void butNot(const Set& s1, const Set& s2, Set& result) {
	ItemType x;
	result = s1;
	for (int i = 0; i < s2.size(); i++) {
		s2.get(i, x);
		result.erase(x);
	}
}