#include "llnode.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace linkedlist
{
    template <class T>
    class LinkedList{
        private:
            Node<T> *head;
            Node<T> *tail;
        public:
            size_t length;
            LinkedList();
            ~LinkedList();
            size_t insertAtTail(T item);
            size_t insertAtHead(T item);
            size_t insertAtIndex(size_t index, T item);
            T removeTail();
            T removeHead();
            T removeAtIndex(size_t index);
            T itemAtIndex(size_t index);
            //size_t findItem(T item);
            //void print();
    };
}

template <class T>
linkedlist::LinkedList<T>::LinkedList(){
    std::cout << "List constructor" << std::endl;
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
    std::cout << "List constructor done." << std::endl;
}

template <class T>
linkedlist::LinkedList<T>::~LinkedList(){
    std::cout << "List destructor" << std::endl;
    Node<T>* current = this->head;
    Node<T>* temp;

    while(current != NULL){
        temp = current;
        current = current->next;
        delete temp;
    }
    std::cout << "Done list destructor" << std::endl;
}

template <class T>
size_t linkedlist::LinkedList<T>::insertAtTail(T item){
    Node<T>* node = new Node<T>(item);

    if(this->head == NULL){
        this->head = node;
        this->tail = node;
    } else {
        this->tail->next = node;
        this->tail = this->tail->next;
    }
    this->length = this->length + 1;
    return 0;
}

template <class T>
size_t linkedlist::LinkedList<T>::insertAtHead(T item){
    Node<T>* node = new Node<T>(item);

    if(this->head == NULL){
        this->head = node;
        this->tail = node;
    } else {
        node->next = this->head;
        this->head = node;
    }
    this->length = this->length + 1;
    return 0;
}

template <class T>
size_t linkedlist::LinkedList<T>::insertAtIndex(size_t index, T item){
    Node<T>* node = new Node<T>(item);

    size_t i = 0;
    Node<T>* prev;
    Node<T>* node = this->head;
    while(node != NULL){
        if(i == index){
            prev->next = node;
            node->next = node;
            return 0;
        } else if (i > index){
            return 0;
        } else {
            i++;
            prev = node;
            node = node -> next;
        }
    }
    this->length = this->length + 1;
    return 0;
}

template <class T>
T linkedlist::LinkedList<T>::removeTail(){
    Node<T>* temp;
    size_t i = 0;

    T item;

    if(this->tail == NULL){
        return NULL;
    } else {
        temp = this -> head;

        while(temp -> next != this -> tail){
            temp = temp->next;
        }

        item = this->tail->item;

        Node<T>* oldTail = this->tail;
        this->tail = temp;
        this->tail->next = NULL;
        this->length = this->length - 1;
        delete oldTail;
    }
    return item;
}

template <class T>
T linkedlist::LinkedList<T>::removeHead(){
    T item;

    if(this->head == NULL){
        return NULL;
    } else {
        item = this->head->item;
        Node<T>* oldHead = this->head;
        this->head = this->head->next;
        this->length = this->length - 1;
        delete oldHead;
    }
    return item;
}

template <class T>
T linkedlist::LinkedList<T>::removeAtIndex(size_t index){
    size_t i = 0;

    Node<T>* prev;
    Node<T>* node = list->head;

    while(node != NULL){
        if(i == index){
            prev->next = node->next;
            T item = node->item;
            delete node;
            this->length = this->length - 1;
            return item;
        } else if(i > index){
            return NULL;
        } else {
            i++;
            prev = node;
            node = node->next;
        }
    }
}

template <class T>
T linkedlist::LinkedList<T>::itemAtIndex(size_t index){
    size_t i = 0;
    Node<T>* node = list->head;
    while(node != NULL){
        if(i == index){
            return node->item;
        } else if(i > index){
            return NULL;
        } else {
            i++;
            node = node->next;
        }
    }
}

