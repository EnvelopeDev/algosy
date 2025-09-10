#pragma once
#include <iostream>
#include <stdexcept> //out_of_range с этим робит

template<typename T>
class List
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;
    };
    Node* head;
    std::size_t sz;
    void freeList();
    Node* getNode(size_t index);
public:
    List();
    List(const T* arr, size_t size);
    ~List();
    void push_back(T value);
    void print();
    size_t getSize();
    T at(size_t index)const;
    void clear();
    bool isEmpty();
    bool contains(const T& value);
    List* substractLists(List** lists, int numLists);
};

//
//Realization of List
//
template<typename T>
List<T>::List(){
    head=nullptr;
    sz=0;
}

template<typename T>
List<T>::~List(){
    freeList();
}

template<typename T>
List<T>::List(const T* arr, size_t size){
    sz=0;
    head=nullptr;
    for(int i=0;i<size;i++){
        this->push_back(arr[i]);
    }
}

template<typename T>
void List<T>::freeList(){
    if(head!=nullptr){
        Node* curr = head;
        Node* temp;
        while(curr!=nullptr){
            temp = curr;
            curr=curr->next;
            delete temp;
        }
    }
}

template<typename T>
void List<T>::push_back(T value){
    Node* newNode = new Node;
    newNode->prev=nullptr;
    newNode->next=nullptr;
    newNode->value=value;
    sz++;
    if(head==nullptr){
        head = newNode;
        return;
    }
    Node* curr = head;
    while(curr->next!=nullptr){
        curr=curr->next;
    }
    curr->next = newNode;
    newNode->prev=curr;
}

template<typename T>
void List<T>::print(){
    if(head==nullptr){
        return;
    }
    Node* curr = head;
    while(curr!=nullptr)
    {
        std::cout << curr->value << ' ';
        curr = curr->next;
    }
    std::cout << '\n';
}

template<typename T>
size_t List<T>::getSize(){
    return sz;
}

template<typename T>
T List<T>::at(size_t index)const{
    return getNode(index)->value;
}

template<typename T>
typename List<T>::Node* List<T>::getNode(size_t index){
    if(index >= sz){
        throw std::out_of_range("Index " + std::to_string(index) + " is out of range");
    }
    Node* curr = head;
    for(size_t i=0; i<index; i++){
        curr=curr->next;
    }
    return curr;
}

template<typename T>
void List<T>::clear(){
    freeList();
    sz=0;
    head=nullptr;
}

template<typename T>
bool List<T>::isEmpty(){
    return !head;
}

template<typename T>
bool List<T>::contains(const T& value){
    if(head==nullptr){
        return false;
    }
    Node* curr = head;
    while(curr!=nullptr){
        if(curr->value == value){
            return true;
        }
        curr=curr->next;
    }
    return false;
}

template<typename T>
List<T>* List<T>::substractLists(List** lists, int numLists){
    Node* curr = this->head;
    Node* currSubSet=nullptr;
    bool flag=true;
    List<T>* res = new List<T>();
    while(curr!=nullptr){
        flag=true;
        for(int i=0;(i<numLists)&&flag;i++){
            Node* currSubSet = (*(lists[i])).head;
            while(currSubSet!=nullptr && flag){
                if(currSubSet->value==curr->value){
                    flag=false;
                }
                currSubSet = currSubSet->next;
            }
        }
        if(flag){
            res->push_back(curr->value);
        }
        curr = curr->next;
    }
    return res;
}