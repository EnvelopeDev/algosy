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
    ~List();
    List& operator=(const List& other);
    void push_back(T value);
    void push_front(T value);
    void print();
    size_t getSize();
    T at(size_t index)const;
    void removeNode(size_t index);
    void removeByValue(T value);
    void clear();
    bool isEmpty();
    List* sorted();
    void pop_back();
    void pop_front();
    void insert(T value, size_t index);
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
List<T>& List<T>::operator=(const List& other){
    if(this == &other){
        return *this;
    }
    Node* curr = other.head;
    this->clear();
    this->sz = other.sz;
    while(curr!=nullptr){
        this->push_back(curr->value);
        curr=curr->next;
    }
    return *this;
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
void List<T>::push_front(T value){
    Node* newNode = new Node;
    newNode->prev=nullptr;
    newNode->next=nullptr;
    newNode->value=value;
    sz++;
    if(head==nullptr){
        head = newNode;
        return;
    }
    newNode->next=head;
    head = newNode;
}

template<typename T>
void List<T>::pop_back(){
    removeNode(sz-1);
}

template<typename T>
void List<T>::pop_front(){
    removeNode(0);
}

template<typename T>
void List<T>::insert(T value, size_t index){
    if(index >= sz){
        throw std::out_of_range("Index " + std::to_string(index) + " is out of range");
    }
    if(index==0){
        push_front(value);
        return;
    }  
    if(index==sz-1){
        push_back(value);
        return;
    }
    Node* curr = head;
    for(size_t i=0;i<index-1;i++){
        curr=curr->next;
    }
    Node* newNode = new Node;
    newNode->value=value;
    newNode->prev=curr;
    newNode->next=curr->next;
    curr->next->prev = newNode;
    curr->next = newNode;
    sz++;
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
void List<T>::removeNode(size_t index){
    if (index >= sz) {
        throw std::out_of_range("Index " + std::to_string(index) + " is out of range");
    }
    Node* curr = head;
    Node* temp;
    sz--;
    if(index==0){
        temp = head;
        head=head->next;
        if(head != nullptr){
            head->prev=nullptr;
        }
        delete temp;
        return;
    }
    for(size_t i=0;i<index-1;i++){
        curr=curr->next;
    }
    temp = curr->next;
    curr->next = temp->next;
    if(temp->next!=nullptr){
        temp->next->prev = curr;
    }
    delete temp;
}

template<typename T>
void List<T>::removeByValue(T value){
    Node* curr = head;
    for(int i=0;i<sz;i++){
        if(curr->value==value){
            removeNode(i);
            return;
        }
        curr = curr->next;
    }
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
List<T>* List<T>::sorted(){
    int minNum = __INT_MAX__;
    List<T> listCp;
    listCp = *this;
    Node* curr = listCp.head;
    List<T>* sorted = new List<T>;

    while(!listCp.isEmpty()){
        curr = listCp.head;
        minNum=__INT_MAX__;
        while(curr!=nullptr){
            if(curr->value<minNum){
                minNum=curr->value;
            }
            curr=curr->next;
        }
        sorted->push_back(minNum);
        listCp.removeByValue(minNum);
    }
    return sorted;
}