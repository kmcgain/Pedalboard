#include "pch.h"
#include "linked_list.h"

template<class T>
LinkedList<T>::LinkedList() {
    this->start = nullptr;
    this->last = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* next = start;
    while (next != nullptr) {
        Node<T>* old = next;
        next = next->Next;
        delete old;
    }
}

template<class T>
void LinkedList<T>::Add(T data) {	
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

template<class T>
Node<T>* LinkedList<T>::Start() {
    return this->start;
}