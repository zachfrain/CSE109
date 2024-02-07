#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


namespace linkedlist{
    template <class T>
    class Node{
        public:
            Node(T item);
            ~Node();
            T item;
            Node<T> *next;
    };
}

template <class T>
linkedlist::Node<T>::Node(T item){
    std::cout << "Node constructor" << std::endl;
    this->item = item;
    this->next = NULL;
    std::cout << "Node constructor done" << std::endl;
}

template <class T>
linkedlist::Node<T>::~Node(){
    std::cout << "Node destructor" << std::endl;
    if(this->next != NULL)
        delete this->next;
    std::cout << "Done node destructor" << std::endl;
}
