// Set.cpp

#include "Set.h"
#include <iostream>
using namespace std;

Set::Set()
{
	Node* dummyNode = new Node();
	m_head = dummyNode;	// set dummy node as head
	dummyNode->next = dummyNode;	// point next to itself
	dummyNode->prev = dummyNode;	// point prev to itself
	m_size = 0;
}

Set::~Set()
{
	if (m_head->next == m_head) {
		delete m_head;
		return;
	}
	Node* tempHead = m_head;
	m_head = m_head->next;
	while (m_head != tempHead) {
		Node* temp = m_head;
		m_head = m_head->next;
		delete temp;
	}
	delete tempHead;
	/*
	if (m_head->next == m_head) {
		delete m_head;
		return;
	}
	Node* nextNodePtr = m_head;
	for (int i = 0; i < m_size; i++) {
		delete nextNodePtr->prev;
		nextNodePtr = nextNodePtr->next;
	}
	*/
}

bool Set::insert(const ItemType& value)
{
	Node* nextNodePtr = findFirstAtLeast(value);
	Node* prevNodePtr = nextNodePtr->prev;
	if (nextNodePtr->data == value) {	// && nextNodePtr != m_tail?
		return false;
	}
	Node* newNodePtr = new Node(value);	// create new node
	prevNodePtr->next = newNodePtr;
	newNodePtr->prev = prevNodePtr;
	newNodePtr->next = nextNodePtr;
	nextNodePtr->prev = newNodePtr;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value)
{
	Node* delNodePtr = findFirstAtLeast(value);
	if (delNodePtr == m_head) return false;
	if (delNodePtr->data != value) return false;
	Node* prevNodePtr = delNodePtr->prev;
	Node* nextNodePtr = delNodePtr->next;
	prevNodePtr->next = nextNodePtr;
	nextNodePtr->prev = prevNodePtr;
	m_size--;
	delete delNodePtr;	// delete erased node
	return true;
}

bool Set::get(int i, ItemType& value) const
{
	if (i < 0 || i >= m_size || m_head->next == m_head) return false;	// if pos is not valid, or the linked list is empty, return false
	Node* currNode = m_head;
	for (int j = i; j >= 0; j--) {
		currNode = currNode->next;
	}
	value = currNode->data;
	return true;
}

void Set::swap(Set& other)
{
	int size_temp = this->m_size;
	this->m_size = other.m_size;
	other.m_size = size_temp;

	Node* node_temp = this->m_head;
	this->m_head = other.m_head;
	other.m_head = node_temp;
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

Set::Set(const Set& other) {	// copy
	Node* dummyNode = new Node();
	m_head = dummyNode;	// set dummy node as head
	dummyNode->next = dummyNode;	// point next to itself
	dummyNode->prev = dummyNode;	// point prev to itself
	m_size = 0;

	ItemType x;

	for (int i = 0; i < other.m_size; i++) {
		other.get(i, x);
		insert(x);
	}
}
Set& Set::operator=(const Set& other) {
	if (this != &other) {	// copy and swap
		Set temp(other);
		swap(temp);
	}
	return *this;
}

void Set::dump() const {
	cerr << "Head	" << m_head << endl;
	cerr << "Next	" << m_head->next << endl;
	cerr << "Prev	" << m_head->prev << endl;
	cerr << "=========================" << endl;
	for (Node* currNodePtr = m_head->next; currNodePtr != m_head; currNodePtr = currNodePtr->next) {
		cerr << currNodePtr->data << endl;
	}
	cerr << "Size: " << m_size << endl;
	cerr << "-------------------------" << endl;
}

Set::Node* Set::findFirstAtLeast(const ItemType& value) const {
	if (m_head->next == m_head) {   // if empty m_head
		return m_head;
	}
	Node* currNodePtr = m_head->next;
	while (currNodePtr != m_head && currNodePtr->data < value) {
		currNodePtr = currNodePtr->next;
	}
	return currNodePtr;
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