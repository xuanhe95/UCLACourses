#ifndef SORTEDDOUBLELINKEDLIST_INCLUDED
#define SORTEDDOUBLELINKEDLIST_INCLUDED
// using ItemType = std::string;
using ItemType = unsigned long;

struct Node {
	Node();
	Node(const ItemType& value);
	ItemType data;
	Node* next;
	Node* prev;
};

class SortedDoubleLinkedList {
public:
	SortedDoubleLinkedList();	//constructor
	~SortedDoubleLinkedList();	//destructor

	SortedDoubleLinkedList(const SortedDoubleLinkedList& other);	//copy constrctor
	void swap(SortedDoubleLinkedList& other);
	SortedDoubleLinkedList& operator=(const SortedDoubleLinkedList& other);

	Node* getHead() const;
	bool get(int pos, ItemType& value) const;
	bool insert(const ItemType& value);
	bool remove(const ItemType& value);
	Node* findNode(const ItemType& value) const;
	bool isEmpty() const;
	int size() const;
	void dump() const;
private:
	Node* m_head;
	int m_size;
};

#endif