#include "linkedlist.h"
#include <iostream>
using namespace std;
using namespace linkedlist;

template <class T>
class HashSet{
    private:
        LinkedList<T>** array;
        size_t size;
        size_t elements;
        unsigned long prehash(T item);
    public:
        HashSet(size_t size);
        ~HashSet();
        unsigned long hash(T item);
        bool insert(T item);
        bool remove(T item);
        bool contains(T item);
        void resize(size_t new_size);
        size_t len();
        size_t capacity();
        void print();
};

template <class T>
HashSet<T>::HashSet(size_t size){
    std::cout << "HashSet constructor" << std::endl;
    this->size = size;
    this->elements = 0;
    this->array = new LinkedList<T>*[size];
    for(int i = 0; i < size; i++){
        this->array[i] = new LinkedList<T>;
    }
    std::cout << "HashSet constructor done." << std::endl;
}

template <class T>
HashSet<T>::~HashSet(){
    std::cout << "HashSet deconstructor" << std::endl;
    for(int i = 0; i < this->size; i++){
        delete this->array[i];
    }
    delete this->array;
    std::cout << "HashSet deconstructor done." << std::endl;
}

