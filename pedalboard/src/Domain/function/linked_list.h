#pragma once

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
	~LinkedList() {
		Node<T>* next = start;
		while (next != NULL) {
			Node<T>* old = next;
			next = next->Next;
			delete old;
		}
	}

	void Add(T data) {
		if (this->last == nullptr) {
			this->last = new Node<T>();
			this->last->Value = data;
			this->start = this->last;
		}
		else {
			Node<T>* next = new Node<T>();
			next->Value = data;			
			this->last->Next = next;
			this->last = next;
		}
	}

	Node<T>* Start() {
		return this->start;
	}
};