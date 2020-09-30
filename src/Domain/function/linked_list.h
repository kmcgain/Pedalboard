#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<class T>
struct Node {
	Node* Next;
	T Value;
};

template<class T>
class LinkedList {
private:
	Node<T>* start;
	Node<T>* last;

public:
	LinkedList();
	~LinkedList();

	void Add(T data);

	Node<T>* Start();
};

#endif