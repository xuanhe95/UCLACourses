#include <string>
#include <iostream>
#include "Node.h"
using namespace std;

SortedDoubleLinkedList::SortedDoubleLinkedList() {
	Node* dummyNode = new Node();
	m_head = dummyNode;	// set dummy node as head
	dummyNode->next = dummyNode;	// point next to itself
	dummyNode->prev = dummyNode;	// point prev to itself
	m_size = 0;
}

SortedDoubleLinkedList::~SortedDoubleLinkedList() {
	delete m_head;
}

SortedDoubleLinkedList::SortedDoubleLinkedList(const SortedDoubleLinkedList& other) {
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
void SortedDoubleLinkedList::swap(SortedDoubleLinkedList& other) {
	Node* temp = m_head;
	m_head = other.m_head;
	other.m_head = temp;
}
SortedDoubleLinkedList& SortedDoubleLinkedList::operator=(const SortedDoubleLinkedList& other) {
	if (this != &other) {
		SortedDoubleLinkedList temp(other);
		swap(temp);
	}
	return *this;
}

Node* SortedDoubleLinkedList::getHead() const {
	return m_head;
}

bool SortedDoubleLinkedList::get(int pos, ItemType& value) const {
	if (pos < 0 || m_head->next == m_head) return false;	// if pos is not valid, or the linked list is empty, return false
	Node* currNode = m_head->next;
	for (currNode != m_head; currNode != m_head; currNode = currNode->next) {
		if (pos == 0) {
			value = currNode->data;
			return true;
		}
		pos--;
	}
	return false;
}

void SortedDoubleLinkedList::dump() const {
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

Node* SortedDoubleLinkedList::findNode(const ItemType& value) const {
	if (m_head->next == m_head) {   // if empty return false
		return m_head;
	}
	Node* currNodePtr = m_head->next;
	while (currNodePtr != m_head && (*currNodePtr).data < value) {
		currNodePtr = currNodePtr->next;
	}
	return currNodePtr;
}

bool SortedDoubleLinkedList::insert(const ItemType& value) {
	Node* nextNodePtr = findNode(value);
	Node* prevNodePtr = nextNodePtr->prev;
	if (nextNodePtr->data == value) {	// && nextNodePtr != m_tail?
		return false;
	}
	Node* newNodePtr = new Node(value);
	prevNodePtr->next = newNodePtr;
	newNodePtr->prev = prevNodePtr;
	newNodePtr->next = nextNodePtr;
	nextNodePtr->prev = newNodePtr;
	m_size++;
	return true;
}

bool SortedDoubleLinkedList::remove(const ItemType& value) {
	Node* delNodePtr = findNode(value);
	if (delNodePtr == m_head) return false;
	if (delNodePtr->data != value) return false;
	Node* prevNodePtr = delNodePtr->prev;
	Node* nextNodePtr = delNodePtr->next;
	prevNodePtr->next = nextNodePtr;
	nextNodePtr->prev = prevNodePtr;
	m_size--;
	delete delNodePtr;
	return true;
}

bool SortedDoubleLinkedList::isEmpty() const {
	return m_size == 0;
}

int SortedDoubleLinkedList::size() const {
	return m_size;
}

/*
int main() {
	SortedDoubleLinkedList sdl;
	sdl.dump();
	sdl.insert(1);
	sdl.dump();
	sdl.insert(2);

	ItemType x;
	sdl.get(2, x);
	cerr << "X is ";
	cerr << x << endl;
	cerr << "=====================" << endl;
	sdl.dump();
	sdl.remove(2);
	sdl.dump();
	sdl.remove(1);
	sdl.dump();
	//cerr << sdl.getTail() << endl;
	//cerr << sdl.findNode(1) << endl;
}

*/

Node::Node() {
	next = nullptr;
	prev = nullptr;
}
Node::Node(const ItemType& value) {
	data = value;
	next = nullptr;
	prev = nullptr;
}